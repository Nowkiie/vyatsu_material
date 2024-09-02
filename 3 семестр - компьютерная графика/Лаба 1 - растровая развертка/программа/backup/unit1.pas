unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls,
  TAGraph, TASeries;

type

  { TForm1 }

  TForm1 = class(TForm)
    Board: TPaintBox;
    BrezCirc: TButton;
    Animation: TButton;
    Brez_8: TToggleBox;
    CheckBox1: TCheckBox;
    Clear: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    SimpCirc: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Label1: TLabel;
    Brez_4: TToggleBox;
    SimLine: TToggleBox;
    procedure AnimationClick(Sender: TObject);
    procedure BrezCircClick(Sender: TObject);
    procedure Brez_4Change(Sender: TObject);
    procedure Brez_8Click(Sender: TObject);
    procedure CheckBox1Change(Sender: TObject);
    procedure ClearClick(Sender: TObject);
    procedure SimLineClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Label1Click(Sender: TObject);
    procedure SimpCircClick(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }
Procedure DrawSimLine(x1,y1,x2,y2:integer;cl:Tcolor);
var l:integer;
  incx,incy,cx,cy:real;
begin
 if abs(x2-x1) > abs(y2-y1) then l:=abs(x2-x1)
                            else l:= abs(y2-y1);
 incx:=(x2-x1)/l;
 incy:=(y2-y1)/l;
 cx:=x1;
 cy:=y1;
 if (x1=x2) or (y1=y2) then
 while  not((cy=y2) and (cx=x2)) do begin
  Form1.Board.canvas.Pixels[round(cx),round(cy)]:=cl;
  cx:=cx+incx;
  cy:=cy+incy;
 end
 else while  not((cy=y2) or (cx=x2)) do begin
  Form1.Board.canvas.Pixels[round(cx),round(cy)]:=cl;
  cx:=cx+incx;
  cy:=cy+incy;
 end;
end;

procedure TForm1.SimLineClick(Sender: TObject);
var x1,x2,y1,y2:integer;
begin
  Form1.Label1.Caption:=' ';
  x1:=StrToInt(Edit1.Text);
  y1:=StrToInt(Edit2.Text);
  x2:=StrToInt(Edit3.Text);
  y2:=StrToInt(Edit4.Text);
  DrawSimLine(x1,y1,x2,y2,ClBlack);
end;

procedure DrawBrez4(x1,y1,x2,y2:integer;cl:TColor);
 var dx,dy,c,e:integer;
   x,y,s2,s1,i:integer;
   l:boolean;
 begin
   dx:=abs(x2-x1);
  dy:=abs(y2-y1);
  x:=x1; y:=y1;
  if (x2-x1>=0) then s1:=1
                else s1:=-1;
  if (y2-y1>=0) then s2:=1
                else s2:=-1;
 // s2:=sign(y2-y1);
  if dx>dy then l:=false
           else begin
             c:=dx;
             dx:=dy;
             dy:=c;
             l:=true;
           end;
   e:=2*dy-dx;
   for i:=1 to (dx+dy) do begin
     Form1.Board.Canvas.Pixels[x,y]:=cl;
     if e<0 then  begin
       if l=true then y:=y+s2
                  else x:=x+s1;
       e:=e+2*dy;
     end
            else begin
        if l=true then x:=x+s1
                  else y:=y+s2;
       e:=e-2*dx;
            end;
   end;
   Form1.Board.Canvas.Pixels[x,y]:=10;
 end;

procedure TForm1.Brez_4Change(Sender: TObject);
var
  x1,x2,y1,y2:integer;

begin
  x1:=StrToInt(Edit1.Text);
  y1:=StrToInt(Edit2.Text);
  x2:=StrToInt(Edit3.Text);
  y2:=StrToInt(Edit4.Text);
  DrawBrez4(x1,y1,x2,y2,clBlack);
end;

procedure TForm1.BrezCircClick(Sender: TObject);
var x,y,x_,r_,y_,e:integer;
begin
  x:=0;
  r_:=120;
  x_:=130;
  y_:=200;
  y:=r_;
  e:=3-2*r_;
   while ( x<y ) do begin

   Form1.Board.Canvas.Pixels[x_+x,y_+y]:=10;
   Form1.Board.Canvas.Pixels[x_+x,y_-y]:=10;
   Form1.board.Canvas.Pixels[x_-x,y_+y]:=10;
   Form1.Board.Canvas.Pixels[x_-x,y_-y]:=10;

   Form1.Board.Canvas.Pixels[x_+y,y_+x]:=10;
   Form1.Board.Canvas.Pixels[x_+y,y_-x]:=10;
   Form1.Board.Canvas.Pixels[x_-y,y_+x]:=10;
   Form1.Board.Canvas.Pixels[x_-y,y_-x]:=10;

   x:=x+1;
   if e<0 then e:=e+4*x+6
          else begin
            e:=e+4*(x-y)+10;
            y:=y-1;
          end;
   end;
   if x=y then begin
      Form1.Board.Canvas.Pixels[x_+x,y_+y]:=10;
   Form1.Board.Canvas.Pixels[x_+x,y_-y]:=10;
   Form1.board.Canvas.Pixels[x_-x,y_+y]:=10;
   Form1.Board.Canvas.Pixels[x_-x,y_-y]:=10;

   Form1.Board.Canvas.Pixels[x_+y,y_+x]:=10;
   Form1.Board.Canvas.Pixels[x_+y,y_-x]:=10;
   Form1.Board.Canvas.Pixels[x_-y,y_+x]:=10;
   Form1.Board.Canvas.Pixels[x_-y,y_-x]:=10;
   end;
end;

procedure delay(ms:double);
begin
  repeat
    application.ProcessMessages;
  until now>ms;
end;

procedure TForm1.AnimationClick(Sender: TObject);
var   angle:real;
  rad,centery,centerx:integer;
begin
  board.Invalidate();
  rad:=50;
  centery:=0;
  centerx:=0;
   Label6.Visible:=true;
  while (centerx<270) or (centery<350) do begin
  Label6.Left:=centerx+Round(rad*cos(angle));
  delay(10000);
  Label6.Top:=centery+Round(rad*sin(angle));
  delay(10000);
  angle:=angle+pi/5;
  delay(10000);
  centery:=centery+1;
  delay(10000);
  centerx:=centerx+1;
  end;
end;





procedure DrawBrez8(x1,y1,x2,y2:integer;cl:TColor);
var dx,dy,c,e:integer;
  x,y,s2,s1,i:integer;
   l:boolean;
begin
  dx:=abs(x2-x1);
  dy:=abs(y2-y1);
  x:=x1; y:=y1;
  if (x2-x1>=0) then s1:=1
                else s1:=-1;
  if (y2-y1>=0) then s2:=1
                else s2:=-1;
 // s2:=sign(y2-y1);
  if dx<dy then begin
             c:=dx;
             dx:=dy;
             dy:=c;
             l:=true;
           end
           else l:=false;
   e:=2*dy-dx;
   for i:=1 to dx do begin
     Form1.Board.Canvas.Pixels[x,y]:=10;
     while e>=0 do  begin
       if l=true then x:=x+s1
                  else y:=y+s2;
       e:=e-2*dx;
     end;
        if l=true then y:=y+s2
                  else x:=x+s1;
       e:=e+2*dy;
            end;
   Form1.Board.Canvas.Pixels[x,y]:=cl;
end;

procedure TForm1.Brez_8Click(Sender: TObject);
var x1,x2,y1,y2:integer;
begin
  x1:=StrToInt(Edit1.Text);
  y1:=StrToInt(Edit2.Text);
  x2:=StrToInt(Edit3.Text);
  y2:=StrToInt(Edit4.Text);
  DrawBrez8(x1,y1,x2,y2,clBlack)
end;

procedure TForm1.CheckBox1Change(Sender: TObject);
  var step,y,x,angle:real;
  base_x,base_y,length,i:integer;
begin
 step:=3.14/10;
 base_x:=130;
 base_y:=200;
 length:=120;
 if CheckBox1.Checked=true then
  if SimLine.Checked then
    for i:=0 to 20 do begin
      angle:=i*step;
      x:=cos(angle)*length+base_x;
      y:=sin(angle)*length+base_y;
      DrawSimLine(base_x,base_y,round(x),round(y),clBlack);
    end
  else if Brez_4.Checked then
    for i:=0 to 20 do begin
      angle:=i*step;
      x:=cos(angle)*length+base_x;
      y:=sin(angle)*length+base_y;
      DrawBrez4(base_x,base_y,round(x),round(y),clBlack);
    end
  else if Brez_8.Checked then
    for i:=0 to 20 do begin
      angle:=i*step;
      x:=cos(angle)*length+base_x;
      y:=sin(angle)*length+base_y;
      DrawBrez8(base_x,base_y,round(x),round(y),clBlack);
    end

                            else
   Board.Invalidate();
end;



procedure TForm1.ClearClick(Sender: TObject);
begin
   Board.Invalidate();
end;

procedure TForm1.FormCreate(Sender: TObject);
var angle:real;
begin
angle:=0;
end;

procedure TForm1.Label1Click(Sender: TObject);
begin

end;

procedure TForm1.SimpCircClick(Sender: TObject);
var y1:real;
   length,x1:integer;
begin
  x1:=0;
  length:=120;
    while x1<>160 do begin
    y1:=sqrt(length*length-x1*x1);
    Board.Canvas.Pixels[130+x1,200+round(y1)]:=10;
    Board.Canvas.Pixels[130+x1,200-round(y1)]:=10;
    Board.Canvas.Pixels[130-x1,200+round(y1)]:=10;
    Board.Canvas.Pixels[130-x1,200-round(y1)]:=10;
    x1:=x1+1;
    end;
end;





end.

