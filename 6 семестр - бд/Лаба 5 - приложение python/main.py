import tkinter as tk
from tkinter import *
from tkinter import ttk
from db import database
from tkinter.messagebox import showwarning


class App(tk.Tk):
    
    
    def __init__(self):
        super().__init__()

        opts={'ipadx':5, 'ipady':5, 'sticky':'nswe'}

        label_table = tk.Label(self, text="Таблица успеваемости студентов")
        label_table.grid(row=0,column=1, **opts) #название таблицы

        group = ["ИВТб-3301-04-00", "ИВТб-3302-04-00"]

        columns = ("id","name","surname","mid_name", "id_group", "addres")

        opts={'ipadx':5, 'ipady':5, 'sticky':'nswe'}
        
        #таблица - создание
        tree = ttk.Treeview(column=columns, show="headings")
        label_tab = tk.Label(self, text="")
        #таблица - описание
        label_tab.grid(row=4, column=0, columnspan=5, **opts)
        tree.grid(row=6, column=0,columnspan=5, sticky="nsew")
        tree.heading("id", text="№")
        tree.heading("name", text="Имя")
        tree.heading("surname", text="Фамилия")
        tree.heading("mid_name", text="Отчество")
        tree.heading("id_group", text="№ группы")
        tree.heading("addres", text="Адрес")


        #настройка выборки - функция
        def add_string():
            for i in tree.get_children():
                tree.delete(i)
            #edit_surname.delete(0, 'end')
            
            selection = combobox.current()+1
            #edit_surname.insert(0, selection)

            dtbs = database()
            dtbs.openConnection()
            s = dtbs.chooseGroup(selection)
            dtbs.closeConnection()
            
            for person in s:
                tree.insert("", END, values=person)
            
            return
        
        
        #настройка выборки - создание
        label_choose = tk.Label(self, text="Настройка выборки")
        #label_surname = tk.Label(self, text="Фамилия")
        label_name_group = tk.Label(self, text="Группа")
        #edit_surname = ttk.Entry()
        combobox = ttk.Combobox(values=group)
        btn_choose= ttk.Button(text="Применить", command=add_string)

        #настройка выборки - описание
        #label_surname.grid(row=2, column=0, **opts)
        label_name_group.grid(row=2, column=1, **opts)
        #edit_surname.grid(row=3, column=0, **opts)
        combobox.grid(row=3, column=1, **opts)
        btn_choose.grid(row =3, column=2, **opts)
        label_choose.grid(row=1,column=0, **opts)#настройка выборки
        


        #добавление записи - создание
        label_tab2 = tk.Label(self, text="")
        
        label_add = tk.Label(self, text="Добавление записи")
        label_add_name = tk.Label(self, text="Имя")
        label_add_surname = tk.Label(self, text="Фамилия")
        label_add_mid_name = tk.Label(self, text="Отчество")
        label_add_adress = tk.Label(self, text="Адрес")
        label_add_group = tk.Label(self, text="Группа")
        label_tab3 = tk.Label(self, text="")
        
        edit_add_name = ttk.Entry()
        edit_add_surname = ttk.Entry()
        edit_add_mid_name = ttk.Entry()
        edit_add_adress = ttk.Entry()

        combobox2=ttk.Combobox(values=group)

        def add_str():
            name = edit_add_name.get()
            surname = edit_add_surname.get()
            mid_name = edit_add_mid_name.get()
            adres = edit_add_adress.get()
            selection = combobox2.current()+1

            dtbs = database()
            dtbs.openConnection()
            dtbs.addPerson(name, surname, mid_name, selection, adres, 2)
            dtbs.closeConnection()

            for i in tree.get_children():
                tree.delete(i)

            dtbs = database()
            dtbs.openConnection()
            s = dtbs.getGroup()
            dtbs.closeConnection()
            
            for person in s:
                tree.insert("", END, values=person)

        

        btn_add=ttk.Button(text="добавить", command = add_str)

        opts={'ipadx':5, 'ipady':5, 'sticky':'nswe'}

        #добавление записи - описание
        label_tab2.grid(row=7, column=0, columnspan=4, **opts)
        label_add.grid(row=8, column =0, **opts)
        
        
        
        label_add_name.grid(row=9, column=0, **opts)
        label_add_surname.grid(row=9, column=1, **opts)
        label_add_mid_name.grid(row=9, column=2, **opts)
        label_add_adress.grid(row=9, column=3, **opts)
        label_add_group.grid(row=9, column=4, **opts)

        edit_add_name.grid(row=10,column=0, **opts)
        edit_add_surname.grid(row=10, column=1, **opts)
        edit_add_mid_name.grid(row=10, column=2, **opts)
        edit_add_adress.grid(row=10,column=3, **opts)
        combobox2.grid(row=10, column=4, **opts)
        btn_add.grid(row=10, column=5, **opts)
        label_tab3.grid(row=11, column =0, columnspan=5, **opts)



        def del_str():
            showwarning(title="?", message = "Вы хотите удалить строку?")
            
            selected=tree.item(tree.selection())
            person = selected['values']
            s = person[0]
            dtbs = database()
            dtbs.openConnection()
            dtbs.delPerson(s)
            dtbs.closeConnection()
            edit_add_surname.insert(0, s)

            for i in tree.get_children():
                tree.delete(i)

            dtbs = database()
            dtbs.openConnection()
            s = dtbs.getGroup()
            dtbs.closeConnection()
            
            for persons in s:
                tree.insert("", END, values=persons)

            
        #удаление - создание
        btn_del_str = ttk.Button(text="Удалить строку", command = del_str)
        btn_del_str.grid(row=8, column =4, **opts)
        
        
        
        
        #начальный вывод
        dtbs = database()
        dtbs.openConnection()
        s = dtbs.getGroup()
        dtbs.closeConnection()
        for person in s:
            tree.insert("", END, values=person)

        


                
if __name__ == "__main__":
    app = App()
    app.mainloop()
