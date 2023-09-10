
file = open("testFile.txt", "w")

line : str = ""

for i in range(1000):
    line += 'a'

file.write(line)
file.close()
