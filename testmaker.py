

with open("noCorruption.txt", "w", encoding = "utf-8") as file:
    line : str = ""
    for j in range(255):
        
        for i in range(255):
            charASCII = i % 128
            if (charASCII == ord("\n") or (charASCII >= ord("0") and charASCII <= ord("9"))):
                continue
            line += chr(charASCII)
            line += ' '
        line += '\n'
    file.write(line)

