unit EditorLocalMenuDemo.Main;

interface

procedure Register;

implementation

uses
  System.SysUtils, Vcl.ActnList, Vcl.Dialogs, Vcl.Forms, ToolsAPI, ToolsAPI.UI;

const
  cMenuCategory = 'TestMenuCategory';

type
  TMenuManager = class
  private
    // The action list holds a list of all the aciton that will be shown as
    // menus items in the editor local menu.
    FActionList: TActionList;
    FRegistered: Boolean;
    FMenuItemChecked: Boolean;
    procedure AddActions;

    procedure OnMenuCheckTestExecute(Sender: TObject);
    procedure OnMenuTestExecute(Sender: TObject);
    procedure OnParentMenuTextExecute(Sender: TObject);
    procedure OnMenuCheckTestUpdate(Sender: TObject);
    procedure OnMenuTestUpdate(Sender: TObject);
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

procedure Register;
begin
  RegisterPackageWizard(TIDEWizard.Create);
end;

{ TMenuManager }

procedure TMenuManager.AddActions;
var
  LAction: TAction;
begin
// Add a basic menu item
  LAction := TAction.Create(FActionList);
  LAction.Name := 'MenuTest';
  LAction.Caption := 'Test Under Debug';
  LAction.Category := 'MenuTest';
  LAction.OnUpdate := OnMenuTestUpdate;
  LAction.OnExecute := OnMenuTestExecute;
  LAction.Enabled := True;
  // Adds the action to the action list
  LAction.ActionList := FActionList;

// Add a menu item to be a parent to a child menu item
  LAction := TAction.Create(FActionList);
  LAction.Name := 'ParentMenuTest';
  LAction.Caption := 'Parent Menu';
  LAction.Category := 'MenuTestParent';
  LAction.OnExecute := OnParentMenuTextExecute;
  LAction.Enabled := True;
  LAction.ActionList := FActionList;

// Add a child menu item
  LAction := TAction.Create(FActionList);
  LAction.Name := 'ChildMenuTest';
  LAction.Caption := 'Child Menu';
  // Notice that the child's category is the parents with a '.' and a name
  // The child must be added to the action list after the parent and all
  // children must come after the parent before another menu that is not a child
  // is added to the action list. At this time only one level of children can be
  // added. Child of a child is not supported.
  LAction.Category := 'MenuTestParent.Child';
  LAction.OnUpdate := OnMenuTestUpdate;
  LAction.OnExecute := OnMenuTestExecute;
  LAction.Enabled := True;
  LAction.ActionList := FActionList;

// Add a child menu item
  LAction := TAction.Create(FActionList);
  LAction.Name := 'CheckMenuTest';
  LAction.Caption := 'Check Menu';
  LAction.Category := 'MenuTest';
  LAction.OnUpdate := OnMenuCheckTestUpdate;
  LAction.OnExecute := OnMenuCheckTestExecute;
  LAction.Enabled := True;
  LAction.ActionList := FActionList;
end;

constructor TMenuManager.Create;
var
  LEditorServices: IOTAEditorServices;
begin
  inherited;
  FActionList := TActionList.Create(nil);

  if Supports(BorlandIDEServices, IOTAEditorServices, LEditorServices) then
  begin
    var LLocalMenuIntf := LEditorServices.GetEditorLocalMenu;
    // The TActionList FActionList is inserted after cEdMenuCatDebug (the debug menu seciton)
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

procedure TMenuManager.OnMenuTestUpdate(Sender: TObject);
begin
// For these menu items no states are changed. You may want to put code here
// to hide or show you menu item based on file types or other conditions by
// setting TAction(Sender).Visible to true or false.
end;

procedure TMenuManager.OnMenuCheckTestExecute(Sender: TObject);
begin
  // Toggle the check state when menu is selected
  FMenuItemChecked := not FMenuItemChecked;
end;

procedure TMenuManager.OnMenuCheckTestUpdate(Sender: TObject);
begin
  // Assign the check state to the action's checked property
  // Visible, Enabled and other property can be set in update
  TAction(Sender).Checked := FMenuItemChecked;
end;

procedure TMenuManager.OnMenuTestExecute(Sender: TObject);
begin
  (BorlandIDEServices as INTAIDEUIServices).MessageDlg('Test menu selected', mtInformation, [mbOK], -1);
end;

procedure TMenuManager.OnParentMenuTextExecute(Sender: TObject);
begin
  // The parent does nothing when it is selected
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
end;

function TIDEWizard.GetIDString: string;
begin
  Result := '[44B2E446-97C5-4D7D-918E-18FBC29D8B5E]';
end;

function TIDEWizard.GetName: string;
begin
  Result := 'Editor.LocalMenu.Demo';
end;

function TIDEWizard.GetState: TWizardState;
begin
  Result := [wsEnabled];
end;

end.
