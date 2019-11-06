import os
for root2, dirs2, files2 in os.walk("./specifications"):
    for file2 in files2:
        if file2.endswith(".spec"):
             print("found "),
             print(os.path.join(root2, file2))
             toto = os.path.join(root2, file2)
             print(toto)
             
             with open(toto, "r") as fp:
              lines = []
              for line in fp:
               print("in file...")
               print(line)
               lines.append(line)
               v=line
              fp.close()
             print(lines)
             for root, dirs, files in os.walk("./unziped"):
                   for file in files:
                     if file.endswith(".txt"):
                       print("found "),
                       print(os.path.join(root2, file2)),
                       print("in"),
                       print(os.path.join(root2))
