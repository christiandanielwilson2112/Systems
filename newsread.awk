BEGIN {
	lonestar = 0;
	runner = 0;
	ringer = 0;
	rings = 0;
	lonestarg = 0;
	runnerg = 0;
	ringerg = 0;
	ringsg = 0;
	lonestarc = 0;
        runnerc = 0;
        ringerc = 0;
        ringsc = 0;
	lonestard = 0;
        runnerd = 0;
        ringerd = 0;
        ringsd = 0;
	lonestart = 0;
	runnert = 0;
	ringert = 0;
	ringst = 0;
}
NR==1{
startmon = $1;
startday = $2;
starttime = $3;
}
#lonestar
($6=="lonestar.jpl.utsa.edu" && $7=="exit"){
lonestar=lonestar + $9;
lonestarg=lonestarg + $11;
}
($6=="lonestar.jpl.utsa.edu" && $7=="group" && $8=="utsa.cs.2413"){
lonestarc=lonestarc + $$9;
}
($6=="lonestar.jpl.utsa.edu" && $7=="group" && $8=="utsa.cs.2413.d"){
lonestard=lonestard + $9;
}
($6=="lonestar.jpl.utsa.edu" && $7=="times"){
lonestart=lonestart + $13;
}
#runner
($6=="runner.jpl.utsa.edu" && $7=="exit"){
runner=runner + $9;
runnerg=runnerg + $11;
}
($6=="runner.jpl.utsa.edu" && $7=="group" && $8=="utsa.cs.2413"){
runnerc=runnerc + $$9;
}
($6=="runner.jpl.utsa.edu" && $7=="group" && $8=="utsa.cs.2413.d"){
runnerd=runnerd + $9;
}
($6=="runner.jpl.utsa.edu" && $7=="times"){
runnert=runnert + $13;
}
#ringer
($6=="ringer.cs.utsa.edu" && $7=="exit"){
ringer=ringer + $9;
ringerg=ringerg + $11;
}
($6=="ringer.cs.utsa.edu" && $7=="group" && $8=="utsa.cs.2413"){
ringerc=ringerc + $9;
}
($6=="ringer.cs.utsa.edu" && $7=="group" && $8=="utsa.cs.2413.d"){
ringerd=ringerd + $9;
}
($6=="ringer.cs.utsa.edu" && $7=="times"){
ringert=ringert + $13;
}
#rings
($6~/^.*ring(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-7]).*$/ && $7=="exit"){
rings=rings + $9;
ringsg=ringsg + $11;
}
($6~/^.*ring(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-7]).*$/ && $7=="group" && $8=="utsa.cs.2413"){
ringsc=ringsc + $9;
}
($6~/^.*ring(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-7]).*$/ && $7=="group" && $8=="utsa.cs.2413.d"){
ringsd=ringsd + $9;
}
($6~/^.*ring(0[0-9]|1[0-9]|2[0-9]|3[0-9]|4[0-7]).*$/ && $7=="times"){
ringst=ringst + $13;
}
END {
print "\t\t\t News Reader Summary\n";
print "\t\tlonestar\trunner\t\tringer\t\trings";
print "Articles:\t"lonestar"\t\t"runner"\t\t"ringer"\t\t"rings;
print "Groups:\t\t"lonestarg"\t\t"runnerg"\t\t"ringerg"\t\t"ringsg;
print "Cs2413:\t\t"lonestarc"\t\t"runnerc"\t\t"ringerc"\t\t"ringsc;
print "Cs2413.d\t"lonestard"\t\t"runnerd"\t\t"ringerd"\t\t"ringsd;
print "User Time:\t"lonestart"\t\t"runnert"\t\t"ringert"\t\t"ringst"\n";
print "Start Time = "startmon" "startday" "starttime"\tEnd Time = "$1" "$2" "$3"\t\n";
}
                   
