const n =5;

type matr=array[1..n,1..n] of longint;
type m=array[1..n,1..n] of real;
var a,b,c:matr;
    d:m;
    i,j,dt:longint;

procedure PrintMatr(m:matr;n:integer);//вывод матрицы 
var i,j:integer;
begin
  for i:=1 to n do begin
    for j:=1 to n do
      write(m[i,j]:3); 
    writeln();
    end;
end;

procedure GetMatr(a:matr; var b:matr; i,j,n:integer);
var di,dj,ki,kj:integer;
begin
  di:=0;
  for ki:=1 to n-1 do begin 
    if (ki=i) then di:=1; 
    dj:=0;
    for kj:=1 to n-1 do begin
      if (kj=j) then dj:=1;
      b[ki,kj]:=a[ki+di,kj+dj];
    end;  
  end;
end;

function Determinate(a:matr; n:integer):longint;
var i,j,d,k:integer;
   b:matr;
begin
   d:=0; k:=1;
   if n<1 then begin
    writeln('determinate can not run. N=',n);
    halt;
   end;
   if n=1 then d:=a[1,1];
   if n=2 then d:=a[1,1]*a[2,2]-a[1,2]*a[2,1]
   else
    for i:=1 to n do
     begin
       GetMatr(a,b,i,1,n);
       writeln('i=',i,' a[',i,',1]=',a[i,1]);
       PrintMatr(b,n-1);
       d:=d+k*a[i,1]*Determinate(b,n-1);
       k:=-k;
     end;
   Determinate:=d;  
end;


begin
randomize;
for i:=1 to 3 do
    for j:=1 to 3 do
      a[i,j]:=random(3);
PrintMatr(a,3);
 dt:=Determinate(a,3);
writeln('=========');
writeln('Determinant=',dt);
writeln();
var k:=1;
for i:=1 to 3 do 
  for j:=1 to 3 do begin
    GetMatr(a,b,i,j,3);
   // writeln(' a[',i,',',j,']=',a[i,j]);
    c[j,i]:=k*Determinate(b,2);
   // writeln(' c[',j,',',i,']=',c[j,i]);
   // PrintMatr(b,2);
  //  writeln();
    k:=-k;
    end;
//PrintMatr(c,3);
writeln('==========');
writeln('Обратная матрица');
for i:=1 to 3 do begin
  for j:=1 to 3 do begin 
    write(c[i,j]/dt:5);
    end;
    writeln;
    end;
end.