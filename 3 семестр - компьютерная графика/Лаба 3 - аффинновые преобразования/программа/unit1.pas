unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls;

const m=4;{фигур }
      n=3;{размер матриц коэффициентов}

type
  mas=array[1..m] of real;
     mtr=array[1..n,1..n] of real;
  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button10: TButton;
    Button11: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    PaintBox1: TPaintBox;
    procedure Button10Click(Sender: TObject);
    procedure Button11Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure PaintBox1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private

  public

  end;



var
  Form1: TForm1;

  xa,ya,xb,yb:mas;{фигуры после перемещения}
    a,r:mtr;{матрицы преобразований}
    xc,yc:integer;{центр экрана }
    ms:real;{масштаб для перевода реальных координат в экранные}
    s:string;{строка для вывода текста}
implementation

{$R *.lfm}

{ TForm1 }
procedure Osi(xc,yc:integer;ms:real);{рисование осей координат}
var i:integer;
begin
with Form1.PaintBox1.Canvas do begin
  Pen.Color:=ClBlue;
  Line(0,yc,Form1.Paintbox1.Width,yc);
  Line(xc,0,xc,Form1.Paintbox1.Height);
  for i:=1 to 10 do
    if i mod 2 =0 then begin
      Line(xc-3,yc-round(i*ms),xc+3,yc-round(i*ms));
      line(xc-3,yc+round(i*ms),xc+3,yc+round(i*ms));
      {подпись оси У}
   str(i,s);
   textout(xc-20,yc-round(i*ms),s);{соответственно засечкам}
   textout(xc-25,yc+round(i*ms),'-'+s);
   line(xc+round(i*ms),yc-3,xc+round(i*ms),yc+3); {засечки на оси Х}
   line(xc-round(i*ms),yc-3,xc-round(i*ms),yc+3);
   {подпись оси Х}
   textout(xc+round(i*ms),yc+10,s);
   textout(xc-round(i*ms),yc+10,'-'+s);
    end;
  {центр}
textout(xc+5,yc+10,'0');
{подписи концов осей}
textout(Form1.Paintbox1.width-10,yc-10,'X');
textout(xc+5,10, 'Y');
font.color:=clBlue;
end;
end;

procedure Draw(x,y:mas;ms:real;xc,yc:integer);{рисование фигуры}
begin
Osi(xc,yc,ms);
with Form1.PaintBox1.Canvas do begin
pen.color:=clRed;
moveto(xc+round(ms*x[1]),yc-round(ms*y[1]));
lineto(xc+round(ms*x[3]),yc-round(ms*y[3]));
lineto(xc+round(ms*x[2]),yc-round(ms*y[2]));
lineto(xc+round(ms*x[4]),yc-round(ms*y[4]));
lineto(xc+round(ms*x[1]),yc-round(ms*y[1]));
end;
end;

procedure Ed; { присвоение матрице R значения единичной }
var i,j:integer;
begin
for  i:=1 to n do
 begin                             {  1 0 0  }
  for j:=1 to n do  r[i,j]:=0; {  0 1 0  }
  r[i,i]:=1;                       {  0 0 1  }
 end;
end;
procedure Mult; {умножение матриц А и R:  R = B = A*R }
var b:mtr;
    z:real;
    i,j,k:integer;
begin
for i:=1 to n do
for j:=1 to n do
 begin
  z:=0;
  for k:=1 to n do
  z:=z+a[i,k]*r[k,j];
  b[i,j]:=z
 end;
for i:=1 to n do
for j:=1 to n do
r[i,j]:=b[i,j]
end;
procedure Stretch;  {расчет матриц А и R для растягивания фигуры}
var i,j:integer;
begin
for  i:=1 to n do
 begin                             {  1  0  0  }
  for j:=1 to n do a[i,j]:=0;      {  0 1.05  0 }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[2,2]:=1.05;{коэффициент растяжения}
a[1,1]:=1.05;
Mult;
end;
procedure Compress;  {расчет матриц А и R для сжатия фигуры}
var i,j:integer;
begin
for i:=1 to n do
 begin                         {  1  0  0  }
  for j:=1 to n do a[i,j]:=0;  {  0 1.05  0  }
  a[i,i]:=1;                   {  0  0  1  }
 end;
a[2,2]:=0.95;{коэффициент растяжения}
a[1,1]:=0.95;
Mult;
end;
procedure MirrorX;  {расчет матриц А и R для отражения фигуры по Х}
var i,j:integer;
begin
for i:=1 to n do
 begin                             {  1  0  0  }
  for j:=1 to n do a[i,j]:=0;      {  0 -1  0  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[2,2]:=-1;
Mult;
end;
procedure MirrorY;  {расчет матриц А и R для отражения фигуры по Х}
var i,j:integer;
begin
for i:=1 to n do
 begin                             { -1  0  0  }
  for j:=1 to n do a[i,j]:=0;      {  0  1  0  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[1,1]:=-1;
Mult;
end;
procedure MoveY(dy:integer);  {расчет матриц А и R для перемещения фигуры по Y}
var i,j:integer;
begin
for i:=1 to n do
 begin                             {  1  0  0  }
  for j:=1 to n do a[i,j]:=0;      {  0  1 dy  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[2,3]:=dy;
Mult;
end;
procedure MoveX(dx:integer);  {расчет матриц А и R для перемещения фигуры по Y}
var i,j:integer;
begin
for  i:=1 to n do
 begin                             {  1  0  dx }
  for j:=1 to n do a[i,j]:=0;  {  0  1  0  }
  a[i,i]:=1;                       {  0  0  1  }
 end;
a[1,3]:=dx;
Mult;
end;
procedure Rotate(u:real); {расчет матриц А и R для поворота  фигуры}
var c, s: real;   {---н  угол alfa(р д)---}
    i,j:integer;
begin                    {  cos(u) -sin(u) 0  }
for i:=1 to 3 do     {  sin(u)  cos(u) 0  }
for j:=1 to 3 do     {   0       0     1  }
a[i,j]:=0;
a[3,3]:=1;
c:=cos(u);   a[1,1]:= c;  a[2,2]:=c;
s:=sin(u);   a[1,2]:=-s;  a[2,1]:=s;
Mult;
end;

procedure New_XY;{расчет новых координат фигуры по исходным}
var i,j:integer;
begin           {с использованием матрицы преобразования R}
for  i:=1 to m do
 begin
  xb[i]:=xa[i]*r[1, 1]+ ya[i]*r[1, 2]+ r[1, 3];
  yb[i]:=xa[i]*r[2, 1]+ ya[i]*r[2, 2]+ r[2, 3]
 end;
end;

procedure TForm1.PaintBox1Click(Sender: TObject);
begin
 xc:=PaintBox1.Width div 2;
 yc:=PaintBox1.Height div 2;
 ms:=(yc-30)/10;
  Osi(xc,yc,ms);
 xa[1]:=-2;ya[1]:=1;
 xa[2]:=2;ya[2]:=2;
 xa[3]:=2;ya[3]:=-2;
 xa[4]:=-2;ya[4]:=-1;
  draw(xa,ya,ms,xc,yc);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Paintbox1.Canvas.clear;
      Ed;
      Stretch; { растяжение}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button10Click(Sender: TObject);
var u:integer;
begin
  u:=0 ;
  while u <> 15 do begin
   Paintbox1.Canvas.clear;
      Ed;
      Stretch; { растяжение}
      New_XY;
      xa:=xb;ya:=yb;
      Rotate(pi/3); {поворот на  pi/4 относительно начала координат}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;{запомним новое положение}
      inc(u);
      sleep(150);
      Application.ProcessMessages;
      end;
end;

procedure TForm1.Button11Click(Sender: TObject);
var u:integer;
begin
   u:=0 ;
  while u <> 15 do begin
   Paintbox1.Canvas.clear;
      Ed;
      Compress; { растяжение}
      New_XY;
      xa:=xb;ya:=yb;
      Rotate(-pi/3); {поворот на  pi/4 относительно начала координат}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;{запомним новое положение}
      inc(u);
      sleep(150);
      Application.ProcessMessages;
      end;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
      Paintbox1.Canvas.clear;
      Ed;
      Compress; { сжатие}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
      Paintbox1.Canvas.clear;
      Ed;
      MirrorX; { отражение по Х}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
      Paintbox1.Canvas.clear;
      Ed;
      MirrorY; { отражение по Х}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
       Paintbox1.Canvas.clear;
      Ed;
      MoveX(1); { отражение по Х}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
   Paintbox1.Canvas.clear;
      Ed;
      MoveX(-1); { отражение по Х}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
    Paintbox1.Canvas.clear;
      Ed;
      MoveY(1); { отражение по Y}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
    Paintbox1.Canvas.clear;
      Ed;
      MoveY(-1); { отражение по Y}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  Paintbox1.Canvas.clear;
      Ed;
      Rotate(pi/3); {поворот на  pi/4 относительно начала координат}
      New_XY;
      Draw(xb,yb,ms,xc,yc);
      xa:=xb;ya:=yb;{запомним новое положение}
end;

end.

