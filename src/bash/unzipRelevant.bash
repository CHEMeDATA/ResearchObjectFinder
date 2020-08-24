#!/bin/bash
## extract only the necessary files... to create list of objects (to generate objects change below....)

onlytouch="yes"

## to get everything... wasting space... maybe also time?!?
## unzip -o -d ../unziped ../data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6_bis_to_del.zip
input="../data/"
output="../unziped"
script="filterzip.source"
script2="extractzip.source"


echo "#### prepare filter model ..."
echo -n "Will unzip "
listOfList="list_of_lists.txt"
echo -n > $listOfList

for each_zip in `ls $input/*.zip`;do
echo -n > $script
echo -n "unzip -Z1 " >>$script
echo -n $each_zip >>$script
echo -n " | grep" >>$script
for toto in `cat ../specifications/list_of_file_to_check.txt`; do
   echo -n " -e " '"'$toto'$"' >>$script
   echo -n  $toto" "
done
   echo "files."
echo "work on files in zip : $each_zip "

thisFile=$each_zip"_listFiles.txt"

echo -n " | grep -v  __MACOSX " >>$script
echo -n " > $thisFile " >>$script
echo >>$script
echo "Running : "
cat $script
source $script
numberl=`cat  $thisFile |wc -l`

echo "#### Prepare extraction of "$numberl" main files ..."
echo -n > $script2
echo -n "unzip -o -q -d $output " >>$script2
echo -n $each_zip >>$script2
echo -n " " >>$script2
while read type_file
do
  echo -n ' "'$type_file'"' >>$script2
done < $thisFile
echo  >>$script2
echo "Running extraction of main files..."
source $script2


cat ../specifications/list_of_related_files2.txt | tail +2 > tmpdellist.txt
../src/bash/doRelated.sh $thisFile $each_zip 

cat ../specifications/ls -lartlist_of_related_files1.txt | tail +2 > tmpdellist.txt
#### Here two possibilites
#### if only touch 
if [ "$onlytouch" == "yes" ]; then
 ../src/bash/doRelated_create_empty.sh $thisFile $each_zip $output
else
#### if need files (to create objects...) 
 ../src/bash/doRelated.sh $thisFile $each_zip 
fi

echo "Comments:"
for type_file in `cat ../specifications/list_of_file_to_check.txt`; do
cat  $each_zip""_listFiles.txt | grep -r "$type_file"'$' > tmp_list_given_type.txt
number=`cat  tmp_list_given_type.txt|wc -l`
echo "Will work on "$number" files of type "$type_file 
done
echo "done with : "  $each_zip "_listFiles.txt ..."
echo  $each_zip"_listFiles.txt">> $listOfList

done
echo "lists of files in "$listOfList
cat  $listOfList

echo "cleaning up temp files... (don't worry about error messages below...)"
rm filterzip.source
rm extractzip.source
rm tmpdellist.txt
rm list_of_files_need_to_be_touched.txt
rm tmp_list_given_type.txt
rm list_of_lists.txt
rm ignoreWarningsempty.txt
rm ignoreWarnings.txt
rm extractziprelated.source
rm tmpList.txt