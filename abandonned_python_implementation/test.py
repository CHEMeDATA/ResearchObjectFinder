import os
for root, dirs, files in os.walk("./unziped"):
    for file in files:
        if file.endswith(".txt"):
             print("found "),
             print(os.path.join(root, file)),
             print("in"),
             print(os.path.join(root))
