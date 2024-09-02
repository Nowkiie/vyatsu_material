unit Unit3;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, Buttons,
  ColorBox,Inifiles;

type

  { TForm3 }

  TForm3 = class(TForm)
    Button1: TButton;
    ColorBox1: TColorBox;
    ColorBox10: TColorBox;
    ColorBox11: TColorBox;
    ColorBox12: TColorBox;
    ColorBox13: TColorBox;
    ColorBox14: TColorBox;
    ColorBox15: TColorBox;
    ColorBox2: TColorBox;
    ColorBox3: TColorBox;
    ColorBox4: TColorBox;
    ColorBox5: TColorBox;
    ColorBox6: TColorBox;
    ColorBox7: TColorBox;
    ColorBox8: TColorBox;
    ColorBox9: TColorBox;
    Ex: TButton;
    Prim: TButton;
    Gen: TBitBtn;
    procedure Button1Click(Sender: TObject);
    procedure ColorBox10Change(Sender: TObject);

    procedure ColorBox11Change(Sender: TObject);

    procedure ColorBox12Change(Sender: TObject);
   // procedure ColorBox12GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox13Change(Sender: TObject);
    //procedure ColorBox13GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox14Change(Sender: TObject);
    //procedure ColorBox14GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox15Change(Sender: TObject);
    //procedure ColorBox15GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox1Change(Sender: TObject);
   // procedure ColorBox1GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox2Change(Sender: TObject);
   // procedure ColorBox2GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox3Change(Sender: TObject);
   // procedure ColorBox3GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox4Change(Sender: TObject);
   // procedure ColorBox4GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox5Change(Sender: TObject);
   // procedure ColorBox5GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox6Change(Sender: TObject);
   // procedure ColorBox6GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox7Change(Sender: TObject);
   // procedure ColorBox7GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox8Change(Sender: TObject);
   // procedure ColorBox8GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ColorBox9Change(Sender: TObject);
   // procedure ColorBox9GetColors(Sender: TCustomColorBox; Items: TStrings);
    procedure ExClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure GenClick(Sender: TObject);
    procedure PrimClick(Sender: TObject);
  private

  public

  end;



var
  Form3: TForm3;
  a,b:array[0..14] of integer; //массив для генерации цвета
implementation
Uses Unit1;
{$R *.lfm}

{ TForm3 }

//************ Процедура для проверки уникальных номеров************
function IsThere(a:array of integer; n:integer; x:integer):boolean;
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

//********** Создание начальных условий   *********
procedure TForm3.FormCreate(Sender: TObject);
var i:integer;
  Ini: Tinifile;
begin

  for i:=0 to 14 do a[i]:=i;
  ColorBox1.Selected:=ColorBox1.Colors[0];
  ColorBox2.Selected:=ColorBox2.Colors[1];
  ColorBox3.Selected:=ColorBox3.Colors[2];
   ColorBox4.Selected:=ColorBox4.Colors[3];
  ColorBox5.Selected:=ColorBox5.Colors[4];
  ColorBox6.Selected:=ColorBox6.Colors[5];
  ColorBox7.Selected:=ColorBox7.Colors[6];
  ColorBox8.Selected:=ColorBox8.Colors[7];
  ColorBox9.Selected:=ColorBox9.Colors[8];
  ColorBox10.Selected:=ColorBox10.Colors[9];
  ColorBox11.Selected:=ColorBox11.Colors[10];
  ColorBox12.Selected:=ColorBox12.Colors[11];
  ColorBox13.Selected:=ColorBox13.Colors[12];
  ColorBox14.Selected:=ColorBox14.Colors[13];
  ColorBox15.Selected:=ColorBox15.Colors[14];


  Ini:=TiniFile.Create(ExtractFilePath(Paramstr(0))+'e.ini');
  Ini.WriteInteger('color','1',0);
  Ini.WriteInteger('color','2',1);
  Ini.WriteInteger('color','3',2);
  Ini.WriteInteger('color','4',3);
  Ini.WriteInteger('color','5',4);
  Ini.WriteInteger('color','6',5);
  Ini.WriteInteger('color','7',6);
  Ini.WriteInteger('color','8',7);
  Ini.WriteInteger('color','9',8);
  Ini.WriteInteger('color','10',9);
  Ini.WriteInteger('color','11',10);
  Ini.WriteInteger('color','12',11);
  Ini.WriteInteger('color','13',12);
  Ini.WriteInteger('color','14',13);
  Ini.WriteInteger('color','15',14);
end;

//*************** Кнопочки ***********
procedure TForm3.GenClick(Sender: TObject);
var bool:boolean;
  i,temp,z:integer;
begin
   randomize;
   z:=0;
   for i:= 0 to 14 do begin
        temp:=random(19);
        bool:=IsThere(a,14,temp);
        if bool=false then
        a[i] :=temp;
        inc(z);
   end;
  ColorBox1.Selected:=ColorBox1.Colors[a[0]];
  ColorBox2.Selected:=ColorBox2.Colors[a[1]];
  ColorBox3.Selected:=ColorBox3.Colors[a[2]];
  ColorBox4.Selected:=ColorBox4.Colors[a[3]];
  ColorBox5.Selected:=ColorBox5.Colors[a[4]];
  ColorBox6.Selected:=ColorBox6.Colors[a[5]];
  ColorBox7.Selected:=ColorBox7.Colors[a[6]];
  ColorBox8.Selected:=ColorBox8.Colors[a[7]];
  ColorBox9.Selected:=ColorBox9.Colors[a[8]];
  ColorBox10.Selected:=ColorBox10.Colors[a[9]];
  ColorBox11.Selected:=ColorBox11.Colors[a[10]];
  ColorBox12.Selected:=ColorBox12.Colors[a[11]];
  ColorBox13.Selected:=ColorBox13.Colors[a[12]];
  ColorBox14.Selected:=ColorBox14.Colors[a[13]];
  ColorBox15.Selected:=ColorBox15.Colors[a[14]];
   {Form2.Shape2.Brush.Color:=ColorBox2.Selected;
   Form2.Shape1.Brush.Color:=ColorBox1.Selected;
   Form2.Shape3.Brush.Color:=ColorBox3.Selected;
   Form2.Shape4.Brush.Color:=ColorBox4.Selected;
   Form2.Shape5.Brush.Color:=ColorBox5.Selected;
   Form2.Shape6.Brush.Color:=ColorBox6.Selected;
   Form2.Shape7.Brush.Color:=ColorBox7.Selected;
   Form2.Shape8.Brush.Color:=ColorBox8.Selected;
   Form2.Shape9.Brush.Color:=ColorBox9.Selected;
   Form2.Shape10.Brush.Color:=ColorBox10.Selected;
   Form2.Shape11.Brush.Color:=ColorBox11.Selected;
   Form2.Shape12.Brush.Color:=ColorBox12.Selected;
   Form2.Shape13.Brush.Color:=ColorBox13.Selected;
   Form2.Shape14.Brush.Color:=ColorBox14.Selected;
   Form2.Shape15.Brush.Color:=ColorBox15.Selected;}
end;

procedure TForm3.PrimClick(Sender: TObject);
begin
  Form2.Shape1.Brush.color:=ColorBox1.Selected;
  Form2.Shape2.Brush.color:=ColorBox2.Selected;
  Form2.Shape3.Brush.color:=ColorBox3.Selected;
  Form2.Shape4.Brush.Color:=ColorBox4.Selected;
   Form2.Shape5.Brush.Color:=ColorBox5.Selected;
   Form2.Shape6.Brush.Color:=ColorBox6.Selected;
   Form2.Shape7.Brush.Color:=ColorBox7.Selected;
   Form2.Shape8.Brush.Color:=ColorBox8.Selected;
   Form2.Shape9.Brush.Color:=ColorBox9.Selected;
   Form2.Shape10.Brush.Color:=ColorBox10.Selected;
   Form2.Shape11.Brush.Color:=ColorBox11.Selected;
   Form2.Shape12.Brush.Color:=ColorBox12.Selected;
   Form2.Shape13.Brush.Color:=ColorBox13.Selected;
   Form2.Shape14.Brush.Color:=ColorBox14.Selected;
   Form2.Shape15.Brush.Color:=ColorBox15.Selected;
   Form2.FormCreate(Sender);
end;

procedure TForm3.ExClick(Sender: TObject);
var Ini:Tinifile;
begin
   Ini:=TiniFile.Create(ExtractFilePath(paramStr(0))+'e.ini');
   Form3.ColorBox1.Selected:=Form3.ColorBox1.Colors[Ini.ReadInteger('color','1',Form3.ColorBox1.ItemIndex)];
  Form3.ColorBox2.Selected:=Form3.ColorBox2.Colors[Ini.ReadInteger('color','2',Form3.ColorBox2.ItemIndex)];
  Form3.ColorBox3.Selected:=Form3.ColorBox3.Colors[Ini.ReadInteger('color','3',Form3.ColorBox3.ItemIndex)];
  Form3.ColorBox4.Selected:=Form3.ColorBox4.Colors[Ini.ReadInteger('color','4',Form3.ColorBox4.ItemIndex)];
  Form3.ColorBox5.Selected:=Form3.ColorBox5.Colors[Ini.ReadInteger('color','5',Form3.ColorBox5.ItemIndex)];
  Form3.ColorBox6.Selected:=Form3.ColorBox6.Colors[Ini.ReadInteger('color','6',Form3.ColorBox6.ItemIndex)];
  Form3.ColorBox7.Selected:=Form3.ColorBox7.Colors[Ini.ReadInteger('color','7',Form3.ColorBox7.ItemIndex)];
  Form3.ColorBox8.Selected:=Form3.ColorBox8.Colors[Ini.ReadInteger('color','8',Form3.ColorBox8.ItemIndex)];
  Form3.ColorBox9.Selected:=Form3.ColorBox9.Colors[Ini.ReadInteger('color','9',Form3.ColorBox9.ItemIndex)];
  Form3.ColorBox10.Selected:=Form3.ColorBox10.Colors[Ini.ReadInteger('color','10',Form3.ColorBox10.ItemIndex)];
  Form3.ColorBox11.Selected:=Form3.ColorBox11.Colors[Ini.ReadInteger('color','11',Form3.ColorBox11.ItemIndex)];
  Form3.ColorBox12.Selected:=Form3.ColorBox12.Colors[Ini.ReadInteger('color','12',Form3.ColorBox12.ItemIndex)];
  Form3.ColorBox13.Selected:=Form3.ColorBox13.Colors[Ini.ReadInteger('color','13',Form3.ColorBox13.ItemIndex)];
  Form3.ColorBox14.Selected:=Form3.ColorBox14.Colors[Ini.ReadInteger('color','14',Form3.ColorBox14.ItemIndex)];
  Form3.ColorBox15.Selected:=Form3.ColorBox15.Colors[Ini.ReadInteger('color','15',Form3.ColorBox15.ItemIndex)];

  Form2.Shape2.Brush.Color:=ColorBox2.Selected;
  Form2.Shape1.Brush.Color:=ColorBox1.Selected;
  Form2.Shape3.Brush.Color:=ColorBox3.Selected;
   Form2.Shape4.Brush.Color:=ColorBox4.Selected;
   Form2.Shape5.Brush.Color:=ColorBox5.Selected;
   Form2.Shape6.Brush.Color:=ColorBox6.Selected;
   Form2.Shape7.Brush.Color:=ColorBox7.Selected;
   Form2.Shape8.Brush.Color:=ColorBox8.Selected;
   Form2.Shape9.Brush.Color:=ColorBox9.Selected;
   Form2.Shape10.Brush.Color:=ColorBox10.Selected;
   Form2.Shape11.Brush.Color:=ColorBox11.Selected;
   Form2.Shape12.Brush.Color:=ColorBox12.Selected;
   Form2.Shape13.Brush.Color:=ColorBox13.Selected;
   Form2.Shape14.Brush.Color:=ColorBox14.Selected;
   Form2.Shape15.Brush.Color:=ColorBox15.Selected;

   Form2.FormCreate(Sender);
  Form3.Close;
end;

procedure TForm3.Button1Click(Sender: TObject);
begin
 Form2.Shape1.Brush.color:=ColorBox1.Selected;
  Form2.Shape2.Brush.color:=ColorBox2.Selected;
  Form2.Shape3.Brush.color:=ColorBox3.Selected;
  Form2.Shape4.Brush.Color:=ColorBox4.Selected;
   Form2.Shape5.Brush.Color:=ColorBox5.Selected;
   Form2.Shape6.Brush.Color:=ColorBox6.Selected;
   Form2.Shape7.Brush.Color:=ColorBox7.Selected;
   Form2.Shape8.Brush.Color:=ColorBox8.Selected;
   Form2.Shape9.Brush.Color:=ColorBox9.Selected;
   Form2.Shape10.Brush.Color:=ColorBox10.Selected;
   Form2.Shape11.Brush.Color:=ColorBox11.Selected;
   Form2.Shape12.Brush.Color:=ColorBox12.Selected;
   Form2.Shape13.Brush.Color:=ColorBox13.Selected;
   Form2.Shape14.Brush.Color:=ColorBox14.Selected;
   Form2.Shape15.Brush.Color:=ColorBox15.Selected;
   Form2.FormCreate(Sender);
   Form3.Close;
end;

//************ Запрет на выбор одинаковых цветов **********

procedure TForm3.ColorBox1Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
   ColorBox1.ItemIndex:=ColorBox1.Selected;
   d:=ColorBox1.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox1.Selected:=ColorBox1.Colors[a[0]];
   end
   else begin
        ColorBox1.Selected:=ColorBox1.Colors[d];
        a[0]:=d;
   end;
  Form2.Shape1.Brush.Color:=ColorBox1.Selected;
end;



procedure TForm3.ColorBox10Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox10.ItemIndex:=ColorBox10.Selected;
   d:=ColorBox10.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox10.Selected:=ColorBox10.Colors[a[9]];
   end
   else begin
        ColorBox10.Selected:=ColorBox10.Colors[d];
        a[9]:=d;
   end;
   Form2.Shape10.Brush.Color:=ColorBox10.Selected;
end;





procedure TForm3.ColorBox11Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
   ColorBox11.ItemIndex:=ColorBox11.Selected;
   d:=ColorBox11.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox11.Selected:=ColorBox11.Colors[a[10]];
   end
   else begin
        ColorBox11.Selected:=ColorBox11.Colors[d];
        a[10]:=d;
   end;
   Form2.Shape11.Brush.Color:=ColorBox11.Selected;
end;



procedure TForm3.ColorBox12Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox12.ItemIndex:=ColorBox12.Selected;
   d:=ColorBox12.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('Такой цвет уже используется!');
     ColorBox12.Selected:=ColorBox12.Colors[a[11]];
   end
   else begin
        ColorBox12.Selected:=ColorBox12.Colors[d];
        a[11]:=d;
   end;
   Form2.Shape12.Brush.Color:=ColorBox12.Selected;
end;



procedure TForm3.ColorBox13Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox13.ItemIndex:=ColorBox13.Selected;
   d:=ColorBox13.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox13.Selected:=ColorBox13.Colors[a[12]];
   end
   else begin
        ColorBox13.Selected:=ColorBox13.Colors[d];
        a[12]:=d;
   end;
   Form2.Shape13.Brush.Color:=ColorBox13.Selected;
end;



procedure TForm3.ColorBox14Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox14.ItemIndex:=ColorBox14.Selected;
   d:=ColorBox14.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox14.Selected:=ColorBox14.Colors[a[13]];
   end
   else begin
        ColorBox14.Selected:=ColorBox14.Colors[d];
        a[13]:=d;
   end;
   Form2.Shape14.Brush.Color:=ColorBox14.Selected;
end;



procedure TForm3.ColorBox15Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox15.ItemIndex:=ColorBox15.Selected;
   d:=ColorBox15.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox15.Selected:=ColorBox15.Colors[a[14]];
   end
   else begin
        ColorBox15.Selected:=ColorBox15.Colors[d];
        a[14]:=d;
   end;
   Form2.Shape15.Brush.Color:=ColorBox15.Selected;
end;



procedure TForm3.ColorBox2Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
   ColorBox2.ItemIndex:=ColorBox2.Selected;
   d:=ColorBox2.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox2.Selected:=ColorBox2.Colors[a[1]];
   end
   else begin
        ColorBox2.Selected:=ColorBox2.Colors[d];
        a[1]:=d;
   end;
   Form2.Shape2.Brush.Color:=ColorBox2.Selected;
end;



procedure TForm3.ColorBox3Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox3.ItemIndex:=ColorBox3.Selected;
   d:=ColorBox3.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox3.Selected:=ColorBox3.Colors[a[2]];
   end
   else begin
        ColorBox3.Selected:=ColorBox3.Colors[d];
        a[2]:=d;
   end;
   Form2.Shape3.Brush.Color:=ColorBox3.Selected;
end;



procedure TForm3.ColorBox4Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox4.ItemIndex:=ColorBox4.Selected;
   d:=ColorBox4.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox4.Selected:=ColorBox4.Colors[a[3]];
   end
   else begin
        ColorBox4.Selected:=ColorBox4.Colors[d];
        a[3]:=d;
   end;
   Form2.Shape4.Brush.Color:=ColorBox4.Selected;
end;



procedure TForm3.ColorBox5Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox5.ItemIndex:=ColorBox5.Selected;
   d:=ColorBox5.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox5.Selected:=ColorBox5.Colors[a[4]];
   end
   else begin
        ColorBox4.Selected:=ColorBox3.Colors[d];
        a[4]:=d;
   end;
   Form2.Shape5.Brush.Color:=ColorBox5.Selected;
end;



procedure TForm3.ColorBox6Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox6.ItemIndex:=ColorBox6.Selected;
   d:=ColorBox6.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox6.Selected:=ColorBox6.Colors[a[5]];
   end
   else begin
        ColorBox6.Selected:=ColorBox6.Colors[d];
        a[5]:=d;
   end;
   Form2.Shape6.Brush.Color:=ColorBox6.Selected;
end;



procedure TForm3.ColorBox7Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox7.ItemIndex:=ColorBox7.Selected;
   d:=ColorBox7.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox7.Selected:=ColorBox7.Colors[a[6]];
   end
   else begin
        ColorBox7.Selected:=ColorBox7.Colors[d];
        a[6]:=d;
   end;
   Form2.Shape7.Brush.Color:=ColorBox7.Selected;
end;



procedure TForm3.ColorBox8Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox8.ItemIndex:=ColorBox8.Selected;
   d:=ColorBox8.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox8.Selected:=ColorBox8.Colors[a[7]];
   end
   else begin
        ColorBox8.Selected:=ColorBox8.Colors[d];
        a[7]:=d;
   end;
   Form2.Shape8.Brush.Color:=ColorBox8.Selected;
end;



procedure TForm3.ColorBox9Change(Sender: TObject);
var d,u:integer;
  bool:boolean;
begin
  ColorBox9.ItemIndex:=ColorBox9.Selected;
   d:=ColorBox9.ItemIndex;
   bool:=IsThere(a,14,d);
   if bool = true then begin
     showmessage('This color is already in use!');
     ColorBox9.Selected:=ColorBox9.Colors[a[8]];
   end
   else begin
        ColorBox9.Selected:=ColorBox9.Colors[d];
        a[8]:=d;
   end;
   Form2.Shape9.Brush.Color:=ColorBox9.Selected;
end;






end.

