import os
for root, dirs, files in os.walk("./unziped"):
    path = root.split(os.sep)
    for file in files:
        print((len(path)-2) * '-'),
        print(file)