unit ShowUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, Grids,
  Generate;

type

  { TFormShow }

  TFormShow = class(TForm)
    StringGrid: TStringGrid;
    procedure ShowFile(path:string);
  private

  public

  end;

var
  FormShow: TFormShow;

implementation



{$R *.lfm}
procedure TFormShow.ShowFile(path:string);
var
  r:TRecord;
  i:integer=0;
  f:file of TRecord;
begin
   AssignFile(f, path);
   Reset(f);
   while not eof(f) do begin
     read (f, r);
     with r do
     begin
       StringGrid. Cells[0,i]:=surname;
       StringGrid. Cells[1,i]:=name;
       StringGrid. Cells[2,i]:=picture;
       StringGrid. Cells[3,i]:=inttostr(price);
       StringGrid. Cells[4,i]:=inttostr(years);
       StringGrid. Cells[5,i]:=country;
     end;
     Inc(i);
   end;
   CloseFile(f);

end;

end.

