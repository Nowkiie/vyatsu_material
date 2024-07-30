uses crt;
const max_users = 20;
type TNode = record
      name,number : string;
   end;
     TBook = array [1..max_users] of TNode;

procedure Input(var b : TBook; const n : byte);
var
   i : byte;
begin
   for i := 1 to n do
    with b[i] do begin
       writeln('Пользователь №', i);
       write('Имя : '); readln(name);
       write('Телефон : '); readln(number);
       writeln;
    end;
end;

var
  book : TBook;
  count : byte;
begin
   clrscr;
   write('Количество записей : '); readln(count);
   Input(book, count);
   readln;
end.