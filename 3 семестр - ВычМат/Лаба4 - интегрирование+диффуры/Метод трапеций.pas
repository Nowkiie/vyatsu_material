program t6;
uses crt;
var h:real;
a,b,s:real;
n,i:integer;
function f(x:real):real;
begin
  f:=1/(sqrt(x*x+1.2));
end;

begin
  a:=1.2;
  b:=2.0;
  n:=100;
  i:=1;
  writeln('исходные данные');
  writeln('функция:');
  writeln('f:=1/(sqrt(x*x+1.2))');
  writeln('Начальная граница:',a);
  writeln('Конечная граница:',b);
  writeln('Число разбиений:',n);
  h:=(b-a)/n;
  Writeln('Шаг:',h);
  writeln();
  writeln('Вычисленные значения');
  writeln(i,' ',a:4:2,0.5*f(a):6:3);
  s:=s+0.5*f(a);
  a:=a+h;
  inc(i);
  while a<(b-h) do begin
    s:=s+f(a);
    writeln(i,' ',a:4:2,f(a):6:3);
    a:=a+h;
    inc(i);
  end;
   s:=s+0.5*f(b);
   writeln(i,' ',b:4:2,0.5*f(a):6:3);
   writeln();
   writeln('Сумма: ',s);
   writeln('Результат: ',h*s);
end.