procedure BBB;
var I,J,K:integer;
begin
    I:=I+1;
    J:=5;
    K:=I+J;
end;
var B,C,I:integer;
begin
    BBB;
    I:=(B+5)-(C-7);
    B:=10;
    I:=(B+5)-(C-7);
    if I>10 then B:=C+15;
    B:=B+15;
end.
