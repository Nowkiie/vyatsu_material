Program t6;
uses crt;
const
 min=1.8;
 max=1.9;
 eps =1e-4;

function phi1(x:real):real;
begin
  phi1:=2.5-exp(x)/2;
end;

function phi(x:real):real;
begin
  phi:=2.5*x-exp(x)/2;
end;

function f(x:real):real;
begin
  f:=3*x-exp(x);
end;

var iter:integer;
 x0,x1:real;
 
begin
  writeln('метод итераций');
  writeln('Исходная формула: 3*x-e^x=0');
  writeln('Каноническая формула: 2.5*x-e^x/2');
  writeln('phi(a)/dx: ',phi1(min));
  writeln('phi(b)/dx: ',phi1(max));
  if (phi1(max)>-1) and (phi1(max)<0) then writeln('двусторонняя сходимость')
                                  else writeln('односторонняя сходимость');
  iter := 0;
  x1 := (min+max)/2;
  repeat 
    x0:=x1;
    x1 := phi(x0);
    inc(iter);
    writeln(iter,':    x1:',(x1):8:4,'   f(x1):',f(x1):6:4,'   x2:',phi(x1):6:4);
  until abs(x0-x1)<=eps ;
  writeln('x= ',x1);
end.