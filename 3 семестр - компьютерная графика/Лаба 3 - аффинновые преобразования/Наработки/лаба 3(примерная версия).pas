uses graphABC;
const m=4;{фигур }
      n=3;{размер матриц коэффициентов}
type mas=array[1..m] of real;
     mtr=array[1..n,1..n] of real;
var xa,ya,xb,yb:mas;{фигуры после перемещения}
    a,r:mtr;{матрицы преобразований}
    xc,yc:integer;{центр экрана }
    ms:real;{масштаб для перевода реальных координат в экранные}
    s:string;{строка для вывода текста}
    procedure Osi;{рисование осей координат}
begin
setpencolor(clBlue);
line(0,yc,windowwidth,yc);{оси}
line(xc,0,xc,windowheight);
for var i:=1 to 10 do{максимальное количество засечек в одну сторону}
if i mod 2=0 then
  begin
    line(xc-3,yc-round(i*ms),xc+3,yc-round(i*ms));{засечки на оси У}
    line(xc-3,yc+round(i*ms),xc+3,yc+round(i*ms));
    {подпись оси У}
    str(i,s);
    textout(xc-20,yc-round(i*ms),s);{соответственно засечкам}
    textout(xc-25,yc+round(i*ms),'-'+s);
    line(xc+round(i*ms),yc-3,xc+round(i*ms),yc+3); {засечки на оси Х}
    line(xc-round(i*ms),yc-3,xc-round(i*ms),yc+3);
    {подпись оси Х}
    textout(xc+round(i*ms),yc+10,s);
    textout(xc-round(i*ms),yc+10,'-'+s);
  end;
{центр}
textout(xc+5,yc+10,'0');
{подписи концов осей}
textout(windowwidth-10,yc-10,'X');
textout(xc+5,10, 'Y');
setfontcolor(clBlue);
textout(30,0,'Rotate - 1');
textout(30,20,'Stretching - 2');
textout(30,40,'Compression - 3');
textout(30,60,'MirrorX - 4');
textout(30,80,'MirrorY - 5');
textout(30,100,'MoveRight - 6');
textout(30,120,'MoveLeft - 7');
textout(30,140,'MoveUp - 8');
textout(30,160,'MoveDown - 9');
textout(30,180,'Exit - Esc');
end;
procedure Draw(x,y:mas);{рисование фигуры}
begin
Osi;
setpencolor(clRed);
moveto(xc+round(ms*x[1]),yc-round(ms*y[1]));
lineto(xc+round(ms*x[3]),yc-round(ms*y[3]));
lineto(xc+round(ms*x[2]),yc-round(ms*y[2]));
lineto(xc+round(ms*x[4]),yc-round(ms*y[4]));
lineto(xc+round(ms*x[1]),yc-round(ms*y[1]));
end;
procedure Ed; { присвоение матрице R значения единичной }
begin
for var i:=1 to n do
 begin                             {  1 0 0  }
  for var j:=1 to n do  r[i,j]:=0; {  0 1 0  }
  r[i,i]:=1;                       {  0 0 1  }
 end;
end;
procedure Mult; {умножение матриц А и R:  R = B = A*R }
var b:mtr;
    z:real;
begin
for var i:=1 to n do
for var j:=1 to n do
 begin
  z:=0;
  for var k:=1 to n do
  z:=z+a[i,k]*r[k,j];
  b[i,j]:=z
 end;
for var i:=1 to n do
for var j:=1 to n do
r[i,j]:=b[i,j]
end;
procedure Stretch;  {расчет матриц А и R для растягивания фигуры}
begin
for var i:=1 to n do
 begin                             {  1  0  0  }
  for var j:=1 to n do a[i,j]:=0;  {  0 1.05  0 }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[2,2]:=1.05;{коэффициент растяжения}
a[1,1]:=1.05;
Mult;
end;
procedure Compress;  {расчет матриц А и R для сжатия фигуры}
begin
for var i:=1 to n do
 begin                         {  1  0  0  }
  for var j:=1 to n do a[i,j]:=0;  {  0 1.05  0  }
  a[i,i]:=1;                   {  0  0  1  }
 end;
a[2,2]:=0.95;{коэффициент растяжения}
a[1,1]:=0.95;
Mult;
end;
procedure MirrorX;  {расчет матриц А и R для отражения фигуры по Х}
begin
for var i:=1 to n do
 begin                             {  1  0  0  }
  for var j:=1 to n do a[i,j]:=0;  {  0 -1  0  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[2,2]:=-1;
Mult;
end;
procedure MirrorY;  {расчет матриц А и R для отражения фигуры по Х}
begin
for var i:=1 to n do
 begin                             { -1  0  0  }
  for var j:=1 to n do a[i,j]:=0;  {  0  1  0  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[1,1]:=-1;
Mult;
end;
procedure MoveY(dy:integer);  {расчет матриц А и R для перемещения фигуры по Y}
begin
for var i:=1 to n do
 begin                             {  1  0  0  }
  for var j:=1 to n do a[i,j]:=0;  {  0  1 dy  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[2,3]:=dy;
Mult;
end;
procedure MoveX(dx:integer);  {расчет матриц А и R для перемещения фигуры по Y}
begin
for var i:=1 to n do
 begin                             {  1  0  dx }
  for var j:=1 to n do a[i,j]:=0;  {  0  1  0  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[1,3]:=dx;
Mult;
end;
procedure Rotate(u:real); {расчет матриц А и R для поворота  фигуры}
var c, s: real;                                                                               {---н  угол alfa(р д)---}
begin                    {  cos(u) -sin(u) 0  }
for var i:=1 to 3 do     {  sin(u)  cos(u) 0  }
for var j:=1 to 3 do     {   0       0     1  }
a[i,j]:=0;
a[3,3]:=1;
c:=cos(u);   a[1,1]:= c;  a[2,2]:=c;
s:=sin(u);   a[1,2]:=-s;  a[2,1]:=s;
Mult;
end;
 
procedure New_XY;{расчет новых координат фигуры по исходным}
begin           {с использованием матрицы преобразования R}
for var i:=1 to m do
 begin
  xb[i]:=xa[i]*r[1, 1]+ ya[i]*r[1, 2]+ r[1, 3];
  yb[i]:=xa[i]*r[2, 1]+ ya[i]*r[2, 2]+ r[2, 3]
 end;
end;
 
procedure Vybor(c:char);
begin
case c of
  #49:begin
      clearwindow;
      Ed;
      Rotate(pi/3); {поворот на  pi/4 относительно начала координат}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;{запомним новое положение}
      end;
  #50:begin
      clearwindow;
      Ed;
      Stretch; { растяжение}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #51:begin
      clearwindow;
      Ed;
      Compress; { сжатие}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #52:begin
      clearwindow;
      Ed;
      MirrorX; { отражение по Х}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #53:begin
      clearwindow;
      Ed;
      MirrorY; {отражение по Y}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #54:begin
      clearwindow;
      Ed;
      MoveX(1); { перемещение по Х}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #55:begin
      clearwindow;
      Ed;
      MoveX(-1); { перемещение по Y}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #56:begin
      clearwindow;
      Ed;
      MoveY(1); {перемещение по Y}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
  #57:begin
      clearwindow;
      Ed;
      MoveY(-1); { перемещение по Y}
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
      end;
   #48:begin
      clearwindow;
      Ed;
      Stretch;
      New_XY;
      xa:=xb;ya:=yb;
      Rotate(pi/3);
      New_XY;
      Draw(xb,yb);
      xa:=xb;ya:=yb;
   end;
  #27:window.close;
  end;
 end;
begin
xc:=windowwidth div 2;
yc:=windowheight div 2; { центр экрана }
ms:=(yc-30)/10;
{зададим координаты вершин фигуры}
xa[1]:=-2;ya[1]:=1;
xa[2]:=2;ya[2]:=2;
xa[3]:=2;ya[3]:=-2;
xa[4]:=-2;ya[4]:=-1;
Draw(xa,ya);{исходный}
onkeypress:=Vybor;
  
end.