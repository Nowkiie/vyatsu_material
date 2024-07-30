unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls,
  Menus, PrintersDlgs, Printers, StrUtils;

type

  { TForm1 }

  TForm1 = class(TForm)
    FontDialog1: TFontDialog;
    MainMenu1: TMainMenu;
    Memo1: TMemo;
    MenuItem1: TMenuItem;
    MenuItem10: TMenuItem;
    MenuItem11: TMenuItem;
    MenuItem12: TMenuItem;
    MenuItem13: TMenuItem;
    MenuItem14: TMenuItem;
    MenuItem15: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem3: TMenuItem;
    MenuItem4: TMenuItem;
    MenuItem5: TMenuItem;
    MenuItem6: TMenuItem;
    MenuItem7: TMenuItem;
    MenuItem8: TMenuItem;
    MenuItem9: TMenuItem;
    OpenDialog1: TOpenDialog;
    PrintDialog1: TPrintDialog;
    SaveDialog1: TSaveDialog;
    procedure Memo1Change(Sender: TObject);
    procedure MenuItem10Click(Sender: TObject);
    procedure MenuItem11Click(Sender: TObject);
    procedure MenuItem12Click(Sender: TObject);
    procedure MenuItem13Click(Sender: TObject);
    procedure MenuItem14Click(Sender: TObject);
    procedure MenuItem15Click(Sender: TObject);
    procedure MenuItem1Click(Sender: TObject);
    procedure MenuItem4Click(Sender: TObject);
    procedure MenuItem5Click(Sender: TObject);
    procedure MenuItem6Click(Sender: TObject);
    procedure MenuItem7Click(Sender: TObject);
    procedure MenuItem8Click(Sender: TObject);
    procedure MenuItem9Click(Sender: TObject);
    procedure SaveChanges;
  private

  public

  end;

var
  Form1: TForm1;
  FileWork:String;

implementation

{$R *.lfm}




procedure SaveAs;
begin
  if Form1.SaveDialog1.Execute then
  begin
    Form1.Memo1.Lines.SaveToFile(Form1.SaveDialog1.FileName);
    FileWork:=Form1.SaveDialog1.FileName;
  end;
end;

{ TForm1 }
procedure TForm1.SaveChanges;
  begin
   if messagedlg('Сохранить изменения в файле?',mtinformation,
   [mbYes,mbNo,mbCancel],0) = mrYes then begin
                                          if FileWork='' then SaveAs
                           else Memo1.Lines.SaveToFile(fileWork);
                                          Form1.close;
                                          end
   else if messagedlg('Сохранить изменения в файле?',mtinformation,
   [mbYes,mbNo,mbCancel],0) = mrNo then Form1.close
   else Form1.Show;
  end;

procedure TForm1.MenuItem1Click(Sender: TObject);
begin

end;

procedure TForm1.MenuItem4Click(Sender: TObject); //создать
begin
  FileWork:='';
  Memo1.Clear;
end;

procedure TForm1.Memo1Change(Sender: TObject);
begin

end;

procedure TForm1.MenuItem10Click(Sender: TObject); //копировать
begin
 Memo1.CopyToClipboard;
end;

procedure TForm1.MenuItem11Click(Sender: TObject); // вставить
begin
  Memo1.PasteFromClipboard;
end;

procedure TForm1.MenuItem12Click(Sender: TObject);//перенос по словам
begin
  if Memo1.WordWrap then
  begin
    Memo1.WordWrap:=false;
    Memo1.ScrollBars:=ssBoth;
    MenuItem12.Checked:=false;
  end
  else
  begin
    Memo1.WordWrap:=true;
    Memo1.ScrollBars:=ssVertical;
    MenuItem12.Checked:=true;
    end;
end;

procedure TForm1.MenuItem13Click(Sender: TObject); //шрифт
begin
  if fontDialog1.Execute then Memo1.Font:=FontDialog1.Font;
end;

procedure TForm1.MenuItem14Click(Sender: TObject);
var
  lh,i:integer;
begin
  if PrintDialog1.Execute then begin
  Printer.BeginDoc;
  Printer.Canvas.Font.Name:='Courier New';
  Printer.Canvas.Font.Size:=10;
  Printer.Canvas.Font.Color:=clBlack;
  lh:=round(1.2*abs(printer.Canvas.TextHeight('I')));
  for i:=0 to Memo1.Lines.Count-1 do begin
    if (i>0) and (i mod 40=0) then Printer.NewPage;
    Printer.Canvas.TextOut(10,3*lh+lh*(i mod 40),Memo1.Lines[i]);
  end;
  Printer.EndDoc;
  ShowMessage('Печать завершена');
end;
end;

procedure TForm1.MenuItem15Click(Sender: TObject);//статистика
var
  words, syms, spaces, strings, i, cnt : Longint;
  message : String;
begin
  words := 0;
  syms := 0;
  spaces := 0;
  strings := Memo1.Lines.Count;
  for i := 0 to strings - 1 do
  begin
    inc(syms, Length(Memo1.Lines.Strings[i]));
    cnt := WordCount(Memo1.Lines.Strings[i], [' ']);
    inc(spaces, cnt - 1);
    inc(words, cnt);
  end;
  message := 'Words: ' + IntToStr(words) + chr(10) +
             'Symbols (with spaces): ' + IntToStr(syms) + chr(10) +
             'Symbols (without spaces): ' + IntToStr(syms - spaces) + chr(10) +
             'Lines: ' + IntToStr(strings);
  MessageDlg('Statistics', message, mtInformation, [mbClose], 0);
end;



procedure TForm1.MenuItem5Click(Sender: TObject); //открыть
begin
  If OpenDialog1.Execute then
  begin
    Memo1.Lines.LoadFromFile(OpenDialog1.FileName);
    FileWork:=OpenDialog1.FileName;
  end;
end;

procedure TForm1.MenuItem6Click(Sender: TObject); // сохранить
begin
  if FileWork='' then SaveAs
                 else Memo1.Lines.SaveToFile(fileWork);
end;

procedure TForm1.MenuItem7Click(Sender: TObject); //сохранить как
begin
  SaveAs;
end;

procedure TForm1.MenuItem8Click(Sender: TObject); //выход
begin
  Close;
end;

procedure TForm1.MenuItem9Click(Sender: TObject); //вырезать
begin
  Memo1.CutToClipboard;
end;

end.

