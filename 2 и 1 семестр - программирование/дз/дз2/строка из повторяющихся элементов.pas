program t6;
uses crt;
var c,s:string;
p:array[1..256] of string;
j,n,i:integer;
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
                                                        {writeln(c);}
                                                        c:='';
                                                         end;
  for i:=1 to n do
            for j:=i to length(s) do
              if (p[i]=p[j]) and (i<>j) then write(p[i],' ');
                                          
end.