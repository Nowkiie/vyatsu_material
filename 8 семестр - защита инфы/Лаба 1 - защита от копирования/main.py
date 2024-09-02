import tkinter as tk
from tkinter import *
from tkinter import ttk
from db import database
from tkinter.messagebox import showwarning
import random
import platform
from cryptography.fernet import Fernet
import subprocess
import pyminizip
import os

def generateRandomNumber():
    return random.randint(256, 541628)


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

def createZipFile(gener_password):
    pyminizip.compress_multiple([u'test.txt', 'test2.txt'], [u'', u''], "file.zip", str(gener_password), 4)

def changePassword():
    createZipFile()

def clearDir():
    os.remove('test.txt')
    os.remove('test2.txt')

class App(tk.Tk):
    
    
    def __init__(self):
        super().__init__()

        
        
        opts={'ipadx':4, 'ipady':4, 'sticky':'nswe'}

        label_id = tk.Label(self, text= "Name:")
        label_id.grid(row=0, column = 1, **opts)

        edit_id = ttk.Entry()
        edit_id.grid(row=0, column=2, columnspan=1, **opts)

        label_otstup = tk.Label(self, text='')
        label_otstup.grid(row=1, column=0, columnspan=4, **opts)
        
        label_passw = tk.Label(self, text="Password")
        label_passw.grid(row=2, column =1, **opts)
        
        edit_passw = tk.Entry()
        edit_passw.grid(row=2, column =2, columnspan=1, **opts)

        label_otstup = tk.Label(self, text='')
        label_otstup.grid(row=3, column=0, columnspan=4, **opts)

        display_text = tk.StringVar()
        label_info = tk.Label(self, textvariable=display_text)
        label_info.grid(row=6, rowspan=2, column=0, columnspan=4, **opts)
        

       
        
        def add_str():
            display_text.set("")
            number_id = edit_id.get()
            password = edit_passw.get()
            password_folder = generateRandomNumber()

            dtbs = database()
            dtbs.openConnection()
            s = dtbs.chooseId(number_id)
            print(len(s))
            if (s):
                print("found")
                display_text.set("This name is already exist. Change name")
            else:
                s = dtbs.addPerson(number_id, password, password_folder)
                display_text.set("Registration is gone succesfully")
                generateKey()
                getSysInfo()
                encryptFile()
                decryptFile()
                createZipFile(password_folder)
                clearDir()
            dtbs.closeConnection()

            


        label_otstup = tk.Label(self, text='')
        label_otstup.grid(row=5, column=0, columnspan=4, **opts)
        
        btn_add=ttk.Button(text="Registration", command = add_str)
        btn_add.grid(row=4, column=1,columnspan =2,**opts)

        
        

        
        

        


                
if __name__ == "__main__":
    app = App()
    app.title('Регистрация')
    app.mainloop()


