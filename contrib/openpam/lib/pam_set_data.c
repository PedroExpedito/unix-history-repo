/*-
 * Copyright (c) 2002 Networks Associates Technology, Inc.
 * All rights reserved.
 *
 * This software was developed for the FreeBSD Project by ThinkSec AS and
 * NAI Labs, the Security Research Division of Network Associates, Inc.
 * under DARPA/SPAWAR contract N66001-01-C-8035 ("CBOSS"), as part of the
 * DARPA CHATS research program.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $P4: //depot/projects/openpam/lib/pam_set_data.c#8 $
 */

#include <stdlib.h>
#include <string.h>

#include <security/pam_appl.h>

#include "openpam_impl.h"

/*
 * XSSO 4.2.1
 * XSSO 6 page 59
 *
 * Set module information
 */

int
pam_set_data(pam_handle_t *pamh,
	const char *module_data_name,
	void *data,
	void (*cleanup)(pam_handle_t *pamh,
		void *data,
		int pam_end_status))
{
	pam_data_t *dp;

	if (pamh == NULL)
		return (PAM_SYSTEM_ERR);

	for (dp = pamh->module_data; dp != NULL; dp = dp->next) {
		if (strcmp(dp->name, module_data_name) == 0) {
			if (dp->cleanup)
				(dp->cleanup)(pamh, dp->data, PAM_SUCCESS);
			dp->data = data;
			dp->cleanup = cleanup;
			return (PAM_SUCCESS);
		}
	}

	if ((dp = malloc(sizeof *dp)) == NULL)
		return (PAM_BUF_ERR);
	if ((dp->name = strdup(module_data_name)) == NULL) {
		free(data);
		return (PAM_BUF_ERR);
	}
	dp->next = pamh->module_data;
	pamh->module_data = data;
	return (PAM_SUCCESS);
}

/*
 * Error codes:
 *
 *	PAM_SYSTEM_ERR
 *	PAM_BUF_ERR
 */

/**
 * The =pam_set_data function associates a pointer to an opaque object
 * with an arbitrary string specified by the =module_data_name argument,
 * in the PAM context specified by the =pamh argument.
 *
 * If not =NULL, the =cleanup argument should point to a function
 * responsible for releasing the resources associated with the object.
 *
 * This function and its counterpart =pam_get_data are useful for managing
 * data that are meaningful only to a particular service module.
 */
