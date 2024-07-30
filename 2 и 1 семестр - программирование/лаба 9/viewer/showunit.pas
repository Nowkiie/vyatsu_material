unit ShowUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, Grids;

type

  { TFormShow }

  TFormShow = class(TForm)
    StringGrid: TStringGrid;
    procedure ShowFile(path:string);
  private

  public

  end;
  TRecord = record
     surname: string[30];
     name: string[30];
     picture: string[30];//+
     price: LongWord;//+
     years: LongWord;
     country: string[20]; //+
  end;

var
  FormShow: TFormShow;

implementation

{$R *.lfm}


procedure TFormShow.ShowFile(path:string);
var
  r:TRecord;
  i:integer=1;
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
       StringGrid. Cells[3,i]:=inttostr(years);
       StringGrid. Cells[4,i]:=inttostr(price);
       StringGrid. Cells[5,i]:=country;
     end;
     Inc(i);
   end;
   CloseFile(f);

end;

end.

