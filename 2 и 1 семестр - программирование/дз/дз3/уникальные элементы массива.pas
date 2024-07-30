program unikal;
const
  n=10;
type
  mas=array[1..20] of integer;
 
function unik(a:mas;n,c:integer):boolean;
var
  i,k:integer;
begin
  k:=0;
  for i:=1 to n do
    if a[i]=c then
      inc(k);
  unik:=k=1;
end;
 
var
  a:mas;
  i:integer;
begin
  randomize;
  for i:=1 to n do
    begin
      a[i]:=random(n);
      write(a[i],' ');
    end;
  writeln;
  for i:=1 to n do
    if unik(a,n,a[i]) then
      write(a[i],' ');
  readln;
end.
