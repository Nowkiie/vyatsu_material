import tkinter as tk
from tkinter import *
from tkinter import filedialog as fd
from PIL import Image, ImageTk
import os


class PyPhotoEditor:
    def __init__(self):
        self.root = Tk()
        self.init()

    def init(self):
        self.root.title("Py Photo Editor")

        self.root.bind("<Escape>",self._close) #не работает, исправить

    def run(self):
        self.draw_menu()
        self.draw_widgets()

        self.root.mainloop()

    def draw_menu(self):
        menu_bar = Menu(self.root)

        file_menu = Menu(menu_bar,tearoff=0)
        
        file_menu.add_command(label="Открыть", command=self.open_new_image)
        file_menu.add_command(label="Сохранить", command=self.save_image)
        file_menu.add_command(label="Выйти",command=self._close)
        menu_bar.add_cascade(label="Файл", menu=file_menu)
        
        edit_menu = Menu(menu_bar,tearoff=0)

        transform_menu = Menu(edit_menu,tearoff=0)
        transform_menu.add_command(label="Повернуть на 90 влево", command =self.rotate_image(-90))
        
        

        self.root.configure(menu=menu_bar)

    def draw_widgets(self):
        pass

    def open_new_image(self):
        global need
        image_path = fd.askopenfilename(filetypes=(("Images","*.jpeg;*.jpg;*.png"),))
        need = Image.open(image_path)
        image = ImageTk.PhotoImage(need)
        image_panel = Label(self.root,image = image)
        image_panel.image = image
        image_panel.pack()

    def save_image(self):  
        filename = fd.asksaveasfilename()
        if filename:
            need.save(str(filename) + '.jpg', 'JPEG')

    def rotate_image(self, degrees): #передаем кол-во градусов
        global need
        im_rotate = need.rotate(degrees)
        image = ImageTk.PhotoImage(im_rotate)
        image_panel = Label(self.root,image = image)
        image_panel.image = image
        image_panel.pack()

    def _close(self):
        self.root.destroy()

    

if __name__ == "__main__": #является ли текущий файл запускаемым
    PyPhotoEditor().run()
