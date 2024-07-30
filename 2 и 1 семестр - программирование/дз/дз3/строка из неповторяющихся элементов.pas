program t6;
uses crt;
type mas=array[1..256] of string;
var c,s:string;
p:mas;
j,n,i:integer;
function unik(p:mas;n:integer;c:string):boolean;
var
  i,k:integer;
begin
  k:=0;
  for i:=1 to n do
    if p[i]=c then
      inc(k);
  unik:=k=1;
end;
begin
  writeln('enter text');
  readln(s);
  n := 0;
  for i:=1 to length(s) do
                  if (s[i]<>' ') and (i<>length(s)) then c := c+s[i]
                                                    else begin
                                                        if i=length(s) then c:=c+s[i];
                                                        inc(n);
                                                        p[n]:=c;
                                                        c:='';
                                                         end;
  for i:=1 to n do
            if unik(p,n,p[i]) then
      write(p[i],' ');
                                          
end.