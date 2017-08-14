BEGIN { accepted = 0;
	canceled = 0;
	rejected = 0;
	accepted2 = 0;
        canceled2 = 0;
        rejected2 = 0;
	accepted3 = 0;
        canceled3 = 0;
        rejected3 = 0;
	}
NR==1{
startmon = $1;
startday = $2;
starttime = $3;
}
($5=="swrinde")&&($4=="+"||$4=="j"||$4=="c"){
accepted = accepted + 1;
}
($5=="swrinde")&&($4=="c"){
canceled = canceled + 1;
}
($5=="swrinde")&&($4=="-"){
rejected = rejected + 1;
}
($5=="news.cais.net")&&($4=="+"||$4=="j"||$4=="c"){
accepted2 = accepted2 + 1;
}
($5=="news.cais.net")&&($4=="c"){
canceled2 = canceled2 + 1;
}
($5=="news.cais.net")&&($4=="-"){
rejected2 = rejected2 + 1;
}
($5=="?")&&($4=="+"||$4=="j"||$4=="c"){
accepted3 = accepted3 + 1;
}
($5=="?")&&($4=="c"){
canceled3 = canceled3 + 1;
}
($5=="?")&&($4=="-"){
rejected3 = rejected3 + 1;
}

END {
print "\t\t\tIncoming News Feed Summary\n"
print "\t\taccepted\trejected\tcanceled"
print "swrinde:\t"accepted"\t\t"rejected"\t\t"canceled"\t"
print "news.cais.net:\t"accepted2"\t\t"rejected2"\t\t"canceled2"\t"
print "?:\t\t"accepted3"\t\t"rejected3"\t\t"canceled3"\t\n"
print "Start Time = "startmon" "startday" "starttime"\tEnd Time = "$1" "$2" "$3"\t\n"
}
