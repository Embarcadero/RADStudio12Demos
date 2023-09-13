unit fMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, FireDAC.Stan.Intf, FireDAC.Stan.Option,
  FireDAC.Stan.Error, FireDAC.UI.Intf, FireDAC.Phys.Intf, FireDAC.Stan.Def,
  FireDAC.Stan.Pool, FireDAC.Stan.Async, FireDAC.Phys, FireDAC.Phys.SQLite,
  FireDAC.Phys.SQLiteDef, FireDAC.Stan.ExprFuncs,
  FireDAC.Phys.SQLiteWrapper.Stat, FireDAC.VCLUI.Wait, FireDAC.Stan.Param,
  FireDAC.DatS, FireDAC.DApt.Intf, FireDAC.DApt, Data.DB, FireDAC.Comp.DataSet,
  FireDAC.Comp.Client, Vcl.Grids, Vcl.DBGrids, FireDAC.Comp.QBE,
  Datasnap.DBClient, Vcl.ExtCtrls, Vcl.DBCtrls, FireDAC.Stan.StorageBin;

type
  TfrmMain = class(TForm)
    FDConnection1: TFDConnection;
    FDQuery1: TFDQuery;
    DataSource1: TDataSource;
    DBGrid1: TDBGrid;
    btnEdit: TButton;
    btnPost: TButton;
    FDQuery1OrderID: TFDAutoIncField;
    FDQuery1CustomerID: TStringField;
    FDQuery1EmployeeID: TIntegerField;
    FDQuery1OrderDate: TDateTimeField;
    FDQuery1RequiredDate: TDateTimeField;
    FDQuery1ShippedDate: TDateTimeField;
    FDQuery1ShipVia: TIntegerField;
    FDQuery1Freight: TCurrencyField;
    FDQuery1ShipName: TStringField;
    FDQuery1ShipAddress: TStringField;
    FDQuery1ShipCity: TStringField;
    FDQuery1ShipRegion: TStringField;
    FDQuery1ShipPostalCode: TStringField;
    FDQuery1ShipCountry: TStringField;
    qLookup: TFDQuery;
    FDQuery1CustomerName: TStringField;
    btnCancel: TButton;
    FDQuery1CustomerName2: TStringField;
    DBGrid2: TDBGrid;
    btnPredef: TButton;
    DBNavigator1: TDBNavigator;
    FDTable1: TFDTable;
    FDTable1OrderID: TFDAutoIncField;
    FDTable1CustomerID: TStringField;
    FDTable1EmployeeID: TIntegerField;
    FDTable1OrderDate: TDateTimeField;
    FDTable1RequiredDate: TDateTimeField;
    FDTable1ShippedDate: TDateTimeField;
    FDTable1ShipVia: TIntegerField;
    FDTable1Freight: TCurrencyField;
    FDTable1ShipName: TStringField;
    FDTable1ShipAddress: TStringField;
    FDTable1ShipCity: TStringField;
    FDTable1ShipRegion: TStringField;
    FDTable1ShipPostalCode: TStringField;
    FDTable1ShipCountry: TStringField;
    FDTable1CustomerName: TStringField;
    FDTable1CustomerName2: TStringField;
    FDMemTable1: TFDMemTable;
    btnSaveToFile: TButton;
    btnLoadFromFile: TButton;
    FDQBE1: TFDQBE;
    rgDatasetType: TRadioGroup;
    rgQuerySource: TRadioGroup;
    DataSource2: TDataSource;
    FDMemTable1OrderID: TFDAutoIncField;
    FDMemTable1CustomerID: TStringField;
    FDMemTable1CustomerName: TStringField;
    FDMemTable1CustomerName2: TStringField;
    FDMemTable1EmployeeID: TIntegerField;
    FDMemTable1OrderDate: TDateTimeField;
    FDMemTable1RequiredDate: TDateTimeField;
    FDMemTable1ShippedDate: TDateTimeField;
    FDMemTable1ShipVia: TIntegerField;
    FDMemTable1Freight: TCurrencyField;
    FDMemTable1ShipName: TStringField;
    FDMemTable1ShipAddress: TStringField;
    FDMemTable1ShipCity: TStringField;
    FDMemTable1ShipRegion: TStringField;
    FDMemTable1ShipPostalCode: TStringField;
    FDMemTable1ShipCountry: TStringField;
    procedure btnEditClick(Sender: TObject);
    procedure btnPostClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FDQuery1CalcFields(DataSet: TDataSet);
    procedure btnPredefClick(Sender: TObject);
    procedure btnSaveToFileClick(Sender: TObject);
    procedure btnLoadFromFileClick(Sender: TObject);
    procedure FDQBE1Preview(Sender: TObject; const AQueryDesc: string);
    procedure FormCreate(Sender: TObject);
    procedure rgDatasetTypeClick(Sender: TObject);
    procedure rgQuerySourceClick(Sender: TObject);
  end;

var
  frmMain: TfrmMain;

implementation

{$R *.dfm}

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  FDConnection1.Connected := True;
  qLookup.Active := True;
end;

procedure TfrmMain.rgDatasetTypeClick(Sender: TObject);
begin
  FDQBE1.Cancel();
  case rgDatasetType.ItemIndex of
  0: DataSource1.DataSet := FDQuery1;
  1: DataSource1.DataSet := FDTable1;
  2: DataSource1.DataSet := FDMemTable1;
  end;
end;

procedure TfrmMain.rgQuerySourceClick(Sender: TObject);
begin
  case rgQuerySource.ItemIndex of
  0: FDQBE1.QuerySource := nil;
  1: FDQBE1.QuerySource := DataSource2;
  end;
end;

procedure TfrmMain.FDQuery1CalcFields(DataSet: TDataSet);
begin
  DataSet.FieldByName('CustomerName2').AsString :=
    qLookup.Lookup('CustomerID', DataSet.FieldByName('CustomerID').AsString, 'CompanyName');
end;

procedure TfrmMain.FDQBE1Preview(Sender: TObject; const AQueryDesc: string);
begin
  ShowMessage(AQueryDesc);
end;

procedure TfrmMain.btnEditClick(Sender: TObject);
begin
  FDQBE1.Edit;
end;

procedure TfrmMain.btnPostClick(Sender: TObject);
begin
  FDQBE1.Post;
end;

procedure TfrmMain.btnCancelClick(Sender: TObject);
begin
  FDQBE1.Cancel;
end;

procedure TfrmMain.btnPredefClick(Sender: TObject);
begin
  FDQBE1.Edit;
  FDQBE1.QBETable.EmptyDataSet;
  FDQBE1.QBETable.Append;
  FDQBE1.QBETable.FieldByName('CustomerName').AsString := '%hor% #1';
  FDQBE1.QBETable.FieldByName('OrderID').AsString := '> 10260 & < 10700';
  FDQBE1.QBETable.Post;
  FDQBE1.Post;
end;

procedure TfrmMain.btnSaveToFileClick(Sender: TObject);
begin
  FDQBE1.SaveToFile('c:\aaa.qbe');
end;

procedure TfrmMain.btnLoadFromFileClick(Sender: TObject);
begin
  FDQBE1.LoadFromFile('c:\aaa.qbe');
  FDQBE1.Post;
end;

end.
