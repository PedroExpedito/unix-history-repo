/*-
 * Copyright (c) 2010 Andreas Tobler
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/bus.h>
#include <sys/systm.h>
#include <sys/module.h>
#include <sys/callout.h>
#include <sys/conf.h>
#include <sys/cpu.h>
#include <sys/ctype.h>
#include <sys/kernel.h>
#include <sys/reboot.h>
#include <sys/rman.h>
#include <sys/sysctl.h>
#include <sys/limits.h>

#include <machine/bus.h>
#include <machine/md_var.h>

#include <dev/iicbus/iicbus.h>
#include <dev/iicbus/iiconf.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/ofw_bus.h>
#include <powerpc/powermac/powermac_thermal.h>

#define FCU_ZERO_C_TO_K     2732

/* CPU A/B sensors, temp and adc: AD7417. */

#define AD7417_TEMP         0x00
#define AD7417_CONFIG       0x01
#define AD7417_ADC          0x04
#define AD7417_CONFIG2      0x05
#define AD7417_CONFMASK     0xe0

uint8_t adc741x_config;

struct ad7417_sensor {
	struct	pmac_therm therm;
	device_t dev;
	int     id;
	enum {
		ADC7417_TEMP_SENSOR,
		ADC7417_ADC_SENSOR
	} type;
};

/* Regular bus attachment functions */
static int ad7417_probe(device_t);
static int ad7417_attach(device_t);

/* Utility functions */
static int ad7417_sensor_sysctl(SYSCTL_HANDLER_ARGS);
static int ad7417_write(device_t dev, uint32_t addr, uint8_t reg,
			uint8_t *buf, int len);
static int ad7417_read_1(device_t dev, uint32_t addr, uint8_t reg,
			 uint8_t *data);
static int ad7417_read_2(device_t dev, uint32_t addr, uint8_t reg,
			 uint16_t *data);
static int ad7417_diode_read(struct ad7417_sensor *sens);
static int ad7417_adc_read(struct ad7417_sensor *sens);
static int ad7417_sensor_read(struct ad7417_sensor *sens);

struct ad7417_softc {
	device_t		sc_dev;
	uint32_t                sc_addr;
	struct ad7417_sensor    *sc_sensors;
	int                     sc_nsensors;
};
static device_method_t  ad7417_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		ad7417_probe),
	DEVMETHOD(device_attach,	ad7417_attach),
	{ 0, 0 },
};

static driver_t ad7417_driver = {
	"ad7417",
	ad7417_methods,
	sizeof(struct ad7417_softc)
};

static devclass_t ad7417_devclass;

DRIVER_MODULE(ad7417, iicbus, ad7417_driver, ad7417_devclass, 0, 0);
MALLOC_DEFINE(M_AD7417, "ad7417", "Supply-Monitor AD7417");


static int
ad7417_write(device_t dev, uint32_t addr, uint8_t reg, uint8_t *buff, int len)
{
	unsigned char buf[4];
	struct iic_msg msg[] = {
		{ addr, IIC_M_WR, 0, buf }
	};

	msg[0].len = len + 1;
	buf[0] = reg;
	memcpy(buf + 1, buff, len);

	if (iicbus_transfer(dev, msg, 1) != 0) {
		device_printf(dev, "iicbus write failed\n");
		return (EIO);
	}

	return (0);

}

static int
ad7417_read_1(device_t dev, uint32_t addr, uint8_t reg, uint8_t *data)
{
	uint8_t buf[4];

	struct iic_msg msg[2] = {
	    { addr, IIC_M_WR | IIC_M_NOSTOP, 1, &reg },
	    { addr, IIC_M_RD, 1, buf },
	};

	if (iicbus_transfer(dev, msg, 2) != 0) {
		device_printf(dev, "iicbus read failed\n");
		return (EIO);
	}

	*data = *((uint8_t*)buf);

	return (0);
}

static int
ad7417_read_2(device_t dev, uint32_t addr, uint8_t reg, uint16_t *data)
{
	uint8_t buf[4];

	struct iic_msg msg[2] = {
	    { addr, IIC_M_WR | IIC_M_NOSTOP, 1, &reg },
	    { addr, IIC_M_RD, 2, buf },
	};

	if (iicbus_transfer(dev, msg, 2) != 0) {
		device_printf(dev, "iicbus read failed\n");
		return (EIO);
	}

	*data = *((uint16_t*)buf);

	return (0);
}

static int
ad7417_init_adc(device_t dev, uint32_t addr)
{
	uint8_t buf;

	adc741x_config = 0;
	/* Clear Config2 */
	buf = 0;
	ad7417_write(dev, addr, AD7417_CONFIG2, &buf, 1);

	 /* Read & cache Config1 */
	buf = 0;
	ad7417_write(dev, addr, AD7417_CONFIG, &buf, 1);

	ad7417_read_1(dev, addr, AD7417_CONFIG, &buf);
	adc741x_config = (uint8_t)buf;

	/* Disable shutdown mode */
	adc741x_config &= 0xfe;
	buf = adc741x_config;
	ad7417_write(dev, addr, AD7417_CONFIG, &buf, 1);

	return (0);

}
static int
ad7417_probe(device_t dev)
{
	const char  *name, *compatible;
	struct ad7417_softc *sc;

	name = ofw_bus_get_name(dev);
	compatible = ofw_bus_get_compat(dev);

	if (!name)
		return (ENXIO);

	if (strcmp(name, "supply-monitor") != 0 ||
	    strcmp(compatible, "ad7417") != 0)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_addr = iicbus_get_addr(dev);

	device_set_desc(dev, "Supply-Monitor AD7417");

	return (0);
}

/*
 * This function returns the number of sensors. If we call it the second time
 * and we have allocated memory for sc->sc_sensors, we fill in the properties.
 */
static int
ad7417_fill_sensor_prop(device_t dev)
{
	phandle_t child;
	struct ad7417_softc *sc;
	u_int id[10];
	char location[96];
	char type[32];
	int i = 0, j, len = 0, prop_len, prev_len = 0;

	sc = device_get_softc(dev);

	child = ofw_bus_get_node(dev);

	/* Fill the sensor location property. */
	prop_len = OF_getprop(child, "hwsensor-location", location,
			      sizeof(location));
	while (len < prop_len) {
		if (sc->sc_sensors != NULL)
			strcpy(sc->sc_sensors[i].therm.name, location + len);
		prev_len = strlen(location + len) + 1;
		len += prev_len;
		i++;
	}
	if (sc->sc_sensors == NULL)
		return (i);

	/* Fill the sensor type property. */
	len = 0;
	i = 0;
	prev_len = 0;
	prop_len = OF_getprop(child, "hwsensor-type", type, sizeof(type));
	while (len < prop_len) {
		if (strcmp(type + len, "temperature") == 0)
			sc->sc_sensors[i].type = ADC7417_TEMP_SENSOR;
		else
			sc->sc_sensors[i].type = ADC7417_ADC_SENSOR;
		prev_len = strlen(type + len) + 1;
		len += prev_len;
		i++;
	}

	/* Fill the sensor id property. Taken from OF. */
	prop_len = OF_getprop(child, "hwsensor-id", id, sizeof(id));
	for (j = 0; j < i; j++)
		sc->sc_sensors[j].id = id[j];

	/* Fill the sensor zone property. Taken from OF. */
	prop_len = OF_getprop(child, "hwsensor-zone", id, sizeof(id));
	for (j = 0; j < i; j++)
		sc->sc_sensors[j].therm.zone = id[j];

	/* Finish setting up sensor properties */
	for (j = 0; j < i; j++) {
		sc->sc_sensors[j].dev = dev;
	
		/* HACK: Apple wired a random diode to the ADC line */
		if (strstr(sc->sc_sensors[j].therm.name, "DIODE TEMP")
		    != NULL) {
			sc->sc_sensors[j].type = ADC7417_TEMP_SENSOR;
			sc->sc_sensors[j].therm.read =
			    (int (*)(struct pmac_therm *))(ad7417_diode_read);
		} else {
			sc->sc_sensors[j].therm.read =
			    (int (*)(struct pmac_therm *))(ad7417_sensor_read);
		}
			
		if (sc->sc_sensors[j].type != ADC7417_TEMP_SENSOR)
			continue;

		/* Make up some ranges */
		sc->sc_sensors[j].therm.target_temp = 500 + 2732;
		sc->sc_sensors[j].therm.max_temp = 900 + 2732;
		
		pmac_thermal_sensor_register(&sc->sc_sensors[j].therm);
	}

	return (i);
}

static int
ad7417_attach(device_t dev)
{
	struct ad7417_softc *sc;
	struct sysctl_oid *oid, *sensroot_oid;
	struct sysctl_ctx_list *ctx;
	char sysctl_name[32];
	int i, j;
	const char *unit;
	const char *desc;

	sc = device_get_softc(dev);

	sc->sc_nsensors = 0;

	/* Count the actual number of sensors. */
	sc->sc_nsensors = ad7417_fill_sensor_prop(dev);

	device_printf(dev, "%d sensors detected.\n", sc->sc_nsensors);

	if (sc->sc_nsensors == 0)
		device_printf(dev, "WARNING: No AD7417 sensors detected!\n");

	sc->sc_sensors = malloc (sc->sc_nsensors * sizeof(struct ad7417_sensor),
				 M_AD7417, M_WAITOK | M_ZERO);

	ctx = device_get_sysctl_ctx(dev);
	sensroot_oid = SYSCTL_ADD_NODE(ctx,
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)), OID_AUTO, "sensor",
	    CTLFLAG_RD, 0, "AD7417 Sensor Information");

	/* Now we can fill the properties into the allocated struct. */
	sc->sc_nsensors = ad7417_fill_sensor_prop(dev);

	/* Add sysctls for the sensors. */
	for (i = 0; i < sc->sc_nsensors; i++) {
		for (j = 0; j < strlen(sc->sc_sensors[i].therm.name); j++) {
			sysctl_name[j] =
			    tolower(sc->sc_sensors[i].therm.name[j]);
			if (isspace(sysctl_name[j]))
				sysctl_name[j] = '_';
		}
		sysctl_name[j] = 0;

		oid = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(sensroot_oid),
				      OID_AUTO,
				      sysctl_name, CTLFLAG_RD, 0,
				      "Sensor Information");

		if (sc->sc_sensors[i].type == ADC7417_TEMP_SENSOR) {
			unit = "temp";
			desc = "Sensor temp in C";
		} else {
			unit = "volt";
			desc = "Sensor Volt in V";
		}
		/* I use i to pass the sensor id. */
		SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(oid), OID_AUTO,
				unit, CTLTYPE_INT | CTLFLAG_RD, dev,
				i, ad7417_sensor_sysctl,
				sc->sc_sensors[i].type == ADC7417_TEMP_SENSOR ?
				"IK" : "I", desc);
	}
	/* Dump sensor location, ID & type. */
	if (bootverbose) {
		device_printf(dev, "Sensors\n");
		for (i = 0; i < sc->sc_nsensors; i++) {
			device_printf(dev, "Location: %s ID: %d type: %d\n",
				      sc->sc_sensors[i].therm.name,
				      sc->sc_sensors[i].id,
				      sc->sc_sensors[i].type);
		}
	}

	return (0);
}

static int
ad7417_get_temp(device_t dev, uint32_t addr, int *temp)
{
	uint16_t buf[2];
	uint16_t read;

	ad7417_read_2(dev, addr, AD7417_TEMP, buf);
	read = *((int16_t*)buf);

	/* The ADC is 10 bit, the resolution is 0.25 C.
	   The temperature is in tenth kelvin.
	*/
	*temp = (((int16_t)(read & 0xffc0)) >> 6) * 25 / 10;
	return (0);
}

static int
ad7417_get_adc(device_t dev, uint32_t addr, unsigned int *value,
	       uint8_t chan)
{
	uint8_t cfg1, tmp;
	uint16_t read, buf[2];

	ad7417_read_1(dev, addr, AD7417_CONFIG, &cfg1);

	tmp = chan << 5;

	cfg1 = (cfg1 & ~AD7417_CONFMASK) | (tmp & AD7417_CONFMASK);

	ad7417_write(dev, addr, AD7417_CONFIG, &cfg1, 1);

	ad7417_read_2(dev, addr, AD7417_ADC, buf);

	read = *((uint16_t*)buf);

	*value = ((uint32_t)read) >> 6;

	return (0);
}

static int
ad7417_diode_read(struct ad7417_sensor *sens)
{
	static int eeprom_read = 0;
	static cell_t eeprom[2][40];
	phandle_t eeprom_node;
	int rawval, diode_slope, diode_offset;
	int temp;

	if (!eeprom_read) {
		eeprom_node = OF_finddevice("/u3/i2c/cpuid@a0");
		OF_getprop(eeprom_node, "cpuid", eeprom[0], sizeof(eeprom[0]));
		eeprom_node = OF_finddevice("/u3/i2c/cpuid@a2");
		OF_getprop(eeprom_node, "cpuid", eeprom[1], sizeof(eeprom[1]));
		eeprom_read = 1;
	}

	rawval = ad7417_adc_read(sens);
	if (strstr(sens->therm.name, "CPU B") != NULL) {
		diode_slope = eeprom[1][0x11] >> 16;
		diode_offset = (int16_t)(eeprom[1][0x11] & 0xffff) << 12;
	} else {
		diode_slope = eeprom[0][0x11] >> 16;
		diode_offset = (int16_t)(eeprom[0][0x11] & 0xffff) << 12;
	}

	temp = (rawval*diode_slope + diode_offset) >> 2;
	temp = (10*(temp >> 16)) + ((10*(temp & 0xffff)) >> 16);
	
	return (temp + FCU_ZERO_C_TO_K);
}

static int
ad7417_adc_read(struct ad7417_sensor *sens)
{
	struct ad7417_softc *sc;
	uint8_t chan;
	int temp;

	sc = device_get_softc(sens->dev);

	switch (sens->id) {
	case 11:
	case 16:
		chan = 1;
		break;
	case 12:
	case 17:
		chan = 2;
		break;
	case 13:
	case 18:
		chan = 3;
		break;
	case 14:
	case 19:
		chan = 4;
		break;
	default:
		chan = 1;
	}

	ad7417_get_adc(sc->sc_dev, sc->sc_addr, &temp, chan);

	return (temp);
}


static int
ad7417_sensor_read(struct ad7417_sensor *sens)
{
	struct ad7417_softc *sc;
	int temp;

	sc = device_get_softc(sens->dev);

	/* Init the ADC. */
	ad7417_init_adc(sc->sc_dev, sc->sc_addr);

	if (sens->type == ADC7417_TEMP_SENSOR) {
		ad7417_get_temp(sc->sc_dev, sc->sc_addr, &temp);
		temp += FCU_ZERO_C_TO_K;
	} else {
		temp = ad7417_adc_read(sens);
	}
	return (temp);
}

static int
ad7417_sensor_sysctl(SYSCTL_HANDLER_ARGS)
{
	device_t dev;
	struct ad7417_softc *sc;
	struct ad7417_sensor *sens;
	int value = 0;
	int error;

	dev = arg1;
	sc = device_get_softc(dev);
	sens = &sc->sc_sensors[arg2];

	value = sens->therm.read(&sens->therm);
	if (value < 0)
		return (ENXIO);

	error = sysctl_handle_int(oidp, &value, 0, req);

	return (error);
}
