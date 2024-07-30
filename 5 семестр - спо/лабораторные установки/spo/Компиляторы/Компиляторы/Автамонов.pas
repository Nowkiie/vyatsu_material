procedure XXX;
var A,B:integer;
begin
    A:=4;
    B:=A+5-A;
end;
procedure YYY;
var C,D,E:integer;
begin
	C:=(D-E)+(C-E);
	E:=(C-E)-(C-D)+E;
	D:=(C-D)+(C-E);
end;
var X:integer;
begin
    X:=10;
    XXX;
    YYY;
end.
