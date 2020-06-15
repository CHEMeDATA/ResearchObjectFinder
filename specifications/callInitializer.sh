#!/bin/bash
cppFile2=$2
nna=$1  
var="0"
echo "vector<string> "$nna";" >> $cppFile2
while read current
do
var=$((var+1))
 current=`echo  $current | sed 's/"//g'  `
 echo $nna".push_back(\""$current"\"); // #"$var  >> $cppFile2
done <curListInit.txt
echo >> $cppFile2

