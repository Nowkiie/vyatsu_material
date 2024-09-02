Program t6;
uses crt;
var M:array[1..3] of integer;
 i,z,k:integer;
 N:integer=3;
procedure DelElM(k:integer);
var i,j:integer;
  begin
   i:=1;
   while i<=N do begin
    if M[i]=k then begin
      if i=N then N:=N-1
              else begin
              for j:=i to n-1 do
                 M[j]:=M[j+1];
                 N:=N-1;
              end;
   end;
    inc(i);
   end;
   for  i:=1 to N do write(M[i]:3);
   writeln;
   //if N = 0 then Form2.timer1.Enabled:=false;
  end;
  
 begin
   for  i:=1 to N do M[i]:=i;
   randomize;
   while N<>0 do begin
   z := random(2)+1;
   writeln(z);
   if z mod N = 0 then k:=M[z]
                  else k:=M[z mod N];
   DElElM(k);
   end;
 end.