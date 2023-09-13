unit CodeEditorLineCellState.Main;

interface

procedure Register;

implementation

uses
  System.Types, System.SysUtils, System.Classes, Winapi.Windows, System.IOUtils,
  System.Generics.Collections, ToolsAPI, ToolsAPI.Editor, Vcl.Graphics,
  Vcl.Controls, Vcl.GraphUtil, Vcl.Forms, Vcl.ExtCtrls, RTTI;

type
  TStatusPanel = class(TCustomPanel)
  strict private
    const ForegroundColor = clWhite;
    const BackgroundColor = clWebDarkgreen;
  private
    FPaintBox: TPaintBox;
    FStatusMsg: string;
    procedure SetStatusMsg(const Value: string);
    procedure PaintBoxPaint(Sender: TObject);
  public
    class function GetStatusPanel(EditWindow: INTAEditWindow): TStatusPanel;
    property StatusMsg: string read FStatusMsg write SetStatusMsg;
    constructor Create(AOwner: TComponent); override;
  end;

  TIDEWizard = class(TNotifierObject, IOTAWizard)
  private
    FEditorEventsNotifier, FLastX, FLastY: Integer;
    FWorking: Boolean;
    procedure CheckStatusPanel(const Editor: TWinControl);
  protected
    procedure EditorMouseMove(const Editor: TWinControl; Shift: TShiftState; X, Y: Integer);
  public
    constructor Create;
    destructor Destroy; override;
    function GetIDString: string;
    procedure Execute;
    function GetName: string;
    function GetState: TWizardState;
  end;

  TCodeEditorNotifier = class(TNTACodeEditorNotifier)
  protected
    function AllowedEvents: TCodeEditorEvents; override;
  end;

procedure Register;
begin
  RegisterPackageWizard(TIDEWizard.Create);
end;

{ TIDEWizard }

procedure TIDEWizard.CheckStatusPanel(const Editor: TWinControl);
begin
  var LEditorServices: INTACodeEditorServices;
  if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) then
  begin
    var LEditWindow := LEditorServices.EditorState[Editor].View.GetEditWindow;
    var LPanel := TStatusPanel.GetStatusPanel(LEditWindow);
    if LPanel = nil then
      TStatusPanel.Create(LEditWindow.Form);
  end;
end;

constructor TIDEWizard.Create;
begin
  inherited;
  var LNotifier := TCodeEditorNotifier.Create;
  var LEditorServices: INTACodeEditorServices;
  if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) then
    FEditorEventsNotifier := LEditorServices.AddEditorEventsNotifier(LNotifier)
  else
    FEditorEventsNotifier := -1;
  LNotifier.OnEditorMouseMove := EditorMouseMove;
end;

destructor TIDEWizard.Destroy;
begin
  var LEditorServices: INTACodeEditorServices;
  if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) and
    (FEditorEventsNotifier <> -1) and Assigned(LEditorServices) then
    LEditorServices.RemoveEditorEventsNotifier(FEditorEventsNotifier);
  inherited;
end;

procedure TIDEWizard.EditorMouseMove(const Editor: TWinControl;
  Shift: TShiftState; X, Y: Integer);
var
  Element, LineFlag: Integer;
begin
  if FWorking or ((X = FLastX) and (FLastY = Y)) then Exit;
  FWorking := True;
  try
    CheckStatusPanel(Editor);
    var LEditorServices: INTACodeEditorServices;
    if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) then
    begin
      FLastX := X;
      FLastY := Y;
      var LView := LEditorServices.EditorState[Editor].View;

      var Line := LView.Position.Row;
      var Col := LView.Position.Column;

      if not LEditorServices.EditorState[Editor].PointToCharacterPos(TPoint.Create(X, Y), Col, Line) or (Col = -1) then
        Exit;

      var LineState := LEditorServices.EditorState[Editor].LineState[Line];
      var LineStateStr := TValue.From(LineState.State).ToString;

      var CellState := LineState.CellState[Col];
      var CellStateStr := TValue.From(CellState).ToString;

      var EdPos: TOTAEditPos;
      EdPos.Col := Col;
      EdPos.Line := Line;
      LView.GetAttributeAtPos(EdPos, True, Element, LineFlag);
      var LToken := '';
      var LSavedPos:= LView.GetCursorPos;
      try
        var LEditPos: TOTAEditPos;
        LEditPos.Col := Col;
        LEditPos.Line := Line;

        LView.SetCursorPos(LEditPos);
        LToken := LEditorServices.EditorState[Editor].EditorToken;
      finally
        LView.SetCursorPos(LSavedPos);
      end;

      var LStrMsg := Format('Line: %d, Col: %d, Token: %s, Element: %s, Line State: %s, Cell State: %s',
        [Line, Col, LToken, OTASyntaxCodeToStr(Element), LineStateStr, CellStateStr]);

      var LPanel := TStatusPanel.GetStatusPanel(LView.GetEditWindow);
      if LPanel <> nil then
        LPanel.StatusMsg := LStrMsg;
    end;
  finally
    FWorking := False;
  end;
end;

procedure TIDEWizard.Execute;
begin
end;

function TIDEWizard.GetIDString: string;
begin
  Result := '[4F686B16-28A3-43E7-AD9F-FE72EAA84ADA]';
end;

function TIDEWizard.GetName: string;
begin
  Result := 'CodeEditor.LineCellState.Demo';
end;

function TIDEWizard.GetState: TWizardState;
begin
  Result := [wsEnabled];
end;

{ TCodeEditorNotifier }

function TCodeEditorNotifier.AllowedEvents: TCodeEditorEvents;
begin
  Result := [cevMouseEvents];
end;

{ TStatusPanel }

constructor TStatusPanel.Create(AOwner: TComponent);
const
  cPanelSize = 28;
begin
  inherited Create(AOwner);
  Name := ClassName;
  Align := alTop;
  BevelOuter := bvNone;
  ShowCaption := False;
  Height := cPanelSize;
  ParentBackground := False;
  StyleElements := StyleElements - [seClient];

  Top := 40; // make sure the panel is align under TEditorNavigationToolbar
  var LForm := AOwner as TCustomForm;
  var LPanel := TPanel(LForm.FindComponent('EditorPanel'));
  // Setting the parent calls to ScaleforDPI
  Parent := LPanel.Parent;

  FPaintBox := TPaintBox.Create(AOwner);
  FPaintBox.Parent := Self;
  FPaintBox.Align := alClient;
  FPaintBox.OnPaint := PaintBoxPaint;

  Visible := True;
  Color := BackgroundColor;
end;

class function TStatusPanel.GetStatusPanel(
  EditWindow: INTAEditWindow): TStatusPanel;
begin
  if EditWindow = nil then
    Exit(nil)
  else
    Result := TStatusPanel(EditWindow.Form.FindComponent(TStatusPanel.ClassName));
end;

procedure TStatusPanel.PaintBoxPaint(Sender: TObject);
const
  cAlignOffset = 8;
begin
  if not FStatusMsg.IsEmpty then
  begin
    var LRect := FPaintBox.ClientRect;
    Inc(LRect.Left, cAlignOffset);
    FPaintBox.Canvas.Font.Color := ForegroundColor;
    FPaintBox.Canvas.TextRect(LRect, FStatusMsg, [tfSingleLine, tfVerticalCenter]);
  end;
end;

procedure TStatusPanel.SetStatusMsg(const Value: string);
begin
  FStatusMsg := Value;
  FPaintBox.Invalidate;
end;

end.

