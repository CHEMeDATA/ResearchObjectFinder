import os
for root2, dirs2, files2 in os.walk("./specifications"):
    for file2 in files2:
        if file2.endswith(".spec"):
             print("In "),
             toto = os.path.join(root2, file2)
             print(toto),
             print("found:")
             with open(toto, "r") as fp:
              lines = []
              for line in fp:
               print(line),
               lines.append(line)
               v=line
              fp.close()
             nb_files = 0
             for root, dirs, files in os.walk("./unziped"):
                  for file in files:
                   count = 0
                   count2 = 0
                   for line in lines:
                    count = count + 1
                    if line.startswith("*"):
                     if file.endswith(line[2:len(line)-1]):
                       print("found1 "),
                       print(os.path.join(root, file)),
                       print("in"),
                       print(os.path.join(root))
                       count2 = count2 + 1
                    else:
                      if file.find(line):
                       print("found2 "),
                       print(os.path.join(root, file)),
                       print("in"),
                       print(os.path.join(root))
                       count2 = count2 + 1  

