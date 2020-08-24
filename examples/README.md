# Listing chemistry objects

Clone [this repository](https://github.com/CHEMeDATA/ResearchObjectFinder).

Store the archive files (.zip) in the `data` folder. (For example this [yareta record](https://yareta.unige.ch/frontend/archive/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6).)

If the program has been compiled for your system (see [src/cpp](../src/cpp/README.md) `src/cpp/README.md`) a list of the chemistry objects will be generated and stored in the `data/` folder with :
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
#### Example of Json file

[demo_archive_yareta.json on GihHub](https://github.com/CHEMeDATA/ResearchObjectFinder/blob/master/examples/demo_archive_yareta.json) (crude data).


[demo_archive_yareta.json](demo_archive_yareta.json) (This file may be reformated by the browser).

Note that only some of these objects are worth being listed to a visitor of the repository.