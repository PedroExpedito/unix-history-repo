#!/usr/bin/env perl
#
# Copyright (C) 2006-2008  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

# $Id: convertxsl.pl,v 1.14 2008/07/17 23:43:26 jinmei Exp $

use strict;
use warnings;

my $rev = '$Id: convertxsl.pl,v 1.14 2008/07/17 23:43:26 jinmei Exp $';
$rev =~ s/\$//g;
$rev =~ s/,v//g;
$rev =~ s/Id: //;

my $xsl = "unknown";
my $lines = '';

while (<>) {
    chomp;
    # pickout the id for comment.
    $xsl = $_ if (/<!-- .Id:.* -->/);
    # convert Id string to a form not recognisable by cvs.
    $_ =~ s/<!-- .Id:(.*). -->/<!-- \\045Id: $1\\045 -->/;
    s/[\ \t]+/ /g;
    s/\>\ \</\>\</g;
    s/\"/\\\"/g;
    s/^/\t\"/;
    s/$/\\n\"/;
    if ($lines eq "") {
	    $lines .= $_;
    } else {
	    $lines .= "\n" . $_;
    }
}

$xsl =~ s/\$//g;
$xsl =~ s/<!-- Id: //;
$xsl =~ s/ -->.*//;
$xsl =~ s/,v//;

print "/*\n * Generated by $rev \n * From $xsl\n */\n";
print 'static char xslmsg[] =',"\n";
print $lines;

print ';', "\n";
