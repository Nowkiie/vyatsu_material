unit Generate;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils{, statusunit};

type
  TRecord = record
     surname: string[30];
     name: string[30];
     picture:string[30] ;//+
     price: LongWord; //+
     years: LongWord;//+
     country: string[20];

  end;

const
  countRecords = 8396810;
var f: File of TRecord;

procedure GenerateFile(path:string);

implementation

function RandomText:string;
var
   l,i:integer;
   s:string='';
begin
    l:=random(255)+1;
    for i:=1 to l do
    begin
      s:=s+Chr(Ord('a') + Random(Ord('z') - Ord('a')));
    end;
    RandomText:=s;
end;

function RandomTRecord:TRecord;
var
   r:TRecord;
begin
   with r do
   begin
     surname:=RandomText;
     name:=RandomText;
     picture:=RandomText;
     price:=random(4294967296);
     years:=random(4294967296);
     country:=RandomText;
   end;
   Exit(r);
end;

procedure GenerateFile(path:string);
var
   i:integer;
begin

   Assign(f, path);
   Rewrite(f);
   for i:=1 to countRecords do
   begin
       Write(f, RandomTRecord());

   end;
   Close(f);
end;




end.

