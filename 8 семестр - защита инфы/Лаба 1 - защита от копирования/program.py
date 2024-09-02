_test = hello world

import platform
from cryptography.fernet import Fernet

def getSysInfo():
    mach = platform.machine()
    vers = platform.version()
    proc = platform.processor()
   
    text = mach + vers + proc #type = str
    
    checkActivation(text.encode('utf-8'))

def openFile(filename):
    try:
        file = open(filename, 'rb')
    except FileNotFoundError:
        print('oops, filenotFound')
        return ""
    else:
        return file.read()

def checkActivation(text_):
    if (openFile('test.txt') != "" and openFile('test2.txt') != ""): 
        key = openFile('test.txt')
        f = Fernet(key)        
        text = openFile('test2.txt')
        dec_text = f.decrypt(text)
        convert_text = dec_text
        print(convert_text)
        print(text_)
        if (convert_text == text_):
            print('success')
        else:
            print('oops, sometimes going wrong')
        

if __name__ == "__main__":
    getSysInfo()
