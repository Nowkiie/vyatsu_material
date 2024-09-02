unit Unit1;

{$mode objfpc}{$H+}

interface
uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ExtCtrls,
  ComCtrls, Menus,Inifiles, FileUtil;

type
   zap1=record
   count:integer;
  // number:integer;
   end;
  { TForm2 }

  TForm2 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Edit1: TStaticText;
    Edit2: TEdit;
    Label1: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    MainMenu1: TMainMenu;
    MenuItem1: TMenuItem;
    MenuItem10: TMenuItem;
    MenuItem2: TMenuItem;
    MenuItem4: TMenuItem;
    MenuItem6: TMenuItem;
    MenuItem9: TMenuItem;
    OpenDialog1: TOpenDialog;
    MenuItem8: TMenuItem;
    SaveDialog1: TSaveDialog;
    Shape1: TShape;
    Shape10: TShape;
    Shape11: TShape;
    Shape12: TShape;
    Shape13: TShape;
    Shape14: TShape;
    Shape15: TShape;
    Shape2: TShape;
    Shape3: TShape;
    Shape4: TShape;
    Shape5: TShape;
    Shape6: TShape;
    Shape7: TShape;
    Shape8: TShape;
    Shape9: TShape;
    MenuItem7: TMenuItem;
    MenuItem5: TMenuItem;
    MenuItem3: TMenuItem;
    Timer1: TTimer;
    TrackBar1: TTrackBar;
    procedure Button3Click(Sender: TObject);
    procedure MenuItem10Click(Sender: TObject);
    procedure MenuItem9Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure MenuItem6Click(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
    procedure Edit2KeyPress(Sender: TObject; var Key: char);
    procedure MenuItem4Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure MenuItem2Click(Sender: TObject);
    procedure MenuItem8Click(Sender: TObject);
    procedure MenuItem3Click(Sender: TObject);
    procedure Shape1ChangeBounds(Sender: TObject);
    procedure Shape2ChangeBounds(Sender: TObject);
    procedure Shape3ChangeBounds(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
  private

  public

  end;

var
  Form2: TForm2;
  book:array[1..15] of zap1;
  N:integer;
  M:array[1..15] of integer;//
  Le:array[1..15] of integer; //сдвиг влево
  L:array[1..15] of integer;


implementation

 Uses Unit3,Unit5;
{$R *.lfm}

{ TForm2 }



procedure DelElM(k,n:integer); //k- номер полки, n -кол-во элементов
var i,j:integer;
  begin
   for i:=1 to N do begin
     if (M[i]=k) then
       if i<>n then for j:=i to n-1 do begin
       M[j]:=M[j+1];
       end;
   end;
  //Dec(N);

   end;




       //********* Процедуры установки книги на некоторую полку ******
procedure put1();//u - опускание вниз, cl - цвет
var Shape:TShape;
  i:integer;
begin
with TShape.Create(Form2) do
begin
 Parent:=Form2;
 Left:=Le[1];
 Top:=70;
 Width:=13;
 Height:=61;
 Visible:=True;
 Shape:=stRectangle;
 Brush.Color:=Form2.Shape1.Brush.Color;
 Name:='Shape62'+intToStr(l[1]);
end;
le[1]:=le[1]+15;
inc(l[1]);
 end;

 procedure put2();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[2];
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape2.Brush.Color;
  Name:='Shape162'+intToStr(l[2]);
 end;
  le[2]:=le[2]+15;
  inc(l[2])
 end;

 procedure put3();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[3];
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape3.Brush.Color;
  Name:='Shape262'+intToStr(l[3]);
 end;
  le[3]:=le[3]+15;
  inc(l[3]);
 end;

 procedure put4();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[4];
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape4.Brush.Color;
  Name:='Shape362'+intToStr(l[4]);
 end;
  le[4]:=le[4]+15;
  inc(l[4]);
 end;

 procedure put5();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[5];
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape5.Brush.Color;
 Name:='Shape462'+intToStr(l[5]);
 end;
  le[5]:=le[5]+15;
 inc(l[5]);
 end;

 procedure put6();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[6];
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape6.Brush.Color;
  Name:='Shape562'+intToStr(l[6]);
 end;
  le[6]:=le[6]+15;
  inc(l[6]);
 end;

 procedure put7();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[7];
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape7.Brush.Color;
  Name:='Shape662'+intToStr(l[7]);
 end;
  le[7]:=le[7]+15;
  Inc(l[7])
 end;

 procedure put8();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[8];
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape8.Brush.Color;
  Name:='Shape762'+intToStr(l[8]);
 end;
  le[8]:=le[8]+15;
  inc(l[8]);
 end;

 procedure put9();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[9];
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape9.Brush.Color;
  Name:='Shape862'+intToStr(l[9]);
 end;
  le[9]:=le[9]+15;
  inc(l[9]);
 end;

 procedure put10();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[10];
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape10.Brush.Color;
  Name:='Shape962'+intToStr(l[10]);
 end;
  le[10]:=le[10]+15;
  inc(l[10]);
 end;

 procedure put11();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[11];
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape11.Brush.Color;
  Name:='Shape1062'+intToStr(l[11]);
 end;
  le[11]:=le[11]+15;
  inc(l[11]);
 end;

  procedure put12();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[12];
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape12.Brush.Color;
  Name:='Shape1162'+intToStr(l[12]);
 end;
  le[12]:=le[12]+15;
  inc(l[12]);
 end;

  procedure put13();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[13];
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape13.Brush.Color;
  Name:='Shape1262'+intToStr(l[13]);
 end;
  le[13]:=le[13]+15;
  inc(l[13]);
 end;

  procedure put14();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[14];
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape14.Brush.Color;
 Name:='Shape1362'+intToStr(l[14]);
 end;
  le[14]:=le[14]+15;
  inc(l[14]);
 end;

  procedure put15();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[15];
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape15.Brush.Color;
  Name:='Shape1462'+intToStr(l[15]);
 end;
  le[15]:=le[15]+15;
  inc(l[15]);
 end;

          //*****прорисовка начального кол-ва книг
  procedure puts1(k:integer);//k- count book on the start
var Shape:TShape;
  i:integer;
begin
for i:=1 to k do begin
with TShape.Create(Form2) do
begin
 Parent:=Form2;
 Left:=Le[1];
 Top:=70;
 Width:=13;
 Height:=61;
 Visible:=True;
 Shape:=stRectangle;
 Brush.Color:=Form3.Colorbox1.Selected;
 Name:='Shape62'+intToStr(l[1]);
end;
le[1]:=le[1]+15;
inc(l[1]);
end;
 end;

 procedure puts2(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[2];
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape2.Brush.Color;
  Name:='Shape162'+intToStr(l[2]);
 end;
  le[2]:=le[2]+15;
  inc(l[2]);
  end;
 end;

 procedure puts3(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[3];
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape3.Brush.Color;
  Name:='Shape262'+intToStr(l[3]);
 end;
  le[3]:=le[3]+15;
  inc(l[3]);
  end;
 end;

 procedure puts4(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[4];
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape4.Brush.Color;
  Name:='Shape362'+intToStr(l[4]);
 end;
  le[4]:=le[4]+15;
  inc(l[4]);
  end;
 end;

 procedure puts5(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[5];
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape5.Brush.Color;
 Name:='Shape462'+intToStr(l[5]);
 end;
  le[5]:=le[5]+15;
 inc(l[5]);
 end;
 end;

 procedure puts6(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[6];
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape6.Brush.Color;
  Name:='Shape562'+intToStr(l[6]);
 end;
  le[6]:=le[6]+15;
  inc(l[6]);
  end;
 end;

 procedure puts7(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[7];
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape7.Brush.Color;
  Name:='Shape662'+intToStr(l[7]);
 end;
  le[7]:=le[7]+15;
  Inc(l[7]);
  end;
 end;

 procedure puts8(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[8];
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape8.Brush.Color;
  Name:='Shape762'+intToStr(l[8]);
 end;
  le[8]:=le[8]+15;
  inc(l[8]);
  end;
 end;

 procedure puts9(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[9];
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape9.Brush.Color;
  Name:='Shape862'+intToStr(l[9]);
 end;
  le[9]:=le[9]+15;
  inc(l[9]);
  end;
 end;

 procedure puts10(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[10];
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape10.Brush.Color;
  Name:='Shape962'+intToStr(l[10]);
 end;
  le[10]:=le[10]+15;
  inc(l[10]);
  end;
 end;

 procedure puts11(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[11];
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape11.Brush.Color;
  Name:='Shape1062'+intToStr(l[11]);
 end;
  le[11]:=le[11]+15;
  inc(l[11]);
  end;
 end;

  procedure puts12(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[12];
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape12.Brush.Color;
  Name:='Shape1162'+intToStr(l[12]);
 end;
  le[12]:=le[12]+15;
  inc(l[12]);
  end;
 end;

  procedure puts13(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[13];
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape13.Brush.Color;
  Name:='Shape1262'+intToStr(l[13]);
 end;
  le[13]:=le[13]+15;
  inc(l[13]);
  end;
 end;

  procedure puts14(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[14];
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape14.Brush.Color;
 Name:='Shape1362'+intToStr(l[14]);
 end;
  le[14]:=le[14]+15;
  inc(l[14]);
  end;
 end;

  procedure puts15(k:integer);
 var Shape:TShape;
   i:integer;
 begin
 for i:=1 to k do begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[15];
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=True;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape15.Brush.Color;
  Name:='Shape1462'+intToStr(l[15]);
 end;
  le[15]:=le[15]+15;
  inc(l[15]);
  end;
 end;

             //******** Процедуры удаления книги с некоторой полки
   procedure Del1();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[1]-15;
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape1.Brush.Color;
 end;
  le[1]:=le[1]-15;
 end;

 procedure Del2();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[2]-15;
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape2.Brush.Color;
 end;
  le[2]:=le[2]-15;
 end;

 procedure Del3();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[3]-15;
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape3.Brush.Color;
 end;
  le[3]:=le[3]-15;
 end;

 procedure Del4();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[4]-15;
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape4.Brush.Color;
 end;
  le[4]:=le[4]-15;
 end;

 procedure Del5();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[5]-15;
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape5.Brush.Color;
 end;
  le[5]:=le[5]-15;
 end;

 procedure Del6();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[6]-15;
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape6.Brush.Color;
 end;
  le[6]:=le[6]-15;
 end;

 procedure Del7();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[7]-15;
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape7.Brush.Color;
 end;
  le[7]:=le[7]-15;
 end;

 procedure Del8();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[8]-15;
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape8.Brush.Color;
 end;
  le[8]:=le[8]-15;
 end;

 procedure Del9();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[9]-15;
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape9.Brush.Color;
 end;
  le[9]:=le[9]-15;
 end;

 procedure Del10();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[10]-15;
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape10.Brush.Color;
 end;
  le[10]:=le[10]-15;
 end;

 procedure Del11();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[11]-15;
  Top:=70;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape11.Brush.Color;
 end;
  le[11]:=le[11]-15;
 end;

 procedure Del12();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[12]-15;
  Top:=140;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape12.Brush.Color;
 end;
  le[12]:=le[12]-15;
 end;

 procedure Del13();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[13]-15;
  Top:=210;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape13.Brush.Color;
 end;
  le[13]:=le[13]-15;
 end;

 procedure Del14();
 var Shape:TShape;
   //i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[14]-15;
  Top:=280;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape14.Brush.Color;
 end;
  le[14]:=le[14]-15;
 end;

 procedure Del15();
 var Shape:TShape;
   i:integer;
 begin
 with TShape.Create(Form2) do
 begin
  Parent:=Form2;
  Left:=Le[15]-15;
  Top:=350;
  Width:=13;
  Height:=61;
  Visible:=False;
  Shape:=stRectangle;
  Brush.Color:=Form2.Shape15.Brush.Color;
 end;
  le[15]:=le[15]-15;
 end;

  procedure Animation(x,y:integer;Cl:Tcolor);
  begin
  end;

  procedure New();
var i,j:integer;
begin
  N:=15;
  randomize;
  for i:=1 to 15 do begin
        if (i<=5) then Le[i]:=25;
        if (i>5) and (i<=10) then Le[i]:=360;
        if (i>10) and (i<=15) then Le[i]:=720;
  end;
  for i:=1 to N do M[i]:=i;
   Puts1(book[1].count);
   puts2(book[2].count);
   puts3(book[3].count);
   puts4(book[4].count);
   puts5(book[5].count);
   puts6(book[6].count);
   puts7(book[7].count);
   puts8(book[8].count);
   puts9(book[9].count);
   puts10(book[10].count);
   puts11(book[11].count);
   puts12(book[12].count);
   puts13(book[13].count);
   puts14(book[14].count);
   puts15(book[15].count);
end;

  Procedure Del();
var i:integer;
begin
  for i:=16 to 1000901 do begin
   (Form2.FindComponent('Shape'+IntTostr(i)) as TShape).Free;
  end;
end;

                 //******** начальная расстановка *******
procedure TForm2.FormCreate(Sender: TObject);
begin
 del();
 Form2.Timer1.Enabled:=false;
 edit2.Text:=IntToStr(TrackBar1.Position);
 {Shape1.Brush.Color:=clBlack;
 Shape2.Brush.Color:=clMaroon;
 Shape3.Brush.Color:=clGreen;
 Shape4.Brush.Color:=clOlive;
 Shape5.Brush.Color:=clNavy;
 Shape6.Brush.Color:=clPurple;
 Shape7.Brush.Color:=clTeal;
 Shape8.Brush.Color:=clGray;
 Shape9.Brush.Color:=clSilver;
 Shape10.Brush.Color:=clRed;
 Shape11.Brush.Color:=clLime;
 Shape12.Brush.Color:=clYellow;
 Shape13.Brush.Color:=clBlue;
 Shape14.Brush.Color:=clFuchsia;
 Shape15.Brush.Color:=clAqua;}
 //Form3.Button1Click(Sender);
 new();
end;

               //**********Кнопочки меню *******
procedure TForm2.MenuItem2Click(Sender: TObject);
var Ini: Tinifile;
begin
 Form3.Show;
 OpenDialog1.DefaultExt:='ini';
  OpenDialog1.Filter:='INI-Files|*.ini';
  OpenDialog1.InitialDir:=ExtractFilePath(paramStr(0));
  if not OpenDialog1.Execute then Exit;
  Ini:=TiniFile.Create(OpenDialog1.FileName);
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

  Shape1.Brush.Color:= Form3.ColorBox1.Selected;
  Shape2.Brush.Color:= Form3.ColorBox2.Selected;
  Shape3.Brush.Color:= Form3.ColorBox3.Selected;
  Shape4.Brush.Color:= Form3.ColorBox4.Selected;
  Shape5.Brush.Color:= Form3.ColorBox5.Selected;
  Shape6.Brush.Color:= Form3.ColorBox6.Selected;
  Shape7.Brush.Color:= Form3.ColorBox7.Selected;
  Shape8.Brush.Color:= Form3.ColorBox8.Selected;
  Shape9.Brush.Color:= Form3.ColorBox9.Selected;
  Shape10.Brush.Color:= Form3.ColorBox10.Selected;
  Shape11.Brush.Color:= Form3.ColorBox11.Selected;
  Shape12.Brush.Color:= Form3.ColorBox12.Selected;
  Shape13.Brush.Color:= Form3.ColorBox13.Selected;
  Shape14.Brush.Color:= Form3.ColorBox14.Selected;
  Shape15.Brush.Color:= Form3.ColorBox15.Selected;


   end;



procedure TForm2.MenuItem8Click(Sender: TObject);
begin
  showmessage('The program implements the arrangement of books')
end;

procedure TForm2.MenuItem9Click(Sender: TObject);
begin
  ShowMessage('Author: Anastasia Ptachova, student CSaE-21, 2021y')
end;

procedure TForm2.Button3Click(Sender: TObject);
begin
  Form2.Close;
end;

procedure TForm2.MenuItem10Click(Sender: TObject);
begin
  Form4.Show;
end;

procedure TForm2.MenuItem3Click(Sender: TObject);
var Ini: Tinifile;
begin
  SaveDialog1.DefaultExt:='ini';
  SaveDialog1.Filter:='INI-Files|*.ini';
  //SaveDialog1.InitialDir:=ExtractFilePath(paramStr(0));
  if not SaveDialog1.Execute then Exit;
  //Ini:=TiniFile.Create(SaveDialog1.FileName);
  Ini:=TiniFile.Create(ExtractFilePath(paramStr(0))+'e.ini');
  Ini.WriteInteger('color','1',Form3.ColorBox1.ItemIndex);
  Ini.WriteInteger('color','2',Form3.ColorBox2.ItemIndex);
  Ini.WriteInteger('color','3',Form3.ColorBox3.ItemIndex);
  Ini.WriteInteger('color','4',Form3.ColorBox4.ItemIndex);
  Ini.WriteInteger('color','5',Form3.ColorBox5.ItemIndex);
  Ini.WriteInteger('color','6',Form3.ColorBox6.ItemIndex);
  Ini.WriteInteger('color','7',Form3.ColorBox7.ItemIndex);
  Ini.WriteInteger('color','8',Form3.ColorBox8.ItemIndex);
  Ini.WriteInteger('color','9',Form3.ColorBox9.ItemIndex);
  Ini.WriteInteger('color','10',Form3.ColorBox10.ItemIndex);
  Ini.WriteInteger('color','11',Form3.ColorBox11.ItemIndex);
  Ini.WriteInteger('color','12',Form3.ColorBox12.ItemIndex);
  Ini.WriteInteger('color','13',Form3.ColorBox13.ItemIndex);
  Ini.WriteInteger('color','14',Form3.ColorBox14.ItemIndex);
  Ini.WriteInteger('color','15',Form3.ColorBox15.ItemIndex);
end;

procedure TForm2.MenuItem6Click(Sender: TObject);
begin
  Form3.Show;
end;

procedure TForm2.MenuItem4Click(Sender: TObject);
begin
  Form2.Close;
end;

                         // не нужное
procedure TForm2.Shape1ChangeBounds(Sender: TObject);
begin
end;

procedure TForm2.Shape2ChangeBounds(Sender: TObject);
begin
end;

procedure TForm2.Shape3ChangeBounds(Sender: TObject);
begin

end;




                      //***** Кнопочки программы********
procedure TForm2.Button1Click(Sender: TObject);
var i:integer;
begin
 //new();
 if Button1.Caption = 'Start' then begin
   if Button2.Caption = 'Continue' then begin
                                     Timer1.Enabled:=false ;
                                     Button1.Caption:='Stop';
                                     end
                                else begin
                                     Button1.Caption:='Stop';
          Form2.Edit2.Text:=IntToStr(Form2.TrackBar1.Position);
          Timer1.Enabled:=true;
                                       end;


        MenuItem1.Enabled:=false;
        MenuItem2.Enabled:=false;
        MenuItem3.Enabled:=false;
        MenuItem4.Enabled:=false;
        MenuItem5.Enabled:=false;
        MenuItem6.Enabled:=false;
        MenuItem7.Enabled:=false;
        MenuItem8.Enabled:=false;
        MenuItem9.Enabled:=false;
 end
 else begin
 del();
 Button1.Caption:='Start' ;
 Button2.Caption:='Pause';
 Edit1.Caption:='';
 Timer1.Enabled:=false;
 MenuItem1.Enabled:=true;
        MenuItem2.Enabled:=true;
        MenuItem3.Enabled:=true;
        MenuItem4.Enabled:=true;
        MenuItem5.Enabled:=true;
        MenuItem6.Enabled:=true;
        MenuItem7.Enabled:=true;
        MenuItem8.Enabled:=true;
        MenuItem9.Enabled:=true;
  {Form4.TrackBar1.Position:=0;
  Form4.TrackBar2.Position:=0;
  Form4.TrackBar3.Position:=0;
  Form4.TrackBar4.Position:=0;
  Form4.TrackBar5.Position:=0;
  Form4.TrackBar6.Position:=0;
  Form4.TrackBar7.Position:=0;
  Form4.TrackBar8.Position:=0;
  Form4.TrackBar9.Position:=0;
  Form4.TrackBar10.Position:=0;
  Form4.TrackBar11.Position:=0;
  Form4.TrackBar12.Position:=0;
  Form4.TrackBar13.Position:=0;
  Form4.TrackBar14.Position:=0;
  Form4.TrackBar15.Position:=0;}
  //for i:=1 to 15 do book[i].count:=0;
  //new();
   book[1].count:=Form4.ComboBox1.ItemIndex;
   book[2].count:=Form4.ComboBox2.ItemIndex;
   book[3].count:=Form4.ComboBox3.ItemIndex;
   book[4].count:=Form4.ComboBox4.ItemIndex;
   book[5].count:=Form4.ComboBox5.ItemIndex;
   book[6].count:=Form4.ComboBox6.ItemIndex;
   book[7].count:=Form4.ComboBox7.ItemIndex;
   book[8].count:=Form4.ComboBox8.ItemIndex;
   book[9].count:=Form4.ComboBox9.ItemIndex;
   book[10].count:=Form4.ComboBox10.ItemIndex;
   book[11].count:=Form4.ComboBox11.ItemIndex;
   book[12].count:=Form4.ComboBox12.ItemIndex;
   book[13].count:=Form4.ComboBox13.ItemIndex;
   book[14].count:=Form4.ComboBox14.ItemIndex;
   book[15].count:=Form4.ComboBox15.ItemIndex;
   Form2.FormCreate(Sender);
end

 end;



procedure TForm2.Button2Click(Sender: TObject);
begin
   If Button2.Caption = 'Pause' then begin
    Button2.Caption:= 'Continue';
    Timer1.Enabled:=false;
  end
  else begin
   Button2.Caption:= 'Pause';
   if Button1.Caption = 'Stop' then Timer1.Enabled:=true;
       end;
end;

              //******* Работа с полем для скорости программы

procedure TForm2.Edit2Change(Sender: TObject);
begin
  if Edit2.text<>'' then begin
  TrackBar1.Position:=StrToInt(Edit2.text);
  end
  else begin
     Edit2.Text:='1';
  //Timer1.Enabled:=false;
  //Button2.Caption:='Продолжить';
  end;
end;



procedure TForm2.Edit2KeyPress(Sender: TObject; var Key: char);
begin
  if (Key = '0') and (Edit2.SelStart= 0) then begin
  Key:=#0;

  end;
end;


                    //*****основная отрисовка программы*******
procedure TForm2.Timer1Timer(Sender: TObject);
var z,k,i:integer;
begin
  Timer1.Interval:=1000-TrackBar1.Position*10;
  randomize;
  if book[15].count=20 then z:=random(14)+1
                       else z:=random(15)+1; //[1..15]
  if (N mod z =0) then k:=M[z]
                  else k:=M[N mod z];
  edit1.Caption:=IntToStr(K);
  // inc(i);
  if k =1 then begin
  inc(book[1].count);
  put1();
  if (book[1].count=20)  then begin
  DelElM(1,n);
  dec(n);
  end;
  end;


  if k =2 then begin
  inc(book[2].count);
  put2();
  if (book[2].count=20) then begin
  DelElM(2,n);
  dec(n);
  end;
  end;

  if k =3 then begin
  inc(book[3].count);
  put3();
  if (book[3].count=20) then begin
  DelElM(3,n);
  dec(n);
  end;
  end;

  if k =4 then begin
  inc(book[4].count);
  put4();
  if (book[4].count=20) then begin
  DelElM(4,n);
  dec(n);
  end;
  end;

  if k =5 then begin
  inc(book[5].count);
  put5();
  if (book[5].count=20) then begin
  DelElM(5,n);
  dec(n);
  end;
  end;

  if k =6 then begin
  inc(book[6].count);
  put6();
  if (book[6].count=20) then begin
  DelElM(6,n);
  dec(n);
  end;
  end;

  if k =7 then begin
  inc(book[7].count);
  put7();
  if (book[7].count=20) then begin
  DelElM(7,n);
  dec(n);
  end;
  end;

  if k =8 then begin
  inc(book[8].count);
  put8();
  if (book[8].count=20) then begin
  DelElM(8,n);
  dec(n);
  end;
  end;

  if k =9 then begin
  inc(book[9].count);
  put9();
  if (book[9].count=20) then begin
  DelElM(9,n);
  dec(n);
  end;
  end;

  if k =10 then begin
  inc(book[10].count);
  put10();
  if (book[10].count=20) then begin
  DelElM(10,n);
  dec(n);
  end;
  end;

  if k =11 then begin
  inc(book[11].count);
  put11();
  if (book[11].count=20) then begin
  DelElM(11,n);
  dec(n);
  end;
  end;

  if k =12 then begin
  inc(book[12].count);
  put12();
  if (book[12].count=20) then begin
  DelElM(12,n);
  dec(n);
  end;
  end;

  if k =13 then begin
  inc(book[13].count);
  put13();
  if (book[13].count=20) then begin
  DelElM(13,n);
  dec(n);
  end;
  end;

  if k =14 then begin
  inc(book[14].count);
  put14();
  if (book[14].count=20) then begin
  DelElM(14,n);
  dec(n);
  end;
  end;

  if k =15 then begin
  inc(book[15].count);
  put15();
  if (book[15].count=20) then begin
  DelElM(15,n);
  dec(n)
  end;
  end;

  while Le[3]>320 do Del3();
  while Le[2]>320 do Del2();
  while Le[4]>320 do Del4();
  while Le[5]>320 do Del5();
  while Le[6]>680 do Del6();
  while Le[7]>680 do Del7();
  while Le[8]>680 do Del8();
  while Le[9]>680 do Del9();
  while Le[10]>680 do Del10();
  while Le[11]>1010 do Del11();
  while Le[12]>1010 do Del12();
  while Le[13]>1010 do Del13();
  while Le[14]>1010 do Del14();
  while Le[15]>1010 do Del15();

   if N=0  then begin
  Form2.timer1.Enabled:=false;
  ShowMessage('The program has been successfully completed');
   end;
end;

procedure TForm2.TrackBar1Change(Sender: TObject);
begin
 edit2.Text:=IntToStr(TrackBar1.Position);

end;

end.

