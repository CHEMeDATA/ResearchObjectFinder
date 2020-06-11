#!/bin/bash
cppFile2=$2
nna=$1  
echo "vector<string> "$nna";" >> $cppFile2
while read current
do
 current=`echo  $current | sed 's/"//g'  `
 echo $nna".push_back(\""$current"\");" >> $cppFile2
done <curListInit.txt
echo >> $cppFile2

