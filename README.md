
## Finding Chemistry Objects 
The goal is to locate chemistry objects such as chemical structure (.mol, .sdf, .cdx files), NMR spectra in the Bruker format *etc.* inside archives in the .zip format.
This will allow to list them, propose a preview, allow selective upload, *etc.* in short: make the content of the .zip file searchable.

## Short list of Chemistry object
This is a preliminary short version of a [longer list](#long-list-of-chemistry-object) (see below) providing more complex examples.

#|Chemistry object | Criteria | Type of data |visualization
-|------|---|---|--
2|Bruker 1D <sup>1</sup>H NMR spectrum|require(`1r`) & require(`procs`) & require(`fid`,2) & require(`acqus`,2)|x/y plot (ppm/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
7|IR spectrum|require(`.sp`)|x/y plot (energy in nm non-homogeneous scale/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
8|X-ray crystallography structure|require(`.cif`)|3D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc.
9|2D molecular structure|require(`.cdx`)|2D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc. after conversion!

Examples of the above-mentionned objects can be found in the files:
```
/researchdata/NMR Files per compound/3r_(R)-Me-FBn-18C6/2/pdata/1/1r
/researchdata/Other Data per compound/3n_(S)-Me-1-naphth-18C6/3n_X-Ray/3n_(S)-Me-1-naphth-18C6-NaBArF.cif
/researchdata/Other Data per compound/3n_(S)-Me-1-naphth-18C6/2nd eluted/3n_(S)-Me-1-naphth-18C6_2nd elt_FT-IR.sp 
/researchdata/Other Data per compound/3n_(S)-Me-1-naphth-18C6/3n_(S)-Me-1-naphth-18C6.cdx
```
From this [yareta record](https://yareta.unige.ch/frontend/archive/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6). Store the zip files in the data folder and the unziped data in the "unziped" folder.

The criteria (third column in the table) are discussed [below](#criteria). 

## Criteria
We consider (thus far) three tests functions:
- [requireFileExtension()](#file-extension) (test the presence of given file - full file name).
- [requireFileNamed()](#file-name) (test the presence of given file - full file name).
- [requireFileInclude()](#presence-of-a-specific-string-in-a-file) (test the presence of a specific string in a text file). 

See below for more details.
### File extension
The criterion may be a given extention.

Examples:
```javascript
requireFileExtension(currentFile, ".cdxml") // for the presence of ChemDrawPro file in the CML format
requireFileExtension(currentFile, ".sp") // for the presence of ChemDrawPro file in the CML format
```
### File name
The criterion may be the presence of one or more specific file(s).
```javascript
requireFileNamed(currentFolder, "1r")
requireFileNamed(currentFolder, "procs")
```
Implicitly all conditions should be fulfilled.
#### Associated files
In some cases, the presence of additional files located at specific location relative to the reference position in the folder tree.
For example a 1D Bruker spectrum should fullfil all these conditions: 
```javascript
requireFileNamed(currentFolder, "1r")
requireFileNamed(currentFolder, "procs")
requireFileNamed(currentFolder, "fid",2) // the 2 means that the file is two steps below in the file tree : ../../fid
requireFileNamed(currentFolder, "acqus",2)
```
Note that associated files may be in a separate folder (see the number following the filename). The locations are relative to the reference folder.

### Presence of a specific string in a file
Additional conditions may be used to refine the identification. For example the presence of a magic key or other [file signature](https://en.wikipedia.org/wiki/List_of_file_signatures). This can be used to test the value for a parameter. 

For example, to test if the detected isotope is carbon-13: 
```javascript
requireFileInclude(currentFolder, "acqus",2,"##$NUC1= <13C>")  // test in the file acqus located two steps below in the tree file for a line including the given string. 
```
For example, to test if the structure in a .mol file is 2D or 3D: 
```javascript
requireFileInclude(currentFolder, 0, "2D", 2, 21) // searches for "2D" at line 2, characters 21 to 22 
requireFileInclude(currentFolder, 0, "3D", 2, 21) // searches for "3D" at line 2, characters 21 to 22 
```

This allows to distinguish different (sub)types of objects. In this specific case, to disthinguish a 1D <sup>13</sup>C NMR spectra from 1D spectra of other isotope). We need to make this distinction to make a precise list of the content of the archive. (For eg. it makes no sense to overlap <sup>1</sup>H and <sup>13</sup>C spectra, the two should be distinguised)
## Other operations
### Using boolean operators
 Using boolean operators
Implicitly all conditions should be fulfilled ( && operator between the lines), but other logical operators can be used:
For a Bruker spectrum (1D or 2D): 
```javascript
(requireFileNamed(currentFolder, "1r") || requireFileNamed(currentFolder, "2rr"))
requireFileNamed(currentFolder, "procs")
(requireFileNamed(currentFolder, "fid", 2) || requireFileNamed(currentFolder, "ser", 2) )
requireFileNamed(currentFolder, "acqus",2)
```
### Determine location in path
Sometimes a set of objects need to be put toghether. At least this is useful with NMR spectra in Bruker files.
This function allows to group together all the experiments/spectra located in the same folder
```javascript
container_name = ( "NMR analysis : " + getNamePathLevel(currentFolder,3) ); 
```
For 
```
CURRENT_PATH = "Volumes/data/studentwork/honey/25/pdata/1/" 
```
getNamePathLevel() should return `honey`.
### Starting point in file tree of complex objects
Sometimes a complex objects should include all the files included in a branch
This function allows to point to the root of the branch to include
```javascript
pathRoot = getNamePathUptoLevel(currentFolder,3); 
```
For 
```
CURRENT_PATH = "/data/studentwork/honey/25/pdata/1/" 
```
it should return `/data/studentwork/honey/`.

## Long list of Chemistry object

To be extendend ...

#|Chemistry object | Criteria | Type of visualization
-|------|---|---
1|Bruker 1D NMR FID|file_name:"fid" & exist_file:"`./acqus`"|x/y plot (time/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
2|Bruker 1D NMR spectrum (generic)|C1=[file_name=="1r" & exist_file:"../../fid" & exist_file:"../../acqus"]|x/y plot (ppm/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
3|Bruker 1D <sup>1</sup>H NMR spectrum|C1 & find_line="##$NUC1= <1H>" in "`../../acqus`"|x/y plot (<sup>1</sup>H ppm/intensity/integrals)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
4|Bruker 1D <sup>13</sup>C NMR spectrum|C1 & find_line="##$NUC1= <13C>" in "`../../acqus`"|x/y plot (<sup>1</sup>1H ppm/intensity/peak picking)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
5|Bruker 2D NMR spectrum(generic)|C2=[file_name=="2rr" & exist_file:"../../ser" & exist_file:"`../../acqus`" & & exist_file:"`../../acqu2s`"]|mesh plot (ppm/ppm/intensity)|[2D JCAMP-DX](http://jcamp-dx.org/), ??
6|Bruker 2D NMR HSQC spectrum|C2 & find_line="##$NUC1= <13C>" in "../../acqus" & find_line="##$NUC2= <1H>" in "`../../acqus`"|mesh plot (ppm/ppm/intensity)|[2D JCAMP-DX](http://jcamp-dx.org/), ??
7|IR spectrum|file_name=="`*.sp`"|x/y plot (energy in nm non-homogeneous scale/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
8|X-ray crystallography structure|file_name=="`*.cif`"|3D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc.
9|2D molecular structure|file_name=="`*.cdx`"|2D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc. after conversion!
10|2D molecular structure|file_name=="`*.mol`" & presence of "2D" at specific location in the file|2D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc.
11|3D molecular structure|file_name=="`*.mol`"  & presence of "3D" at specific location in the file|3D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc.

The list of examples is quite preliminary and (purposively) uneven and (in some cases incomplete). The aim is only to show the underlying ontology which should be defined (possibly using [OWL](https://www.w3.org/TR/owl2-primer/)?).

## Chemistry Objects Ontology

Why an ontology:

In chemistry (for example), we often record the "Full analysis" of compounds. It is composed of a set of experiment, which are themself composed of smaller elements (FID's that are processed into spectra).

* Full analysis 
  * 1D <sup>1</sup>H spectrum
    * Fid of the above spectrum
  * 1D <sup>13</sup>C spectrum
    * Fid of the above spectrum
  * 2D <sup>1</sup>H-<sup>13</sup>C HSQC spectrum
    * Fid of the above spectrum
  * etc.
  
  The ontology will facilitate the generation of the criteria for a "full analysis". Instead of listing all the conditions to fulfill, it would inherit the conditions of the siblings.

- The condition for spectrum object will includes the conditions of FID
- The conditions about the "full analysis" could be defined based on the list of spectra, without needing to care about the conditions to fulfill for each spectrum.
- 1D <sup>1</sup>H,<sup>13</sup>C, etc. spectra would be a subclass of 1D spectra


## Installation of the demo 

## Get data for the demo

The input should be located in the **data** folder. 

You can get a demo zip using your browser, or, it the file is directly accessible with:
```javascript
cd data
wget ... // not directly accessible use your browser to get it from this page: 

```

The unziped files should be located in the **unziped** folder.

The folder [**specifications**](https://github.com/CHEMeDATA/ResearchObjectFinder/tree/master/specifications) includes the criteria for each type of research object.

The identification can be done with a:
1) file with a specific file extension. 
2) a folder where a set of test about the presence of multiple files (say fid and acqus in Bruker language) is satisfied. 

The object may include multiple files or all files included in a branch of the file tree.

The output is:

**In progress.** If you want to contribute, the most direct manner is to [fork this project](https://github.com/CHEMeDATA/ResearchObjectFinder/edit/master/README.md), make changes and make a pull request.
A more simple methods consits in [submitting a ticket](https://github.com/CHEMeDATA/ResearchObjectFinder/issues/new). All contributions are welcome!

[examples](examples/README.md)