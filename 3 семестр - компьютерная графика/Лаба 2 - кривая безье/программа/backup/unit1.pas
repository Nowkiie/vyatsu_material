unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Image1: TImage;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;
  P: array[0..2] of record
    x,y: integer;
  end;

  B: array[0..2] of record
    x,y: integer;
  end;

implementation

{$R *.lfm}

{ TForm1 }

procedure spline(x1,x2,x3,y1,y2,y3:integer);
var
  t: real;
  i: integer;
  begin
    t := 0;
    P[0].x := x1; P[0].y := y1;
  P[1].x := x2; P[1].y := y2;
  P[2].x := x3; P[2].y := y3;

  Form1.Image1.Canvas.Pen.Color := clRed;
  Form1.Image1.Canvas.Line(P[0].x,P[0].y,P[1].x,P[1].y);
  Form1.Image1.Canvas.Line(P[1].x,P[1].y,P[2].x,P[2].y);


  Form1.Image1.Canvas.Pen.Color := clBlue;
  Form1.Image1.Canvas.Pen.Width := 1;
  Form1.Image1.Canvas.Pen.Style := psDash;
  while t < 1 do

    begin

      B[0].x := P[0].x; B[0].y := P[0].y;
      B[1].x := P[1].x; B[1].y := P[1].y;
      B[2].x := P[2].x; B[2].y := P[2].y;

      for i := 0 to 1 do
      begin
        B[i].x := B[i].x + round(t * (B[i + 1].x - B[i].x));
        B[i].y := B[i].y + round(t * (B[i + 1].y - B[i].y));
      end;
     sleep(150);
      application.ProcessMessages;
      Form1.Image1.Canvas.Line(B[0].x,B[0].y,B[1].x,B[1].y);
      t := t + 0.1;
    end;

  end;

procedure TForm1.FormCreate(Sender: TObject);
begin
   clientwidth := 600;
  clientheight := 600;
  Image1.Width := clientwidth;
  Image1.Height := clientheight;

end;

procedure TForm1.Button1Click(Sender: TObject);
begin
    Image1.Canvas.Brush.Color := clWhite;
  Image1.Canvas.FillRect(0,0,Image1.Width,Image1.Height);
  Spline(100,200,300,500,300,400);
  Spline(300,400,500,400,500,300);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Image1.Canvas.Clear;
end;


end.

