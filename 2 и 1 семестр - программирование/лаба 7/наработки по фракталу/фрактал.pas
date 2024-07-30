uses GraphABC;

const
  Step = 10;
  
var
  angle: integer := 1;

procedure Draw();
begin
  angle := angle mod 4;
  case angle of
    0: LineRel(Step, 0);
    1,-3: LineRel(0, Step);
    2,-2: LineRel(-Step, 0);
    3,-1: LineRel(0, -Step);
  end;
end;

procedure Fractal(depth: integer; dividedAngle: integer);
begin
  if (depth <= 0) then  exit;
  Dec(depth);
  Fractal(depth, dividedAngle);
  Draw();
  Fractal(depth, -dividedAngle);
  Draw();
  Fractal(depth, dividedAngle);
  angle += dividedAngle;
  Draw();
  angle += dividedAngle;
  Fractal(depth, -dividedAngle);
  Draw();
  Fractal(depth, dividedAngle);
  Draw();
  Fractal(depth, -dividedAngle);
  angle -= dividedAngle;
  Draw();
  angle -= dividedAngle;
  Fractal(depth, dividedAngle);
  Draw();
  Fractal(depth, -dividedAngle);
  Draw();
  Fractal(depth, dividedAngle);
end;

begin
  SetWindowSize(500, 500);
  MoveTo(5, 5);
  Fractal(3, -1);
end.