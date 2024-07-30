Program t6;
uses crt;
var a:array[1..100] of integer;
i,p,k,n,j,max:integer;
begin
  readln(n);
  for  i:=1 to n  do read(a[i]);
  writeln;
  max := 0;
  i := 2;
  p := 0;
  while i<=n do 
      if a[i]*a[i-1]<0 then begin
                         j := i;
                         k := 0;
                         while (a[j]*a[j-1]<0) and (j<=n) do begin
                                                        j := j+1;
                                                        k:=k+1;
                                                             end;
                         if k>max then max:=k+1;
                         if k>0 then p:=p+1;
                         i := j+1;
                         end
                         else i:=i+1;
                         writeln('количество интервалов знакочередования=',p);
                         writeln('наибольшая длина интервала=',max);
                         
end.