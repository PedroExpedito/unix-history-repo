/* Copyright (c) 1982 Regents of the University of California */

/* static char sccsid[] = "@(#)command.h 1.2 %G%"; */

/*
 * Definitions for the command module.
 *
 * The command module scans and parses the commands.  This includes
 * input file management (i.e. the "source" command), and some error
 * handling.
 */

char *initfile;		/* file to read initial commands from */
BOOLEAN nlflag;		/* for error and signal recovery */

#define HELPFILE "/vb/arpa/linton/lib/pdx.help"

prompt();		/* print a prompt */
int yyparse();		/* parser generated by yacc */
lexinit();		/* initialize debugger symbol table */
gobble();		/* eat input up to a newline for error recovery */
remake();		/* recompile program, read in new namelist */
alias();		/* create an alias */
BOOLEAN isstdin();	/* input is from standard input */
