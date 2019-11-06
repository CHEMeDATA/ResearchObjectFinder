# ResearchObjectFinder
develop method to identify reserch objects (RO) within archive files

The goal here is to locate research objects (chemistry structure file (.mol, .sdf, .cdx), NMR spectra in the Bruker format etc.) inside archives in the .zip format.

The demo .zip files are in located in the **data** folder
The unziped files are located in the **unzipped** folder (dont add files here - but as .tip in the data folder)

The folder **specifications** includes the criteria for each type of research object.

A RO can be a file with a:
1) files with a given extension. (in some cases, the first line of the file gives more details !? .cdx about version.... ?!)
2) a folder with simultaneous presence of given files (say fid and acqus in Bruker language)

In some cases, RO can have different levels pointing to the same files. Eg, an "nmr_analysis" can include multiple "nmr_experiments" which may include different "nmr_spectra" (difference processing).
