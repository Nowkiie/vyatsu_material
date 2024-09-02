program t6;
uses crt;
var k:integer;
 x,y:real;
 h:real;
 g,z,d,m,del,t,e1,e2:real;
 bol1,bol2,p:real;
 
Function F(x,y:real):real;
begin
  f:=x*x-y
end;

function Acc(x:real):real;
begin
  acc:=-2/(exp(x))+sqr(x)-2*x+2;
end;

begin
  writeln('Формула Эйлера-Коши 2ого порядка точности');
  writeln();
  writeln('Диффур:');
  writeln('dy/dx=x*x-y');
  writeln('Частное решение:');
  writeln('y=-2/(exp(x))+sqr(x)-2*x+2');
  K:=0;
  X:=0;
  Y:=0;
  h:=0.1;
  writeln('k  Xk   Yk         Fk     Xk+h    Yk+h*Fk   Fkh   д.Y     Yt        E');  
  g:=x+h;
    z:=(y+h*f(x,y));
    d:=F(x,y);
    m:=F(g,z);
    del:=h/2*(d+m);
    t:=acc(x);
    e1:=abs(y-t);
    writeln(k,' ',X,'   ', y:8:5, d:8:3,'   ', g:1:1,' ', z:9:3, m:9:3,del:9:5,t:9:5,e1:9:4);
    inc(k);
    x:=x+h;
    y:=y+del;
  while x<1 do begin
    g:=x+h;
    z:=(y+h*f(x,y));
    d:=F(x,y);
    m:=F(g,z);
    del:=h/2*(d+m);
    t:=acc(x);
    e1:=abs(y-t);
    writeln(k,' ',X,' ', y:8:5,d:8:3,'   ', g:1:1,' ', z:9:3, m:9:3,del:9:5,t:9:5,e1:9:4);
    inc(k);
    x:=x+h;
    y:=y+del;
  end;
  p:=y;
  writeln();
  writeln('для шага h/2');
  K:=0;
  X:=0;
  Y:=0;
  h:=0.05;
  writeln('k  Xk   Yk        Fk     Xk+h     Yk+h*Fk    Fkh     д.Y     Yt      E');  
  g:=x+h;
    z:=(y+h*f(x,y));
    d:=F(x,y);
    m:=F(g,z);
    del:=h/2*(d+m);
    t:=acc(x);
    e2:=abs(y-t);
    writeln(k,' ',X,'   ', y:8:5, d:8:3,'   ', g:1:2,' ', z:9:3, m:9:3,del:9:5,t:9:5,e2:9:4);
    inc(k);
    x:=x+h;
    y:=y+del;
  while x<=1.05 do begin
    g:=x+h;
    z:=(y+h*f(x,y));
    d:=F(x,y);
    m:=F(g,z);
    del:=h/2*(d+m);
    t:=acc(x);
    e2:=abs(y-t);
    writeln(k,' ',X:3:2,' ', y:8:5,d:8:3,'   ', g:1:2,' ', z:9:3, m:9:3,del:9:5,t:9:5,e2:9:4);
    inc(k);
    x:=x+h;
    y:=y+del;
  end;
  writeln();
  write('Выполнения условия:');
  bol2:=abs(y-t);
  bol1:=abs(y-p);
  if bol2<bol1 then writeln('true')
               else writeln('false');
end.