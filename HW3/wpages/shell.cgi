#!/usr/bin/perl -w

print "Content-Type: text/plain\n\n";

open(PS,"ps -e -o pid,stime,args |") || die "Failed: $!\n";
while ( <PS> ) {
    print;
}
