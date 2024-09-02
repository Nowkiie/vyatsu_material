program t6;
uses crt;
const e=0.0001;
eps=0.00001;
var s,a,b,z,d,ed:real;
m,j:real; 
  i:integer=1;
function h():real;
begin
  h:=exp(1/4*ln(e));
end;

function f(x:real):real;
begin
  f:=(ln(sqr(x)+3)/(ln(10)))/(2*x);
end;

begin
  a:=1.2;
  b:=2.0;
  writeln('Исходные данные');
  writeln('функция:');
  writeln('f:=(ln(sqr(x)+3)/(ln(10)))/(2*x)');
  writeln('Начальная граница:',a);
  writeln('Конечная граница:',b);
  Writeln('Шаг:',h);
  writeln();
  writeln('Вычисленные значения для шага h');
  s:=s+f(a);
  writeln(a:4:2,f(a):6:3);
  a:=a+h;
  i:=1;
  while a < b do begin
    if i mod 2 <> 0 then begin
      s:=s+4*f(a);
      writeln(a:4:2,f(a):6:3);
    end
                  else begin
      s:=s+2*f(a);
      writeln(a:4:2,f(a):6:3);
                  end;
      a:=a+h;
      inc(i);
  end;
  s:=s+f(b);
  writeln(b:4:2,f(b):6:3);
  writeln();
  writeln('Полученный результат:',s*h/3);
  
  
  a:=1.2;
  i:=1;
  writeln();
  writeln('Вычисленные значения для шага h/2');
  z:=z+f(a);
  writeln(a:4:2,f(a):6:3);
  a:=a+h/2;
  while a<b do begin
    if i mod 2 =0 then begin
      z:=z+4*f(a);
      writeln(a:4:2,4*f(a):6:3);
    end
                  else begin
      z:=z+2*f(a);
      writeln(a:4:2,2*f(a):6:3);
                  end;
      a:=a+h/2;
      inc(i);
  end;
  z:=z+f(b);
  writeln(b:4:2,f(b):6:3);
  writeln('Полученный результат:',z*(h/6));
  
  writeln();
  writeln('Погрешность между h, h/2:',(abs((s*h/3)-(z*(h/6)))):6:5);
  
  
  a:=1.2;
  b:=2.0;
  i:=1;
  writeln();
  writeln('Вычисленные значения для шага h/4');
  d:=d+f(a);
  writeln(a:4:2,f(a):6:3);
  a:=a+h/4;
  while a<b do begin
    if i mod 2 =0 then begin
      d:=d+4*f(a);
      writeln(a:4:2,4*f(a):6:3);
    end
                  else begin
      d:=d+2*f(a);
      writeln(a:4:2,2*f(a):6:3);
                  end;
      a:=a+h/4;
      inc(i);
  end;
  d:=d+f(b);
  writeln(b:4:2,f(b):6:3);
  writeln('Полученный результат:',d*(h/12));
  
  writeln();
  writeln('Погрешность между h/2, h/4:',(abs((z*h/6)-(d*(h/12)))):6:5);
  
  a:=1.2;
  b:=2.0;
  i:=1;
  writeln();
  writeln('Вычисленные значения для шага h/8');
  ed:=ed+f(a);
  writeln(a:4:2,f(a):6:3);
  a:=a+h/8;
  while a<b do begin
    if i mod 2 =0 then begin
      ed:=ed+4*f(a);
      writeln(a:4:2,4*f(a):6:3);
    end
                  else begin
      ed:=ed+2*f(a);
      writeln(a:4:2,2*f(a):6:3);
                  end;
      a:=a+h/8;
      inc(i);
  end;
  ed:=ed+f(b);
  writeln(b:4:2,f(b):6:3);
  writeln('Полученный результат:',ed*(h/24));
  
  writeln();
  writeln('Погрешность между h/4, h/8:',(abs((d*h/12)-(ed*(h/24)))):6:5);
  
  d:=0;
  a:=1.2;
  b:=2.0;
  i:=1;
  writeln();
  writeln('Вычисленные значения для шага h/16');
  d:=d+f(a);
  writeln(a:4:2,f(a):6:3);
  a:=a+h/16;
  while a<b do begin
    if i mod 2 =0 then begin
      d:=d+4*f(a);
      writeln(a:4:2,4*f(a):6:3);
    end
                  else begin
      d:=d+2*f(a);
      writeln(a:4:2,2*f(a):6:3);
                  end;
      a:=a+h/16;
      inc(i);
  end;
  d:=d+f(b);
  writeln(b:4:2,f(b):6:3);
  writeln('Полученный результат:',d*(h/48));
  
  writeln();
  writeln('Погрешность между h/16, h/8:',(abs((ed*h/24)-(d*(h/48)))):6:5);
end.