import postgresql
from postgresql import exceptions

class database:
        
    _connection = None

    _db_url = "pq://postgres:74771@localhost:5432/lab"

    def openConnection(self):
        try:
            self._connection = postgresql.open(self._db_url)
            print("Подключено")
        except postgresql.exceptions.AuthenticationMethodError: # неподдерживаемый тип авторизации
            print("Ошибка! Неподдерживаемый тип авторизации.")
        except postgresql.exceptions.ClientCannotConnectError: # клиенту не удалось установить соединение с сервером
            print("Ошибка! Клиенту не удалось установить соединение с сервером.")
        except postgresql.exceptions.ConnectTimeoutError: # клиенту не  удалось установить соединение в заданное время
            print("Ошибка! Клиенту не удалось установить соединение в заданное время.")
        except postgresql.exceptions.DriverError: # Ошибка в реализации драйвера
            print("Ошибка в реализации драйвера")


    def getGroup(self):
        try:
            return self._connection.query("SELECT * FROM public.student")
        except postgresql.exceptions.ConnectionDoesNotExistError:
            print("Error")
        except:
            print("Error1")

    def chooseGroup(self, number):
        try:
            sql = "SELECT * FROM public.student WHERE id_group ="+str(number)

            ps = self._connection.query(sql)
            return ps
        except:
            print("Error!")


    def addPerson(self, name, surname, mid_name, id_group, adres, course):
        try:
            val_str = "('"+name + "','"+surname+"','"+mid_name+"',"+str(id_group)+",'"+adres+"',"+str(course)+")"
            
            self._connection.query("INSERT INTO student(name, surname, middle_name, id_group, address, cource) VALUES"+val_str)
        except:
            print("Error")

    def delPerson(self, id_person):
        try:
            self._connection.query("DELETE FROM student where id="+str(id_person))
        except:
            print("Error")

    def closeConnection(self):
        self._connection.close()
