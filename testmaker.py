from random import randint

with open("singleWithDigits.txt", "w", encoding = "utf-8") as file:
    line : str = ""
    for j in range(1):
        
        for i in range(255):
            charASCII = i
            
            if (charASCII == ord("\n") or (charASCII >= ord("0") and charASCII <= ord("9"))):
                continue
            
            line += chr(charASCII)
            if (randint(0, 3) == 0):
                line += str(randint(0, 255))
        line += '\n'
    file.write(line)

