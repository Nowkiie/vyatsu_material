uses crt;
const nmax=10;
var n:integer;
type
 Tmass=array[1..nmax] of real;
 Tmatrix=array[1..nmax,1..nmax] of real;
{перестановка строк при главном элементе=0}
procedure Per(k:integer;var a:Tmatrix;var p:integer);
var z:Real;
    j,i:integer;
begin
 z:=abs(a[k,k]);{модуль главного элемента}
 i:=k;{номер строки, в которой находится нулевой элемент}
 p:=0;{количество перестановок}
 for j:=k+1 to n do {ищем в столбце ниже}
  begin
   if abs(a[j,k])>z then {элемент по модулю больше}
    begin
     z:=abs(a[j,k]);//тут происходит проталкивание нулевого элемента вниз
     i:=j;
     p:=p+1;//счетчик перестановок
    end;
  end;
if i>k then{если нашли}
for j:=k to n do
 begin
  z:=a[i,j];
  a[i,j]:=a[k,j];{обмениваем строки}
  a[k,j]:=z;
 end;
end;
{определение знака определителя}
function Znak(p:integer):integer;
begin
if p mod 2=0 then
Znak:=1 else Znak:=-1;
end;
{вычисление определителя матрицы коэффициентов по Гауссу}
procedure Opr(var det:real;var a:tmatrix);
var k,i,j,p:integer;r:real;
begin
det:=1.0;
for k:=1 to n do
 begin
  if a[k,k]=0 then Per(k,a,p);//перестановка строк
  det:=znak(p)*det*a[k,k];//вычисление определителя
  for j:=k+1 to n do //пересчет коэффициентов
   begin //столбец
    r:=a[j,k]/a[k,k];//вычисление множителя
    writeln('множитель[',j,']=',r);
    for i:=k to n do begin //строка
    a[j,i]:=a[j,i]-r*a[k,i];//изменение элементов строки
    write(a[j,i]:6:3);
    end;
    writeln()
   end;
   writeln;
   inc(p);
 end;
end;
{вычисление алгебраических дополнений}
procedure Dop(d:tmatrix;var det1:real);
var k,i,j,p:integer;r:real;
begin
det1:=1.0;
for k:=2 to n do
 begin
  Per(k,d,p);
  det1:=znak(p)*det1*d[k,k];
  for j:=k+1 to n do
   begin
    r:=d[j,k]/d[k,k];
    for i:=k to n do
    d[j,i]:=(d[j,i]-r*d[k,i]);
   end;
 end;
 for i:=1 to n do begin
   for j:=1 to n do write(d[i,j]:8:3);
   writeln();
   end;
end;
{установление знака алгебраических дополнений}
function Znak1(i,m:integer):integer;
begin
if (i+m) mod 2=0 then
Znak1:=1 else Znak1:=-1;
end;
{формирование присоединенной матрицы}
Procedure Peresch(b:Tmatrix;var e:Tmatrix );
var i,m,k,j:integer;z,det1:real;d,c:Tmatrix;
begin
for i:=1 to n do
 begin
  for m:=1 to n do
   begin
    for j:=1 to n do  {перестановка строки}
     begin
      z:=b[i,j];
      for k:=i downto 2 do
      d[k,j]:=b[k-1,j];
      for k:=i+1 to n do
      d[k,j]:=b[k,j];
      d[1,j]:=z;
     end;
    for k:=1 to n do  {перестановка столбца}
     begin
      z:=d[k,m];
      for j:=m downto 2 do
      c[k,j]:=d[k,j-1];
      for j:=m+1 to n do
      c[k,j]:=d[k,j];
      c[k,1]:=z;
     end;
    Dop(c,det1); {вычисление дополнений}
    writeln();
    e[i,m]:=(det1)*znak1(i,m); {установление знака дополнений и }
   end;                       {формирование присоединенной матрицы }
 end;
end;
 
{транспонирование матрицы}
Procedure Trans(b:Tmatrix;var e:Tmatrix);
var i,j:integer;
begin
for i:=1 to n do begin
for j:=1 to n do begin
e[i,j]:=b[j,i];
end;
writeln;
end;
end;
 
{нахождение корней умножением обратной матрицы на столбец свободных членов}
Procedure Resh(n:integer;a:Tmatrix;b:Tmass;var x:Tmass);
var k,j:integer;z:real;
begin
for k:=1 to n do
 begin
  x[k]:=0;
  for j:=1 to n do
   begin
    z:=a[k,j]*b[j];
    x[k]:=x[k]+z;
   end;
 end;
end;
var a,a1,at,b,c,d:Tmatrix;
    f,x:Tmass;
    det:Real;
    i,j:integer;
begin
clrscr;
{решение системы}
{write('Порядок системы  до ',nmax,' n=');
readln(n);
until n in [1..nmax];
writeln('Введите коэффициенты системы:');
for i:=1 to n do
for j:=1 to n do
 begin
  write('a[',i,',',j,']=');
  readln(a[i,j]);
 end;
clrscr;
writeln('Введите свободнык члены:');
for i:=1 to n do
 begin
  write('f[',i,']=');
  readln(f[i]);
 end;
clrscr;}
n:=3;
a[1,1]:=4;      
a[1,2]:=8;               
a[1,3]:=7;               
               
 
a[2,1]:=1;
a[2,2]:=2;
a[2,3]:=2;

 
a[3,1]:=2;
a[3,2]:=3;
a[3,3]:=1;

 

 
f[1]:=9.0; 
f[2]:=2.0;
f[3]:=9.0;


writeln('Исходная система:');
for i:=1 to n do
 begin
  for j:=1 to n do
  write(a[i,j]:5:1);
  writeln(f[i]:7:1);
 end;
writeln;
a1:=a;{сделаем копию матрицы для нахождения определителя, она изменится}
Opr(det,a1);{вычисление определителя  матрицы}
writeln('Определитель=',det:0:0);
if det=0 then
 begin
  write('Решений не существует');
  readln;
  exit;
 end;
Peresch(a,b); { вычисление присоединенной матрицы}
Trans(b,c);{транспонирование присоединенной матрицы}
writeln('матрица определителей:');
for i:=1 to n do begin
    for j:=1 to n do write(c[i,j]:8:3);
    writeln;
    end;
writeln();
for i:=1 to n do
for j:=1 to n do 
c[i,j]:=c[i,j]/det;{деление на определитель=обратная матрица}
{нахождение корней}
writeln();
writeln('обратная матрица:');
for i:=1 to n do begin
  for j:=1 to n do write(c[i,j]:8:3);
  writeln();
end;
Resh(n,c,f,x);
for i:=1 to n do
writeln('x[',i,']=',x[i]:0:1);
f[1]:=4*x[1]+8*x[2]+7*x[3];
f[2]:=x[1]+2*x[2]+2*x[3];
f[3]:=2*x[1]+3*x[2]+x[3];
writeln();
writeln('Проверка в соответсвии с матрицей В');
writeln(f[1]);
writeln(f[2]);
writeln(f[3]);
readln;
end.