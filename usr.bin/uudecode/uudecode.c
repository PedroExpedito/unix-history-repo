/*-
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef lint
static const char copyright[] =
"@(#) Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#if 0
#ifndef lint
static char sccsid[] = "@(#)uudecode.c	8.2 (Berkeley) 4/2/94";
#endif /* not lint */
#endif

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

/*
 * uudecode [file ...]
 *
 * create the specified file, decoding as you go.
 * used with uuencode.
 */
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <netinet/in.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <resolv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *filename;
char *outfile;
FILE *infp, *outfp;
int cflag, iflag, oflag, pflag, sflag;

static void usage(void);
int	decode(void);
int	decode2(void);
int	base64_decode(const char *);

int
main(int argc, char *argv[])
{
	int rval, ch;

	while ((ch = getopt(argc, argv, "cio:ps")) != -1) {
		switch(ch) {
		case 'c':
			if (oflag)
				usage();
			cflag = 1; /* multiple uudecode'd files */
			break;
		case 'i':
			iflag = 1; /* ask before override files */
			break;
		case 'o':
			if (cflag || pflag || sflag)
				usage();
			oflag = 1; /* output to the specified file */
			sflag = 1; /* do not strip pathnames for output */
			outfile = optarg; /* set the output filename */
			break;
		case 'p':
			if (oflag)
				usage();
			pflag = 1; /* print output to stdout */
			break;
		case 's':
			if (oflag)
				usage();
			sflag = 1; /* do not strip pathnames for output */
			break;
		default:
			usage();
		}
	}
        argc -= optind;
        argv += optind;

	if (*argv) {
		rval = 0;
		do {
			infp = fopen(filename = *argv, "r");
			if (infp == NULL) {
				warn("%s", *argv);
				rval = 1;
				continue;
			}
			rval |= decode();
			fclose(infp);
		} while (*++argv);
	} else {
		filename = "stdin";
		infp = stdin;
		rval = decode();
	}
	exit(rval);
}

int
decode(void)
{
	int r, v;

	v = decode2();
	if (v == EOF) {
		warnx("%s: missing or bad \"begin\" line", filename);
		return (1);
	}
	for (r = v; cflag; r |= v) {
		v = decode2();
		if (v == EOF)
			break;
	}
	return (r);
}

int
decode2(void)
{
	int base64, i;
	size_t n;
	char ch, *p, *q;
	void *mode;
	struct passwd *pw;
	struct stat st;
	char buf[MAXPATHLEN+1];
	char buffn[MAXPATHLEN+1]; /* file name buffer */

	base64 = 0;
	/* search for header line */
	for (;;) {
		if (fgets(buf, sizeof(buf), infp) == NULL)
			return (EOF);
		p = buf;
		if (strncmp(p, "begin-base64 ", 13) == 0) {
			base64 = 1;
			p += 13;
		} else if (strncmp(p, "begin ", 6) == 0)
			p += 6;
		else
			continue;
		/* p points to mode */
		q = strchr(p, ' ');
		if (q == NULL)
			continue;
		*q++ = '\0';
		/* q points to filename */
		n = strlen(q);
		while (n > 0 && (q[n-1] == '\n' || q[n-1] == '\r'))
			q[--n] = '\0';
		/* found valid header? */
		if (n > 0)
			break;
	}

	mode = setmode(p);
	if (mode == NULL) {
		warnx("%s: unable to parse file mode", filename);
		return (1);
	}

	if (oflag) {
		/* use command-line filename */
		n = strlcpy(buffn, outfile, sizeof(buffn));
	} else if (sflag) {
		/* don't strip, so try ~user/file expansion */
		p = NULL;
		pw = NULL;
		if (*q == '~')
			p = strchr(q, '/');
		if (p != NULL) {
			*p = '\0';
			pw = getpwnam(q + 1);
			*p = '/';
		}
		if (pw != NULL) {
			strlcpy(buffn, pw->pw_dir, sizeof(buffn));
			n = strlcat(buffn, p, sizeof(buffn));
		} else {
			n = strlcpy(buffn, q, sizeof(buffn));
		}
	} else {
		/* strip down to leaf name */
		p = strrchr(q, '/');
		if (p != NULL)
			n = strlcpy(buffn, p+1, sizeof(buffn));
		else
			n = strlcpy(buffn, q, sizeof(buffn));
	}
	if (n >= sizeof(buffn) || *buffn == '\0') {
		warnx("%s: bad output filename", filename);
		return (1);
	}

	if (pflag)
		outfp = stdout;
	else {
		int flags = O_WRONLY|O_CREAT|O_EXCL;
		if (lstat(buffn, &st) == 0) {
			if (iflag) {
				warnc(EEXIST, "%s: %s", filename, buffn);
				return (0);
			}
			switch (st.st_mode & S_IFMT) {
			case S_IFREG:
			case S_IFLNK:
				/* avoid symlink attacks */
				if (unlink(buffn) == 0 || errno == ENOENT)
					break;
				warn("%s: unlink %s", filename, buffn);
				return (1);
			case S_IFDIR:
				warnc(EISDIR, "%s: %s", filename, buffn);
				return (1);
			default:
				if (oflag) {
					/* trust command-line names */
					flags &= ~O_EXCL;
					break;
				}
				warnc(EEXIST, "%s: %s", filename, buffn);
				return (1);
			}
		} else if (errno != ENOENT) {
			warn("%s: %s", filename, buffn);
			return (1);
		}
		if ((i = open(buffn, flags, getmode(mode, 0) & 0666)) < 0 ||
		    (outfp = fdopen(i, "w")) == NULL) {
			warn("%s: %s", filename, buffn);
			return (1);
		}
	}
	free(mode);

	if (base64)
		return (base64_decode(buffn));

	/* for each input line */
	for (;;) {
		if (fgets(p = buf, sizeof(buf), infp) == NULL) {
			warnx("%s: short file", filename);
			return (1);
		}

#define	DEC(c)	(((c) - ' ') & 077)		/* single character decode */
#define IS_DEC(c) ( (((c) - ' ') >= 0) && (((c) - ' ') <= 077 + 1) )

#define OUT_OF_RANGE do {						\
	warnx("%s: %s: character out of range: [%d-%d]",		\
	    filename, buffn, 1 + ' ', 077 + ' ' + 1);			\
        return (1);							\
} while (0)

		/*
		 * `i' is used to avoid writing out all the characters
		 * at the end of the file.
		 */
		if ((i = DEC(*p)) <= 0)
			break;
		for (++p; i > 0; p += 4, i -= 3)
			if (i >= 3) {
				if (!(IS_DEC(*p) && IS_DEC(*(p + 1)) &&
				     IS_DEC(*(p + 2)) && IS_DEC(*(p + 3))))
                                	OUT_OF_RANGE;

				ch = DEC(p[0]) << 2 | DEC(p[1]) >> 4;
				putc(ch, outfp);
				ch = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
				putc(ch, outfp);
				ch = DEC(p[2]) << 6 | DEC(p[3]);
				putc(ch, outfp);
			}
			else {
				if (i >= 1) {
					if (!(IS_DEC(*p) && IS_DEC(*(p + 1))))
	                                	OUT_OF_RANGE;
					ch = DEC(p[0]) << 2 | DEC(p[1]) >> 4;
					putc(ch, outfp);
				}
				if (i >= 2) {
					if (!(IS_DEC(*(p + 1)) &&
						IS_DEC(*(p + 2))))
		                                OUT_OF_RANGE;

					ch = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
					putc(ch, outfp);
				}
				if (i >= 3) {
					if (!(IS_DEC(*(p + 2)) &&
						IS_DEC(*(p + 3))))
		                                OUT_OF_RANGE;
					ch = DEC(p[2]) << 6 | DEC(p[3]);
					putc(ch, outfp);
				}
			}
	}
	if (fgets(buf, sizeof(buf), infp) == NULL ||
	    (strcmp(buf, "end") && strcmp(buf, "end\n") &&
	     strcmp(buf, "end\r\n"))) {
		warnx("%s: no \"end\" line", filename);
		return (1);
	}
	if (fclose(outfp) != 0) {
		warnx("%s: %s", filename, buffn);
		return (1);
	}
	return (0);
}

int
base64_decode(const char *outname)
{
	int n;
	char buf[MAXPATHLEN+1];
	unsigned char out[MAXPATHLEN * 4];

	for (;;) {
		if (fgets(buf, sizeof(buf), infp) == NULL) {
			warnx("%s: short file", filename);
			return (1);
		}
		if (strcmp(buf, "====") == 0 ||
		    strcmp(buf, "====\n") == 0 ||
		    strcmp(buf, "====\r\n") == 0)
			return (0);
		n = strlen(buf);
		while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r'))
			buf[--n] = '\0';
		n = b64_pton(buf, out, sizeof(out));
		if (n < 0) {
			warnx("%s: %s: error decoding base64 input stream", filename, outname);
			return (1);
		}
		fwrite(out, 1, n, outfp);
	}
}

static void
usage(void)
{
	(void)fprintf(stderr,
"usage: uudecode [-cips] [file ...]\n"
"       uudecode [-i] -o output_file [file]\n"
"       b64decode [-cips] [file ...]\n"
"       b64decode [-i] -o output_file [file]\n");
	exit(1);
}
