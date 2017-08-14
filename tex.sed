s/\\/\\verb+\\+/g; 
s/\%/\\%/g;
s/\^/\\^/g;
s/\-\-/\-\\hspace\{01.cm\}\-/g;
1s/$/\n\} \\end\{center\}\n\\begin\{description\}\n\n/
1s/^/\\documentstyle\[11pt\]\{article\}\n\\begin\{document\}\n\\begin\{center\} \{\\bf\n/
$s/$/\\end\{description\}\n\\end\{document\}/
s/^\([A-Z]\{4,\}\)$/\\item\[\1\] \\hfill \\\\/g
