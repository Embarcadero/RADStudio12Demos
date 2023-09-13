unit EditorWriteDemo.Main;


interface

// This demo will add a local editor menu item called "Write to File"

procedure Register;

implementation

uses
  System.Actions, System.Classes, System.Generics.Collections, System.Diagnostics,
  System.SysUtils, Vcl.ActnList, Vcl.Dialogs, Vcl.Forms, ToolsApi, ToolsAPI.UI,
  Winapi.ActiveX, IStreams;

const
  cMenuCategory = 'RawWriteMenuCategory';

type
  TResultRec = record
    FTotalSize: Integer;
    FLongestLine: Integer;
  end;
  PResultRec = ^TResultRec;

  TMenuManager = class
  private
    // The action list holds a list of all the action that will be shown as
    // menus items in the editor local menu.
    FActionList: TActionList;
    FEditorServices: IOTAEditorServices;
    FMenuItemChecked: Boolean;
    FRegistered: Boolean;
    FWriter: IOTAEditWriter;
    FLine: Integer;
    procedure AddActions;
    procedure OnRawWriteAddExecute(Sender: TObject);
    procedure OnRawWriteDeleteExecute(Sender: TObject);
    procedure OnRawWriteReplaceExecute(Sender: TObject);
    procedure OnRawWriteMain(Sender: TObject);
    function BeginWrite: Boolean;
    procedure EndWrite;
    procedure OnRawWriteUpdate(Sender: TObject);
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TIDEWizard = class(TNotifierObject, IOTAWizard)
  private
    FMenuManager: TMenuManager;
  public
    constructor Create;
    destructor Destroy; override;
    function GetIDString: string;
    procedure Execute;
    function GetName: string;
    function GetState: TWizardState;
  end;

{ TMenuManager }

procedure TMenuManager.AddActions;
var
  LAddAction: TAction;
  LDeleteAction: TAction;
  LReplaceAction: TAction;
begin
// Add editor local menu to allow user to run test.
  LAddAction := TAction.Create(FActionList);
  LAddAction.Name := 'MenuRawWriteTestMain';
  LAddAction.Caption := 'Write to File';
  LAddAction.Category := 'RawWriteTest';
  LAddAction.OnUpdate := OnRawWriteUpdate;
  LAddAction.OnExecute := OnRawWriteMain;
  LAddAction.Enabled := True;
  LAddAction.ActionList := FActionList;


  LAddAction := TAction.Create(FActionList);
  LAddAction.Name := 'MenuRawWriteTestAdd';
  LAddAction.Caption := 'Add';
  LAddAction.Category := 'RawWriteTest.Add';
  LAddAction.OnUpdate := OnRawWriteUpdate;
  LAddAction.OnExecute := OnRawWriteAddExecute;
  LAddAction.Enabled := True;
  LAddAction.ActionList := FActionList;

  LDeleteAction := TAction.Create(FActionList);
  LDeleteAction.Name := 'MenuRawWriteTestDelete';
  LDeleteAction.Caption := 'Delete';
  LDeleteAction.Category := 'RawWriteTest.Delete';
  LDeleteAction.OnUpdate := OnRawWriteUpdate;
  LDeleteAction.OnExecute := OnRawWriteDeleteExecute;
  LDeleteAction.Enabled := True;
  LDeleteAction.ActionList := FActionList;

  LReplaceAction := TAction.Create(FActionList);
  LReplaceAction.Name := 'MenuRawWriteTestReplace';
  LReplaceAction.Caption := 'Replace';
  LReplaceAction.Category := 'RawWriteTest.Replace';
  LReplaceAction.OnUpdate := OnRawWriteUpdate;
  LReplaceAction.OnExecute := OnRawWriteReplaceExecute;
  LReplaceAction.Enabled := True;
  LReplaceAction.ActionList := FActionList;
end;

constructor TMenuManager.Create;
begin
  inherited;
  FActionList := TActionList.Create(nil);

  if Supports(BorlandIDEServices, IOTAEditorServices, FEditorServices) then
  begin
    var LLocalMenuIntf := FEditorServices.GetEditorLocalMenu;
    // The TActionList FActionList is inserted after cEdMenuCatDebug (the debug menu section)
    // There are other constants listed in ToolsApi.pas to control the location
    // you menu is inserted.
    LLocalMenuIntf.RegisterActionList(FActionList, cMenuCategory, cEdMenuCatDebug);
    FRegistered := True;
    AddActions;
  end
  else
    FRegistered := False;

  FMenuItemChecked := False;
end;

destructor TMenuManager.Destroy;
var
  LEditorServices: IOTAEditorServices;
begin
  // it is very important to unregister the action list before the package is
  // unloaded from memory, otherwise anytime the editor local menu is shown it
  // will throw an exception when trying to call OnUpdate.

  if FRegistered then
  begin
    if Supports(BorlandIDEServices, IOTAEditorServices, LEditorServices) then
    begin
      var LLocalMenuIntf := LEditorServices.GetEditorLocalMenu;
      LLocalMenuIntf.UnregisterActionList(cMenuCategory);
    end;
  end;
  FreeAndNil(FActionList);
  inherited;
end;

function TMenuManager.BeginWrite: Boolean;
var
  LBuffer: IOTAEditBuffer;
begin
  LBuffer := FEditorServices.GetTopBuffer;
  // Verify that we have a buffer and view.
  if (LBuffer = nil) or (LBuffer.TopView = nil) then
    Exit(False);

  // Create a writer that uses undo.
  FWriter := LBuffer.CreateUndoableWriter;

  // Line to be edited
  FLine := LBuffer.TopView.CursorPos.Line;
  Result := True;
end;

procedure TMenuManager.EndWrite;
begin
  // It is important to close the writer after use. The IDE reparse and can change
  // the file and internal information at any time so close the writer when used
  // to prevent issues.
  FWriter := nil;
  FLine := 0;
end;

procedure TMenuManager.OnRawWriteAddExecute(Sender: TObject);
begin
  if BeginWrite then
  begin
    FWriter.InsertLine(FLine, 'Added/Inserted new line.');
    EndWrite;
  end;
end;

procedure TMenuManager.OnRawWriteDeleteExecute(Sender: TObject);
begin
  if BeginWrite then
  begin
    FWriter.DeleteLine(FLine);
    EndWrite;
  end;
end;

procedure TMenuManager.OnRawWriteMain(Sender: TObject);
begin
// do nothing
end;

procedure TMenuManager.OnRawWriteReplaceExecute(Sender: TObject);
begin
  if BeginWrite then
  begin
    FWriter.ReplaceLine(FLine, 'Replaced Line with this.');
    EndWrite;
  end;
end;

procedure TMenuManager.OnRawWriteUpdate(Sender: TObject);
begin
  TAction(Sender).Enabled := FEditorServices.TopView <> nil;
end;


procedure Register;
begin
  RegisterPackageWizard(TIDEWizard.Create);
end;

{ TIDEWizard }

constructor TIDEWizard.Create;
begin
  FMenuManager := TMenuManager.Create;
end;

destructor TIDEWizard.Destroy;
begin
  // It is important to free FMenuManager when the package is unloaded because
  // it will unregister its action list in the destructor which is required.
  FreeAndNil(FMenuManager);
  inherited;
end;

procedure TIDEWizard.Execute;
begin
// Do nothing
end;

function TIDEWizard.GetIDString: string;
begin
  Result := '[27E61DED-37E6-49A6-AED9-96E518161485]';
end;

function TIDEWizard.GetName: string;
begin
  Result := 'Editor.RawWrite.Demo';
end;

function TIDEWizard.GetState: TWizardState;
begin
  Result := [wsEnabled];
end;

end.
