{$G+,N+}                      {Подрубаем 286 и сопроцессор, можно и без них}
 
Uses CRT;
Const
     AA : Real = 1.4;           {Нижний предел}
     BB : Real = 2.6;           {Верхний предел}
     NN : Word = 4;           {Кол-во итераций}
     N7: Word = 7;
var i:byte;
X,C:array [1..4] of real;
X7,C7:array [1..7] of real;
res1,res2:real;
 
Function F(X:Real):Real;      {Подынтегральная функция}
Begin
     F := x/sqrt(x*x+2.5);
End;
 
Function GaussMethod(A,B: Real;N:Word):Real;
{Интегрирование по квадратурной формуле Гаусса, N - от 1 до 8
чем больше N, тем точнее вычисления
ВНИМАНИЕ! Проверка на допустимые значения N не осуществляется!!!
}
Const
Xi : Array [1..4] of Real = (-0.86114,-0.33998,0.33998,0.86114);
 
Ci : Array [1..4] of Real = (0.34785,0.65215,0.65215,0.34785);
Var
   Ing : real;
   I : Byte;
Begin
     Ing := 0;
     For I := 1 to N do begin
              Ing := Ing + F( (a+b)/2+((b-a)/2)*Xi[I] )*Ci[I];
              writeln(ing:4:4);
              end;
     GaussMethod := Ing*((b-a)/2);
     for i:=1 to 4 do begin
       X[i]:=xi[i];
       C[i]:=ci[i];
       end;
End;

Function GaussMethod7(A,B: Real;N:Word):Real;
{Интегрирование по квадратурной формуле Гаусса, N - от 1 до 8
чем больше N, тем точнее вычисления
ВНИМАНИЕ! Проверка на допустимые значения N не осуществляется!!!
}
Const
X7i : Array [1..7] of Real = (-0.949107912, -0.741531186, 0.405845151, 0.0, 0.405845151, 0.741531186, 0.949107912);
 
C7i : Array [1..7] of Real = (0.129484966,0.279705391,0.381830051,0.417959184, 0.381830051, 0.279705391, 0.129484966);
Var
   Ing : real;
   I : Byte;
Begin
     Ing := 0;
     For I := 1 to N do begin
              Ing := Ing + F( (a+b)/2+((b-a)/2)*X7i[I] )*C7i[I];
              writeln(ing:4:4);
              end;
     GaussMethod7 := Ing*((b-a)/2);
     for i:=1 to 7 do begin
       X7[i]:=x7i[i];
       C7[i]:=c7i[i];
       end;
End;

 
Begin
     Writeln('Подынтегральная функция');
     writeln('F := x/sqrt(x*x+2.5)');
     writeln();
     WriteLn('Квадратурная формула Гаусса 4 узла  : ',GaussMethod(AA,BB,NN):0:3);
     WRITELN('Квадратурная формула Гаусса 7 узлов  : ',GaussMethod7(AA,BB,N7):0:3);
     writeln();
     writeln('4:');
     writeln('Узлы и веса:');
     for i:=1 to 4 do writeln('x[',i,']= ',x[i],'    C[',i,']=', C[i]);
     writeln('7:');
     writeln('Узлы и веса:');
     for i:=1 to 7 do writeln('x[',i,']= ',x7[i],'    C[',i,']=', C7[i]);
     Readln;
End.