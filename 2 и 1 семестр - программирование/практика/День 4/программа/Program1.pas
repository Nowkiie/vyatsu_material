type po=record 
a,b:integer; 
end;

var f:text;
b:array of boolean; int:array of integer;
gr:array of po; col:longint;
io,io1,i,po2:longint;
po1:int64;

procedure incer(); 
var a:integer; 
begin 
  for a:=0 to b.Length-1 do 
    if b[a] then b[a]:=false 
            else begin 
              b[a]:=true; 
              exit; 
              end; 
end;
function ender():boolean; 
var a:boolean; 
i1:integer; 
begin 
  a:=true; 
  for i1:=0 to b.Length-1 do a:=(a) and (b[i1]); ender:=not(a); end;

begin
Assign(f,'task2.txt');
reset(f);
read(f,io);
setlength(b,io);
setlength(int,io);
for i:= 0 to io-1 do
   begin 
     b[i]:=false; 
     read(f,io1); 
     int[i]:=io1; 
     end;
b[0]:=true;
read(f,io);
setlength(gr,io);
for i:= 0 to io-1 do begin 
  read(f,io1); 
  gr[i].a:=io1;
  read(f,io1);
  gr[i].b:=io1; 
  end;
close(f);
Assign(f,'z3.txt');
rewrite(f); 
write(f,'0');
 close(f);


while ender do begin
col:=0;
while (col<gr.Length-1)and((b[gr[col].a-1])or(b[gr[col].b-1])) do 
  inc(col);
  if (col=gr.Length-1)and((b[gr[gr.Length-1].a-1])or(b[gr[gr.Length-1].b-1]))and((b[gr[gr.Length-2].a-1])or(b[gr[gr.Length-2].b-1])) then begin
     po1:=0; po2:=0;
      for i:=0 to b.Length-1 do 
        if not(b[i]) then begin 
          po1:=po1+int[i]; 
          inc(po2);
          end;
reset(f);
read(f,io);
close(f);
if po1>io then begin
rewrite(f);
writeln(f,po1);
writeln(f,po2);
for i:=0 to b.Length-1 do if not(b[i]) then write(f,int[i],' ');
close(f);
end;
end;
incer;
end;
end.