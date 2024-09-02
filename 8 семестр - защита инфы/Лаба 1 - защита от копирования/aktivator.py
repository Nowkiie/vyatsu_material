import platform
from cryptography.fernet import Fernet
import subprocess
import pyminizip
import random
import os

def writeInfoToFile(filename, text, mode):
    file = open(filename, mode)
    file.write(text)
    file.close()
    

def getSysInfo():
    mach = platform.machine()
    vers = platform.version()
    proc = platform.processor()
    
    text = mach + vers + proc
    text_decod = text.encode('utf-8')
    writeInfoToFile('test2.txt', text_decod, 'wb')
    

def generateKey():
    key = Fernet.generate_key()
    f = Fernet(key)
    writeInfoToFile("test.txt",key, 'wb')
    

def decryptFile():
    with open ('test.txt', 'rb') as keyfile:
        key = keyfile.read()

    with open('test2.txt', 'rb') as file:
        f = Fernet(key)
        text = file.read()
        dec_text = f.decrypt(text)
        print(dec_text.decode())

def encryptFile():
    with open('test.txt', 'rb') as filekey:
        key = filekey.read()

    with open("test2.txt", "rb") as file:
        f = Fernet(key)
        text = file.read()
        enc_text = f.encrypt(text)
        writeInfoToFile("test2.txt",enc_text, 'wb')

def generateRandomNumber():
    return random.randint(256, 541628)
        
def createZipFile():
    gener_password = generateRandomNumber()
    print(gener_password)
    pyminizip.compress_multiple([u'test.txt', 'test2.txt'], [u'', u''], "file.zip", str(gener_password), 4)

def changePassword():
    createZipFile()

def clearDir():
    os.remove('test.txt')
    os.remove('test2.txt')

if __name__ == "__main__":
    generateKey()
    getSysInfo()
    encryptFile()
    decryptFile()
    #subprocess.run(["attrib","+H","test.txt"],check=True)
    #subprocess.run(["attrib","+H","test2.txt"],check=True)
    createZipFile()
    clearDir()
    
                    


