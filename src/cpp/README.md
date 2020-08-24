# Compilation

The files `specifications/forCprog.txt` and `specifications/forCprogInit.txt` are included (using `#include ...`) includes the criteria using to identify chemistry objects.

If the "ontology" is changed, call the generator of these files (see [specifications](specifications/README.md)) and recompile.

Use your favorite C compiler (clang/cpp/gpp, *etc.*).
```
cd src/cpp
clang++ listChemObjects.cpp -o listChemObjects.o 
cd ../..

```
# Usage

See [examples](examples/README.md).