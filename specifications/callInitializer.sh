#!/bin/bash
cppFile2=$2
nna=$1  
var="0"
if [ "$nna" == "Level" ]; then
	echo "vector<int> "$nna"; // "$var >> $cppFile2
else
	echo "vector<string> "$nna"; // "$var >> $cppFile2
fi
while read current
do
var=$((var+1))
 current=`echo  $current | sed 's/"//g'  `
 if [ "$nna" != "Level" ]; then
 	echo $nna".push_back(\""$current"\"); // "$var  >> $cppFile2
 else
 	echo $nna".push_back("$current"); // "$var  >> $cppFile2
 fi
done <curListInit.txt
echo >> $cppFile2

