unit main;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  game, LCLType, ComCtrls, StdCtrls ,MMSystem;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Image1: TImage;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Shape2: TShape;
    Timer1: TTimer;
    Timer2: TTimer;
    Timer3: TTimer;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure FormKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure FormPaint(Sender: TObject);
    procedure Image1Click(Sender: TObject);
    procedure Image2Click(Sender: TObject);
    procedure Image3Click(Sender: TObject);
    procedure Image4Click(Sender: TObject);
    procedure Label1Click(Sender: TObject);
    procedure Label3Click(Sender: TObject);
   // procedure Label4Click(Sender: TObject);
   // procedure Label5Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Draw;
    procedure NewGame;
    procedure GameOver;
    procedure Sound(sound0 : String);
    procedure Exploding(x0,y0 : Integer; bitmap0 : array of TBitmap; frames0 : Integer);
    procedure Timer2Timer(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;
  Player : TPlayer;
  Ground : array [1..3] of TGround;
  Bullet : array [1..100] of TBullet;
  EnBullet : array [1..100] of TEnBullet;
  Sky : array [1..2] of TSky;
  Explode : array [1..100] of TExplode;
  Enemy0 : array [1..100] of TEnemy;
  Enemy1 : array [1..100] of TBigEnemy;
  Boat : array [1..100] of TBoat;
  Level_Up : array [1..4] of TLevel_Up;
  Help : array [1..4] of THelp;
  PPic, GPic, ExPic, BExPic, EnPic0, EnPic1, EnPic2, EnPic3, BEnPic0 , BEnPic1: array of TBitmap;
  BPic, SPic, EnBPic0, EnBPic1, LPic,HPic : TBitmap;
  MovL, MovR, Firing, MovF, MovB,PR, PL,PF : Boolean;
  Shoot : Boolean;
  Interval : Integer;
  Health : Integer; // Player's health
  Score : Integer;
  Level : Integer;
  //povorot:Integer;

implementation

{$R *.lfm}

{ TForm1 }



procedure TForm1.FormCreate(Sender: TObject);
var i,c,j : Integer;
begin
  DoubleBuffered := True;
  //Color := clSkyBlue;
  Image1.Width := 600;
  Image1.Height := 600;

  Image1.Canvas.Brush.Color := $00000000;
  Image1.Canvas.FillRect(0,0,Width,Height);

  {SetLength(PPic,3);
  PPic[0] := TBitmap.Create;
  PPic[0].LoadFromFile('img\player0.bmp');
  PPic[0].Transparent := True;
  PPic[1] := TBitmap.Create;
  PPic[1].LoadFromFile('img\player1.bmp');
  PPic[1].Transparent := True;
  PPic[2] := TBitmap.Create;
  PPic[2].LoadFromFile('img\player2.bmp');
  PPic[2].Transparent := True;
  Player := PPic[0].Canvas.Pixels[300,540];}
 //TPlayer;
 //.Create(300,540,PPic,2);
  {for j:= 0 to PPic[0].Height - 1 do
     for i:=0 to PPic[0].Width -1 do begin
       c:= PPic[1].Canvas.Pixels[300,540];
        PPic[1].Canvas.Pixels[540,300]:=c;
     end;}
    SetLength(PPic,1);
    PPic[0] := TBitmap.Create;
    PPic[0].LoadFromFile('img\player0.bmp');
    PPic[0].Transparent := True;
    Player := TPlayer.Create(300,540,PPic,0);


  SetLength(GPic,3);
  GPic[0] := TBitmap.Create;
  GPic[0].LoadFromFile('img\ground0.bmp');
  GPic[0].Transparent := True;
  GPic[1] := TBitmap.Create;
  GPic[1].LoadFromFile('img\ground1.bmp');
  GPic[1].Transparent := True;
  GPic[2] := TBitmap.Create;
  GPic[2].LoadFromFile('img\ground2.bmp');
  GPic[2].Transparent := True;

  BPic := TBitmap.Create;
  BPic.LoadFromFile('img\bullet.bmp');
  BPic.Transparent := True;

  HPic := TBitmap.Create;
  HPic.LoadFromFile('img\help.bmp');
  HPic.Transparent := True;

  SPic := TBitmap.Create;
  SPic.LoadFromFile('img\sky1.bmp');
  Sky[1] := TSky.Create(0,-300,SPic);
  Sky[2] := TSky.Create(0,300,SPic);

  LPic := TBitmap.Create;
  LPic.LoadFromFile('img\level_up.bmp');
  LPic.Transparent := True;

  SetLength(ExPic,6);
  ExPic[0] := TBitmap.Create;
  ExPic[0].LoadFromFile('img\explode0.bmp');
  ExPic[0].Transparent := True;
  ExPic[1] := TBitmap.Create;
  ExPic[1].LoadFromFile('img\explode1.bmp');
  ExPic[1].Transparent := True;
  ExPic[2] := TBitmap.Create;
  ExPic[2].LoadFromFile('img\explode2.bmp');
  ExPic[2].Transparent := True;
  ExPic[3] := TBitmap.Create;
  ExPic[3].LoadFromFile('img\explode3.bmp');
  ExPic[3].Transparent := True;
  ExPic[4] := TBitmap.Create;
  ExPic[4].LoadFromFile('img\explode4.bmp');
  ExPic[4].Transparent := True;
  ExPic[5] := TBitmap.Create;
  ExPic[5].LoadFromFile('img\explode5.bmp');
  ExPic[5].Transparent := True;

  SetLength(BExPic,6);
  BExPic[0] := TBitmap.Create;
  BExPic[0].LoadFromFile('img\big_explode0.bmp');
  BExPic[0].Transparent := True;
  BExPic[1] := TBitmap.Create;
  BExPic[1].LoadFromFile('img\big_explode1.bmp');
  BExPic[1].Transparent := True;
  BExPic[2] := TBitmap.Create;
  BExPic[2].LoadFromFile('img\big_explode2.bmp');
  BExPic[2].Transparent := True;
  BExPic[3] := TBitmap.Create;
  BExPic[3].LoadFromFile('img\big_explode3.bmp');
  BExPic[3].Transparent := True;
  BExPic[4] := TBitmap.Create;
  BExPic[4].LoadFromFile('img\big_explode4.bmp');
  BExPic[4].Transparent := True;
  BExPic[5] := TBitmap.Create;
  BExPic[5].LoadFromFile('img\big_explode5.bmp');
  BExPic[5].Transparent := True;
  BExPic[6] := TBitmap.Create;
  BExPic[6].LoadFromFile('img\big_explode6.bmp');
  BExPic[6].Transparent := True;

  SetLength(EnPic0,3);
  EnPic0[0] := TBitmap.Create;
  EnPic0[0].LoadFromFile('img\enemy00.bmp');
  EnPic0[0].Transparent := True;
  EnPic0[1] := TBitmap.Create;
  EnPic0[1].LoadFromFile('img\enemy01.bmp');
  EnPic0[1].Transparent := True;
  EnPic0[2] := TBitmap.Create;
  EnPic0[2].LoadFromFile('img\enemy02.bmp');
  EnPic0[2].Transparent := True;
  SetLength(EnPic1,3);
  EnPic1[0] := TBitmap.Create;
  EnPic1[0].LoadFromFile('img\enemy10.bmp');
  EnPic1[0].Transparent := True;
  EnPic1[1] := TBitmap.Create;
  EnPic1[1].LoadFromFile('img\enemy11.bmp');
  EnPic1[1].Transparent := True;
  EnPic1[2] := TBitmap.Create;
  EnPic1[2].LoadFromFile('img\enemy12.bmp');
  EnPic1[2].Transparent := True;
  SetLength(EnPic2,3);
  EnPic2[0] := TBitmap.Create;
  EnPic2[0].LoadFromFile('img\enemy20.bmp');
  EnPic2[0].Transparent := True;
  EnPic2[1] := TBitmap.Create;
  EnPic2[1].LoadFromFile('img\enemy21.bmp');
  EnPic2[1].Transparent := True;
  EnPic2[2] := TBitmap.Create;
  EnPic2[2].LoadFromFile('img\enemy22.bmp');
  EnPic2[2].Transparent := True;
  SetLength(EnPic3,3);
  EnPic3[0] := TBitmap.Create;
  EnPic3[0].LoadFromFile('img\enemy30.bmp');
  EnPic3[0].Transparent := True;
  EnPic3[1] := TBitmap.Create;
  EnPic3[1].LoadFromFile('img\enemy31.bmp');
  EnPic3[1].Transparent := True;
  EnPic3[2] := TBitmap.Create;
  EnPic3[2].LoadFromFile('img\enemy32.bmp');
  EnPic3[2].Transparent := True;

  EnBPic0 := TBitmap.Create;
  EnBPic0.LoadFromFile('img\enbullet0.bmp');
  EnBPic0.Transparent := True;
  EnBPic1 := TBitmap.Create;
  EnBPic1.LoadFromFile('img\enbullet1.bmp');
  EnBPic1.Transparent := True;

  SetLength(BEnPic0,3);
  BEnPic0[0] := TBitmap.Create;
  BEnPic0[0].LoadFromFile('img\b_enemy00.bmp');
  BEnPic0[0].Transparent := True;
  BEnPic0[1] := TBitmap.Create;
  BEnPic0[1].LoadFromFile('img\b_enemy01.bmp');
  BEnPic0[1].Transparent := True;
  BEnPic0[2] := TBitmap.Create;
  BEnPic0[2].LoadFromFile('img\b_enemy02.bmp');
  BEnPic0[2].Transparent := True;
  SetLength(BEnPic1,2);
  BEnPic1[0] := TBitmap.Create;
  BEnPic1[0].LoadFromFile('img\b_enemy10.bmp');
  BEnPic1[0].Transparent := True;
  BEnPic1[1] := TBitmap.Create;
  BEnPic1[1].LoadFromFile('img\b_enemy11.bmp');
  BEnPic1[1].Transparent := True;


  Enemy0[1] := TEnemy.Create(200,0,EnPic0,2);
  Enemy0[1].setSpeed(20);

  for i := 1 to 4 do
     begin
       randomize;
       Ground[i] := TGround.Create(random(width),-100-random(50),GPic,2);
     end;

 { Timer1.Enabled := True;
  Timer2.Enabled := True;
  Timer3.Enabled := True;}

end;

procedure TForm1.Button1Click(Sender: TObject);//начать
begin
  NewGame;
  Button1.Visible :=false;
  Button2.Visible :=false;
  label3.Visible:=false;
  //label4.Visible:=false;
 // label5.Visible:=false;
  Button3.Visible :=false;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Close;
  Button2.Visible :=false;
  //s:=score;
  //write(f,s);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  ShowMessage('Привет!'+#13+ 'Если ты это читаешь, значит у тебя проблемы с игрой.'+
  #13+  'Вот правила, которые помогут тебе разобраться что тут и как:'+#13+
  '1) управление игроком происходит при помощи стрелок'+#13+
  '2) стрельба - нажатие пробела'+#13+
  '3) переход на новый уровень - касание "маяка" ');

end;


procedure TForm1.FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState
  );
begin
  if Key = VK_E then begin
       PPic[0].LoadFromFile('img\player1.bmp');
       PR:=true;
       PL:=false;
       PF:=false;
                     end;
  if Key = VK_Q then begin
    PPic[0].LoadFromFile('img\player2.bmp');
    PL:=true;
    PR:=false;
    PF:=false;
  end;
  if Key = VK_W then begin
    PPic[0].LoadFromFile('img\player0.bmp');
    PF:=true;
    PL:=false;
    PR:=false;
  end;
  if Key = VK_DOWN then MovB := True;
  if Key = VK_UP then MovF := True;
  if Key = VK_ESCAPE then Close;
  if Key = VK_LEFT then MovL := True;
  if Key = VK_RIGHT then MovR := True;
  if Key = VK_SPACE then Firing := True;
end;

procedure TForm1.FormKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
begin
  if Key = VK_LEFT then MovL := False;
  if Key = VK_RIGHT then MovR := False;
  if Key = VK_UP then MovF := False;
  if Key = VK_SPACE then Firing := False;
  if Key = VK_DOWN then MovB := False;
end;

procedure TForm1.FormPaint(Sender: TObject);
begin

end;

procedure TForm1.Image1Click(Sender: TObject);
begin
 Image1.Canvas.Brush.Color := $00C08000;
 Image1.Canvas.FillRect(0,0,Width,Height);
 Label3.Visible:= false;
// Label4.Visible:= false;
// Label5.Visible:= false;
      end;

procedure TForm1.Image2Click(Sender: TObject);
begin

end;

procedure TForm1.Image3Click(Sender: TObject);
begin

end;

procedure TForm1.Image4Click(Sender: TObject);
begin

end;

procedure TForm1.Label1Click(Sender: TObject);
begin

end;

procedure TForm1.Label3Click(Sender: TObject);
begin
  Label3.Visible:= false;
end;



{procedure TForm1.Label4Click(Sender: TObject);
begin
  Label4.Visible:= false;
end;

procedure TForm1.Label5Click(Sender: TObject);
begin
  Label5.Visible:= false;
end;}



procedure TForm1.Timer1Timer(Sender: TObject);
var i, j, k : Integer;
begin
 if Timer1.Enabled = True then begin
  if MovL then Player.moveLeft;
  if MovR then Player.moveRight;
  if MovF then Player.moveForward;
  if MovB then Player.moveBack;
  if (Firing) and (Shoot) then
     begin
       k := 0;
       j := 1;
       if Level = 1 then
          while k = 0 do
            begin
            if Bullet[j] = nil then
               begin
                 Shoot := False;
                 if PR then
                    Bullet[j] := TBullet.Create(Player.getX-5,Player.getY + 20,BPic,90);
                 if PL then
                 Bullet[j] := TBullet.Create(Player.getX,Player.getY ,BPic,-90);
                 if PF then
                 Bullet[j] := TBullet.Create(Player.getX+17,Player.getY-20 ,BPic,0);
                 k := k + 1;
                 Sound('shoot.wav');
               end;
            j := j + 1;
            end;

       if Level = 2 then
          while k < 2 do
            begin
            if Bullet[j] = nil then
               begin
                 if PR then begin
                 if k = 0 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 10,BPic,90);
                 if k = 1 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 30,BPic,90);
                 k := k + 1;
                 if k = 2 then Sound('shoot.wav');
                 end;
                 if PL then begin
                 if k = 0 then
                    Bullet[j] := TBullet.Create(Player.getX - 15,Player.getY + 10,BPic,-90);
                 if k = 1 then
                    Bullet[j] := TBullet.Create(Player.getX - 15,Player.getY + 30,BPic,-90);
                 k := k + 1;
                 if k = 2 then Sound('shoot.wav');
                 end;
                 if PF then begin
                 if k = 0 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY - 20,BPic,0);
                 if k = 1 then
                    Bullet[j] := TBullet.Create(Player.getX + 39,Player.getY - 20,BPic,0);
                 k := k + 1;
                 if k = 2 then Sound('shoot.wav');
                 end;
                 end;
            j := j + 1;
            Shoot := False;
            Timer2.Interval := 2000;
            end;

       if Level = 3 then
          while k < 3 do
            begin
            if Bullet[j] = nil then
               begin
               if PF then begin
                 if k = 0 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY - 20,BPic, -5);
                 if k = 1 then
                    Bullet[j] := TBullet.Create(Player.getX + 17,Player.getY - 20,BPic,0);
                 if k = 2 then
                    Bullet[j] := TBullet.Create(Player.getX + 39,Player.getY - 20,BPic,5);
                 k := k + 1;
                 if k = 3 then Sound('shoot.wav');
                 end;
                 if PR then begin
                 if k = 0 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 10,BPic, 85);
                 if k = 1 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 25,BPic,90);
                 if k = 2 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 40,BPic,95);
                 k := k + 1;
                 if k = 3 then Sound('shoot.wav');
                 end;
                  if PL then begin
                 if k = 0 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 10,BPic, -95);
                 if k = 1 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 25,BPic,-90);
                 if k = 2 then
                    Bullet[j] := TBullet.Create(Player.getX - 5,Player.getY + 45,BPic,-85);
                 k := k + 1;
                 if k = 3 then Sound('shoot.wav');
                  end;

               end;
            j := j + 1;
            Shoot := False;
            Timer2.Interval := 2000;
            end;
     end;

  Player.move;

  for i := 1 to 4 do
     if Ground[i].getY < Height then Ground[i].move
     else  Ground[i].resp;
  Draw;
  Player.nextFrame;
  //Shape2.Width := Health;
  Form1.Caption := 'Score: '+IntToStr(Score);
  Label2.Caption := 'Level: '+IntToStr(Level);
  GameOver;
  if Health < 84 then image4.Picture.LoadFromFile('img\heart2.bmp');
  if Health < 68 then image4.Visible:=false;
  if Health < 52 then image3.Picture.LoadFromFile('img\heart2.bmp');
  if Health < 36 then image3.Visible:=false;
  if Health < 20 then image2.Picture.LoadFromFile('img\heart2.bmp');
  if Health = 0  then image2.Visible:=false;
  end;
end;

procedure TForm1.Draw;
var i, j, k, hor : Integer;
begin

  {Background}
  Image1.Canvas.Brush.Color := $00000000;
  Image1.Canvas.FillRect(0,0,Width,Height);
  {Sky}
  for i := 1 to 2 do
    begin
      Sky[i].move;
        Image1.Canvas.Draw(Sky[1].getX,Sky[1].getY,Sky[1].getBitmap);
      end;

  {Islands}
  for i := 1 to 4 do
     Image1.Canvas.Draw(Ground[i].getX,Ground[i].getY,Ground[i].getBitmap);

 if Timer1.Enabled = True then begin

  {Bullets}
  for i := 1 to 100 do
     if Bullet[i] <> nil then
        begin
          Bullet[i].move;
          Image1.Canvas.Draw(Bullet[i].getX,Bullet[i].getY,Bullet[i].getBitmap);
          if Bullet[i].getY <= 10 then Bullet[i] := nil;
        end;

  for i := 1 to 100 do
     for j := 1 to 100 do
         if (Bullet[i] <> nil) and (Enemy0[j] <> nil) then
            if ((Bullet[i].getX - Enemy0[j].getX < 32)and(Bullet[i].getX - Enemy0[j].getX > 0)and
                (Bullet[i].getY < Enemy0[j].getY + 32)and(Bullet[i].getY > Enemy0[j].getY))or
               ((Bullet[i].getX + 32 - Enemy0[j].getX < 32)and(Bullet[i].getX + 32 - Enemy0[j].getX > 0)and
                (Bullet[i].getY < Enemy0[j].getY + 32)and(Bullet[i].getY > Enemy0[j].getY)) then
                  begin
                    Bullet[i] := nil;
                    Exploding(Enemy0[j].getX,Enemy0[j].getY,ExPic,5);
                    Enemy0[j] := nil;
                    Score := Score + 10;
                  end;

  for i := 1 to 100 do
     for j := 1 to 100 do
         if (Bullet[i] <> nil) and (Enemy1[j] <> nil) then
            if ((Bullet[i].getX - Enemy1[j].getX < 65)and(Bullet[i].getX - Enemy1[j].getX > 0)and
                (Bullet[i].getY < Enemy1[j].getY + 65)and(Bullet[i].getY > Enemy1[j].getY))or
               ((Bullet[i].getX + 65 - Enemy1[j].getX < 65)and(Bullet[i].getX + 65 - Enemy1[j].getX > 0)and
                (Bullet[i].getY < Enemy1[j].getY + 65)and(Bullet[i].getY > Enemy1[j].getY)) then
                  begin
                    Enemy1[j].setHealth(Enemy1[j].getHealth - 5);
                    Exploding(Bullet[i].getX,Bullet[i].getY,ExPic,5);
                    Bullet[i] := nil;
                    Score := Score + 10;
                  end;

  for i := 1 to 100 do
     for j := 1 to 100 do
         if (Bullet[i] <> nil) and (Boat[j] <> nil) then
            if ((Bullet[i].getX - Boat[j].getX < 41)and(Bullet[i].getX - Boat[j].getX > 0)and
                (Bullet[i].getY < Boat[j].getY + 180)and(Bullet[i].getY > Boat[j].getY))or
               ((Bullet[i].getX + 32 - Boat[j].getX < 41)and(Bullet[i].getX + 41 - Boat[j].getX > 0)and
                (Bullet[i].getY < Boat[j].getY + 180)and(Bullet[i].getY > Boat[j].getY)) then
                  begin
                    Boat[j].setHealth(Boat[j].getHealth - 5);
                    Exploding(Bullet[i].getX,Bullet[i].getY,ExPic,5);
                    Bullet[i] := nil;
                    Score := Score + 10;
                  end;

  {Shooting}
  If (not Shoot) and (Interval < 5) then Interval := Interval + 1;
  If Interval >=5 then
     begin
       Interval := 0;
       Shoot := True;
     end;

  {Boat}
  for i := 1 to 100 do
     if Boat[i] <> nil then
        begin
          Boat[i].nextFrame;
          Boat[i].move;
          Image1.Canvas.Draw(Boat[i].getX,Boat[i].getY,Boat[i].getBitmap);

          //shooting
          if (Boat[i].getShoot > 40) and (Player.getY - Boat[i].getY > 150) then
             begin
               k := 0;
               j := 1;
               while k = 0 do
                    begin
                    if EnBullet[j] = nil then
                       begin
                         hor := EnShooting(Boat[i].getX,Boat[i].getY,Player.getX + 20,Player.getY);
                         EnBullet[j] := TEnBullet.Create(Boat[i].getX + 5,Boat[i].getY + 88,EnBPic1,hor,10);
                         k := k + 1;
                       end;
                    j := j + 1;
                    end;

               {if Boat[i].getX > Player.getX + 100 then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Boat[i].getX + 10,Boat[i].getY + 88,EnBPic1,-1,10);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;

               if Boat[i].getX < Player.getX - 100 then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Boat[i].getX + 10,Boat[i].getY + 88,EnBPic1,1,10);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;

               if (Boat[i].getX < Player.getX + 99) and (Boat[i].getX > Player.getX - 99) then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Boat[i].getX + 10,Boat[i].getY + 88,EnBPic1,0,10);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;  }

               Boat[i].resetShoot;
             end;
             if Boat[i].getY > 600 then Boat[i] := nil;
        end;

  for i := 1 to 100 do
     if Boat[i] <> nil then
        if Boat[i].getHealth <= 0 then
           begin
             Exploding(Boat[i].getX,Boat[i].getY + 30,BExPic,5);
             Exploding(Boat[i].getX,Boat[i].getY + 80,BExPic,5);
             Boat[i] := nil;
             Sound('boom.wav');
           end;

  {Big Enemies}
  for i := 1 to 100 do
     if Enemy1[i] <> nil then
        begin
          Enemy1[i].nextFrame;
          Enemy1[i].move;
          Image1.Canvas.Draw(Enemy1[i].getX,Enemy1[i].getY,Enemy1[i].getBitmap);

          //shooting
          if (Enemy1[i].getShoot > 60) and (Player.getY - Enemy1[i].getY > 150) then
             begin
               k := 0;
               j := 1;
               while k = 0 do
                    begin
                    if EnBullet[j] = nil then
                       begin
                         hor := EnShooting(Enemy1[i].getX,Enemy1[i].getY,Player.getX + 20,Player.getY);
                         EnBullet[j] := TEnBullet.Create(Enemy1[i].getX + 20,Enemy1[i].getY + 20,EnBPic1,hor,10);
                         k := k + 1;
                       end;
                    j := j + 1;
                    end;

               {if Enemy1[i].getX > Player.getX + 100 then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Enemy1[i].getX + 20,Enemy1[i].getY + 20,EnBPic1,-1,10);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;

               if Enemy1[i].getX < Player.getX - 100 then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Enemy1[i].getX + 20,Enemy1[i].getY + 20,EnBPic1,1,10);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;

               if (Enemy1[i].getX < Player.getX + 99) and (Enemy1[i].getX > Player.getX - 99) then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Enemy1[i].getX + 20,Enemy1[i].getY + 20,EnBPic1,0,10);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;  }

               Enemy1[i].resetShoot;
             end;
             if Enemy1[i].getY > 600 then Enemy1[i] := nil;
        end;

  for i := 1 to 100 do
     if Enemy1[i] <> nil then
        if Enemy1[i].getHealth <= 0 then
           begin
             Exploding(Enemy1[i].getX,Enemy1[i].getY,BExPic,5);
             Enemy1[i] := nil;
             Sound('boom.wav');
           end;

  {Enemies}
  for i := 1 to 100 do
     if Enemy0[i] <> nil then
        begin
          Enemy0[i].nextFrame;
          Enemy0[i].move;
          Image1.Canvas.Draw(Enemy0[i].getX,Enemy0[i].getY,Enemy0[i].getBitmap);

          //shooting
          if (Enemy0[i].getShoot > 60) and (Player.getY - Enemy0[i].getY > 150) then
             begin
               k := 0;
               j := 1;
               while k = 0 do
                    begin
                    if EnBullet[j] = nil then
                       begin
                         hor := EnShooting(Enemy0[i].getX,Enemy0[i].getY,Player.getX + 20,Player.getY);
                         EnBullet[j] := TEnBullet.Create(Enemy0[i].getX,Enemy0[i].getY + 20,EnBPic0,hor,5);
                         k := k + 1;
                       end;
                    j := j + 1;
                    end;
               {if Enemy0[i].getX > Player.getX + 100 then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Enemy0[i].getX,Enemy0[i].getY + 20,EnBPic0,-1,5);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;

               if Enemy0[i].getX < Player.getX - 100 then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Enemy0[i].getX,Enemy0[i].getY + 20,EnBPic0,1,5);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;

               if (Enemy0[i].getX < Player.getX + 99) and (Enemy0[i].getX > Player.getX - 99) then
                  while k = 0 do
                       begin
                       if EnBullet[j] = nil then
                          begin
                            EnBullet[j] := TEnBullet.Create(Enemy0[i].getX,Enemy0[i].getY + 20,EnBPic0,0,5);
                            k := k + 1;
                          end;
                       j := j + 1;
                       end;}

               Enemy0[i].resetShoot;
             end;
             if Enemy0[i].getY > 600 then Enemy0[i] := nil;
        end;

  //collisions enemies
   for i := 1 to 99 do
     if (Enemy0[i] <> nil) and (Enemy0[i+1] <> nil) then
        if (Enemy0[i].getX = Enemy0[i+1].getX) and
           (Enemy0[i].getY = Enemy0[i+1].getY) then
              Enemy0[i+1] := nil;

   for i := 1 to 100 do
     if EnBullet[i] <> nil then
         if EnBullet[i].getY >= 600 then EnBullet[i] := nil;

   for i := 1 to 100 do
      if EnBullet[i] <> nil then
         begin
           EnBullet[i].move;
           Image1.Canvas.Draw(EnBullet[i].getX,EnBullet[i].getY,EnBullet[i].getBitmap);
         end;

   //collisions Big Enemies
    for i := 1 to 99 do
      if (Enemy1[i] <> nil) and (Enemy1[i+1] <> nil) then
         if (Enemy1[i].getX = Enemy1[i+1].getX) and
            (Enemy1[i].getY = Enemy1[i+1].getY) then
               Enemy1[i+1] := nil;

    //collisions Boats
     for i := 1 to 99 do
       if (Boat[i] <> nil) and (Boat[i+1] <> nil) then
          if (Boat[i].getX = Boat[i+1].getX) and
             (Boat[i].getY = Boat[i+1].getY) then
                Boat[i+1] := nil;

   //Collisions Level Up
   if Level < 3 then
       for i := 1 to 4 do
         if Level_Up[i] <> nil then
            if ((Level_Up[i].getX - Player.getX < 65)and(Level_Up[i].getX - Player.getX > 0)and
                (Level_Up[i].getY < Player.getY + 65)and(Level_Up[i].getY > Player.getY))or
               ((Level_Up[i].getX + 32 - Player.getX < 65)and(Level_Up[i].getX + 32 - Player.getX > 0)and
                (Level_Up[i].getY < Player.getY + 65)and(Level_Up[i].getY > Player.getY)) then
                  begin
                    Level_Up[i] := nil;
                    Level := Level + 1;
                  end;

   if Level < 3 then
       for i := 1 to 4 do
         if Help[i] <> nil then
            if ((Help[i].getX - Player.getX < 65)and(Help[i].getX - Player.getX > 0)and
                (Help[i].getY < Player.getY + 65)and(Help[i].getY > Player.getY))or
               ((Help[i].getX + 32 - Player.getX < 65)and(Help[i].getX + 32 - Player.getX > 0)and
                (Help[i].getY < Player.getY + 65)and(Help[i].getY > Player.getY)) then
                  begin
                    Help[i] := nil;
                    Health := 100;
                  end;
   {Damage}
   for i := 1 to 100 do
         if EnBullet[i] <> nil then
            if ((EnBullet[i].getX - Player.getX < 65)and(EnBullet[i].getX - Player.getX > 0)and
                (EnBullet[i].getY < Player.getY + 65)and(EnBullet[i].getY > Player.getY))or
               ((EnBullet[i].getX + 32 - Player.getX < 65)and(EnBullet[i].getX + 32 - Player.getX > 0)and
                (EnBullet[i].getY < Player.getY + 65)and(EnBullet[i].getY > Player.getY)) then
                  begin
                    Health := Health - EnBullet[i].getDamage;
                    EnBullet[i] := nil;
                  end;

   for i := 1 to 100 do
         if Enemy0[i] <> nil then
            if ((Enemy0[i].getX - Player.getX < 65)and(Enemy0[i].getX - Player.getX > 0)and
                (Enemy0[i].getY < Player.getY + 65)and(Enemy0[i].getY > Player.getY))or
               ((Enemy0[i].getX + 32 - Player.getX < 65)and(Enemy0[i].getX + 32 - Player.getX > 0)and
                (Enemy0[i].getY < Player.getY + 65)and(Enemy0[i].getY > Player.getY)) then
                  begin
                    Exploding(Enemy0[i].getX,Enemy0[i].getY,ExPic,5);
                    Enemy0[i] := nil;
                    Health := Health - 5;
                  end;

   for i := 1 to 100 do
         if Enemy1[i] <> nil then
            if ((Enemy1[i].getX - Player.getX < 65)and(Enemy1[i].getX - Player.getX > 0)and
                (Enemy1[i].getY < Player.getY + 65)and(Enemy1[i].getY > Player.getY))or
               ((Enemy1[i].getX + 32 - Player.getX < 65)and(Enemy1[i].getX + 32 - Player.getX > 0)and
                (Enemy1[i].getY < Player.getY + 65)and(Enemy1[i].getY > Player.getY)) then
                  begin
                    Exploding(Enemy1[i].getX,Enemy1[i].getY,BExPic,5);
                    Enemy1[i] := nil;
                    Health := Health - 15;
                    Sound('boom.wav');
                  end;

  {Level Up}
  for i := 1 to 4 do
     if Level_Up[i] <> nil then
        begin
          Level_Up[i].move;
          Image1.Canvas.Draw(Level_Up[i].getX,Level_Up[i].getY,Level_Up[i].getBitmap);
          if Level_Up[i].getY >= 600 then Level_Up[i] := nil;
        end;

  {LHelp}
  for i := 1 to 4 do
     if Help[i] <> nil then
        begin
          Help[i].move;
          Image1.Canvas.Draw(Help[i].getX,Help[i].getY,Help[i].getBitmap);
          if Help[i].getY >= 600 then Help[i] := nil;
        end;

  {Player}
  //Image1.Canvas.Draw
  Image1.Canvas.Draw(Player.getX-5,Player.getY-20,Player.getBitmap);
  {Explode}
  for i := 1 to 100 do
     if Explode[i] <> nil then
        if Explode[i].getFrame < Explode[i].getMaxFrame then
           begin
             Explode[i].nextFrame;
             Image1.Canvas.Draw(Explode[i].getX,Explode[i].getY,Explode[i].getBitmap);
           end
        else
            Explode[i] := nil;
end;
 if health = 100 then begin
  image4.Visible:=true;
  image3.Visible:=true;
  image2.Visible:=true;
 image4.Picture.LoadFromFile('img\heart1.bmp');
 image3.Picture.LoadFromFile('img\heart1.bmp');
 image2.Picture.LoadFromFile('img\heart1.bmp');
 end;
end;

procedure TForm1.NewGame;
begin
  Health := 100;
  Timer1.Enabled := True;
  Timer2.Enabled := True;
  Timer3.Enabled := True;
  Timer2.Interval := 2000;
  Timer3.Interval := 15000;
  MovL := False;
  MovR := False;
  Firing := False;
  Score := 0;
  Level := 1;
  image4.Visible:=true;
  image3.Visible:=true;
  image2.Visible:=true;
  image4.Picture.LoadFromFile('img\heart1.bmp');
  image3.Picture.LoadFromFile('img\heart1.bmp');
  image2.Picture.LoadFromFile('img\heart1.bmp');
end;

procedure TForm1.GameOver;
var i : Integer;
begin
  if (Health <= 0) or (score = 1000) then
     begin
       Timer1.Enabled := False;
       Timer2.Enabled := False;
       Timer3.Enabled := False;
       //ShowMessage('Game Over!!');
       for i := 1 to 100 do
          begin
            Enemy0[i] := nil;
            Enemy1[i] := nil;
            Bullet[i] := nil;
            EnBullet[i] := nil;
            Boat[i] := nil;
          end;
       for i := 1 to 4 do
          Enemy1[i] := nil;
       Firing := False;
       Button1.Visible:=True;
       Button2.Visible:=True;
       Label3.Visible:=true;
     end;

end;

procedure TForm1.Sound(sound0: String);
var str : String;
begin
  str := 'snd\'+sound0;
  PlaySound(PChar(str), 0, SND_ASYNC);

end;

procedure TForm1.Exploding(x0, y0: Integer; bitmap0: array of TBitmap;
  frames0: Integer);
var k, m : Integer;
begin
  k := 0;
  m := 1;
  while k = 0 do
        begin
         if Explode[m] = nil then
            begin
              Explode[m] := TExplode.Create(x0,y0,bitmap0,frames0);
              k := k + 1;
            end;
         m := m + 1;
         end;
end;

procedure TForm1.Timer2Timer(Sender: TObject);
var i, k : Integer;
    shans : Integer;
begin
  if Timer2.Enabled = True then
  i := 1;
  k := 0;
  while k = 0 do
     begin
      if Enemy0[i] = nil then
         begin
           randomize;
           shans := random(4);
           case shans of
              0: begin
                 Enemy0[i] := TEnemy.Create(random(550)+50,-50-random(100),EnPic0,2);
                 Enemy0[i].setSpeed(1); k := k +1; end;
              1: begin
                 Enemy0[i] := TEnemy.Create(random(550)+50,-50-random(100),EnPic1,2);
                 Enemy0[i].setSpeed(1); k := k +1; end;
              2: begin
                 Enemy0[i] := TEnemy.Create(random(550)+50,-50-random(100),EnPic2,2);
                 Enemy0[i].setSpeed(2); k := k +1; end;
              3: begin
                 Enemy0[i] := TEnemy.Create(random(550)+50,-50-random(100),EnPic3,2);
                 Enemy0[i].setSpeed(3); k := k +1; end;
           end;
         end;
      i := i + 1;
     end;
 {if level = 2 then Timer2.Interval := 3000;
 if level = 3 then Timer2.Interval := 4000;}
  {if Timer2.Interval > 400 then
     Timer2.Interval := Timer2.Interval - 10;}
  end;


procedure TForm1.Timer3Timer(Sender: TObject);
var i, k, shans : Integer;
begin
  if Timer3.Enabled = True then
  if (Level < 3) and (Score > 200) then
     begin
         i := 1;
         k := 0;
         while k = 0 do
           begin
             if (Level_Up[i] = nil) or (Help[i] = nil) then
               begin
                 Level_Up[i] := TLevel_Up.Create(random(550)+50,-50-random(100),LPic);
                 Help[i] := THelp.Create(random(550)+50,-50-random(100),HPic);
                 k := k + 1;
               end;
             i := i + 1;
           end;
     end;

  i := 1;
  k := 0;
  randomize;
  shans := random(2);

  if shans = 0 then
  while k = 0 do
     begin
      if Enemy1[i] = nil then
         begin
           {randomize;
           shans := random(2);
           case shans of
              0: begin
                 Enemy1[i] := TEnemy.Create(random(550)+50,-50-random(100),EnPic0,2);
                 Enemy1[i].setSpeed(1); k := k +1; end;
              1: begin}
                 Enemy1[i] := TBigEnemy.Create(random(550)+50,-50-random(100),BEnPic0,2);
                 Enemy1[i].setSpeed(3); k := k +1; {end;
           end;}
         end;
      i := i + 1;
     end;

  if shans = 1 then
  while k = 0 do
     begin
      if Boat[i] = nil then
         begin
           {randomize;
           shans := random(2);
           case shans of
              0: begin
                 Enemy1[i] := TEnemy.Create(random(550)+50,-50-random(100),EnPic0,2);
                 Enemy1[i].setSpeed(1); k := k +1; end;
              1: begin}
                 Boat[i] := TBoat.Create(random(550)+50,-200-random(50),BEnPic1,1);
                 Boat[i].setSpeed(3); k := k +1; {end;
           end;}
         end;
      i := i + 1;
     end;

 { if Timer3.Interval > 200 then
     Timer3.Interval := Timer3.Interval - 10;}
  end;

end.

