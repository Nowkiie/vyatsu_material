program t6;
uses crt;
var M:array[0..6,0..6] of real;
 mX:array[0..6] of real;
 mY:array[0..6] of real;
 D,T:array[0..6] of real;
 S,p:real;
 x,y,sigma:real;
begin
  p:=1.0;
  
  mX[0]:=0.62;
  mx[1]:=0.67;
  mx[2]:=0.74;
  mx[3]:=0.80;
  mx[4]:=0.87;
  mx[5]:=0.96;
  mx[6]:=0.99;
  
  my[0]:=0.537944;
  my[1]:=0.511709;
  my[2]:=0.477114;
  my[3]:=0.449329;
  my[4]:=0.418952;
  my[5]:=0.382893;
  my[6]:=0.371577;
  
  for var i:=0 to 6 do
    D[i]:=1; 
  
  X:=0.692;
  Writeln('X=',x);
  writeln;
  
  Writeln('Исходные данные:');
  for var i:=0 to 6 do
    writeln(mx[i]:4:2,'  ',my[i]:8:6);
  
  for var i:=0 to 6 do
    for var j:=0 to 6 do 
       if i=j then M[i,j]:=x-mx[i]
              else M[i,j]:=mx[i]-mx[j];
              
  for var i:=0 to 6 do begin
    for var j:=0 to 6 do 
      D[i]:=D[i]*M[i,j];
    T[i]:=my[i]/D[i];
    end;
    
  for var i:=0 to 6 do 
    S:=s+T[i];
  
  Writeln('Элементы главной диагонали');
  for var i:=0 to 6 do begin
    write(M[i,i]:6:2);
    p:=p*m[i,i];
    end;
  writeln();
  writeln();
  writeln('Полученная таблица:');
  for var i:=0 to 6 do begin
    for var j:=0 to 6 do
      write(M[i,j]:7:3);
    write('   ',D[i]:7:3);
    write('   ',T[i]:7:3);
    writeln;
    end;
   writeln();
   writeln('Сумма: ',S:7:3);
   writeln('Произведение: ',P:13:8);
   y:=p*s;
   writeln('Y:',y:10:9);
end.