Program t6;
Uses Crt;
var
  a,b:real;
   e,e1:real;
      x0,x1,x2:real;
       i,n,k:integer;
  function f(x:real):real;
  begin
    f:=3*x-exp(x);
  end;
  function f1(x:real):real;
  begin
    f1:=3-exp(x);
  end;
  function f2(x:real):real;
  begin
    f2:=-exp(x);
  end;
begin
 A := 1.0;
 B := 1.9;
 e:=0.00001;

WriteLn ( 'Комбинированный метод : ' ) ;
writeln('Исходная формула: 3*x- e^x =0');
writeln('f(a):',f(a):4:5);
writeln('f(b):',f(b):4:5);
writeln('f"(a):',f2(a):4:5);
writeln('f"(b):',f2(b):4:5);
k:=0;
  if f(a)*f2(a)>0 then x0:=a else x0:=b;
     if X0=a then writeln('левая граница интервала - неподвижная точка')
             else writeln('правая граница интервала - неподвижная точка');
     x1:=x0-f(x0)/f1(x0);
     x2:=a-((b-a)*f(a)/(f(b)-f(a)));
     //e1:=(x1+x2)/2;
      while  abs(x2-x1)>e do
        begin
         a:=x1;
         b:=x2;
         x1:= a-f(a)/f1(a);
         x2:= a-((b-a)*f(a)/(f(b)-f(a)));
         //e1:=(x1+x2)/2;
         inc(k);
         writeln(k,' x1:',x1:5:6,' f(x1):',f(x1):5:6,' h(x1):',(f(a)/f1(a)):5:6,' x2:',x2:5:6,' f(x2):',f(x2):5:6,' h(x2):',(((b-a)*f(a)/(f(b)-f(a))):5:6));
        end;
writeln ( 'x=',x1:10:8);

readln

 end.