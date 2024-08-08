unit CodeEditorScrollbarAnnotations.Main;

interface

procedure Register;

implementation

uses
  System.Types, System.SysUtils, Winapi.Windows, System.IOUtils, System.Generics.Collections,
  ToolsAPI, ToolsAPI.Editor, Vcl.Graphics, Vcl.Controls, Vcl.GraphUtil, System.StrUtils;

type
  TIDEWizard = class(TNotifierObject, IOTAWizard)
  private
    FScrollbarAnnotationNotifier: Integer;
  public
    constructor Create;
    destructor Destroy; override;
    function GetIDString: string;
    procedure Execute;
    function GetName: string;
    function GetState: TWizardState;
  end;

  TNTAScrollbarAnnotation = class(TNotifierObject, INTACodeEditorScrollbarAnnotation)
  const
    cColor = clWebSeaGreen;
  private
    FIndex, FWidth, FStart: Integer;
    FEnabled: Boolean;
  public
    constructor Create;
    function GetEnabled: Boolean;
    procedure SetEnabled(const Value: Boolean);
    function GetName: string;
    function GetWidth: Integer;
    procedure SetWidth(const Value: Integer);
    function GetStart: Integer;
    procedure SetStart(const Value: Integer);
    function GetColor: TColor;
    function GetCustomDraw: Boolean;
    procedure DrawMark(const AEditor: TWinControl; LineNum: Integer; ACanvas: TCanvas; ARect: TRect);
    procedure GetScrollbarAnnotations(const AEditor: TWinControl);
  end;

procedure Register;
begin
  RegisterPackageWizard(TIDEWizard.Create);
end;

{ TIDEWizard }

constructor TIDEWizard.Create;
begin
  inherited;
  var LNotifier := TNTAScrollbarAnnotation.Create;
  var LEditorServices: INTACodeEditorServices;
  if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) then
  begin
    FScrollbarAnnotationNotifier := LEditorServices.RegisterScrollbarAnnotation(LNotifier);
    LNotifier.FIndex := FScrollbarAnnotationNotifier;
  end
  else
    FScrollbarAnnotationNotifier := -1;
end;

destructor TIDEWizard.Destroy;
begin
  var LEditorServices: INTACodeEditorServices;
  if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) and
    (FScrollbarAnnotationNotifier <> -1) and Assigned(LEditorServices) then
    LEditorServices.RemoveScrollbarAnnotation(FScrollbarAnnotationNotifier);
  inherited;
end;

procedure TIDEWizard.Execute;
begin
end;

function TIDEWizard.GetIDString: string;
begin
  Result := '[53FDF8DD-664F-488E-A092-55877F48633D]';
end;

function TIDEWizard.GetName: string;
begin
  Result := 'CodeEditor.ScrollbarAnnotations.Demo';
end;

function TIDEWizard.GetState: TWizardState;
begin
  Result := [wsEnabled];
end;

{ TNTAScrollbarAnnotation }

constructor TNTAScrollbarAnnotation.Create;
begin
  FWidth := 4;
  FStart := 0;
  FEnabled := True;
end;

procedure TNTAScrollbarAnnotation.DrawMark(const AEditor: TWinControl;
  LineNum: Integer; ACanvas: TCanvas; ARect: TRect);
begin
//
end;

function TNTAScrollbarAnnotation.GetColor: TColor;
begin
  Result := cColor;
end;

function TNTAScrollbarAnnotation.GetCustomDraw: Boolean;
begin
  Result := False;
end;

function TNTAScrollbarAnnotation.GetEnabled: Boolean;
begin
  Result := FEnabled;
end;

function TNTAScrollbarAnnotation.GetName: string;
begin
  Result := 'Demo Annotation';
end;

procedure TNTAScrollbarAnnotation.GetScrollbarAnnotations(
  const AEditor: TWinControl);
begin
  var LEditorServices: INTACodeEditorServices;
  if Supports(BorlandIDEServices, INTACodeEditorServices, LEditorServices) then
  begin
    var Lines := LEditorServices.EditorState[AEditor].View.Buffer.GetLinesInBuffer;
    for var I := 1 to Lines do
    begin
      //var LText := LEditorServices.EditorState[AEditor].LogicalLineState[I].Text;
      var LState := LEditorServices.EditorState[AEditor].LogicalLineState[I].State;
      if eleBreakpoint in LState then
        LEditorServices.AddScrollbarAnnotationEntry(AEditor, FIndex, I, clWebRed)
      else if eleCompiled in LState then
        LEditorServices.AddScrollbarAnnotationEntry(AEditor, FIndex, I, clWebBlue);
    end;
  end;
end;

function TNTAScrollbarAnnotation.GetStart: Integer;
begin
  Result := FStart;
end;

function TNTAScrollbarAnnotation.GetWidth: Integer;
begin
  Result := FWidth;
end;

procedure TNTAScrollbarAnnotation.SetEnabled(const Value: Boolean);
begin
  FEnabled := Value;
end;

procedure TNTAScrollbarAnnotation.SetStart(const Value: Integer);
begin
  FStart := Value;
end;

procedure TNTAScrollbarAnnotation.SetWidth(const Value: Integer);
begin
  FWidth := Value;
end;

end.
