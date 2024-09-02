unit Unit5;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ComCtrls, StdCtrls;

type

  { TForm4 }

  TForm4 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    ComboBox1: TComboBox;
    ComboBox10: TComboBox;
    ComboBox11: TComboBox;
    ComboBox12: TComboBox;
    ComboBox13: TComboBox;
    ComboBox14: TComboBox;
    ComboBox15: TComboBox;
    ComboBox2: TComboBox;
    ComboBox3: TComboBox;
    ComboBox4: TComboBox;
    ComboBox5: TComboBox;
    ComboBox6: TComboBox;
    ComboBox7: TComboBox;
    ComboBox8: TComboBox;
    ComboBox9: TComboBox;
    Label1: TLabel;
    Label10: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    TrackBar8: TTrackBar;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    //procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure TrackBar12Change(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
  private

  public
   // procedure new();
  end;

var
  Form4: TForm4;


implementation
Uses unit1;
{$R *.lfm}

{ TForm4 }

procedure TForm4.TrackBar12Change(Sender: TObject);
begin

end;

procedure TForm4.Button1Click(Sender: TObject); //auto
begin

  ComboBox1.ItemIndex:=random(19);
  ComboBox2.ItemIndex:=random(19);
  ComboBox3.ItemIndex:=random(19);
  ComboBox4.ItemIndex:=random(19);
  ComboBox5.ItemIndex:=random(19);
  ComboBox6.ItemIndex:=random(19);
  ComboBox7.ItemIndex:=random(19);
  ComboBox8.ItemIndex:=random(19);
  ComboBox9.ItemIndex:=random(19);
  ComboBox10.ItemIndex:=random(19);
  ComboBox11.ItemIndex:=random(19);
  ComboBox12.ItemIndex:=random(19);
  ComboBox13.ItemIndex:=random(19);
  ComboBox14.ItemIndex:=random(19);
  ComboBox15.ItemIndex:=random(19);

  {ColorBox2.Selected:=ColorBox2.Itemind[a[1]];
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
  ColorBox15.Selected:=ColorBox15.Colors[a[14]];}

   //new();
end;

procedure TForm4.Button2Click(Sender: TObject);
begin
 book[1].count:=ComboBox1.ItemIndex;
   book[2].count:=ComboBox2.ItemIndex;
   book[3].count:=ComboBox3.ItemIndex;
   book[4].count:=ComboBox4.ItemIndex;
   book[5].count:=ComboBox5.ItemIndex;
   book[6].count:=ComboBox6.ItemIndex;
   book[7].count:=ComboBox7.ItemIndex;
   book[8].count:=ComboBox8.ItemIndex;
   book[9].count:=ComboBox9.ItemIndex;
   book[10].count:=ComboBox10.ItemIndex;
   book[11].count:=ComboBox11.ItemIndex;
   book[12].count:=ComboBox12.ItemIndex;
   book[13].count:=ComboBox13.ItemIndex;
   book[14].count:=ComboBox14.ItemIndex;
   book[15].count:=ComboBox15.ItemIndex;

   Form2.FormCreate(Sender);
end;



procedure TForm4.Button3Click(Sender: TObject);
begin
   book[1].count:=ComboBox1.ItemIndex;
   book[2].count:=ComboBox2.ItemIndex;
   book[3].count:=ComboBox3.ItemIndex;
   book[4].count:=ComboBox4.ItemIndex;
   book[5].count:=ComboBox5.ItemIndex;
   book[6].count:=ComboBox6.ItemIndex;
   book[7].count:=ComboBox7.ItemIndex;
   book[8].count:=ComboBox8.ItemIndex;
   book[9].count:=ComboBox9.ItemIndex;
   book[10].count:=ComboBox10.ItemIndex;
   book[11].count:=ComboBox11.ItemIndex;
   book[12].count:=ComboBox12.ItemIndex;
   book[13].count:=ComboBox13.ItemIndex;
   book[14].count:=ComboBox14.ItemIndex;
   book[15].count:=ComboBox15.ItemIndex;

   Form2.FormCreate(Sender);
   //new();
   {puts1(book[1].count);
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
   puts15(book[15].count); }
   Form4.close;
end;

procedure TForm4.Button4Click(Sender: TObject);
var i:integer;
begin
  for i:=1 to 15 do
   book[i].count:=0;
  Form2.FormCreate(sender);
  Form4.Close;
end;

procedure TForm4.TrackBar1Change(Sender: TObject);
begin
end;

end.

