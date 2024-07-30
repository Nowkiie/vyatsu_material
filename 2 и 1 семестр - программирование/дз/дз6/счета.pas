program t6;
uses crt;
var
  s,f,c:string;
  p:integer;
  f1,f2:Text;
begin
  ClrScr;//все неверно
  writeln('enter the currence(dollar,euro,rub,yek)');
  readln(c);
  Assign(f1,'in.txt');
  Assign(f2,'out.txt');
  Reset(f1);
  Rewrite(f2);
  while not Eof(f1) do begin
    Readln(f1,s);
    p:=Pos(' ',s);
    f:=Copy(s,1,p-1);
    if (s[p+1]=c[1]) then
      Writeln(f2,f)
    end;
  Close(f1);
  Close(f2);
end.
{имеется типизированный файл,в котором размещена информация о наличии денежных средств
на банковском счёте(номер счёта - валюта- размер). Прочитать этот файл и записать записать в нетипизированный файл по пять штук
номера счетов принадлежащих заданной валюте)