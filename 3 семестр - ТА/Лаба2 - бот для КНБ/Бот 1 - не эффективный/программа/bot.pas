unit bot;

interface

const
   rock:integer=1;
   paper:integer=2;
   scissors:integer=3;

//procedure setParameters(setCount:integer; winsPerSet:integer);

//procedure OnGameStart();

function Choose(previousOpponentChoice:integer):integer;

//procedure OnGameEnd();

implementation

function search1(s:string;number:integer):real; //s-сходная послед-ть, number -номер фигуры, которую ищем
var 
i,k:integer;
begin
  k:=0;
  for i:=1 to length(s) do
    if s[i]=IntToStr(number) then inc(k);
  search1:=k/length(s);
end;

function search2(s:string;number:integer;previousOpponentChoice:integer):real;//s-исходная послед-ть, number-номер фигуры, ...-ход соперника
var 
  i,k,p:integer;
  str,ds:string; //str-подстрока(number+...   , ds- дубликат подстроки
begin
  str:=intToStr(previousOpponentChoice)+IntToStr(number);
  ds:=s;
  k:=0;
  p:=1;
  while p<>0 do begin
    p:=pos(str,ds);
    if p<>0 then begin
      inc(k);
      delete(ds,1,p);
    end;
  end;
  search2:=k/length(s);
end;

function Mult(a,b,c:real):real;
var m:array[1..3]of real;
i:integer;
rez:real;
begin
  rez:=1;
  m[1]:=a;
  m[2]:=b;
  m[3]:=c;
  for i:=1 to 3 do 
    if m[i]<>0 then rez:=rez*m[i];
  if ((m[1]=1) or (m[2]=1) or (m[3]=1)) and (rez=1)  then Mult:=1
                                                     else if (m[1]=0) or (m[2]=0) or (m[3]=0) then Mult:=0
                                                                                              else Mult:=rez;
end; 

function Hod(r,p,sc:real;s:string):integer;
begin
  if (r>sc) and (r>p) then hod:=paper
                      else if (sc>r) and (sc>p) then hod:=rock
                                                else hod:=scissors;
  if (sc=r) then hod:=paper
            else if (sc=p) then hod:=rock
                           else hod:=paper;
  if (sc=r) and (sc=p) then begin
                  if s[1]='1' then hod:=paper;
                  if s[1]='2' then hod:=rock;
                  if s[1]='3' then hod:=scissors;
                 end;
end; 

function Choose(previousOpponentChoice:integer):integer;
var r1,r2,r3:real;
  p1,p2,p3:real;
  s1,s2,s3:real;
  s:string;
  r,p,sc:real;
begin
  if previousOpponentChoice=0 then choose:=paper
                              else begin
   s:=s+IntToStr(previousOpponentChoice);
   r1:=search1(s,1);
   r2:=search2(s,1,previousOpponentChoice);
   r3:=search2(s,1,1);
   r:=Mult(r1,r2,r3);
   
   p1:=search1(s,2);
   p2:=search2(s,2,previousOpponentChoice);
   p3:=search2(s,2,2);
   p:=Mult(p1,p2,p3);
   
   s1:=search1(s,3);
   s2:=search2(s,3,previousOpponentChoice);
   s3:=search2(s,3,3);
   sc:=Mult(s1,s2,s3);
   
   choose:=Hod(r,p,sc,s);
                              end;
end;

end.
