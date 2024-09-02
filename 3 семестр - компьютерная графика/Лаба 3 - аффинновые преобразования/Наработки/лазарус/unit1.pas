unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Image1Click(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;
  pol:array[1..4] of TPoint;
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
begin
 Form1.Canvas.Brush.Color:=clForm;
 form1.Canvas.Rectangle(0,0,300,320);
 Form1.Canvas.Line(0,160,300,160);
 Form1.Canvas.Line(150,0,150,320);
end;

procedure TForm1.Image1Click(Sender: TObject);
begin
 //Form1.Canvas.Line(150,0,150,320);
end;

procedure TForm1.Button1Click(Sender: TObject); // нарисовать многоугольник
begin
Form1.Canvas.Pen.Color:=ClBlack;
pol[1].x:=10;
pol[1].y:=20;
pol[2].x:=150;
pol[2].y:=50;
pol[3].x:=140;
pol[3].y:=150;
pol[4].x:=80;
pol[4].y:=80;
Form1.Canvas.Polygon(pol);
end;

procedure TForm1.Button2Click(Sender: TObject);// переместить
var i:integer;
begin
for i:=1 to 4 do begin
 pol[i].x:=pol[i].x+100;
 pol[i].y:=pol[i].y+50;
end;
Form1.Canvas.Polygon(pol);
end;

procedure TForm1.Button3Click(Sender: TObject); // отображение
var i:integer;
begin
  for i:=1 to 4 do begin
   pol[i].y:=160+pol[i].y;
  end;
  Form1.Canvas.Polygon(pol);
end;

procedure TForm1.Button4Click(Sender: TObject); //увеличение
var i:integer;
begin
 for i:=1 to 4 do begin
 pol[i].x:=pol[i].x*2;
 pol[i].y:=pol[i].y*2;
 end;
  Form1.Canvas.Polygon(pol);
end;

end.

