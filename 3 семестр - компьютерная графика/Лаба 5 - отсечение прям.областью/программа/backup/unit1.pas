unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Edit2: TEdit;
    PaintBox1: TPaintBox;
    procedure Button1Click(Sender: TObject);
    procedure PaintBox1Click(Sender: TObject);
  private

  public

  end;


var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

function kod(x,y,xl,ya,xr,yb:longint):byte;
var kp:byte;
begin
  kp:=0;
  if x < xl then
     if y < ya then kp:=6
               else if y < yb then kp:=1
                              else kp:=5;
  if (x < xr) and (x > xl) then
     if y < ya then kp:=2
               else if y > yb then kp:=4;
  if (x > xr) then
     if y < ya then kp:=7
               else if y < yb then kp:=3
                              else kp:=8;
  kod:=kp;

end;

procedure Draw(x1,x2,y1,y2,xl,ya,xr,yb:longint);
var p1,p2,x,y:byte;
begin
  repeat
   p1:=kod(x1,y1,xl,ya,xr,yb);
   p2:=kod(x2,y2,xl,ya,xr,yb);
   if p1=0 then begin
                              x:=x1;
                              x1:=x2;
                              x2:=x;
                              y:=y1;
                              y1:=y2;
                              y2:=y;
                              p1:=p2;
                              end;
   if (p1=6) or (p1=1) or (p1=5) then begin
                              y1:=round(y1+(y2-y1)*(xl-x1)/(x2-x1));
                               x1:=xl;
                               end;
   if (p1=2) or (p1=7) or (p1=6) then begin
                 x1:=round(x1+(x2-x1)*(ya-y1)/(y2-y1));
                 y1:=ya;
                                end;
    if (p1=7) or (p1=3) or (p1=8) then begin
                                  y1:=round(y1+(y2-y1)*(xr-x1)/(x2-x1));
                                  x1:=xr;
                                       end;
    if (p1=4) or (p1=8) or (p1=5) then begin
                   x1:=round(x1+(x2-x1)*(yb-y1)/(y2-y1));
                   y1:=yb;
                   end;
    if (p1=8) or (p1=7) then begin
                   x1:=round(x1+(x2-x1)*(ya-y1)/(y2-y1));
                   y1:=round(y1+(y2-y1)*(xr-x1)/(x2-x1));
    end;
    until (p1=0) and (p2=0);
    Form1.PaintBox1.Canvas.Line(x1,y1,x2,y2);
    //Form1.paintBox1.Canvas.Rectangle(100,100,200,200);
   end;

procedure TForm1.PaintBox1Click(Sender: TObject);
begin
  paintBox1.Canvas.Rectangle(100,100,200,200);
  PaintBox1.Canvas.Line(50,150,200,200);
  PaintBox1.Canvas.Line(110,90,150,150);
  PaintBox1.Canvas.Line(110,110,220,80);
end;

procedure TForm1.Button1Click(Sender: TObject);
var  p1,p2:byte;
  x1,x2,y1,y2,xl,xr,ya,yb:longint;
begin
  PaintBox1.Canvas.Clear;
  Form1.paintBox1.Canvas.Rectangle(100,100,200,200);
  x1:=50;
  x2:=200;
  y1:=150;
  y2:=200;
  ya:=100;
  xl:=100;
  yb:=200;
  xr:=200;
   p1:=kod(50,150,100,100,200,200);
   edit1.text:=inttostr(p1);
   p2:=kod(200,200,100,100,200,200);
   edit2.Text:=inttostr(p2);
   if (p1=0) and (p2=0) then
          Form1.PaintBox1.Canvas.Line(x1,y1,x2,y2)
                         else draw(x1,x2,y1,y2,xl,ya,xr,yb);
   draw(110,150,90,150,100,100,200,200);
   draw(110,220,110,80,100,100,200,200);

end;

end.

