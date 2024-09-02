from PIL import Image
import numpy as np

img = Image.open("djangopony.png").convert('RGB') # Загружаем изображение из файла, формат файла определяется автоматически
pix = img.load()               # Получаем ссылку на массив пикселей
for x in range(0, img.width):       # Цикл по оси OX, слева направо
    for y in range(0, img.height):  # Цикл по оси OY, cверху вниз
        r, g, b = pix[x, y]         # pix[x, y] - это кортеж из трёх чисел
        gr = (b + r ) // 2      # берём среднее из них
        pix[x, y] = (255-r, 255-g, 255-b )    # записываем новый кортеж

img.show()                        # Если оставить эту строчку, то картинка отобразится во внешней программе просмотра
img.save("negativ.png", "png") 

img = Image.open("djangopony.png").convert('RGB') # Загружаем изображение из файла, формат файла определяется автоматически
pix = img.load()               # Получаем ссылку на массив пикселей
for x in range(0, img.width):       # Цикл по оси OX, слева направо
    for y in range(0, img.height):  # Цикл по оси OY, cверху вниз
        r, g, b = pix[x, y]         # pix[x, y] - это кортеж из трёх чисел
        gr = (b + r + g ) // 3     # берём среднее из них
        pix[x, y] = (gr, gr, gr )    # записываем новый кортеж

img.show()                        # Если оставить эту строчку, то картинка отобразится во внешней программе просмотра
img.save("grey.png", "png")

img = Image.open("djangopony.png").convert('L') # Загружаем изображение из файла, формат файла определяется автоматически
bw = np.asarray(img).copy()
bw[bw < 128 ] = 0
bw[bw >= 128 ] = 255
imfile = Image.fromarray(bw)
imfile.show()
imfile.save("bw.png", "png")

img = Image.open("djangopony.png").convert('RGB') # Загружаем изображение из файла, формат файла определяется автоматически
na = np.asarray(img).copy()
mBlueHi = na[...,2] >= 174
mGreenHi = na[...,1] >= 174
na[mGreenHi | mBlueHi] = [255,255,255]
imfile = Image.fromarray(na)
imfile.show()
imfile.save("bw.png", "png")
