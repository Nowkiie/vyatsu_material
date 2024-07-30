var
  s,f:string;
  p:integer;
  f1,f2:Text;
begin
  Assign(f1,'in.txt');
  Assign(f2,'out.txt');
  Reset(f1);
  Rewrite(f2);
  while not Eof(f1) do begin
    Readln(f1,s);
    p:=Pos(' ',s);
    f:=Copy(s,1,p-1);
    if (s[p+1]='2') or (s[p+3]='2') or (s[p+5]='2') or (s[p+7]='2') or (s[p+9]='2') or (s[p+11]='2') then
      Writeln(f2,f)
    end;
  Close(f1);
  Close(f2)
end.


{задание: в файле находится строка с фамилией и 6 оценок студента. В файл вывода
вывести фамилии тех,у которых нет двоек}