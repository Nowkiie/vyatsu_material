import pyminizip
import platform
from cryptography.fernet import Fernet

#pyminizip.compress_multiple([u'test.txt', 'test2.txt'], [u'', u''], "file.zip", "1233", 4)

#pyminizip.uncompress("file.zip", "1233", "", 0)

def writeInfoToFile(filename, text, mode):
    file = open(filename, mode)
    file.write(text)
    file.close()

def aktivate():
    sysInfo = lambda : str(platform.machine()+platform.processor()+platform.version())

    key = Fernet.generate_key()
    f = Fernet(key) 
    writeInfoToFile('tes.txt', 'gfdaf', 'w')
    
    print(sysInfo())

def createZipFile():
    pyminizip.compress_multiple([u'test.txt', 'test2.txt'], [u'', u''], "file.zip", "1233", 4)
    

if __name__ == "__main__":
    aktivate()
