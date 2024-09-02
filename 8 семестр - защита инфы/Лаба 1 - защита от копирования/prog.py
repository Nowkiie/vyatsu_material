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
from main import clearDir, generateRandomNumber, createZipFile




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
                display_text.set('oops, filenotFound')
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
                    display_text.set('success')
                    clearDir()
                else:
                    display_text.set('oops, sometimes going wrong')

        def changePassword(str_pass_folder):
            pyminizip.uncompress("file.zip", str_pass_folder, "", 0)
            password_folder = generateRandomNumber()
            createZipFile(password_folder)
            
            return password_folder
        
        def add_str():
            display_text.set("")
            number_id = edit_id.get()
            password = edit_passw.get()

            

            dtbs = database()
            dtbs.openConnection()
            s = dtbs.chooseId(number_id)
            if (s):
                for data in s:
                    if (data[1]==password):
                        pass_folder = str(data[2])
                        change_passw = changePassword(pass_folder)
                        dtbs.updateInfo(number_id, change_passw)
                        display_text.set("It's okay")
                    else:
                        display_text.set("Name or password is wrong")
            else:
                display_text.set("You are haven't registration")
            dtbs.closeConnection()

            dtbs = database()
            dtbs.openConnection()
            s = dtbs.chooseId(number_id)
            if (s):
                for data in s:
                    if (data[1]==password):
                        str_pass_folder = str(data[2])
                        try:
                            pyminizip.uncompress("file.zip", str_pass_folder, "", 0)
                            getSysInfo()
                        except:
                            display_text.set("Password was changed")
                    else:
                        display_text.set("Name or password is wrong")
            else:
                display_text.set("You are haven't registration")
            dtbs.closeConnection()
            


        label_otstup = tk.Label(self, text='')
        label_otstup.grid(row=5, column=0, columnspan=4, **opts)
        
        btn_add=ttk.Button(text="Log out", command = add_str)
        btn_add.grid(row=4, column=1,columnspan =2,**opts)

        
        

        
        

        


                
if __name__ == "__main__":
    app = App()
    app.title('Proga')
    app.mainloop()
