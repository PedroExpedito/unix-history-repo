/* A lexical scanner generated by flex */

/* scanner skeleton version:
 * $Header: /pub/FreeBSD/FreeBSD-CVS/src/gnu/usr.bin/bc/scan.c,v 1.2 1995/05/30 04:49:02 rgrimes Exp $
 */

#define FLEX_SCANNER

#include <stdio.h>


/* cfront 1.2 defines "c_plusplus" instead of "__cplusplus" */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif


#ifdef __cplusplus

#include <stdlib.h>
#include <osfcn.h>

/* use prototypes in function declarations */
#define YY_USE_PROTOS

/* the "const" storage-class-modifier is valid */
#define YY_USE_CONST

#else	/* ! __cplusplus */

#ifdef __STDC__

#ifdef __GNUC__
#include <stddef.h>
void *malloc( size_t );
void free( void* );
#else
#include <stdlib.h>
#endif	/* __GNUC__ */

#define YY_USE_PROTOS
#define YY_USE_CONST

#endif	/* __STDC__ */
#endif	/* ! __cplusplus */


#ifdef __TURBOC__
#define YY_USE_CONST
#endif


#ifndef YY_USE_CONST
#define const
#endif


#ifdef YY_USE_PROTOS
#define YY_PROTO(proto) proto
#else
#define YY_PROTO(proto) ()
/* we can't get here if it's an ANSI C compiler, or a C++ compiler,
 * so it's got to be a K&R compiler, and therefore there's no standard
 * place from which to include these definitions
 */
/* char *malloc();
int free(); */
int read();
#endif


/* amount of stuff to slurp up with each read */
#ifndef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE 8192
#endif

/* returned upon end-of-file */
#define YY_END_TOK 0

/* copy whatever the last rule matched to the standard output */

/* cast to (char *) is because for 8-bit chars, yytext is (unsigned char *) */
/* this used to be an fputs(), but since the string might contain NUL's,
 * we now use fwrite()
 */
#define ECHO (void) fwrite( (char *) yytext, yyleng, 1, yyout )

/* gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
 * is returned in "result".
 */
#define YY_INPUT(buf,result,max_size) \
	if ( (result = read( fileno(yyin), (char *) buf, max_size )) < 0 ) \
	    YY_FATAL_ERROR( "read() in flex scanner failed" );
#define YY_NULL 0

/* no semi-colon after return; correct usage is to write "yyterminate();" -
 * we don't want an extra ';' after the "return" because that will cause
 * some compilers to complain about unreachable statements.
 */
#define yyterminate() return ( YY_NULL )

/* report a fatal error */

/* The funky do-while is used to turn this macro definition into
 * a single C statement (which needs a semi-colon terminator).
 * This avoids problems with code like:
 *
 * 	if ( something_happens )
 *		YY_FATAL_ERROR( "oops, the something happened" );
 *	else
 *		everything_okay();
 *
 * Prior to using the do-while the compiler would get upset at the
 * "else" because it interpreted the "if" statement as being all
 * done when it reached the ';' after the YY_FATAL_ERROR() call.
 */

#define YY_FATAL_ERROR(msg) \
	do \
		{ \
		(void) fputs( msg, stderr ); \
		(void) putc( '\n', stderr ); \
		exit( 1 ); \
		} \
	while ( 0 )

/* default yywrap function - always treat EOF as an EOF */
#define yywrap() 1

/* enter a start condition.  This macro really ought to take a parameter,
 * but we do it the disgusting crufty way forced on us by the ()-less
 * definition of BEGIN
 */
#define BEGIN yy_start = 1 + 2 *

/* action number for EOF rule of a given start state */
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)

/* special action meaning "start processing a new file" */
#define YY_NEW_FILE \
	do \
		{ \
		yy_init_buffer( yy_current_buffer, yyin ); \
		yy_load_buffer_state(); \
		} \
	while ( 0 )

/* default declaration of generated scanner - a define so the user can
 * easily add parameters
 */
#define YY_DECL int yylex YY_PROTO(( void ))

/* code executed at the end of each rule */
#define YY_BREAK break;

#define YY_END_OF_BUFFER_CHAR 0

#ifndef YY_BUF_SIZE
#define YY_BUF_SIZE (YY_READ_BUF_SIZE * 2) /* size of default input buffer */
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;

#define YY_CHAR unsigned char
# line 1 "scan.l"
#define INITIAL 0
# line 2 "scan.l"
/* scan.l: the (f)lex description file for the scanner. */

/*  This file is part of bc written for MINIX.
    Copyright (C) 1991, 1992 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License , or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; see the file COPYING.  If not, write to
    the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

    You may contact the author by:
       e-mail:  phil@cs.wwu.edu
      us-mail:  Philip A. Nelson
                Computer Science Department, 9062
                Western Washington University
                Bellingham, WA 98226-9062

*************************************************************************/

#include "bcdefs.h"
#include "y.tab.h"
#include "global.h"
#include "proto.h"

/* Using flex, we can ask for a smaller input buffer.  With lex, this
   does nothing! */

#ifdef SMALL_BUF
#undef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE 512
#endif

/* We want to define our own yywrap. */
#undef yywrap
_PROTOTYPE(int yywrap, (void));

/* MINIX returns from read with < 0 if SIGINT is  encountered.
   In flex, we can redefine YY_INPUT to the following.  In lex, this
   does nothing! */
#include <errno.h>
#undef  YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	while ( (result = read( fileno(yyin), (char *) buf, max_size )) < 0 ) \
	    if (errno != EINTR) \
		YY_FATAL_ERROR( "read() in flex scanner failed" );

# line 60 "scan.l"

/* done after the current pattern has been matched and before the
 * corresponding action - sets up yytext
 */
#define YY_DO_BEFORE_ACTION \
	yytext = yy_bp; \
	yyleng = yy_cp - yy_bp; \
	yy_hold_char = *yy_cp; \
	*yy_cp = '\0'; \
	yy_c_buf_p = yy_cp;

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

/* return all but the first 'n' matched characters back to the input stream */
#define yyless(n) \
	do \
		{ \
		/* undo effects of setting up yytext */ \
		*yy_cp = yy_hold_char; \
		yy_c_buf_p = yy_cp = yy_bp + n; \
		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
		} \
	while ( 0 )

#define unput(c) yyunput( c, yytext )


struct yy_buffer_state
    {
    FILE *yy_input_file;

    YY_CHAR *yy_ch_buf;		/* input buffer */
    YY_CHAR *yy_buf_pos;	/* current position in input buffer */

    /* size of input buffer in bytes, not including room for EOB characters*/
    int yy_buf_size;

    /* number of characters read into yy_ch_buf, not including EOB characters */
    int yy_n_chars;

    int yy_eof_status;		/* whether we've seen an EOF on this buffer */
#define EOF_NOT_SEEN 0
    /* "pending" happens when the EOF has been seen but there's still
     * some text process
     */
#define EOF_PENDING 1
#define EOF_DONE 2
    };

static YY_BUFFER_STATE yy_current_buffer;

/* we provide macros for accessing buffer states in case in the
 * future we want to put the buffer states in a more general
 * "scanner state"
 */
#define YY_CURRENT_BUFFER yy_current_buffer


/* yy_hold_char holds the character lost when yytext is formed */
static YY_CHAR yy_hold_char;

static int yy_n_chars;		/* number of characters read into yy_ch_buf */



#ifndef YY_USER_ACTION
#define YY_USER_ACTION
#endif

#ifndef YY_USER_INIT
#define YY_USER_INIT
#endif

extern YY_CHAR *yytext;
extern int yyleng;
extern FILE *yyin, *yyout;

YY_CHAR *yytext;
int yyleng;

FILE *yyin = (FILE *) 0, *yyout = (FILE *) 0;

#define YY_END_OF_BUFFER 40
typedef int yy_state_type;
static const short int yy_accept[144] =
    {   0,
        0,    0,   40,   38,   33,   31,   25,   38,   26,   38,
       22,   26,   22,   22,   38,   26,   37,   29,   27,   29,
       38,   22,   35,   35,   35,   35,   35,   35,   35,   35,
       35,   35,   35,   35,   35,   35,   35,   35,   38,   33,
       29,    0,   36,   27,   23,   30,   37,    0,   34,   37,
       37,    0,   28,   32,   35,   35,   35,   35,   35,   35,
       35,   35,   35,    7,   35,   35,   35,   35,   35,   35,
       35,   35,   35,   35,   35,   24,   37,    0,    0,   37,
        0,   35,   35,   35,   35,   35,    6,   35,   35,   35,
       35,   35,   35,   35,   35,   35,   35,   35,   35,   35,

       35,   13,   35,   35,   35,   14,   16,   35,   17,   35,
       35,   35,   35,    3,   15,   35,   35,    9,   35,   35,
        2,   35,   35,   11,   35,   35,   12,   20,   35,   10,
       35,    8,   35,    1,    4,   21,    5,   35,   35,   35,
       19,   18,    0
    } ;

static const YY_CHAR yy_ec[256] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    2,    4,    5,    1,    1,    6,    7,    1,    8,
        9,   10,   11,   12,   13,   14,   15,   16,   16,   16,
       16,   16,   16,   16,   16,   16,   16,    1,   17,   18,
       19,   20,    1,    1,   21,   21,   21,   21,   21,   21,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
       22,   23,   24,   25,   26,    1,   27,   28,   29,   30,

       31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
       41,   42,   43,   44,   45,   46,   47,   36,   48,   36,
       49,   36,   50,   51,   52,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,

        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1
    } ;

static const YY_CHAR yy_meta[53] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    2,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    2,    2,    2,    2,    2,
        2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
        2,    2,    2,    2,    2,    2,    2,    2,    2,    1,
        1,    1
    } ;

static const short int yy_base[146] =
    {   0,
        0,    0,  193,  194,  190,  194,  172,  185,  170,  181,
      194,  168,   42,   41,   41,   46,   52,  167,   61,  166,
      181,  164,  135,  137,  139,  148,  140,  136,    0,  149,
       27,   50,  147,  130,  126,  141,   40,   36,  120,  168,
      194,  164,  194,  194,  194,  194,   66,  165,  194,   72,
       76,  164,  194,  194,    0,  120,  134,  124,  131,  117,
      117,  122,  132,    0,  113,  117,  117,  128,  119,  118,
       52,  125,  107,  106,  114,  194,   80,  145,   84,   88,
      144,  105,  118,   98,  108,  111,    0,   95,   95,   93,
      105,  102,   91,   95,   88,  103,   85,   93,   84,   85,

       90,    0,   90,   91,   85,    0,    0,   93,    0,   77,
       76,   90,   74,    0,    0,   75,   87,    0,   90,   85,
        0,   75,   83,    0,   76,   63,    0,    0,   66,    0,
       62,    0,   47,    0,    0,    0,    0,   45,   53,   29,
        0,    0,  194,  111,   56
    } ;

static const short int yy_def[146] =
    {   0,
      143,    1,  143,  143,  143,  143,  143,  144,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  145,  145,  145,  143,  143,
      143,  144,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  143,  143,  143,  143,  143,
      143,  145,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  145,  145,  145,  145,  145,

      145,  145,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,  145,  145,  145,  145,  145,  145,  145,  145,
      145,  145,    0,  143,  143
    } ;

static const short int yy_nxt[247] =
    {   0,
        4,    5,    6,    7,    8,    9,   10,   11,   11,   12,
       13,   11,   14,   15,   16,   17,   11,   18,   19,   20,
       17,   11,   21,   11,   22,    4,   23,   24,   25,   26,
       27,   28,   29,   30,   31,   29,   29,   32,   29,   29,
       33,   34,   35,   36,   37,   29,   29,   38,   29,   11,
       39,   11,   46,   46,   63,   49,   47,   55,   64,   44,
       44,   47,   74,   48,   44,   50,   53,   51,   72,   75,
       53,   53,   51,   53,   52,   53,   65,  142,   96,   41,
       66,   77,   73,  141,   67,   53,   77,   80,   78,   50,
      140,   51,   80,  139,   81,   77,   51,   97,   52,   47,

       77,  138,   78,   80,   47,  137,   48,  136,   80,  135,
       81,   42,   42,  134,  133,  132,  131,  130,  129,  128,
      127,  126,  125,  124,  123,  122,  121,  120,  119,  118,
      117,  116,  115,  114,  113,  112,  111,  110,  109,  108,
      107,  106,  105,  104,  103,  102,   80,   77,  101,  100,
       99,   98,   95,   94,   93,   92,   91,   90,   89,   88,
       87,   86,   85,   84,   83,   82,   51,   79,   43,   40,
       76,   71,   70,   69,   68,   62,   61,   60,   59,   58,
       57,   56,   44,   54,   41,   41,   44,   45,   44,   43,
       41,   40,  143,    3,  143,  143,  143,  143,  143,  143,

      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143
    } ;

static const short int yy_chk[247] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,   13,   14,   31,   16,   15,  145,   31,   14,
       13,   15,   38,   15,   16,   17,   19,   17,   37,   38,
       19,   19,   17,   19,   17,   19,   32,  140,   71,   19,
       32,   47,   37,  139,   32,   19,   47,   50,   47,   51,
      138,   51,   50,  133,   50,   77,   51,   71,   51,   79,

       77,  131,   77,   80,   79,  129,   79,  126,   80,  125,
       80,  144,  144,  123,  122,  120,  119,  117,  116,  113,
      112,  111,  110,  108,  105,  104,  103,  101,  100,   99,
       98,   97,   96,   95,   94,   93,   92,   91,   90,   89,
       88,   86,   85,   84,   83,   82,   81,   78,   75,   74,
       73,   72,   70,   69,   68,   67,   66,   65,   63,   62,
       61,   60,   59,   58,   57,   56,   52,   48,   42,   40,
       39,   36,   35,   34,   33,   30,   28,   27,   26,   25,
       24,   23,   22,   21,   20,   18,   12,   10,    9,    8,
        7,    5,    3,  143,  143,  143,  143,  143,  143,  143,

      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143,  143,  143,  143,  143,
      143,  143,  143,  143,  143,  143
    } ;

static yy_state_type yy_last_accepting_state;
static YY_CHAR *yy_last_accepting_cpos;

/* the intent behind this definition is that it'll catch
 * any uses of REJECT which flex missed
 */
#define REJECT reject_used_but_not_detected
#define yymore() yymore_used_but_not_detected
#define YY_MORE_ADJ 0

/* these variables are all declared out here so that section 3 code can
 * manipulate them
 */
/* points to current character in buffer */
static YY_CHAR *yy_c_buf_p = (YY_CHAR *) 0;
static int yy_init = 1;		/* whether we need to initialize */
static int yy_start = 0;	/* start state number */

/* flag which is used to allow yywrap()'s to do buffer switches
 * instead of setting up a fresh yyin.  A bit of a hack ...
 */
static int yy_did_buffer_switch_on_eof;

static yy_state_type yy_get_previous_state YY_PROTO(( void ));
static yy_state_type yy_try_NUL_trans YY_PROTO(( yy_state_type current_state ));
static int yy_get_next_buffer YY_PROTO(( void ));
static void yyunput YY_PROTO(( YY_CHAR c, YY_CHAR *buf_ptr ));
void yyrestart YY_PROTO(( FILE *input_file ));
void yy_switch_to_buffer YY_PROTO(( YY_BUFFER_STATE new_buffer ));
void yy_load_buffer_state YY_PROTO(( void ));
YY_BUFFER_STATE yy_create_buffer YY_PROTO(( FILE *file, int size ));
void yy_delete_buffer YY_PROTO(( YY_BUFFER_STATE b ));
void yy_init_buffer YY_PROTO(( YY_BUFFER_STATE b, FILE *file ));

#define yy_new_buffer yy_create_buffer

#ifdef __cplusplus
static int yyinput YY_PROTO(( void ));
#else
static int input YY_PROTO(( void ));
#endif

YY_DECL
    {
    register yy_state_type yy_current_state;
    register YY_CHAR *yy_cp, *yy_bp;
    register int yy_act;



    if ( yy_init )
	{
	YY_USER_INIT;

	if ( ! yy_start )
	    yy_start = 1;	/* first start state */

	if ( ! yyin )
	    yyin = stdin;

	if ( ! yyout )
	    yyout = stdout;

	if ( yy_current_buffer )
	    yy_init_buffer( yy_current_buffer, yyin );
	else
	    yy_current_buffer = yy_create_buffer( yyin, YY_BUF_SIZE );

	yy_load_buffer_state();

	yy_init = 0;
	}

    while ( 1 )		/* loops until end-of-file is reached */
	{
	yy_cp = yy_c_buf_p;

	/* support of yytext */
	*yy_cp = yy_hold_char;

	/* yy_bp points to the position in yy_ch_buf of the start of the
	 * current run.
	 */
	yy_bp = yy_cp;

	yy_current_state = yy_start;
yy_match:
	do
	    {
	    register YY_CHAR yy_c = yy_ec[*yy_cp];
	    if ( yy_accept[yy_current_state] )
		{
		yy_last_accepting_state = yy_current_state;
		yy_last_accepting_cpos = yy_cp;
		}
	    while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
		{
		yy_current_state = yy_def[yy_current_state];
		if ( yy_current_state >= 144 )
		    yy_c = yy_meta[yy_c];
		}
	    yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
	    ++yy_cp;
	    }
	while ( yy_base[yy_current_state] != 194 );

yy_find_action:
	yy_act = yy_accept[yy_current_state];

	YY_DO_BEFORE_ACTION;
	YY_USER_ACTION;

do_action:	/* this label is used only to access EOF actions */


	switch ( yy_act )
	    {
	    case 0: /* must backtrack */
	    /* undo the effects of YY_DO_BEFORE_ACTION */
	    *yy_cp = yy_hold_char;
	    yy_cp = yy_last_accepting_cpos;
	    yy_current_state = yy_last_accepting_state;
	    goto yy_find_action;

case 1:
# line 61 "scan.l"
return(Define);
	YY_BREAK
case 2:
# line 62 "scan.l"
return(Break);
	YY_BREAK
case 3:
# line 63 "scan.l"
return(Quit);
	YY_BREAK
case 4:
# line 64 "scan.l"
return(Length);
	YY_BREAK
case 5:
# line 65 "scan.l"
return(Return);
	YY_BREAK
case 6:
# line 66 "scan.l"
return(For);
	YY_BREAK
case 7:
# line 67 "scan.l"
return(If);
	YY_BREAK
case 8:
# line 68 "scan.l"
return(While);
	YY_BREAK
case 9:
# line 69 "scan.l"
return(Sqrt);
	YY_BREAK
case 10:
# line 70 "scan.l"
return(Scale);
	YY_BREAK
case 11:
# line 71 "scan.l"
return(Ibase);
	YY_BREAK
case 12:
# line 72 "scan.l"
return(Obase);
	YY_BREAK
case 13:
# line 73 "scan.l"
return(Auto);
	YY_BREAK
case 14:
# line 74 "scan.l"
return(Else);
	YY_BREAK
case 15:
# line 75 "scan.l"
return(Read);
	YY_BREAK
case 16:
# line 76 "scan.l"
return(Halt);
	YY_BREAK
case 17:
# line 77 "scan.l"
return(Last);
	YY_BREAK
case 18:
# line 78 "scan.l"
return(Warranty);
	YY_BREAK
case 19:
# line 79 "scan.l"
return(Continue);
	YY_BREAK
case 20:
# line 80 "scan.l"
return(Print);
	YY_BREAK
case 21:
# line 81 "scan.l"
return(Limits);
	YY_BREAK
case 22:
# line 82 "scan.l"
{ yylval.c_value = yytext[0];
					      return((int)yytext[0]); }
	YY_BREAK
case 23:
# line 84 "scan.l"
{ return(AND); }
	YY_BREAK
case 24:
# line 85 "scan.l"
{ return(OR); }
	YY_BREAK
case 25:
# line 86 "scan.l"
{ return(NOT); }
	YY_BREAK
case 26:
# line 87 "scan.l"
{ yylval.c_value = yytext[0]; return(MUL_OP); }
	YY_BREAK
case 27:
# line 88 "scan.l"
{ yylval.c_value = yytext[0]; return(ASSIGN_OP); }
	YY_BREAK
case 28:
# line 89 "scan.l"
{
#ifdef OLD_EQ_OP
			 char warn_save;
			 warn_save = warn_not_std;
			 warn_not_std = TRUE;
			 warn ("Old fashioned =<op>");
			 warn_not_std = warn_save;
			 yylval.c_value = yytext[1];
#else
			 yylval.c_value = '=';
			 yyless (1);
#endif
			 return(ASSIGN_OP);
		       }
	YY_BREAK
case 29:
# line 103 "scan.l"
{ yylval.s_value = strcopyof(yytext); return(REL_OP); }
	YY_BREAK
case 30:
# line 104 "scan.l"
{ yylval.c_value = yytext[0]; return(INCR_DECR); }
	YY_BREAK
case 31:
# line 105 "scan.l"
{ line_no++; return(NEWLINE); }
	YY_BREAK
case 32:
# line 106 "scan.l"
{  line_no++;  /* ignore a "quoted" newline */ }
	YY_BREAK
case 33:
# line 107 "scan.l"
{ /* ignore spaces and tabs */ }
	YY_BREAK
case 34:
# line 108 "scan.l"
{
	int c;

	for (;;)
	  {
	    while ( ((c=input()) != '*') && (c != EOF))
	      /* eat it */
	      if (c == '\n') line_no++;
	    if (c == '*')
 	      {
		while ( (c=input()) == '*') /* eat it*/;
		if (c == '/') break; /* at end of comment */
		if (c == '\n') line_no++;
	      }
	    if (c == EOF)
	      {
		fprintf (stderr,"EOF encountered in a comment.\n");
		break;
	      }
	  }
      }
	YY_BREAK
case 35:
# line 129 "scan.l"
{ yylval.s_value = strcopyof(yytext); return(NAME); }
	YY_BREAK
case 36:
# line 130 "scan.l"
{
 	      unsigned char *look;
	      int count = 0;
	      yylval.s_value = strcopyof(yytext);
	      for (look = yytext; *look != 0; look++)
		{
		  if (*look == '\n') line_no++;
		  if (*look == '"')  count++;
		}
	      if (count != 2) yyerror ("NUL character in string.");
	      return(STRING);
	    }
	YY_BREAK
case 37:
# line 142 "scan.l"
{
	      unsigned char *src, *dst;
	      int len;
	      /* remove a trailing decimal point. */
	      len = strlen(yytext);
	      if (yytext[len-1] == '.')
	        yytext[len-1] = 0;
	      /* remove leading zeros. */
	      src = yytext;
	      dst = yytext;
	      while (*src == '0') src++;
	      if (*src == 0) src--;
	      /* Copy strings removing the newlines. */
	      while (*src != 0)
		{
	          if (*src == '\\')
		    {
		      src++; src++;
		      line_no++;
		    }
		  else
		    *dst++ = *src++;
	        }
	      *dst = 0;
	      yylval.s_value = strcopyof(yytext);
	      return(NUMBER);
	    }
	YY_BREAK
case 38:
# line 169 "scan.l"
{
	  if (yytext[0] < ' ')
	    yyerror ("illegal character: ^%c",yytext[0] + '@');
	  else
	    if (yytext[0] > '~')
	      yyerror ("illegal character: \\%3d", (int) yytext[0]);
	    else
	      yyerror ("illegal character: %s",yytext);
	}
	YY_BREAK
case 39:
# line 178 "scan.l"
ECHO;
	YY_BREAK
case YY_STATE_EOF(INITIAL):
    yyterminate();

	    case YY_END_OF_BUFFER:
		{
		/* amount of text matched not including the EOB char */
		int yy_amount_of_matched_text = yy_cp - yytext - 1;

		/* undo the effects of YY_DO_BEFORE_ACTION */
		*yy_cp = yy_hold_char;

		/* note that here we test for yy_c_buf_p "<=" to the position
		 * of the first EOB in the buffer, since yy_c_buf_p will
		 * already have been incremented past the NUL character
		 * (since all states make transitions on EOB to the end-
		 * of-buffer state).  Contrast this with the test in yyinput().
		 */
		if ( yy_c_buf_p <= &yy_current_buffer->yy_ch_buf[yy_n_chars] )
		    /* this was really a NUL */
		    {
		    yy_state_type yy_next_state;

		    yy_c_buf_p = yytext + yy_amount_of_matched_text;

		    yy_current_state = yy_get_previous_state();

		    /* okay, we're now positioned to make the
		     * NUL transition.  We couldn't have
		     * yy_get_previous_state() go ahead and do it
		     * for us because it doesn't know how to deal
		     * with the possibility of jamming (and we
		     * don't want to build jamming into it because
		     * then it will run more slowly)
		     */

		    yy_next_state = yy_try_NUL_trans( yy_current_state );

		    yy_bp = yytext + YY_MORE_ADJ;

		    if ( yy_next_state )
			{
			/* consume the NUL */
			yy_cp = ++yy_c_buf_p;
			yy_current_state = yy_next_state;
			goto yy_match;
			}

		    else
			{
			goto yy_find_action;
			}
		    }

		else switch ( yy_get_next_buffer() )
		    {
		    case EOB_ACT_END_OF_FILE:
			{
			yy_did_buffer_switch_on_eof = 0;

			if ( yywrap() )
			    {
			    /* note: because we've taken care in
			     * yy_get_next_buffer() to have set up yytext,
			     * we can now set up yy_c_buf_p so that if some
			     * total hoser (like flex itself) wants
			     * to call the scanner after we return the
			     * YY_NULL, it'll still work - another YY_NULL
			     * will get returned.
			     */
			    yy_c_buf_p = yytext + YY_MORE_ADJ;

			    yy_act = YY_STATE_EOF((yy_start - 1) / 2);
			    goto do_action;
			    }

			else
			    {
			    if ( ! yy_did_buffer_switch_on_eof )
				YY_NEW_FILE;
			    }
			}
			break;

		    case EOB_ACT_CONTINUE_SCAN:
			yy_c_buf_p = yytext + yy_amount_of_matched_text;

			yy_current_state = yy_get_previous_state();

			yy_cp = yy_c_buf_p;
			yy_bp = yytext + YY_MORE_ADJ;
			goto yy_match;

		    case EOB_ACT_LAST_MATCH:
			yy_c_buf_p =
			    &yy_current_buffer->yy_ch_buf[yy_n_chars];

			yy_current_state = yy_get_previous_state();

			yy_cp = yy_c_buf_p;
			yy_bp = yytext + YY_MORE_ADJ;
			goto yy_find_action;
		    }
		break;
		}

	    default:
#ifdef FLEX_DEBUG
		printf( "action # %d\n", yy_act );
#endif
		YY_FATAL_ERROR(
			"fatal flex scanner internal error--no action found" );
	    }
	}
    }


/* yy_get_next_buffer - try to read in a new buffer
 *
 * synopsis
 *     int yy_get_next_buffer();
 *
 * returns a code representing an action
 *     EOB_ACT_LAST_MATCH -
 *     EOB_ACT_CONTINUE_SCAN - continue scanning from current position
 *     EOB_ACT_END_OF_FILE - end of file
 */

static int yy_get_next_buffer()

    {
    register YY_CHAR *dest = yy_current_buffer->yy_ch_buf;
    register YY_CHAR *source = yytext - 1; /* copy prev. char, too */
    register int number_to_move, i;
    int ret_val;

    if ( yy_c_buf_p > &yy_current_buffer->yy_ch_buf[yy_n_chars + 1] )
	YY_FATAL_ERROR(
		"fatal flex scanner internal error--end of buffer missed" );

    /* try to read more data */

    /* first move last chars to start of buffer */
    number_to_move = yy_c_buf_p - yytext;

    for ( i = 0; i < number_to_move; ++i )
	*(dest++) = *(source++);

    if ( yy_current_buffer->yy_eof_status != EOF_NOT_SEEN )
	/* don't do the read, it's not guaranteed to return an EOF,
	 * just force an EOF
	 */
	yy_n_chars = 0;

    else
	{
	int num_to_read = yy_current_buffer->yy_buf_size - number_to_move - 1;

	if ( num_to_read > YY_READ_BUF_SIZE )
	    num_to_read = YY_READ_BUF_SIZE;

	else if ( num_to_read <= 0 )
	    YY_FATAL_ERROR( "fatal error - scanner input buffer overflow" );

	/* read in more data */
	YY_INPUT( (&yy_current_buffer->yy_ch_buf[number_to_move]),
		  yy_n_chars, num_to_read );
	}

    if ( yy_n_chars == 0 )
	{
	if ( number_to_move == 1 )
	    {
	    ret_val = EOB_ACT_END_OF_FILE;
	    yy_current_buffer->yy_eof_status = EOF_DONE;
	    }

	else
	    {
	    ret_val = EOB_ACT_LAST_MATCH;
	    yy_current_buffer->yy_eof_status = EOF_PENDING;
	    }
	}

    else
	ret_val = EOB_ACT_CONTINUE_SCAN;

    yy_n_chars += number_to_move;
    yy_current_buffer->yy_ch_buf[yy_n_chars] = YY_END_OF_BUFFER_CHAR;
    yy_current_buffer->yy_ch_buf[yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;

    /* yytext begins at the second character in yy_ch_buf; the first
     * character is the one which preceded it before reading in the latest
     * buffer; it needs to be kept around in case it's a newline, so
     * yy_get_previous_state() will have with '^' rules active
     */

    yytext = &yy_current_buffer->yy_ch_buf[1];

    return ( ret_val );
    }


/* yy_get_previous_state - get the state just before the EOB char was reached
 *
 * synopsis
 *     yy_state_type yy_get_previous_state();
 */

static yy_state_type yy_get_previous_state()

    {
    register yy_state_type yy_current_state;
    register YY_CHAR *yy_cp;

    yy_current_state = yy_start;

    for ( yy_cp = yytext + YY_MORE_ADJ; yy_cp < yy_c_buf_p; ++yy_cp )
	{
	register YY_CHAR yy_c = (*yy_cp ? yy_ec[*yy_cp] : 1);
	if ( yy_accept[yy_current_state] )
	    {
	    yy_last_accepting_state = yy_current_state;
	    yy_last_accepting_cpos = yy_cp;
	    }
	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
	    {
	    yy_current_state = yy_def[yy_current_state];
	    if ( yy_current_state >= 144 )
		yy_c = yy_meta[yy_c];
	    }
	yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
	}

    return ( yy_current_state );
    }


/* yy_try_NUL_trans - try to make a transition on the NUL character
 *
 * synopsis
 *     next_state = yy_try_NUL_trans( current_state );
 */

#ifdef YY_USE_PROTOS
static yy_state_type yy_try_NUL_trans( register yy_state_type yy_current_state )
#else
static yy_state_type yy_try_NUL_trans( yy_current_state )
register yy_state_type yy_current_state;
#endif

    {
    register int yy_is_jam;
    register YY_CHAR *yy_cp = yy_c_buf_p;

    register YY_CHAR yy_c = 1;
    if ( yy_accept[yy_current_state] )
	{
	yy_last_accepting_state = yy_current_state;
	yy_last_accepting_cpos = yy_cp;
	}
    while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
	{
	yy_current_state = yy_def[yy_current_state];
	if ( yy_current_state >= 144 )
	    yy_c = yy_meta[yy_c];
	}
    yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
    yy_is_jam = (yy_current_state == 143);

    return ( yy_is_jam ? 0 : yy_current_state );
    }


#ifdef YY_USE_PROTOS
static void yyunput( YY_CHAR c, register YY_CHAR *yy_bp )
#else
static void yyunput( c, yy_bp )
YY_CHAR c;
register YY_CHAR *yy_bp;
#endif

    {
    register YY_CHAR *yy_cp = yy_c_buf_p;

    /* undo effects of setting up yytext */
    *yy_cp = yy_hold_char;

    if ( yy_cp < yy_current_buffer->yy_ch_buf + 2 )
	{ /* need to shift things up to make room */
	register int number_to_move = yy_n_chars + 2; /* +2 for EOB chars */
	register YY_CHAR *dest =
	    &yy_current_buffer->yy_ch_buf[yy_current_buffer->yy_buf_size + 2];
	register YY_CHAR *source =
	    &yy_current_buffer->yy_ch_buf[number_to_move];

	while ( source > yy_current_buffer->yy_ch_buf )
	    *--dest = *--source;

	yy_cp += dest - source;
	yy_bp += dest - source;
	yy_n_chars = yy_current_buffer->yy_buf_size;

	if ( yy_cp < yy_current_buffer->yy_ch_buf + 2 )
	    YY_FATAL_ERROR( "flex scanner push-back overflow" );
	}

    if ( yy_cp > yy_bp && yy_cp[-1] == '\n' )
	yy_cp[-2] = '\n';

    *--yy_cp = c;

    /* note: the formal parameter *must* be called "yy_bp" for this
     *       macro to now work correctly
     */
    YY_DO_BEFORE_ACTION; /* set up yytext again */
    }


#ifdef __cplusplus
static int yyinput()
#else
static int input()
#endif

    {
    int c;
    YY_CHAR *yy_cp = yy_c_buf_p;

    *yy_cp = yy_hold_char;

    if ( *yy_c_buf_p == YY_END_OF_BUFFER_CHAR )
	{
	/* yy_c_buf_p now points to the character we want to return.
	 * If this occurs *before* the EOB characters, then it's a
	 * valid NUL; if not, then we've hit the end of the buffer.
	 */
	if ( yy_c_buf_p < &yy_current_buffer->yy_ch_buf[yy_n_chars] )
	    /* this was really a NUL */
	    *yy_c_buf_p = '\0';

	else
	    { /* need more input */
	    yytext = yy_c_buf_p;
	    ++yy_c_buf_p;

	    switch ( yy_get_next_buffer() )
		{
		case EOB_ACT_END_OF_FILE:
		    {
		    if ( yywrap() )
			{
			yy_c_buf_p = yytext + YY_MORE_ADJ;
			return ( EOF );
			}

		    YY_NEW_FILE;

#ifdef __cplusplus
		    return ( yyinput() );
#else
		    return ( input() );
#endif
		    }
		    break;

		case EOB_ACT_CONTINUE_SCAN:
		    yy_c_buf_p = yytext + YY_MORE_ADJ;
		    break;

		case EOB_ACT_LAST_MATCH:
#ifdef __cplusplus
		    YY_FATAL_ERROR( "unexpected last match in yyinput()" );
#else
		    YY_FATAL_ERROR( "unexpected last match in input()" );
#endif
		}
	    }
	}

    c = *yy_c_buf_p;
    yy_hold_char = *++yy_c_buf_p;

    return ( c );
    }


#ifdef YY_USE_PROTOS
void yyrestart( FILE *input_file )
#else
void yyrestart( input_file )
FILE *input_file;
#endif

    {
    yy_init_buffer( yy_current_buffer, input_file );
    yy_load_buffer_state();
    }


#ifdef YY_USE_PROTOS
void yy_switch_to_buffer( YY_BUFFER_STATE new_buffer )
#else
void yy_switch_to_buffer( new_buffer )
YY_BUFFER_STATE new_buffer;
#endif

    {
    if ( yy_current_buffer == new_buffer )
	return;

    if ( yy_current_buffer )
	{
	/* flush out information for old buffer */
	*yy_c_buf_p = yy_hold_char;
	yy_current_buffer->yy_buf_pos = yy_c_buf_p;
	yy_current_buffer->yy_n_chars = yy_n_chars;
	}

    yy_current_buffer = new_buffer;
    yy_load_buffer_state();

    /* we don't actually know whether we did this switch during
     * EOF (yywrap()) processing, but the only time this flag
     * is looked at is after yywrap() is called, so it's safe
     * to go ahead and always set it.
     */
    yy_did_buffer_switch_on_eof = 1;
    }


#ifdef YY_USE_PROTOS
void yy_load_buffer_state( void )
#else
void yy_load_buffer_state()
#endif

    {
    yy_n_chars = yy_current_buffer->yy_n_chars;
    yytext = yy_c_buf_p = yy_current_buffer->yy_buf_pos;
    yyin = yy_current_buffer->yy_input_file;
    yy_hold_char = *yy_c_buf_p;
    }


#ifdef YY_USE_PROTOS
YY_BUFFER_STATE yy_create_buffer( FILE *file, int size )
#else
YY_BUFFER_STATE yy_create_buffer( file, size )
FILE *file;
int size;
#endif

    {
    YY_BUFFER_STATE b;

    b = (YY_BUFFER_STATE) malloc( sizeof( struct yy_buffer_state ) );

    if ( ! b )
	YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

    b->yy_buf_size = size;

    /* yy_ch_buf has to be 2 characters longer than the size given because
     * we need to put in 2 end-of-buffer characters.
     */
    b->yy_ch_buf = (YY_CHAR *) malloc( (unsigned) (b->yy_buf_size + 2) );

    if ( ! b->yy_ch_buf )
	YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );

    yy_init_buffer( b, file );

    return ( b );
    }


#ifdef YY_USE_PROTOS
void yy_delete_buffer( YY_BUFFER_STATE b )
#else
void yy_delete_buffer( b )
YY_BUFFER_STATE b;
#endif

    {
    if ( b == yy_current_buffer )
	yy_current_buffer = (YY_BUFFER_STATE) 0;

    free( (char *) b->yy_ch_buf );
    free( (char *) b );
    }


#ifdef YY_USE_PROTOS
void yy_init_buffer( YY_BUFFER_STATE b, FILE *file )
#else
void yy_init_buffer( b, file )
YY_BUFFER_STATE b;
FILE *file;
#endif

    {
    b->yy_input_file = file;

    /* we put in the '\n' and start reading from [1] so that an
     * initial match-at-newline will be true.
     */

    b->yy_ch_buf[0] = '\n';
    b->yy_n_chars = 1;

    /* we always need two end-of-buffer characters.  The first causes
     * a transition to the end-of-buffer state.  The second causes
     * a jam in that state.
     */
    b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
    b->yy_ch_buf[2] = YY_END_OF_BUFFER_CHAR;

    b->yy_buf_pos = &b->yy_ch_buf[1];

    b->yy_eof_status = EOF_NOT_SEEN;
    }
# line 178 "scan.l"




/* This is the way to get multiple files input into lex. */

int
yywrap()
{
  if (!open_new_file ()) return (1);	/* EOF on standard in. */
  return (0);				/* We have more input. */
}
