import random
import pyminizip
import os

def uncompressZip():
    pyminizip.uncompress("file.zip", "537112", "", 0)

def generateRandomNumber():
    return random.randint(256, 541628)

def createZipFile():
    gener_password = generateRandomNumber()
    print(gener_password)
    pyminizip.compress_multiple([u'test.txt', 'test2.txt'], [u'', u''], "file.zip", str(gener_password), 4)

def changePassword():
    createZipFile()



if __name__ == "__main__":
    uncompressZip()
    #changePassword()
