from random import randint
from random import random 

FILE_NAME : str = "possible3"
dimensions = (2000, 2000) # Line Count, Line Size (in terms of numbers)
injectLineSize = 3000
fakeLineChance = 0.1 # 0...fakeLineChance is pulled, and 


def makeNumbers(size : int = dimensions[1]) -> list:
    numData : list = list()
    for i in range(size):
        numData.append(randint(0, 255))
    
    return numData

def corruptLine(numData : list, injected : str) -> str:
    line : str = ""
    dataSize : int = len(numData)
    injectSize = len(injected)
    injectPosition = 0

    for dataIdx in range(dataSize):

        maxPossibleNumInsert = injectSize - injectPosition - (dataSize - dataIdx - 1)
        numCharInsert = 1 

        if maxPossibleNumInsert > 1:
            numCharInsert = randint(1 if dataIdx > 0 else 0, maxPossibleNumInsert)
        
        line += injected[injectPosition : injectPosition + numCharInsert + 1] 
        line += str(numData[dataIdx])
        injectPosition += injectPosition + 1

    line += injected[injectPosition:]
    return line

def makeInjectionStr(size : int = injectLineSize) -> str:
    line : str = ""
    for i in range(size):
        ch : str = chr(randint(0, 255))
        while ch.isnumeric() or ch == '\n':
            ch : str = chr(randint(0, 255))
        
        line += ch
    return line 

# MAIN
with open(FILE_NAME + ".txt", "w", encoding = "utf-8") as file, open(FILE_NAME + "ANSWER.txt", "w", encoding = "utf-8") as fileAns:
    realLine = makeInjectionStr()
    seen : set = {realLine}
    for lineCount in range(dimensions[0]):

        # print("Line", lineCount)
        # Write in a bunch of fake lines
        while (random() < fakeLineChance):
        #     print("Add Fake Line")
            fakeLineData : list = makeNumbers()
            fakeInject : str    = makeInjectionStr()
            while fakeInject in seen:
                fakeInject : str = makeInjectionStr()
            fakeLine : str = corruptLine(fakeLineData, fakeInject) + "\n"
            file.write(fakeLine)
        #     print("Fake Line:", fakeLine)
        
        # Make the real line
        # print("Add Real Line")
        numData  = makeNumbers() 
        injected = makeInjectionStr()
        line     = corruptLine(numData, realLine) + "\n"

        for num in numData:
            fileAns.write(str(num) +" ")
        fileAns.write("\n")
        # print("Real Line", line)
        file.write(line)

        

# with open("singleWithDigits.txt", "w", encoding = "utf-8") as file:
#     line : str = ""
#     for j in range(1):
        
#         for i in range(255):
#             charASCII = i
            
#             if (charASCII == ord("\n") or (charASCII >= ord("0") and charASCII <= ord("9"))):
#                 continue
            
#             line += chr(charASCII)
#             if (randint(0, 3) == 0):
#                 line += str(randint(0, 255))
#         line += '\n'
#     file.write(line)

