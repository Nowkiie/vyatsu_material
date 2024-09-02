import random

def generate_key(length):
    key = [random.choice([0, 1]) for _ in range(length)]
    return key

def encrypt(message, key):
    encrypted_message = ""
    for i in range(len(message)):
        encrypted_char = chr(ord(message[i]) ^ key[i % len(key)])
        encrypted_message += encrypted_char
    return encrypted_message

def decrypt(encrypted_message, key):
    decrypted_message = ""
    for i in range(len(encrypted_message)):
        decrypted_char = chr(ord(encrypted_message[i]) ^ key[i % len(key)])
        decrypted_message += decrypted_char
    return decrypted_message



message = "Пример сообщения для шифрования"

# Генерируем гамму
key = generate_key(len(message))


# Шифруем сообщение
encrypted_message = encrypt(message, key)
print("Зашифрованное сообщение:", encrypted_message)

# Расшифровываем сообщение
decrypted_message = decrypt(encrypted_message, key)
print("Расшифрованное сообщение:", decrypted_message)
