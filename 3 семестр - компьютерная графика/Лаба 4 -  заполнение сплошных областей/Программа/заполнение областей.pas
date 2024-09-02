uses GraphABC;
 
procedure Zakraska(i,j:integer);
begin
  var ColorTek := GetPixel(i,j);//техущий цвет
  var ColorZ := ClRandom;//выбор случайного цвета
  var vorkug := |(0,1), (0,-1),(-1,0),(1,0)|; //(влево  вправо вниз вверх )
  var q := new Stack<(integer,integer)>; //создаем стек q
  q.Push((i, j));//инициализировать стек 
  repeat 
   var (ii, jj) := q.Pop;//достать пиксель из стека
    For var w := 0 to 3 do //пробежка с разных сторон затравки
    begin       
      var (u, v) :=((ii+vorkug[w].Item1).Clamp(0,500), (jj+vorkug[w].Item2).Clamp(0,500) );//заполняем интервал 1) слева от затравки,2) справа, 3)внизу
      if GetPixel(u,v) = ColorTek then begin 
      PutPixel(u,v,ColorZ);//нарисовать пиксель  
      q.Push((u,v)) //подожить его в стек
      end;
    end;
  until not q.Any;//пока затравленный пиксель внутри
end;
 
procedure Init;
begin
   Window.Clear;
   Moveto(50,50);//начинаем из этой координаты
   loop 5 do lineto(Random(10,490),Random(10,490));//случайные координаты для рисования линий
   lineto(50,50);//замыкаем
   DrawCircle(100,100,20);//кружочек - не подвижен
end;
 
begin
  OnMouseDown := procedure (x,y, mb:integer) →  if mb = 1 then Zakraska(x,y) //если нажимаем на правую кнопку мыши - закрашивается область
  else Init;//если нажата левая - перерисовка фигуры
  window.SetSize(500,500);
  Init;
end.