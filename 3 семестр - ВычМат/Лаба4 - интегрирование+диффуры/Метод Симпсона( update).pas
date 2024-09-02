program Simpson;
uses crt;
var
x,a,b,h,s,d:real;
n:integer;

function Y(x:real):real;
begin
Y:=ln(x*x+3)/ln(10)*1/(2*x);
end;

 
begin
clrscr;
a:=1.2;
b:=2.0;
h:=0.08;
s:=0; x:=a+h;
 writeln('Исходные данные');
  writeln('функция:');
  writeln('f:=(ln(sqr(x)+3)/(ln(10)))/(2*x)');
  writeln('Начальная граница:',a);
  writeln('Конечная граница:',b);
  Writeln('Шаг:',h);
  writeln();
  writeln('Вычисленные значения для шага h');
while x<b do
begin
s:=s+4*Y(x);
writeln(x:2:2,'  ',y(x):8:6);
x:=x+h;
s:=s+2*Y(x);
writeln(x:2:2,'  ',y(x):8:6);
x:=x+h;
end;
s:=h/3*(s+Y(a)-Y(b));
writeln;
writeln('Интеграл = ',s);
writeln();
 writeln('Вычисленные значения для шага h/2');
d:=0; x:=a+h/2;
while x<b do
begin
d:=d+4*Y(x);
writeln(x:2:2,'  ',y(x):8:6);
x:=x+h/2;
d:=d+2*Y(x);
writeln(x:2:2,'  ',y(x):8:6);
x:=x+h/2;
end;
d:=h/6*(d+Y(a)-Y(b));
writeln;
writeln('Интеграл = ',d);

writeln('Погрешность:',abs(s-d):10:10);
readkey;
end.