#!/bin/bash
file=$1
file_in=$file".txt"
file_in2=$file"_2.txt"
file_in3=$file"_3.txt"
file_in4=$file"_4.txt"
file_in5=$file"_5.txt"
file_in_bis=$file"_bis.txt"
cat $file_in |  iconv -c -t ascii//TRANSLIT | sed 's/\;/TT\;TT/g'  > $file_in_bis
cat $file_in_bis | sed $'s/\t/;/g' > $file_in5
cat $file_in5 | sed 's/TT\;TT/\;/g' > $file_in4
cat $file_in4 | grep -v "LineToIgnore" > $file_in2
wc $file_in4 $file_in2
head -n 1 $file_in2 > $file_in3


while IFS=$';' read -r -a arr
do
b=("${arr[@]}")
done < $file_in3

file_out=$file".xml"
obj="Object"
echo '<?xml version="1.0"?>' > $file_out
echo "<$obj"'s>' >> $file_out
while IFS=$';' read -r -a arry
do
for idx in "${!b[@]}"; do
 if [[ ! -z ${b[$idx]} ]]; then
 echo -n '    ' >> $file_out
 echo -n '<'${b[$idx]}'>' >> $file_out
 echo -n ${arry[$idx]} >> $file_out
 echo -n '</'${b[$idx]}'>' >> $file_out
 echo >> $file_out
 fi
done
echo "  </$obj>" >> $file_out
done < $file_in2
echo "</$obj"'s>' >> $file_out

