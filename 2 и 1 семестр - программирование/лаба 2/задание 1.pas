program t6;
uses crt;
var a:array [1..100] of integer;
i,k,n:integer;
begin
  writeln('ввод: ');
  readln(n);{ вводим кол-во элементов}
  {кол-во элементов не должно быть отрицательным числом или числом больше 100,
  если одно из условий нарушено просим повторить ввод}
  while (n<=0)or  (n>100) do begin 
  if n<=0 then writeln('введите положительное число');
  if n>100 then writeln('ввведите число, не превышающие 100');
  writeln('повторите ввод: ');
  readln(n);
  end;
  for i:=1 to n do {формируем массив}
    read(a[i]); 
  k:=0;  
  for i:=2 to n do {проходя по массиву, проверяем выполнение условий}
    if (a[i] >= a[i-1]) then inc(k);
    {в зависимости от значения к делаем вывод о монотонности массива}
  if k=0 then writeln('монотонный')
          else if k=n-1 then writeln('монотонный')
                        else writeln('не монотонный');
end.