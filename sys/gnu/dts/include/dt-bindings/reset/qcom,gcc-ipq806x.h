/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#ifndef _DT_BINDINGS_RESET_IPQ_806X_H
#define _DT_BINDINGS_RESET_IPQ_806X_H

#define QDSS_STM_RESET					0
#define AFAB_SMPSS_S_RESET				1
#define AFAB_SMPSS_M1_RESET				2
#define AFAB_SMPSS_M0_RESET				3
#define AFAB_EBI1_CH0_RESET				4
#define AFAB_EBI1_CH1_RESET				5
#define SFAB_ADM0_M0_RESET				6
#define SFAB_ADM0_M1_RESET				7
#define SFAB_ADM0_M2_RESET				8
#define ADM0_C2_RESET					9
#define ADM0_C1_RESET					10
#define ADM0_C0_RESET					11
#define ADM0_PBUS_RESET					12
#define ADM0_RESET					13
#define QDSS_CLKS_SW_RESET				14
#define QDSS_POR_RESET					15
#define QDSS_TSCTR_RESET				16
#define QDSS_HRESET_RESET				17
#define QDSS_AXI_RESET					18
#define QDSS_DBG_RESET					19
#define SFAB_PCIE_M_RESET				20
#define SFAB_PCIE_S_RESET				21
#define PCIE_EXT_RESET					22
#define PCIE_PHY_RESET					23
#define PCIE_PCI_RESET					24
#define PCIE_POR_RESET					25
#define PCIE_HCLK_RESET					26
#define PCIE_ACLK_RESET					27
#define SFAB_LPASS_RESET				28
#define SFAB_AFAB_M_RESET				29
#define AFAB_SFAB_M0_RESET				30
#define AFAB_SFAB_M1_RESET				31
#define SFAB_SATA_S_RESET				32
#define SFAB_DFAB_M_RESET				33
#define DFAB_SFAB_M_RESET				34
#define DFAB_SWAY0_RESET				35
#define DFAB_SWAY1_RESET				36
#define DFAB_ARB0_RESET					37
#define DFAB_ARB1_RESET					38
#define PPSS_PROC_RESET					39
#define PPSS_RESET					40
#define DMA_BAM_RESET					41
#define SPS_TIC_H_RESET					42
#define SFAB_CFPB_M_RESET				43
#define SFAB_CFPB_S_RESET				44
#define TSIF_H_RESET					45
#define CE1_H_RESET					46
#define CE1_CORE_RESET					47
#define CE1_SLEEP_RESET					48
#define CE2_H_RESET					49
#define CE2_CORE_RESET					50
#define SFAB_SFPB_M_RESET				51
#define SFAB_SFPB_S_RESET				52
#define RPM_PROC_RESET					53
#define PMIC_SSBI2_RESET				54
#define SDC1_RESET					55
#define SDC2_RESET					56
#define SDC3_RESET					57
#define SDC4_RESET					58
#define USB_HS1_RESET					59
#define USB_HSIC_RESET					60
#define USB_FS1_XCVR_RESET				61
#define USB_FS1_RESET					62
#define GSBI1_RESET					63
#define GSBI2_RESET					64
#define GSBI3_RESET					65
#define GSBI4_RESET					66
#define GSBI5_RESET					67
#define GSBI6_RESET					68
#define GSBI7_RESET					69
#define SPDM_RESET					70
#define SEC_CTRL_RESET					71
#define TLMM_H_RESET					72
#define SFAB_SATA_M_RESET				73
#define SATA_RESET					74
#define TSSC_RESET					75
#define PDM_RESET					76
#define MPM_H_RESET					77
#define MPM_RESET					78
#define SFAB_SMPSS_S_RESET				79
#define PRNG_RESET					80
#define SFAB_CE3_M_RESET				81
#define SFAB_CE3_S_RESET				82
#define CE3_SLEEP_RESET					83
#define PCIE_1_M_RESET					84
#define PCIE_1_S_RESET					85
#define PCIE_1_EXT_RESET				86
#define PCIE_1_PHY_RESET				87
#define PCIE_1_PCI_RESET				88
#define PCIE_1_POR_RESET				89
#define PCIE_1_HCLK_RESET				90
#define PCIE_1_ACLK_RESET				91
#define PCIE_2_M_RESET					92
#define PCIE_2_S_RESET					93
#define PCIE_2_EXT_RESET				94
#define PCIE_2_PHY_RESET				95
#define PCIE_2_PCI_RESET				96
#define PCIE_2_POR_RESET				97
#define PCIE_2_HCLK_RESET				98
#define PCIE_2_ACLK_RESET				99
#define SFAB_USB30_S_RESET				100
#define SFAB_USB30_M_RESET				101
#define USB30_0_PORT2_HS_PHY_RESET			102
#define USB30_0_MASTER_RESET				103
#define USB30_0_SLEEP_RESET				104
#define USB30_0_UTMI_PHY_RESET				105
#define USB30_0_POWERON_RESET				106
#define USB30_0_PHY_RESET				107
#define USB30_1_MASTER_RESET				108
#define USB30_1_SLEEP_RESET				109
#define USB30_1_UTMI_PHY_RESET				110
#define USB30_1_POWERON_RESET				111
#define USB30_1_PHY_RESET				112
#define NSSFB0_RESET					113
#define NSSFB1_RESET					114
#define UBI32_CORE1_CLKRST_CLAMP_RESET			115
#define UBI32_CORE1_CLAMP_RESET				116
#define UBI32_CORE1_AHB_RESET				117
#define UBI32_CORE1_AXI_RESET				118
#define UBI32_CORE2_CLKRST_CLAMP_RESET			119
#define UBI32_CORE2_CLAMP_RESET				120
#define UBI32_CORE2_AHB_RESET				121
#define UBI32_CORE2_AXI_RESET				122
#define GMAC_CORE1_RESET				123
#define GMAC_CORE2_RESET				124
#define GMAC_CORE3_RESET				125
#define GMAC_CORE4_RESET				126
#define GMAC_AHB_RESET					127
#define NSS_CH0_RST_RX_CLK_N_RESET			128
#define NSS_CH0_RST_TX_CLK_N_RESET			129
#define NSS_CH0_RST_RX_125M_N_RESET			130
#define NSS_CH0_HW_RST_RX_125M_N_RESET			131
#define NSS_CH0_RST_TX_125M_N_RESET			132
#define NSS_CH1_RST_RX_CLK_N_RESET			133
#define NSS_CH1_RST_TX_CLK_N_RESET			134
#define NSS_CH1_RST_RX_125M_N_RESET			135
#define NSS_CH1_HW_RST_RX_125M_N_RESET			136
#define NSS_CH1_RST_TX_125M_N_RESET			137
#define NSS_CH2_RST_RX_CLK_N_RESET			138
#define NSS_CH2_RST_TX_CLK_N_RESET			139
#define NSS_CH2_RST_RX_125M_N_RESET			140
#define NSS_CH2_HW_RST_RX_125M_N_RESET			141
#define NSS_CH2_RST_TX_125M_N_RESET			142
#define NSS_CH3_RST_RX_CLK_N_RESET			143
#define NSS_CH3_RST_TX_CLK_N_RESET			144
#define NSS_CH3_RST_RX_125M_N_RESET			145
#define NSS_CH3_HW_RST_RX_125M_N_RESET			146
#define NSS_CH3_RST_TX_125M_N_RESET			147
#define NSS_RST_RX_250M_125M_N_RESET			148
#define NSS_RST_TX_250M_125M_N_RESET			149
#define NSS_QSGMII_TXPI_RST_N_RESET			150
#define NSS_QSGMII_CDR_RST_N_RESET			151
#define NSS_SGMII2_CDR_RST_N_RESET			152
#define NSS_SGMII3_CDR_RST_N_RESET			153
#define NSS_CAL_PRBS_RST_N_RESET			154
#define NSS_LCKDT_RST_N_RESET				155
#define NSS_SRDS_N_RESET				156

#endif
