In progress. To contribute, the most direct manner is to [fork this project](https://github.com/CHEMeDATA/ResearchObjectFinder/edit/master/README.md), make changes and make a pull request.
A more simple methods consits in raising issues [raising issues](https://github.com/CHEMeDATA/ResearchObjectFinder/issues/new).

## Finding Chemistry Objects 
The goal is to locate chemistry objects (chemistry structure file (.mol, .sdf, .cdx), NMR spectra in the Bruker format etc.) inside archives in the .zip format.

The demo .zip files are in located in the **data** folder
The unziped files are located in the **unzipped** folder (dont add files here - but as .tip in the data folder)

The folder **specifications** includes the criteria for each type of research object.

The identification can be done with a:
1) a file extension extension. Except if specified otherwise, the object will consist in a single file.
2) a folder with simultaneous presence of one or more files (say fid and acqus in Bruker language). The object include multiple files or all files included in a branch of the file tree.

In some cases, CO can have different levels pointing to the same files. Eg, an "nmr_analysis" can include multiple "nmr_experiments" which may include different "nmr_spectra" (different processing).

 ... to be developped ...


## Short list of Chemistry object
This is a preliminary short version of a [longer list](#long-list-of-chemistry-object) (see below) providing more complex examples.

#|Chemistry object | Criteria | Type of data |visualization
-|------|---|---|--
2|Bruker 1D <sup>1</sup>H NMR spectrum|file_name=="`1r`" & exist_file:"`../../fid`" & exist_file:"`../../acqus`" & find_line="##$NUC1= <1H>" in "`../../acqus`"|x/y plot (ppm/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
7|IR spectrum|file_name=="`*.sp`"|x/y plot (energy in nm non-homogeneous scale/intensity)|[JCAMP-DX](http://jcamp-dx.org/), simple x/y plot
8|X-ray crystallography structure|file_name=="`*.cif`"|3D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc.
9|2D molecular structure|file_name=="`*.cdx`"|2D chemistry structure visualization)|[JSmol](http://wiki.jmol.org/index.php/Main_Page), etc. after conversion!

Examples of the above-mentionned objects can be found in the files:
```
/researchdata/NMR Files per compound/3r_(R)-Me-FBn-18C6/2/pdata/1/1r
/researchdata/Other Data per compound/3n_(S)-Me-1-naphth-18C6/3n_X-Ray/3n_(S)-Me-1-naphth-18C6-NaBArF.cif
/researchdata/Other Data per compound/3n_(S)-Me-1-naphth-18C6/2nd eluted/3n_(S)-Me-1-naphth-18C6_2nd elt_FT-IR.sp 
/researchdata/Other Data per compound/3n_(S)-Me-1-naphth-18C6/3n_(S)-Me-1-naphth-18C6.cdx
```
from this [yareta record](https://yareta.unige.ch/frontend/archive/62c9dc3b-6f44-4b3b-963d-1ab31c17f6c6). 

The criteria (third column in the table) are discussed [below](#criteria). 

# Criteria
We consider (thus far) three tests functions:
- [requireFileExtension()](#file-extension) (test the presence of given file - full file name).
- [requireFileNamed()](#file-name) (test the presence of given file - full file name).
- [requireFileInclude()](#presence-of-a-specific-string-in-a-file) (test the presence of a specific string in a text file). 

See below for more details.
## File extension
The criterion is the presence of filename with a given extention (file_name=="`*.sp`"). 
Example:
```javascript
requireFileExtension("cdxml") // for the presence of ChemDrawPro file in the CML format
```
## File name
The criterion is the presence of one or more specific file.
```javascript
requireFileNamed("1r")
requireFileNamed("procs")
```
 or filename extention (file_name=="`*.sp`"). 

## Presence of associated files
In some cases, the presence of additional located at specific location relative to the reference position in the folder tree.
This is done with: 
```javascript
requireFileNamed("1r")
requireFileNamed("procs")
requireFileNamed("fid",2) // the 2 means that the file is two steps below in the file tree : ../../fid
requireFileNamed("acqus",2)
```
Note that associated files may be in a separate folder (see the number following the filename). The locations are relative to the reference folder (see above).
## Using boolean operators
Implicitly all conditions should be fulfilled ( && operator), but OR can be explicitly expressed:
This is done with: 
```javascript
requireFileNamed("1r") || requireFileNamed("2rr")
requireFileNamed("procs")
requireFileNamed("fid", 2) || requireFileNamed("ser", 2) 
requireFileNamed("acqus",2)
```

## Presence of a specific string in a file
Additional conditions may be used to refine the identification. For example the presence of a magic key or other [file signature](https://en.wikipedia.org/wiki/List_of_file_signatures). This can be used to test the value for a parameter. For example: 
```javascript
requireFileInclude("acqus",2,"##$NUC1= <13C>")  // test in the file acqus located two steps below in the tree file for a line including the given string.
requireFileInclude(CURRENT_FILE, 0, "2D", 2, 21) // searches for "2D" at line 2, characters 21 to 22 (start counting at 1) in the currently studied file (same location , therefore 0 )
```
means that a given string of characters if found in a given file.

This allows to distinguish different (sub)types of objects. Inthis specific case, to disthinguish a 1D <sup>13</sup>C NMR spectra from 1D spectra of other isotope). We need to make this distinction to make a precise list of the content of the archive.


## Presence of a specific string in a file
Sometimes a set of objects need to be put toghether. At least this is useful with NMR spectra in Bruker files.
This function allows to group together all the experiments/spectra located in the same folder
```javascript
container_name = ( "NMR analysis : " + getNamePathLevel(CURRENT_PATH,3) ); 
```
For 
```
CURRENT_PATH = "Volumes/data/studentwork/honey/25/pdata/1/" 
```
it should return `honey`.

## Long list of Chemistry object

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
  * 1D 1H spectrum
    * Fid of the above spectrum
  * 1D 13C spectrum
    * Fid of the above spectrum
  * 2D 1H-13C HSQC spectrum
    * Fid of the above spectrum
  * etc.
  
  The onthology will facilitate the generation of the criteria for a "full analysis". Instead of listing all the conditions to fullfill, it would inherit the conditions of the siblings.

- The condition for spectrum object will includes the conditions of FID
- The conditions about the "full analysis" could be defined based on the list of spectra, without needing to care about the conditions to fullfill for each spectrum.
- 1D <sup>1</sup>H,<sup>13</sup>C, etc. spectra would be a subclass of 1D spectra



The criteria (third column in the table) are discussed [below](#criteria). 

# Criteria
We consider (thus far) three tests functions:
- [file_name](#file-name) (test the presence of given file - full file name or by extension extension using wildcard).
- [exist_file](#presence-of-associated-files) (test the presence of additional files related to file_name. They may contain parameters). 
- [find_line](#presence-of-a-specific-string-in-a-file) (test the presence of a specific string in a text file). 

See below for more details.
## File name
In the simplest cases, the only criterion is the presence of a specific file (file_name=="`1r`") or filename extention (file_name=="`*.sp`"). 
## Presence of associated files
In some cases, the presence of additional files has to be tested.
This is done with: 
```
exist_file:"./procs" 
exist_file:"../../acqus" 
exist_file:"../../fid" 
```
Note that associated files may be in a separate folder (see the path before the file name). The locations are relative to the reference file (see above).
## Presence of a specific string in a file
Additional conditions may be necessary to refine the identification. For example the presence of a magic key or other [file signature](https://en.wikipedia.org/wiki/List_of_file_signatures). This can be used to test the value for a parameter. For example: 
```
find_line="##$NUC1= <13C>" in "`../../acqus`
```
means that a given string of characters if found in a give file.

This allows to distinguish different (sub)types of objects. Inthis specific case, to disthinguish a 1D <sup>13</sup>C NMR spectra from 1D spectra of other isotope). We need to make this distinction to make a precise list of the content of the archive.

## Long list of Chemistry object

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
  * 1D 1H spectrum
    * Fid of the above spectrum
  * 1D 13C spectrum
    * Fid of the above spectrum
  * 2D 1H-13C HSQC spectrum
    * Fid of the above spectrum
  * etc.
  
  The onthology will facilitate the generation of the criteria for a "full analysis". Instead of listing all the conditions to fullfill, it would inherit the conditions of the siblings.

- The condition for spectrum object will includes the conditions of FID
- The conditions about the "full analysis" could be defined based on the list of spectra, without needing to care about the conditions to fullfill for each spectrum.
- 1D <sup>1</sup>H,<sup>13</sup>C, etc. spectra would be a subclass of 1D spectra