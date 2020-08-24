# Specifications of chemisty objects 
List of properties of chemistry objects are in the .xlsx file.
They converted into lists of criteria that can be used for different languages.
For now, it exsits only for C++.
# Generation of code including criteria 


Thes files are generated using:
```
cd specifications
./compileList.sh
cd ..

```

## C++ implementation
The files [forCprog.txt](forCprog.txt) and [forCprogInit.txt](forCprogInit.txt) are included (using `#include ...`) in the C++ program ([src/cpp](../src/cpp/README.md).
