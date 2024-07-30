var a:integer;
  mas:array[1..10] of integer;
  procedure sort(l,r:integer);
  var nl,nr,z,x:integer;
  begin
    nl := l;
    nr:=r;
    z := mas[(l+r)div 2];
    repeat
      while mas[nl]<z do
        nl:=nl+1;
      while mas[nr]>z do
        nr := nr-1;
      if nl<=nr then 
      begin
        x := mas[nl];
        mas[nl]:=mas[nr];
        mas[nr]:=x;
        nl := nl+1;
        nr:=nr-1;
      end;
    until nl>nr;
    if nr>l then 
      sort(l,nr);
    if nl<r then
      sort(nl,r);  
  end;
  begin
    for a:=1 to 10 do begin
      mas[a]:=random(19)-9;
      write(mas[a]:3);
      end;
      writeln;
      sort(1,10);
      for a:=1 to 10 do
        write(mas[a]:3);
  end.