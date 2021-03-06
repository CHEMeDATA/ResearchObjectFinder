# Listing chemistry objects

Clone [this repository](https://github.com/CHEMeDATA/ResearchObjectFinder).

Store the archive files (.zip) you want to list the chemistry objets from in the `data` folder. (For example this [yareta record](https://yareta.unige.ch/frontend/archive/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6).)

If the program has been compiled for your system (see [src/cpp](../src/cpp/README.md) `src/cpp/README.md`) a list of the chemistry objects will be generated and stored in the `data/` folder with this bash script:
```
src/bash/generateChemistryObjects.bash
```
## More details 

The chemisty objects are generated in two steps.

### 1 Extraction of the relevant files from the archive file

The first step uses a shell script (`src/bash/unzipRelevant.bash`) extracting the list of files. It generates a lists of the relevant files in the "_listFiles.txt" file located in the `data` folder. In some cases the second step will need to read the content of some of the files (to test of presence of a keyword, for example). In this case the script will extract the file and store it in the `unziped` folder, otherwise it will just create an empty file.

Usage: 

```
cd data
../src/bash/unzipRelevant.bash
cd ..
```

### 2 Analysis of the relevant files 

The analysis uses the C++ program `src/cpp/listChemObjects.cpp`.

It includes tests to identify chemistry objects.

The criteria for the identification of chemistry objects are included in the program (see [specifications](../specifications/README.md)).
It generates Json, but other formats could be easily generated - Just 
[submitting a ticket](https://github.com/CHEMeDATA/ResearchObjectFinder/issues/new).
#### Analysis of the data

The compiled C++ program reads the relevant files and generates the list of chemisty objects as a json: 

Examples of generation of .json output from a list of files:
```
src/cpp/listChemObjects.o data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6.zip_listFiles.txt "" unziped/
src/cpp/listChemObjects.o data/prepareYaretaFolderNasca_phyto.zip_listFiles.txt "" unziped/
```
The output can be redirected into a file:
```
src/cpp/listChemObjects.o data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6.zip_listFiles.txt "" unziped/ > examples/demo_archive_yareta.json
```
This will also create a xml file which can be used to make html (second line)
```
src/cpp/listChemObjects.o data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6.zip_listFiles.txt "" unziped/ ./out.xml >out.json
xsltproc src/xmltStylesheet/stylesheet.xml out.xml > doc/index.html
```
#### Example of Json file

[demo_archive_yareta.json on GihHub](https://github.com/CHEMeDATA/ResearchObjectFinder/blob/master/examples/demo_archive_yareta.json) (crude data).

[demo_archive_yareta.json](demo_archive_yareta.json) (This file may be reformated by the browser).

After [converting](https://www.freeformatter.com/json-to-xml-converter.html) the json to xml and using the xml to [generate](https://www.freeformatter.com/xsd-generator.html) xsd we get the following schema:
```xml
<xs:schema attributeFormDefault="unqualified" elementFormDefault="qualified" xmlns:xs="http://www.w3.org/2001/XMLSchema">
  <xs:element name="root" type="rootType"/>
  <xs:complexType name="rowType">
    <xs:sequence>
      <xs:element type="xs:string" name="objTitle"/>
      <xs:element type="xs:string" name="basicCategory"/>
      <xs:element type="xs:string" name="type"/>
      <xs:element type="xs:string" name="subType"/>
      <xs:element type="xs:string" name="fileKey"/>
      <xs:element type="xs:byte" name="level"/>
      <xs:element type="xs:string" name="file"/>
    </xs:sequence>
  </xs:complexType>
  <xs:complexType name="rootType">
    <xs:sequence>
      <xs:element type="rowType" name="row" maxOccurs="unbounded" minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>
</xs:schema>
```

Note that only some of these objects are worth being listed to a visitor of the repository.

[show examples of output](../doc/index.html)


get doi only:
```
xsltproc src/xmltStylesheet/stylesheetOnlydoi.xml /Volumes/san256/users_for_mac_system_macPro/jeannerat/mygit/djeanner/ResearchObjectFinder/unziped/data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6/dlcm.xml
```

get doi and author information :
```
xsltproc src/xmltStylesheet/stylesheetheader.xml /Volumes/san256/users_for_mac_system_macPro/jeannerat/mygit/djeanner/ResearchObjectFinder/unziped/data/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6/dlcm.xml
```


See also our [ontology page](https://chemedata.github.io/ontologies/).