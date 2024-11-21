//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------
unit WP.BasicDemoPlugIn.View;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes,
  Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls;

type
  TMainFrame = class(TFrame)
    Label1: TLabel;
    Panel1: TPanel;
  private
    { Private declarations }
  public
  public
    constructor Create(AOwner: TComponent); override;
  end;

implementation

uses
  ToolsAPI, ToolsAPI.UI;

{$R *.dfm}

constructor TMainFrame.Create(AOwner: TComponent);
var
  LThemingServices: IOTAIDEThemingServices;
begin
  inherited;
  if Supports(BorlandIDEServices, IOTAIDEThemingServices, LThemingServices) and
    LThemingServices.IDEThemingEnabled then
  begin
    Panel1.StyleElements := Panel1.StyleElements - [seClient];
    Panel1.ParentBackground := False;
    Panel1.Color := LThemingServices.StyleServices.GetSystemColor(clWindow);
  end;
end;

end.
