program t6;
uses crt;
var A,x:array[1..10] of real;
 i:integer;
 s:real;
 
function f(x:real):real;
begin
  f:=x/sqrt(x*x+2.5);  
end;

begin
  x[1]:=-0.86114;
  x[2]:=-0.33998;
  x[3]:=0.33998;
  x[4]:=0.86114;
  A[1]:=0.34785;
  A[2]:=0.65215;
  A[3]:=0.34785;
  A[4]:=0.65215;
  writeln('Исходные данные: ');
  for i:= 1 to 4 do
    writeln('x[',i,']=',x[i],'   A[',i,']=',A[i]);
  writeln('Вычисленные значения');
  for i:=1 to 4 do begin
    s:=s+a[i]*f(x[i]);
    writeln(a[i]*f(x[i]):6:3);
    end;
  writeln('Результат:',s);
  
  writeln();
  writeln('Для 7 узлов');
  s:=0;
  x[1]:=-0.949107912;
  x[2]:=-0.741531186;
  x[3]:=-0.405845151;
  x[4]:=0;
  x[5]:=0.405845151;
  x[6]:=0.741531186;
  x[7]:=0.949107912;
  
  A[1]:=0.129484966;
  A[2]:=0.279705391;
  A[3]:=0.381830051;
  A[4]:=0.417959184;
  A[5]:=0.381830051;
  A[6]:=0.279705391;
  A[7]:=0.129484966;
  writeln('Исходные данные: ');
  for i:= 1 to 7 do
    writeln('x[',i,']=',x[i],'   A[',i,']=',A[i]);
  writeln('Вычисленные значения');
  for i:=1 to 7 do begin
    s:=s+a[i]*f(x[i]);
    writeln(a[i]*f(x[i]):6:3);
    end;
  writeln('Результат:',s);
end.