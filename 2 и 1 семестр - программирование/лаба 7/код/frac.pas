program test_modul143;
uses modul1143,wincrt,graph;

const   eps=1e-6;
        step=10.0;
        scale=10.0;

var v,p,u,dr,m:integer;
 x,y:real;
 s:boolean=true;
 ch:char;
 code:integer;
{procedure a(i,u: integer);
procedure b(i,u: integer);
procedure c(i,u: integer);
procedure d(i,u: integer);}

procedure ShowInfo();
begin
    OutTextXY(10,10,'Peano Curve');
    OutTextXY(10,20,'<up> - move to the up');
    OutTextXY(10,30,'<down> - move to the down');
    OutTextXY(10,40,'<right> - move to the right');
    OutTextXY(10,50,'<left> - move to the left');
    OutTextXY(10,60,'<q> - increase the depth');
    OutTextXY(10,70,'<a> - reduce the depth');
    OutTextXY(10,80,'<w> - zoom in');
    OutTextXY(10,90,'<s> - zoom out');
    OutTextXY(10,100,'<Esc> - Exit');
end;

begin
    dr:=detect;
    initgraph(dr,m,'');
    x:=640;
    y:=480;


    {x1:=x/5;
    x2:=(x/5)*4;

    y1:=y/2;
    y2:=y/2;}
    p:=4;
    u:=4;
    repeat
        if s then
        begin
            cleardevice;
            paint(x, y, p ,u);
            ShowInfo();
        end;

        s:=true;
        ch:=readkey();
        code:=ord(ch);

        if code = 0 then
        begin
            ch:=readkey();
            code:=ord(ch);
            case code of
                80 : // up
                begin
                    if y < getmaxy()-100  then
                    begin
                        y:=y+step;
                       // y2:=y2+step;
                    end;
                end;

                72 : // down
                begin
                    if y > getmaxy()-600  then
                    begin
                        y:=y-step;
                       // y2:=y2-step;
                    end;
                end;
                77 : // left
                    if x < 1300 then
                    begin
                        x:=x+step;
                       // x2:=x2+step;
                    end;

                75 : // right
                begin
                    if x > 50 then
                    begin
                        x:=x-step;
                       // x2:=x2-step;
                    end;
                end;
                else
                begin
                    s:=false;
                end;
            end;
        end
        else
        case code of
            113://q - увеличение глубины фрактала
                begin
                    if p<7 then
                    begin
                        p:=p+1;
                    end
                    else
                    begin
                        s := false;
                    end;

                end;
            97://a - уменьшение глубины фрактала
                begin
                    if p>0 then
                    begin
                        p:=p-1;
                    end
                    else
                    begin
                        s := false;
                    end;

                end;
           119: // w - ?????????
                begin

                    if u < 9  then
                    begin
                       u:=u+1;
                    end;

                end;
            115: // s - ?????????
                begin
                    if u > 3 then
                    begin
                        u:=u-1;

                    end else
                    begin
                        s := false;
                    end;
                end;
            99: // c - ?????
                begin
                    x:=640;
                    y:=480;

                    u:=4;

                    p:=4;
                end;
            else
                s := false;
        end;

    until code = 27;
    CloseGraph;
end.


{begin
p:=9; u:= 7;
x:=640; y:=480;
// write('Vvedite stepen krivoi Gilberta (po umolchaniu=3) ....> ');
// readln(v);
// If v in [1,2,3,4,5,6,7,8,9] then p:=v;
// write('Vvedite shirinu krivoi Gilberta (po umolchaniu=6) ....> ');
// readln(v);
// If v in [1,2,3,4,5,6,7,8,9] then u:=v;
 dr:=detect;
 initgraph(dr,m,'');
 paint(x,y,p,u);
// delay(1000);
// moveto(640-u,480-u);
// b(p,u);

 readln;
closegraph;
end.}
