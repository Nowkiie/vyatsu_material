import postgresql
from postgresql import exceptions

class database:
        
    _connection = None

    _db_url = "pq://postgres:74771@localhost:5432/lab_securityInfo"

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

    def chooseId(self, number):
        try:
            sql = "SELECT * FROM public.users WHERE id ="+str(number)

            ps = self._connection.query(sql)
            return ps
        except:
            print("Error!")


    def updateInfo(self, id_person, password_folder):
        try:
            sql = "update users set password_folder="+str(password_folder)+" where id="+str(id_person)
            self._connection.query(sql)
        except:
            print("Error!")

    def addPerson(self, id_person, password, password_folder):
        try:
            val_str = "("+str(id_person) + ",'"+password+"', "+str(password_folder)+")"
            print(val_str)
            self._connection.query("INSERT INTO users(id, password, password_folder) VALUES"+val_str)
        except:
            print("Error")

    def delPerson(self, id_person):
        try:
            self._connection.query("DELETE FROM student where id="+str(id_person))
        except:
            print("Error")

    def closeConnection(self):
        self._connection.close()

