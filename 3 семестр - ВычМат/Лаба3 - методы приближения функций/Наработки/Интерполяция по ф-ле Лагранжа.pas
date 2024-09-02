Uses crt;
Const nmax = 100;
type arr = array [1..nmax] of real;
Var n,k,m,I,j : integer;
    ct,u,f:real;
    x,y,r,pt:arr;
    
function func(x:real;const r:arr ):real;  
//var r:array [1..nmax] of real;
begin
  func:=r[1]+r[2]*x+r[3]*x*x+r[4]*x*x*x+r[5]*x*x*x*x+r[6]*x*x*x*x*x*x;
end;  
    
begin
clrscr;
repeat
write('Число узлов интерполирования от 2 до ',nmax,' n=');
readln(n);
until n in [2..nmax];
writeln('Введите массив узлов интерполирования:');
for i:=1 to n do
 begin
  write('x[',i,']=');
  readln(x[i]);
 end;
writeln('Введите массив значений функции в узлах:');
for i:=1 to n do
 begin
  write('y[',i,']=');
  readln(y[i]);
 end;
clrscr;
writeln('Массив узлов:');
for i:=1 to n do
write(x[i]:6:4,' ');
writeln;
writeln;
writeln('Массив значений:');
for i:=1 to n do
write(y[i]:6:4,' ');
writeln;
writeln;
for i:=1 to n do R[i]:=0;
for i:=1 to n do
 begin
  ct:=1;pt[1]:=1;k:=1;
  for j:=1 to n do
  if i<>j then
   begin
    ct:=ct*(x[i]-x[j]);
    pt[k+1]:=1;
    if k>1 then
    for m:=k downto 2 do
    pt[m]:=pt[m-1]-pt[m]*x[j];
    pt[1]:=-pt[1]*x[j];
    k:=k+1;
   end;
  u:=y[i]/ct;
  for m:=1 to n do
  r[m]:=r[m]+pt[m]*u;
 end;
f:=func(0.692,r);
writeln('Массив коэффициентов:');
for i:=1 to n do
write('R[', i, ']=', r[i]:6:4,' ');
writeln();
writeln(r[1]:3:2,r[2]:3:2,'*x+',r[3]:3:2,'*x^2',r[4]:3:2,'*x^3+',r[5]:3:2,'*x^4',r[6]:3:2,'*x^5+',r[7]:3:2,'*x^6');
writeln(f:6:4);
readln;
end.