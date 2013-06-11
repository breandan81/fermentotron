#!/usr/bin/perl


open (INSER, '</dev/ttyACM0');
open (OUTSER, '>>/dev/ttyACM0');

print "starting\n";

while(1)
{
	$a = <STDIN>;	
	print OUTSER $a;
	$s = <INSER>;
	print $s;
}

