uses crt;
const n=4; eps=0.00001;
type matrix=array[1..n,1..n] of real;
     mas=array[1..n] of real;
var a:matrix;
    b,x,f:mas;
    i,j,l:integer;
    s,r,w,d:real;
 
function req(a:matrix):boolean;
 var i,j:integer;
 begin
   for i:=1 to n do
     for j:=1 to n do 
       if abs(a[i,i])<=abs(a[i,j]) then begin
         req:=false;
         break;
       end;
    req:=true;
 end;
 
begin
a[1,1]:=-0.77;      
a[1,2]:=-0.04;               
a[1,3]:=0.21;               
a[1,4]:=-0.18;               
 
a[2,1]:=0.45;
a[2,2]:=-1.23;
a[2,3]:=0.66;
a[2,4]:=0;
 
a[3,1]:=0.26;
a[3,2]:=0.34;
a[3,3]:=-1.11;
a[3,4]:=0;
 
a[4,1]:=0.05;
a[4,2]:=-0.26;
a[4,3]:=0.34;
a[4,4]:=-1.12;
 
b[1]:=-1.24; 
b[2]:=0.88;
b[3]:=-0.62;
b[4]:=1.17; 

writeln('Исходная система:');
for i:=1 to n do
 begin
  for j:=1 to n do
  write(a[i,j]:6:2);
  writeln(b[i]:7:1);
 end;
l:=1;//кол-во итерраций
//writeln('Сходится');
if req(a)=false then writeln('система не может быть решена итерационным методом')
                else begin
                   writeln('итерационный процесс сходится');
repeat
 // for i:=1 to n do x[i]:=0;
r:=0; // сброс значений точностей
writeln(l);
for i:=1 to n do//бежим по столбцам
   begin
        s:=0; //обнуляем сумму элементов строки
          for j:=1 to n do //бежим по строке
             begin
                  if i<>j then s:=s+a[i,j]*x[j] ; //вычисляем сумму элементов строки за исключением элемента, находящего на главной диагонали
             end;
         w:=(b[i]-s)/a[i,i];//вычисляем значение элемента главной диагонали
         d:=abs(w-x[i]);//вычисляем достигнутую точность
       if r<d then  r:=d;//находим максимальную из достигнутых точностей 
    x[i]:=w;//присваеиваем элементу матрицы x новое значение
    write(X[i]:6:2);
    end;
    writeln;
    inc(l);
    writeln('Погрешность: ',r);
until r<eps;// проверка на остановку
//end;
writeln('Корни:'); 
for i:=1 to n do
begin
writeln('x',i,'=',x[i]:5:3);
end;
f[1]:=-0.77*x[1]-0.04*x[2]+0.21*x[3]-0.18*x[4];
f[2]:=0.45*x[1]-1.23*x[2]+0.66*x[3]+0*x[4];
f[3]:=0.26*x[1]+0.34*x[2]-1.11*x[3]+0*x[4];
f[4]:=0.05*x[1]-0.26*x[2]+0.34*x[3]-1.12*x[4];
writeln();
writeln('Проверка в соответсвии с матрицей В');
writeln(f[1]);
writeln(f[2]);
writeln(f[3]);
writeln(f[4]);
end;
end.