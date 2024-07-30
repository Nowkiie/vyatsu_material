unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs;

type

  { TForm1 }

  TForm1 = class(TForm)
    procedure FormCreate(Sender: TObject);
  private

  public

  end;

var
  Form1: TForm1;
  b:Tbitmap;
  cnt1,cnt2:integer;
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
var i,j,cnt:integer;
begin
  b:=TBitmap.Create;
  b.loadFromFile('C:\Users\1\Desktop\практика\День 1\task3.bmp');
  for i:=0 to b.Width-1 do
     for j:=0 to b.Height-1 do begin
      if b.canvas.Pixels[i,j] = clBlack then inc(cnt);
     // if cnt mod 400 > 100 then cnt:=cnt+1;
     end;
  b.Free;
  Caption:=IntToStr(cnt div 400);
end;

end.

