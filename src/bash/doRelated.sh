#!/bin/bash

thisFile=$1
each_zip=$2
script3="extractziprelated.source"
while read line
do
ref=`echo  $line | cut -d" " -f1 `
refd=$ref"$"
other=`echo  $line | cut -d" " -f2 `
pos=`echo  $line | cut -d" " -f3 `
cat $thisFile| grep -e $ref >tmpList.txt
echo "#### Prepare extraction of files "$other" associated to "$ref" at relative position "$pos
echo -n > $script3
echo -n "unzip -o -q -d ../unziped " >>$script3
echo -n $each_zip >>$script3
echo -n " " >>$script3
while read currentFile
do
currentFile_fixed=`echo $currentFile | sed s/$refd/$other/ `
## fix path
fileName=`echo $currentFile_fixed | rev | cut -d"/" -f1 | rev `
pathfull=`echo $currentFile_fixed | rev | cut -d"/" -f2- | rev `
pathcut=$pathfull
if [ "$pos" == "1" ]; then
pathcut=`echo $pathfull | rev | cut -d"/" -f2- | rev `
fi
if [ "$pos" == "2" ]; then
pathcut=`echo $pathfull | rev | cut -d"/" -f3- | rev `
fi
currentFile_fixed=$pathcut"/"$fileName
#echo "currentFile:" $currentFile 
#echo "related    :" $currentFile_fixed
  echo -n ' "'$currentFile_fixed'"' >>$script3
done < tmpList.txt
echo  >>$script3
echo "Running extraction of related files..."
source $script3 &>ignoreWarnings.txt
done < tmpdellist.txt
