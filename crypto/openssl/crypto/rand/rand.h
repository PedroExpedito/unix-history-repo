/* crypto/rand/rand.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
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
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#ifndef HEADER_RAND_H
# define HEADER_RAND_H

# include <stdlib.h>
# include <openssl/ossl_typ.h>
# include <openssl/e_os2.h>

# if defined(OPENSSL_SYS_WINDOWS)
#  include <windows.h>
# endif

#ifdef  __cplusplus
extern "C" {
#endif

# if defined(OPENSSL_FIPS)
#  define FIPS_RAND_SIZE_T int
# endif

/* Already defined in ossl_typ.h */
/* typedef struct rand_meth_st RAND_METHOD; */

struct rand_meth_st {
    void (*seed) (const void *buf, int num);
    int (*bytes) (unsigned char *buf, int num);
    void (*cleanup) (void);
    void (*add) (const void *buf, int num, double entropy);
    int (*pseudorand) (unsigned char *buf, int num);
    int (*status) (void);
};

# ifdef BN_DEBUG
extern int rand_predictable;
# endif

int RAND_set_rand_method(const RAND_METHOD *meth);
const RAND_METHOD *RAND_get_rand_method(void);
# ifndef OPENSSL_NO_ENGINE
int RAND_set_rand_engine(ENGINE *engine);
# endif
RAND_METHOD *RAND_SSLeay(void);
void RAND_cleanup(void);
int RAND_bytes(unsigned char *buf, int num);
int RAND_pseudo_bytes(unsigned char *buf, int num);
void RAND_seed(const void *buf, int num);
void RAND_add(const void *buf, int num, double entropy);
int RAND_load_file(const char *file, long max_bytes);
int RAND_write_file(const char *file);
const char *RAND_file_name(char *file, size_t num);
int RAND_status(void);
int RAND_query_egd_bytes(const char *path, unsigned char *buf, int bytes);
int RAND_egd(const char *path);
int RAND_egd_bytes(const char *path, int bytes);
int RAND_poll(void);
# ifndef OPENSSL_NO_ENGINE
#  ifdef OPENSSL_FIPS
void int_RAND_init_engine_callbacks(void);
void int_RAND_set_callbacks(int (*set_rand_func) (const RAND_METHOD *meth,
                                                  const RAND_METHOD **pmeth),
                            const RAND_METHOD *(*get_rand_func) (const
                                                                 RAND_METHOD
                                                                 **pmeth));
#  endif
# endif

# if defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_WIN32)

void RAND_screen(void);
int RAND_event(UINT, WPARAM, LPARAM);

# endif

/* BEGIN ERROR CODES */
/*
 * The following lines are auto generated by the script mkerr.pl. Any changes
 * made after this point may be overwritten when the script is next run.
 */
void ERR_load_RAND_strings(void);

/* Error codes for the RAND functions. */

/* Function codes. */
# define RAND_F_ENG_RAND_GET_RAND_METHOD                  108
# define RAND_F_FIPS_RAND                                 103
# define RAND_F_FIPS_RAND_BYTES                           102
# define RAND_F_FIPS_RAND_GET_RAND_METHOD                 109
# define RAND_F_FIPS_RAND_SET_DT                          106
# define RAND_F_FIPS_SET_DT                               104
# define RAND_F_FIPS_SET_PRNG_SEED                        107
# define RAND_F_FIPS_SET_TEST_MODE                        105
# define RAND_F_RAND_GET_RAND_METHOD                      101
# define RAND_F_SSLEAY_RAND_BYTES                         100

/* Reason codes. */
# define RAND_R_NON_FIPS_METHOD                           105
# define RAND_R_NOT_IN_TEST_MODE                          106
# define RAND_R_NO_KEY_SET                                107
# define RAND_R_PRNG_ASKING_FOR_TOO_MUCH                  101
# define RAND_R_PRNG_ERROR                                108
# define RAND_R_PRNG_KEYED                                109
# define RAND_R_PRNG_NOT_REKEYED                          102
# define RAND_R_PRNG_NOT_RESEEDED                         103
# define RAND_R_PRNG_NOT_SEEDED                           100
# define RAND_R_PRNG_SEED_MUST_NOT_MATCH_KEY              110
# define RAND_R_PRNG_STUCK                                104

#ifdef  __cplusplus
}
#endif
#endif
