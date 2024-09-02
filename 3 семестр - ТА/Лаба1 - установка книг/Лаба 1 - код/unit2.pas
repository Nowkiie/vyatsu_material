unit unit2;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ColorBox, StdCtrls,
  Menus, Inifiles, FileUtil;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    ColorBox1: TColorBox;
    ColorBox2: TColorBox;
    MainMenu1: TMainMenu;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    procedure Button1Click(Sender: TObject);
    procedure ColorBox1Change(Sender: TObject);
    procedure ColorBox1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormCreate(Sender: TObject);
    procedure MenuItem1Click(Sender: TObject);
    procedure MenuItem2Click(Sender: TObject);
  private

  public

  end;

type
  clbox = array [0..2] of integer;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

//проверка на присутствие
function IsThere(a:clbox; n:integer; x:integer):boolean;
var i:integer;
  b:boolean;
  begin
     for i:=0 to n do
       if a[i]=x then begin
         b:=true;
         break;
       end
     else b:=false;
     Result:=b;
  end;


procedure TForm1.ColorBox1Change(Sender: TObject);
var d:integer;
  a:clbox;
  bool:boolean;
begin
   ColorBox1.ItemIndex:=ColorBox1.Selected;
   d:=ColorBox1.ItemIndex;
   bool:=IsThere(a,2,d);
   if bool = true then begin
     showmessage('ты не прав');
     ColorBox1.Selected:=ColorBox1.Colors[a[0]];
   end
   else begin
        ColorBox1.Selected:=ColorBox1.Colors[d];
        a[0]:=d;

   end;
end;

procedure TForm1.ColorBox1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin

end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  //ColorBox1.ItemIndex:=ColorBox1.Items.IndexOf();
end;

procedure TForm1.MenuItem1Click(Sender: TObject); //сохранить
var Ini: Tinifile;
  a:clbox;
begin
  Ini:=TiniFile.Create(extractfilepath(paramstr(0))+'MyIni.ini');
  Ini.WriteInteger('color','1',ColorBox1.ItemIndex);
  Ini.WriteInteger('color','2',ColorBox2.ItemIndex);
end;

procedure TForm1.MenuItem2Click(Sender: TObject);
var Ini: Tinifile;
  d:TColor;
begin
  Ini:=TiniFile.Create(extractfilepath(paramstr(0))+'MyIni.ini');
  ColorBox1.Selected:=ColorBox1.Colors[Ini.ReadInteger('color','1',ColorBox1.ItemIndex)];
  //colorBox1.ItemIndex:=ColorBox1.Items.IngexOf(d);
end;



procedure TForm1.Button1Click(Sender: TObject);
var bool:boolean;
  i,temp,z:integer;
  a: clbox;
begin
   randomize;
   z:=0;
   for i:= 1 to 2 do begin
        temp:=random(3);
        bool:=IsThere(a,i,temp);
        if bool=false then
        a[z] :=temp;
        inc(z);
   end;
  ColorBox1.Selected:=ColorBox1.Colors[a[0]];
  ColorBox2.Selected:=ColorBox2.Colors[a[1]];

end;

end.

