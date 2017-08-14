BEGIN{input = 0;
      output = 0;}
/Acct-Input-Packets/{
    input += $3;
}

/Acct-Output-Packets/{
    output += $3;
}

END{print "Total Input Bandwidth Usage  =",input,"packets\nTotal Output Bandwidth Usage =",output,"packets"}

