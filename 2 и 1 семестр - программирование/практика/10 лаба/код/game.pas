unit game;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Graphics;

type

  { TBase }

  TBase = class (TObject)
    private
      x : Integer;
      y : Integer;
    public
      function getX : Integer;
      function getY : Integer;
  end;

  { TAnimate }

  TAnimate = class (TBase)
    private
      bitmap : array [0..100] of TBitmap;
      frame : Integer;
      maxframe : Integer;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : array of TBitmap;
        maxframe0 : Integer);
      function getBitmap : TBitmap;
      procedure nextFrame;
  end;

  { TStatic }

  TStatic = class (TBase)
    private
      bitmap : TBitmap;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : TBitmap);
      function getBitmap : TBitmap;
  end;


  { TPlayer }

  TPlayer = class (TAnimate)
    private
      speed : Integer;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : array of TBitmap; maxframe0 : Integer);
      procedure moveLeft;
      procedure moveRight;
      procedure moveForward;
      procedure moveBack;
       //procedure povorot;
      procedure move;
  end;

  { TGround }

  TGround = class (TAnimate)
    private
      speed : Integer;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : array of TBitmap; maxframe0 : Integer);
      procedure move;
      procedure resp;
  end;

  { TBullet }

  TBullet = class (TStatic)
    private
      speed_H : Integer;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : TBitmap; speed_H0 : Integer);
      procedure move;
      //function getBitmap : TBitmap;
  end;

  { TEnBullet }

  TEnBullet = class (TBullet)
    private
      hor : Integer;
      damage : Integer;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : TBitmap; hor0, damage0 : Integer);
      procedure move;
      function getDamage : Integer;
  end;

  { TSky }

  TSky = class (TStatic)
    public
     procedure move;
  end;

  { TExplode }

  TExplode = class (TAnimate)
    procedure nextFrame;
    function getFrame : Integer;
    function getMaxFrame : Integer;
  end;

  { TEnemy }

  TEnemy = class (TAnimate)
    private
      speed : Integer;
      shoot1 : Integer;
    public
      procedure move;
      procedure setSpeed(speed0 : Integer);
      procedure resetShoot;
      function getShoot : Integer;
  end;

  { TBigEnemy }

  TBigEnemy = class (TEnemy)
    private
      health : Integer;
    public
      Constructor Create(x0,y0 : Integer; bitmap0 : array of TBitmap; maxframe0 : Integer);
      procedure setHealth(health0 : Integer);
      function getHealth : Integer;
  end;

  TBoat = class (TBigEnemy)

  end;

  { TLevel_Up }

  TLevel_Up = class (TStatic)
    public
      procedure move;
  end;

  { THelp }

  THelp = class (TStatic)
    public
      procedure move;
  end;

  function EnShooting(x1, y1, x2, y2: Integer): Integer;
  function RoundEx(r : real) : integer;

implementation



{ THelp }

procedure THelp.move;
begin
 y := y + 5;
end;

{ TStatic }

constructor TStatic.Create(x0, y0: Integer; bitmap0: TBitmap);
begin
  x := x0;
  y := y0;
  bitmap  := bitmap0;
end;

function TStatic.getBitmap: TBitmap;
begin
  Result := bitmap;
end;

{ TAnimate }

constructor TAnimate.Create(x0, y0: Integer; bitmap0: array of TBitmap;
  maxframe0: Integer);
begin
  x := x0;
  y := y0;
  bitmap := bitmap0;
  maxframe := maxframe0;
  //SetLength(bitmap,maxframe);
  frame := 0;
end;

function TAnimate.getBitmap: TBitmap;
begin
  Result := bitmap[frame];
end;

procedure TAnimate.nextFrame;
begin
  if frame < maxframe then frame := frame + 1
  else frame := 0;
end;

{ TBigEnemy }

constructor TBigEnemy.Create(x0, y0: Integer; bitmap0: array of TBitmap;
  maxframe0: Integer);
begin
  inherited;
  health := 40;
end;

procedure TBigEnemy.setHealth(health0: Integer);
begin
  health := health0;
end;

function TBigEnemy.getHealth: Integer;
begin
  Result := health;
end;

{ TLevel_Up }

procedure TLevel_Up.move;
begin
  y := y + 5;
end;

{ TEnBullet }

constructor TEnBullet.Create(x0, y0: Integer; bitmap0: TBitmap; hor0,
  damage0: Integer);
begin
  x := x0;
  y := y0;
  bitmap := bitmap0;
  hor := hor0;
  damage := damage0;
end;

procedure TEnBullet.move;
begin
  y := y + 10;
  x := x + hor;
end;

function TEnBullet.getDamage: Integer;
begin
  Result := damage;
end;

function RoundEx(r : real) : integer;
  var f : real;
begin
  f := Frac(r);
  If f = 0.5 then f := r + 0.1;
  If f = -0.5 then f := r - 0.1;
  Result := round(f);
end;

function EnShooting(x1, y1, x2, y2: Integer): Integer;
var x0,y0 : Integer;
begin
  y0 := y1 + 10;
  {
  x0 := Round(((x1-x2)*y0 + (x2*y1 - x1*y2))/(y1 - y2));}
  x0 := Round((x2*y1-x1*y2+x1*y0-x2*y0)/(y1-y2));
  if x0 > x1 then
     Result := x0 - x1
  else
      Result := -(x1 - x0);
end;

{ TEnemy }

procedure TEnemy.move;
//var xy:double;
begin
  y := y + 7;
  x:= x - 2 ;
  if shoot1 < 200 then shoot1 := shoot1 + 1
  else shoot1 := 0;
end;

procedure TEnemy.setSpeed(speed0: Integer);
begin
  speed := speed0;
end;

procedure TEnemy.resetShoot;
begin
  shoot1 := 0;
end;

function TEnemy.getShoot: Integer;
begin
  Result := shoot1;
end;

{ TExplode }

procedure TExplode.nextFrame;
begin
  if frame < maxframe then frame := frame + 1;
end;

function TExplode.getFrame: Integer;
begin
  Result := frame;
end;

function TExplode.getMaxFrame: Integer;
begin
  Result := maxframe;
end;

{ TSky }

procedure TSky.move;
begin
  y := y + 5;
  if y >= 600 then y := -600;
end;

{ TBullet }

constructor TBullet.Create(x0, y0: Integer; bitmap0: TBitmap; speed_H0: Integer
  );
begin
  x := x0;
  y := y0;
  bitmap := bitmap0;
  speed_H := speed_H0;
end;

procedure TBullet.move;
begin
  y := y - 15;
  x := x + speed_H;
end;

{ TGround }

constructor TGround.Create(x0, y0: Integer; bitmap0: array of TBitmap;
  maxframe0: Integer);
begin
  x := x0;
  y := y0;
  bitmap := bitmap0;
  maxframe := maxframe0;

  randomize;
  frame := random(3);
end;

procedure TGround.move;
begin
  y := y + 5;
end;

procedure TGround.resp;
begin
  randomize;
  x := random(600);
  y := -50-random(500);
  frame := random(3);
  speed := random(2) + 1;
end;

{ TPlayer }

constructor TPlayer.Create(x0, y0: Integer; bitmap0: array of TBitmap;
  maxframe0: Integer);
begin
  inherited;
  speed := 0;
end;

procedure TPlayer.moveLeft;
begin
  if speed > -10 then
     if x > 0 then
        speed := speed - 3;
end;

procedure TPlayer.moveRight;
begin
  if speed < 10 then
     if x < 550 then
        speed := speed + 3;
end;

procedure TPlayer.moveForward;
begin
    y := y - 10;
end;

procedure TPlayer.moveBack;
begin
   y := y + 10;
end;



procedure TPlayer.move;
begin
  x := x + speed;
  if speed > 0 then speed := speed - 1;
  if speed < 0 then speed := speed + 1;
  if x < 0 then x := x + 5;
  if x > 550 then x := x - 5;
end;

{ TBase }

function TBase.getX: Integer;
begin
  Result := x;
end;

function TBase.getY: Integer;
begin
  Result := y;
end;

end.

