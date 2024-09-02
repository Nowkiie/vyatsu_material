uses
  crt;
 
const
  e = 0.000001;
type
 marica = array[1..10,1..10] of real;
 vector = array[1..10] of real;
var
  //a,a1:matruica
  a,a1: array[1..10, 1..10] of real;
  b,b1: array[1..10] of real;
  x: array[1..10] of real; 
  n, i, j, k: integer;z, r, g,h: real;
 
begin
  clrscr;
  {write('Порядок: ');
  readln(n);
  writeln('Введите коэффициенты системы и свободные члены');
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      write('a[', i, ',', j, ']= ');
      readln(a[i, j]);
      a1[i,j]:=a[i,j];
    end;
    Writeln('b[', i, ']= ');
    readln(b[i]);
  end;}
 n:=4; 
  a[1,1]:=0.17;      
a[1,2]:=-0.13;               
a[1,3]:=-0.11;               
a[1,4]:=-0.12;               
 
a[2,1]:=1.00;
a[2,2]:=-1.00;
a[2,3]:=-0.13;
a[2,4]:=0.13;
 
a[3,1]:=0.35;
a[3,2]:=0.33;
a[3,3]:=0.12;
a[3,4]:=0.13;
 
a[4,1]:=0.13;
a[4,2]:=0.1;
a[4,3]:=-0.13;
a[4,4]:=-0.11;
 
b[1]:=0.22; 
b[2]:=0.11;
b[3]:=0.12;
b[4]:=1.00; 

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
    x[n]:=b[n]/a[n,n];
   // write(x[n]:3:5);
   // writeln;
  for i := n-1 downto 1 do { обратный ход Гаусса }
  begin
    h := b[i];
    for j := i + 1 to n do
    begin
      h:=h-x[j]*a[i,j]
      {g := a[k, j] * x[j];
      r := r + g;}
    end;
    x[i] := h / a[i, i];
  end;
  
  writeln();
  writeln('Корни системы:');
  for i := 1 to n do
    write('x[', i, ']=', x[i]:0:2, '   ');
  writeln();
  writeln('Проверка в соответствии с матрицей B: ');
 
  for i:=1 to n do
   begin 
    for j:=1 to n do  
      b1[i]:=b1[i]+a1[i,j]*x[j];     
     writeln(b1[i]:5:2,' ');
    end; 
  readln;
end.