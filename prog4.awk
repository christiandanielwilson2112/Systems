BEGIN{first = 0;
      second = 0;
      third = 0;
      fourth = 0;
      fifth = 0; }

(/Ascend-Data-Rate/) && ($3>=0) && ($3<=14400) {
    first++;
}
(/Ascend-Data-Rate/) && ($3>=14401) && ($3<=19200) {
    second++;
}
(/Ascend-Data-Rate/) && ($3>=19201) && ($3<=28800) {
    third++;
}
(/Ascend-Data-Rate/) && ($3>=28801) && ($3<=33600) {
    fourth++;
}
(/Ascend-Data-Rate/) && ($3>=33601) {
    fifth++;
}  

END{print "0-14400\t\t"first
    print "14401-19200\t"second
    print "19201-28800\t"third
    print "28801-33600\t"fourth
    print "above 33600\t"fifth}
