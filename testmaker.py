

with open("linesOfAll.txt", "w", encoding = "utf-8") as file:
    line : str = ""
    for i in range(255):
        charASCII = i % 128
        if (charASCII == ord("\n") or (charASCII >= ord("0") and charASCII <= ord("9"))):
            continue
        line += chr(charASCII)
    file.write(line)

