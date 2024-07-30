{параметризация: n-кол-во дисков,
init,aux,fin-название стержней,
Декомпозиция: if n=1 then writeln(init,#26,fin,'(',n,')')
База: tower(n-1,init,fin,aux); tower(n-1,aux,init,fin);}
program t6;
uses crt;
const n=4;
procedure tower(n:integer; init,aux,fin:char);
  begin
    if n=1 then writeln(init,#26,fin,'(',n,')')
           else begin
                 tower(n-1,init,fin,aux);
                 writeln(init,#26,fin,'(',n,')');
                 tower(n-1,aux,init,fin);
                end;
  end;
begin
  tower(n,'a','b','c');
  {readkey;}
  writeln('время работы ',milliseconds div 100,'миллисекунд(а)');
end.  