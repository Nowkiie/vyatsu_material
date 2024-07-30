program test;
var A: array[1..100] of string;
i,j,c:integer;
str: string;
u:boolean ;
begin
 c := 0;
 u := true;
 repeat
 writeln('Write string:');
 readln(str); 
 until (length(str)<=100);
 for i:=1 to 100 do A[i]:='';{инициализация массива строк}
 {идем по строке и заносим в массив каждую подстроку из 3х символов}
 for i:=1 to Length(str)-2 do
        for j:=i to i+2 do A[i]:=A[i]+str[j];  
 {поиск уникальных подстрок из 3х символов}        
 for i:=1 to Length(str)-2 do begin
        for j:=i+1 to Length(str) do
           if (A[i] = A[j]) and not (j=i) then u:=false;
           if u then Inc(c);
           u:=true;
                              end;
 Writeln(c)
end.