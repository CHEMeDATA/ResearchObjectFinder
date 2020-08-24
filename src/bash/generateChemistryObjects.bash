
echo "**********************************"
echo "*********** step 1  **************"
echo "**********************************"
echo "running src/bash/unzipRelevant.bash from data/"
cd data
../src/bash/unzipRelevant.bash
cd ..

echo "**********************************"
echo "*********** step 2  **************"
echo "**********************************"

for file in `ls data/*.zip_listFiles.txt `;do
    echo "Calling src/cpp/listChemObjects.o for " $file ". Output in " $file.json
	src/cpp/listChemObjects.o $file "" unziped/ > $file.json
done  

echo "Done!"
