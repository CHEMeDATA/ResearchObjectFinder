# ResearchObjectFinder
develop method to identify chemistry objects (CO) within archive files

## Chemistry objects
This is a tentative list of objects and relations.
- 1) Compound
  - Types
    - Formula
    - 2D structure in file (.mol .cdx .dcxml)
    - 3D mol file (.mol .out from gaussian09, *etc.*)
    - image of any of the above
  - Properties
    - Has a formula (always)
    - Has an INCHI (always)
    - Has a list of atoms (always can it be explicit? Always?  Even for diastereotopic H of structure with implicit H?)
    - Has a list of bonds (always ? from mol file? or from xray for structure in solid?)
    - Has an origin link to (article, thesis, website communication, database, ? // with DOI ?)
    - Has an reference into to above-mentionned (article, thesis, website communication, database, ? // with DOI ?) For example compound 1.
    - Is shown in Figure... into to above-mentionned (article, thesis, website communication, database, ? // with DOI ?) For example compound 1.
    - Is mentionned at page ... into to above-mentionned (article, thesis, website communication, database, ? // with DOI ?) For example compound 1.
    - Characterization (NMR, MS, etc... )
        - has predicted chemical shifts? Is this embedded chemical property?
        - has chemical shifts
          - has assigned chemical shifts ? (for visualization...)
          - just text of chemical shifts?
        - has experimental J-coupling constants ? (for visualization...)
      - explicit link to atoms of the molecules canonical numbering of H and C?
    - NMR characterization - is this part of the compound properties - make the reciprocal link to the assignment (see below)? 
- 2) Chemical property, spectra, etc.
  - Types
    - Melting point
    - NMR spectrum (the post processing part)
    - NMR experiment (the pre processing part)
    - IR spectrum 
    - Image of the spectrum
  - Properties
    - From:to x_axis (for all spectra)
    - From:to additional dimension in 2D NMR (not always)
    - Units (for each dimension) (always)
    - peaks (not always) peak may have additional features... coupling structures, etc.
    - for NMR, essential property is Larmor....
    - Assignment
  - metadata 
    - instrument, date of acquisition )
    - Associated publication ? (is this part of the spectrum property - make reciprocal link to the publication)
    - Associated compound ? (is this part of the spectrum property - make reciprocal link to the assignment)
- Assignment (only necessary if includes some detail - if just this spectrum corresponds to this molecule, link may be in the spectrum/compound object ?? Or always, because this is a link)
  - Properties
    - has one (or more - if mixture) molecules
      - just link to .mol file?
    - has one or more spectra.
      - just link to spectrum object file?
    - Collection of links of:
      - Property of spectrum (peak) to a property of Compound (atom for NMR - bound for IR - fragment for MS)
    - metadata 
      - date?
      - computer/algo/operator?
      - correction/addition to other assignemnt?

A full NMReDATA records could create:
- one molecule(or more if mixture) 
- one spectrum per spectrum mentionned in the NMR record, and 
- one/multiple assignment ? (one per spectrum, one for the whole NMR - one for all analitics of a compound?)

NMReDATA includes multiple ontologies:
-The core assignment (chemical shift and coupling (agregated) linked to atom number in molecule.
-ontology of single-spectrum description
-ontology of a 1D signal
-ontology of a 2D signal

## Working with Chemistry Objects 
The goal here is to locate chemistry objects (chemistry structure file (.mol, .sdf, .cdx), NMR spectra in the Bruker format etc.) inside archives in the .zip format.

The demo .zip files are in located in the **data** folder
The unziped files are located in the **unzipped** folder (dont add files here - but as .tip in the data folder)

The folder **specifications** includes the criteria for each type of research object.

A CRO can be a file with a:
1) files with a given extension. (in some cases, the first line of the file gives more details !? .cdx about version.... ?!)
2) a folder with simultaneous presence of given files (say fid and acqus in Bruker language)

In some cases, CO can have different levels pointing to the same files. Eg, an "nmr_analysis" can include multiple "nmr_experiments" which may include different "nmr_spectra" (difference processing).

