# Specifications of chemisty objects 
List of properties of chemistry objects are in this (very ugly) [mainClassification.xlsx](mainClassification.xlsx) file.
It is converted (after some manual work...  - this is work in progress...) into lists of criteria that can be used to program object finders in different languages.

For now, it exists only for C++.
# Generation of code  

The code including the criteria applied for the identification of chemistry objects is generated using:
```
cd specifications
./compileList.sh
cd ..

```

## C++ implementation
The files [forCprog.txt](forCprog.txt) and [forCprogInit.txt](forCprogInit.txt) are included (using `#include ...`) in the C++ program ([listChemObjects.cpp](../src/cpp/listChemObjects.cpp)). More details in the [C++](../src/cpp/README.md) implementation page.
