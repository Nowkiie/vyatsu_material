Uses Crt;
Type vector=array[1..50] of real;

Function Interpol (var X,Y:vector;n,nom:integer;a:real):real;
Var
 D1,D2,D3,D4:vector;
 h,q:real;
 k,i:integer;
 f:real;
 Begin
      for i:=1 to n-1 do d1[i]:=y[i+1]-y[i];
      for i:=1 to n-2 do d2[i]:=d1[i+1]-d1[i];
      for i:=1 to n-3 do d3[i]:=d2[i+1]-d2[i];
      for i:=1 to n-4 do d4[i]:=d3[i+1]-d3[i];
       
      for i:=1 to n-1 do begin
        Write(d1[i]:7:3);
        if d2[i]<>0 then write(d2[i]:10:6);
        if d3[i]<>0 then write(d3[i]:10:6);
        if d4[i]<>0 then write(d4[i]:10:6);
        writeln();
      end;
       
      h:=abs(x[2]-x[1]);
      case nom of
        1:begin
            k:=1;
            q:=(a-x[1])/h;
            f:=y[k]+d1[k]*q+(d2[k]*q*(q-1))/2+(d3[k]*q*(q-1)*(q-2))/6+(d4[k]*q*(q-1)*(q-2)*(q-3))/24;
          end;
        2:begin
            k:=n;
            q:=(a-x[n])/h;
            f:=y[k]+d1[k-1]*q+(d2[k-2]*q*(q+1))/2+(d3[k-3]*q*(q+1)*(q+2))/6+(d4[k-4]*q*(q+1)*(q+2)*(q+3))/24;
          end;
      end;
     interpol:=f;
 End;



Var
  X,Y:vector;
  x1,x2,x3,x4:real;
   y1,y2,y3,y4:real;
  n,nom,i:integer;
  D1,D2,D3,D4:vector;
Begin
  x[1]:=0.01;
  x[2]:=0.06;
  x[3]:=0.11;
  x[4]:=0.16;
  x[5]:=0.21;
  x[6]:=0.26;
  x[7]:=0.31;
  x[8]:=0.36;
  x[9]:=0.41;
  x[10]:=0.46;
  x[11]:=0.51;
  x[12]:=0.56;
  
  y[1]:=0.991824;
  y[2]:=0.951935;
  y[3]:=0.913650;
  y[4]:=0.876905;
  y[5]:=0.841638;
  y[6]:=0.807789;
  y[7]:=0.775301;
  y[8]:=0.744120;
  y[9]:=0.714198;
  y[10]:=0.685470;
  y[11]:=0.657902;
  y[12]:=0.631442;
  
  
  
  Writeln('исходные данные');
  for i:=1 to 12 do begin
    write(x[i]:7:2,y[i]:9:6);
    writeln;
  end;
  writeln();  
  x1:=0.1243;
  y1:=Interpol(x,y,12,1,x1);
  Writeln('y1(',x1,')=',y1:9:6);
  x2:=0.492;
  y2:=Interpol(x,y,12,2,x2);
  Writeln('y2(',x2,')=',y2:9:6);
  x3:=0.0024;
  y3:=Interpol(x,y,12,1,x3);
  Writeln('y3(',x3,')=',y3:9:6);
  x4:=0.660;
  y4:=Interpol(x,y,12,2,x4);
  Writeln('y4(',x4,')=',y4:9:6);
end.