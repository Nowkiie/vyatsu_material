uses crt;
Const
 e=0.00001;

Var
 x, y, z:real;
 gn,hn:real;
 
function Fun_1(x,y:real):real;
begin
  Fun_1:=30*x*x+7*y*y-1;
end;

function Fun_2(x,y:real):real;
begin
  Fun_2:=sin(4*x-0.5*y)+5*x;
end;
 
Function Fun_1x(x:real):real;
begin
 Fun_1x:=60*x;
end;

Function Fun_1y(x:real):real;
begin
 Fun_1y:=14*y;
end;

Function Fun_2x(x,y:real):real;
begin
 Fun_2x:=4*cos(4*x-0.5*y)+5;
end;

Function Fun_2y(x,y:real):real;
begin
 Fun_2y:=-0.5*cos(4*x-0.5*y);
end;

Begin 
 writeln('Исходная система уравнений');
 writeln('30*x^2+7*y^2-1=0');
 writeln('sin(4*x-0.5*y)+5*x=0');
 writeln();
 writeln('Производные:');
 writeln('Fun_1x:=60*x');
 writeln('Fun_1y:=14*y');
 writeln('Fun_2x:=4*cos(4*x-0.5*y)+5');
 writeln('Fun_2y:=-0.5*cos(4*x-0.5*y)');
 writeln();
 x:=-0.1;//см график функций
 y:=-0.2;
 repeat
   hn:=(Fun_1x(x)*Fun_2(x,y)-Fun_1(x,y))/(Fun_1y(y)*Fun_2x(x,y)-Fun_1x(x)*Fun_2y(x,y));
   gn:=(-Fun_2(x,y)-Fun_2y(x,y)*hn)/(Fun_2x(x,y));
   if sqr(hn)>sqr(gn) then z:=sqr(hn)
                      else z:=sqr(gn);
   x:=x+gn;
   y:=y+hn;
   writeln('y=',y);
   writeln('x=',x);
   writeln('Погрешность: ',z);
 until z<e;
 writeln('Корни:');
 writeln('y=',y);
 writeln('x=',x);
 writeln('Проверка');
 writeln(Fun_1(x,y));
 writeln(Fun_2(x,y));
 
writeln();
  x:=0.1;//см график функций
 y:=0.2;
 repeat
   hn:=(Fun_1x(x)*Fun_2(x,y)-Fun_1(x,y))/(Fun_1y(y)*Fun_2x(x,y)-Fun_1x(x)*Fun_2y(x,y));
   gn:=(-Fun_2(x,y)-Fun_2y(x,y)*hn)/(Fun_2x(x,y));
   if sqr(hn)>sqr(gn) then z:=sqr(hn)
                      else z:=sqr(gn);
   x:=x+gn;
   y:=y+hn;
   writeln('y=',y);
   writeln('x=',x);
   writeln('Погрешеность: ',z);
 until z<e;
 writeln('Корни:');
 writeln('y=',y);
 writeln('x=',x);
 writeln('Проверка');
 writeln(Fun_1(x,y));
 writeln(Fun_2(x,y));
 end.  