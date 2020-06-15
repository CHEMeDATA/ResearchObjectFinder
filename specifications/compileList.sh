#!/bin/bash
cppFile="forCprog.txt"
cppFile2="forCprogInit.txt"
echo -n > $cppFile
echo -n > $cppFile2

echo "#### Prepare list of types of files to look at... from column 3"
cat mainClassification.txt | iconv -c -t ascii//TRANSLIT |  grep -v "LineToIgnore" > uncommentedASCIIlist.txt 
echo "make list of file extension to keep"
location="3"
cat uncommentedASCIIlist.txt | sed 's/"//g' | cut -d$'\t' -f$location| tr " " "\n"| sort|uniq | grep "\S"> list_of_file_to_check.txt

echo -n "#### Work on additional conditions located in columns "
locationFrom="5"
locationTo="13"
echo $locationFrom " to " $locationTo
echo "#reference file, related filename to check exists, relative position in the path">list_of_related_files1.txt
echo "#reference file, related filename to read, relative position in the path">list_of_related_files2.txt

for toto in `cat list_of_file_to_check.txt`; do
# get the lines for this type of file
   to_catch='"'$toto'"'
   	     echo "  if(currFileName.find(\""$toto"\") != std::string::npos) {"  >> $cppFile
   	     echo "    switch(caseNumber) {"  >> $cppFile

   cat uncommentedASCIIlist.txt |  cut -d$'\t' -f$location| grep -n $to_catch | cut -d":" -f1 > tmp_list_line_number.txt
   for lineNum in `cat tmp_list_line_number.txt`; do
	     echo "    case "  $lineNum ":">> $cppFile

     cat uncommentedASCIIlist.txt | head -n $lineNum | tail -n 1 |  cut -d$'\t' -f$locationFrom-$locationTo | tr "\t" "\n"> tmp_conditions_in_diff_lines.txt
   	  while read fieldf
	   do
	   if [ "$fieldf" != "" ]; then
	     echo "For type " $toto " at line : " $lineNum " field : " $fieldf
		nott=`echo  $fieldf | grep '!' | wc -l `
		if [ "$nott" -gt 0 ]; then
			notta="!"
		else
			notta=" "
		fi
		field=`echo  $fieldf | sed s/TYPE//g | sed s/string//g | sed s/int//g | sed 's/"//g' | sed 's/!//g' | sed 's/ //g' `
		fileNs=`echo  $field | cut -d"," -f1 `
		echo "for field <"$fieldf"> 1 :===: " $fileN
		relativePathPosition2=`echo $field | cut -d"," -f2`
		
		fileN=`echo  $fieldf | cut -d"," -f1 `
		echo "for field <"$fieldf"> 1 :===: " $fileN
		relativePathPosition=`echo  $fieldf | cut -d"," -f2 `
		echo "for field <"$field"> 2 :===: " $relativePathPosition
		contentString=`echo  $field | cut -d"," -f3 `
		echo "for field <"$fieldf"> 3 :=-=: " $contentString
		echo "for field <"$field"> 3 :=_=: " $contentString
		if [ "$fileNs" != "" ]; then
			if [ "$contentString" == "" ]; then
				echo "for file type " $toto " also test file existance " $fileNs " at rel position " $relativePathPosition2
				echo $toto" "$fileNs" "$relativePathPosition2 >> list_of_related_files1.txt
			else
				echo "for file type " $toto " also test file " $fileNs " at rel position " $relativePathPosition2	
				echo $toto" "$fileNs" "$relativePathPosition2 >> list_of_related_files2.txt
			fi
		fi

		lineContent=`echo  $field | cut -d"," -f4 `
		echo "for field <"$field"> 4 :===: " $lineContent
		charContent=`echo  $field | cut -d"," -f5 `
		echo "for field <"$field"> 5 :===: " $charContent

		# comment...
		echo -n "       if (debug) cout << \""$notta"test in "$fileNs"(-"$relativePathPosition2") for <"$contentString">"  >> $cppFile
		if [ "$lineContent" != "" ]; then 
		  echo -n " line: "$lineContent >> $cppFile
		fi
		if [ "$charContent" != "" ]; then 
			echo -n " char: "$charContent >> $cppFile
		fi
		echo " \" << endl;" >> $cppFile

		echo -n "       condition = condition && (">> $cppFile
		echo -n " "$notta" " >> $cppFile
		echo -n "test(currentFile, \""$fileNs"\", "$relativePathPosition2", \""$contentString"\"" >> $cppFile
		if [ "$lineContent" != "" ]; then 
		  echo -n ", "$lineContent >> $cppFile
		fi
		if [ "$charContent" != "" ]; then 
			echo -n ", "$charContent >> $cppFile
		fi
		echo ")); " >> $cppFile

	   fi
	  done < tmp_conditions_in_diff_lines.txt
	  		 echo "       condition2 = true;">> $cppFile
	  	     echo "       break; " >> $cppFile

   done
 ##     	     echo "     default:"  >> $cppFile
##			 echo "        condition2 = false;">> $cppFile
      	     echo "     }"  >> $cppFile
      	     echo "   }"  >> $cppFile

done

## Initialization
cat  uncommentedASCIIlist.txt| cut -d$'\t' -f15>curListInit.txt
./callInitializer.sh ObjTitle $cppFile2
cat  uncommentedASCIIlist.txt| cut -d$'\t' -f16>curListInit.txt
./callInitializer.sh Level $cppFile2

cat  uncommentedASCIIlist.txt| cut -d$'\t' -f18>curListInit.txt
./callInitializer.sh BasicCathegory $cppFile2
cat  uncommentedASCIIlist.txt| cut -d$'\t' -f19>curListInit.txt
./callInitializer.sh Type $cppFile2
cat  uncommentedASCIIlist.txt| cut -d$'\t' -f20>curListInit.txt
./callInitializer.sh SubType $cppFile2
cat  uncommentedASCIIlist.txt| cut -d$'\t' -f3>curListInit.txt
./callInitializer.sh fileKey $cppFile2
rm tmp_list_line_number.txt
rm tmp_conditions_in_diff_lines.txt
cat list_of_related_files1.txt | sort | uniq > list_of_related_filesTMP.txt
mv list_of_related_filesTMP.txt list_of_related_files1.txt
cat list_of_related_files2.txt | sort | uniq > list_of_related_filesTMP.txt
mv list_of_related_filesTMP.txt list_of_related_files2.txt