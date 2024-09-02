program t6;
uses crt;
var X,Y:array[1..10] of real;
 two,p1,p2,p3,three,four,five,six:array[1..10] of real;
 s1,s2,s3,s4,s5,s6,xy1,xy2,xy3,sy:real;
var
  //a,a1:matruica
  a,a1: array[1..10, 1..10] of real;
  b,b1: array[1..10] of real;
  An: array[1..10] of real; 
  n, i, j, k: integer;z, r, g,h,sig: real;
  fp,eps:array[1..10] of real;
begin
  X[1]:=0.1;
  x[2]:=0.2;
  x[3]:=0.3;
  x[4]:=0.4;
  x[5]:=0.5;
  x[6]:=0.6;
  x[7]:=0.7;
  x[8]:=0.8;
  x[9]:=0.9;
  x[10]:=1.0;
  
  y[1]:=1.91;
  y[2]:=3.03;
  y[3]:=3.98;
  y[4]:=4.82;
  y[5]:=5.59;
  y[6]:=6.31;
  y[7]:=7.00;
  y[8]:=7.65;
  y[9]:=8.27;
  y[10]:=8.88;
  
  for i:=1 to 10 do begin
    two[i]:=x[i]*x[i];
    three[i]:=two[i]*x[i];
    four[i]:=three[i]*x[i];
    five[i]:=four[i]*x[i];
    six[i]:=five[i]*x[i];
    p1[i]:=x[i]*y[i];
    p2[i]:=two[i]*y[i];
    p3[i]:=three[i]*y[i];
    end; 
    
  write('x[i]: ');
  for i:= 1 to 10 do 
    write(x[i]:4:1);
  writeln();
  
  write('y[i]: ');
  for i:=1 to 10 do
    write(y[i]:5:2);
  writeln();
  
  write('x[i]^2: ');
  for i:=1 to 10 do
    write(two[i]:6:3);
  writeln;
  
  write('x[i]^3: ');
  for i:=1 to 10 do
    write(three[i]:6:3);
  writeln;
  
   write('x[i]^4: ');
  for i:=1 to 10 do
    write(four[i]:6:3);
  writeln;
  
   write('x[i]^5: ');
  for i:=1 to 10 do
    write(five[i]:6:3);
  writeln;
  
   write('x[i]^6: ');
  for i:=1 to 10 do
    write(six[i]:6:3);
  writeln;
  
  write('x[i]*y[i]: ');
  for i:=1 to 10 do
    write(p1[i]:6:3);
  writeln;
  
 write('x[i]^2*y[i]: ');
  for i:=1 to 10 do
    write(p2[i]:6:3);
  writeln; 
  
  write('x[i]^3*y[i]: ');
  for i:=1 to 10 do
    write(p3[i]:6:3);
  writeln;
  
  for i:=1 to 10 do begin
    s1:=s1+x[i];
    s2:=s2+two[i];
    s3:=s3+three[i];
    s4:=s4+four[i];
    s5:=s5+five[i];
    s6:=s6+six[i];
    xy1:=xy1+p1[i];
    xy2:=xy2+p2[i];
    xy3:=xy3+p3[i];
    sy:=sy+y[i];
    end;
   writeln;
   writeln('Сумма Xi: ',s1);
   writeln('Сумма Xi^2: ',s2);
   writeln('Сумма Xi^3: ',s3);
   writeln('Сумма Xi^4: ',s4);
   writeln('Сумма Xi^5: ',s5);
   writeln('Сумма Xi^6: ',s6);
   writeln('Сумма Xi*Yi: ',xy1);
   writeln('Сумма Xi^2*Yi: ',xy2);
   writeln('Сумма Xi^3: ',xy3);
   writeln('Сумма Yi: ',sy);
  
   n:=4; 
a[1,1]:=s3;      
a[1,2]:=s2;               
a[1,3]:=s1;               
a[1,4]:=10;               
 
a[2,1]:=s4;
a[2,2]:=s3;
a[2,3]:=s2;
a[2,4]:=s1;
 
a[3,1]:=s5;
a[3,2]:=s4;
a[3,3]:=s3;
a[3,4]:=s2;
 
a[4,1]:=s6;
a[4,2]:=s5;
a[4,3]:=s4;
a[4,4]:=s3;
 
b[1]:=sy; 
b[2]:=xy1;
b[3]:=xy2;
b[4]:=xy3;

a1:=a;

writeln('Исходная система:');
for i:=1 to n do
 begin
  for j:=1 to n do
  write(a[i,j]:6:2);
  writeln(b[i]:7:1);
 end;
  writeln;
 { прямой ход Гаусса } 
  for i := 1 to n-1 do //бежим по столбцам 
    for j := i + 1 to n do //бежим по строкам, без первого элемента
    begin
      a[j,i] := -a[j, i] / a[i, i];//вычисляем множитель 
      write('m[',j,']=',a[j,i],'  '); //выписываем его
      writeln();
      for k := i+1 to n do
      begin
        a[j, k] := a[j, k] + a[j,i] * a[i, k]; //новый элемент матрицы = его начальное значение - элемент строки выше * множитель
        write(a[j,k]:7:3);
      end;
      writeln;
      b[j] := b[j] + a[j,i] * b[i]; //то же самое для матрицы свободных членов 
    end;
    An[n]:=b[n]/a[n,n];
   // write(x[n]:3:5);
   // writeln;
  for i := n-1 downto 1 do { обратный ход Гаусса }
  begin
    h := b[i];
    for j := i + 1 to n do
    begin
      h:=h-An[j]*a[i,j]
      {g := a[k, j] * x[j];
      r := r + g;}
    end;
    An[i] := h / a[i, i];
  end;
  
  writeln();
  writeln('Корни системы:');
  for i := 1 to n do
    write('x[', i, ']=', An[i]:0:2, '   ');
 
  Writeln();
  Writeln('Полученное уравнение:');
  writeln('y = ',An[1]:0:2,' * x^3 ',An[2]:0:2,' * x^2 + ', An[3]:0:2,' * x + ', An[4]:0:2);
  writeln('У теорет.');
  For i:=1 to 10 do begin
    fp[i]:=an[1]*x[i]*x[i]*x[i]+an[2]*x[i]*x[i]+an[3]*x[i]+an[4];
    write(fp[i]:6:3)
    end;
    writeln();
    writeln('Квадраты:');
  for i:= 1 to 10 do begin
    eps[i]:=sqr(y[i]-fp[i]);
    sig:=sig+eps[i];
    write(eps[i]:6:3);
  end;
  writeln();
  writeln('Погрешность: ',(sqrt(sig)/10));
end.