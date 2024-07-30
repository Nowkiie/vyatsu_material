unit modul1143;

interface
uses graph;

procedure a(i,u: integer);
procedure b(i,u: integer);
procedure c(i,u: integer);
procedure d(i,u: integer);
procedure paint(x,y:real; i,u:integer);

implementation
//var v,p,u,dr,m:integer;

procedure a(i,u: integer);
  begin
    if i > 0 then begin
      d(i-1,u); LineTo(getX+u,getY);
      a(i-1,u); LineTo(getX,getY+u);
      a(i-1,u); LineTo(getX-u,getY);
      c(i-1,u);
    end;
  end;

procedure b(i,u: integer);
  begin
   if i > 0 then
   begin
      c(i-1,u); LineTo(getX-u,getY);
      b(i-1,u); LineTo(getX,getY-u);
      b(i-1,u); LineTo(getX+u,getY);
      d(i-1,u);
   end;
  end;

procedure c(i,u: integer);
  begin
   if i > 0 then
   begin
      b(i-1,u); LineTo(getX,getY-u);
      c(i-1,u); LineTo(getX-u,getY);
      c(i-1,u); LineTo(getX,getY+u);
      a(i-1,u);
   end;
  end;

procedure d(i,u: integer);
  begin
   if i > 0 then
   begin
      a(i-1,u); LineTo(getX,getY+u);
      d(i-1,u); LineTo(getX+u,getY);
      d(i-1,u); LineTo(getX,getY-u);
      b(i-1,u);
   end;
  end;

procedure paint(x,y:real; i,u:integer);
// var u:integer;
 begin
  moveto(round(x),round(y));
  b(i,u);
  end;
 end.

{BEGIN
 p:=3; u:= 6;
 write('Vvedite stepen krivoi Gilberta (po umolchaniu=3) ....> ');
 readln(v); If v in [1,2,3,4,5,6,7,8,9] then p:=v;
 write('Vvedite shirinu krivoi Gilberta (po umolchaniu=6) ....> ');
 readln(v); If v in [1,2,3,4,5,6,7,8,9] then u:=v;
 dr:=detect;
 initgraph(dr,m,'');
 delay(1000);
 moveto(640-u,480-u);
 b(p);
 readln;

end.}
