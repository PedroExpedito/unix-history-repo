int source DCLPROTO((char *s));
void sourcehome DCLPROTO((char *s));
void zerrnam DCLPROTO((char *cmd, char *fmt, char *str,int num));
void zerr DCLPROTO((char *fmt, char *str,int num));
void niceputc DCLPROTO((int c,FILE *f));
void intr DCLPROTO((void));
void noholdintr DCLPROTO((void));
void holdintr DCLPROTO((void));
char *fgetline DCLPROTO((char *buf,int len,FILE *in));
char *findpwd DCLPROTO((char *s));
char *fixpwd DCLPROTO((char *s));
int ispwd DCLPROTO((char *s));
char *xsymlink DCLPROTO((char *s));
char **slashsplit DCLPROTO((char *s));
int islink DCLPROTO((char *s));
int xsymlinks DCLPROTO((char *s,int flag));
void fprintdir DCLPROTO((char *s, FILE *f));
void printdir DCLPROTO((char *s));
void printdircr DCLPROTO((char *s));
int finddir DCLPROTO((char *s));
void adduserdir DCLPROTO((char *s,char *t));
int dircmp DCLPROTO((char *s,char *t));
int ddifftime DCLPROTO((time_t t1,time_t t2));
void scanjobs DCLPROTO((void));
void preprompt DCLPROTO((void));
int arrlen DCLPROTO((char **s));
void checkmailpath DCLPROTO((char **s));
void saveoldfuncs DCLPROTO((char *x,Cmdnam y));
void newcmdnamtab DCLPROTO((void));
void freecmdnam DCLPROTO((vptr a));
void freecompctl DCLPROTO((vptr a));
void freestr DCLPROTO((vptr a));
void freeanode DCLPROTO((vptr a));
void freepm DCLPROTO((vptr a));
void restoretty DCLPROTO((void));
void gettyinfo DCLPROTO((struct ttyinfo *ti));
void settyinfo DCLPROTO((struct ttyinfo *ti));
void sanetty DCLPROTO((struct ttyinfo *ti));
void adjustwinsize DCLPROTO((void));
int zyztem DCLPROTO((char *s,char *t));
int waitfork DCLPROTO((void));
int movefd DCLPROTO((int fd));
void redup DCLPROTO((int x,int y));
void settrap DCLPROTO((int t0,List l));
void unsettrap DCLPROTO((int t0));
void dotrap DCLPROTO((int sig));
void ztrncpy DCLPROTO((char *s,char *t,int len));
void strucpy DCLPROTO((char **s,char *t));
void struncpy DCLPROTO((char **s,char *t,int n));
void checkrmall DCLPROTO((char *s));
int getquery DCLPROTO((void));
void spscannodis DCLPROTO((char *s,char *cn));
void spscan DCLPROTO((char *s,char *junk));
void spckword DCLPROTO((char **s,char **s2,char **tptr,int cmd,int ask));
int ztrftime DCLPROTO((char *buf,int bufsize,char *fmt,struct tm *tm));
char *join DCLPROTO((char **arr,int delim));
char *spacejoin DCLPROTO((char **s));
char *colonjoin DCLPROTO((char **s));
char **colonsplit DCLPROTO((char *s));
char **spacesplit DCLPROTO((char *s));
List getshfunc DCLPROTO((char *nam));
vptr allocnode DCLPROTO((int type));
vptr dupstruct DCLPROTO((vptr a));
void freestruct DCLPROTO((vptr a));
Lklist duplist DCLPROTO((Lklist l,VFunc func));
char **mkarray DCLPROTO((char *s));
void feep DCLPROTO((void));
void freearray DCLPROTO((char **s));
int equalsplit DCLPROTO((char *s,char **t));
void simplifyright DCLPROTO((List l));
void inittyptab DCLPROTO((void));
char **arrdup DCLPROTO((char **s));
char *spname  DCLPROTO((char *oldname));
int mindist DCLPROTO((char *dir,char *guess,char *best));
int spdist DCLPROTO((char *s,char *t,int thresh));
char *zgetenv DCLPROTO((char *s));
int tulower DCLPROTO((int c));
int tuupper DCLPROTO((int c));
void setcbreak DCLPROTO((void));
int getlineleng DCLPROTO((void));
void unsetcbreak DCLPROTO((void));
void attachtty DCLPROTO((long pgrp));
long gettygrp DCLPROTO((void));
