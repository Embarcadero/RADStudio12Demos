unit EditorRawReadDemo.Main;

interface

// This demo will add a local editor menu item called "Calculate File Data"
// When the menu item is selected the code will use two different techniques
// to calculate the number of bytes in a file and the length of the longest
// line. Both test are run multuple times and the result times are shown.
// If you only care about the Raw Read code look at procedure RawReadGetFileData

procedure Register;

implementation

uses
  System.Actions, System.Classes, System.Generics.Collections, System.Diagnostics,
  System.SysUtils, Vcl.ActnList, Vcl.Dialogs, Vcl.Forms, ToolsApi, ToolsAPI.UI,
  Winapi.ActiveX, IStreams;

const
  cMenuCategory = 'RawReadMenuCategory';

type
  TResultRec = record
    FTotalSize: Integer;
    FLongestLine: Integer;
  end;
  PResultRec = ^TResultRec;

  TMenuManager = class
  private
    // The action list holds a list of all the aciton that will be shown as
    // menus items in the editor local menu.
    FActionList: TActionList;
    FEditorServices: IOTAEditorServices;
    FMenuItemChecked: Boolean;
    FRegistered: Boolean;
    procedure AddActions;
    procedure OnRawReadExecute(Sender: TObject);
    procedure OnRawReadUpdate(Sender: TObject);
    procedure StreamReadGetFileData(const ABuffer: IOTAEditBuffer;
      var AResults: TResultRec);
    procedure RawReadGetFileData(const ABuffer: IOTAEditBuffer;
      var AResults: TResultRec);
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
  LAction: TAction;
begin
// Add editor local menu to allow user to run test.
  LAction := TAction.Create(FActionList);
  LAction.Name := 'MenuRawReadTest';
  LAction.Caption := 'Calculate File Data';
  LAction.Category := 'RawReadTest';
  LAction.OnUpdate := OnRawReadUpdate;
  LAction.OnExecute := OnRawReadExecute;
  LAction.Enabled := True;
  LAction.ActionList := FActionList;
end;

constructor TMenuManager.Create;
begin
  inherited;
  FActionList := TActionList.Create(nil);

  if Supports(BorlandIDEServices, IOTAEditorServices, FEditorServices) then
  begin
    var LLocalMenuIntf := FEditorServices.GetEditorLocalMenu;
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

procedure TMenuManager.OnRawReadExecute(Sender: TObject);
const
  cNumTests = 1000;
  cResultString = 'Number of test runs = %d' + #10#13 +
                   #10#13 +
                  'Read from stream results' + #10#13 +
                  'Total file size = %d' + #10#13 +
                  'Longest Line = %d' + #10#13 +
                  'Time taken = %d Milliseconds' + #10#13 +
                   #10#13 +
                  'Read from raw results' + #10#13 +
                  'Total file size = %d' + #10#13 +
                  'Longest Line = %d' + #10#13 +
                  'Time taken = %d Milliseconds';
var
  LBuffer: IOTAEditBuffer;
  LRawReader: IOTARawEditReader;
begin
  LBuffer := FEditorServices.GetTopBuffer;
  if Supports(LBuffer, IOTARawEditReader, LRawReader) then
  begin
    // Do tests using stream reader
    var LStopWatch := TStopWatch.Create;
    var LStreamReadData: TResultRec;
    LStopWatch.Start;
    for var I := 1 to cNumTests  do
      StreamReadGetFileData(LBuffer, LStreamReadData);
    LStopWatch.Stop;
    var LStreamTime := LStopWatch.ElapsedMilliseconds;

    // Do test using raw data reader
    LStopWatch.Reset;
    LStopWatch.Start;
    var LRawReadData: TResultRec;
    for var I := 1 to cNumTests  do
      RawReadGetFileData(LBuffer, LRawReadData);
    LStopWatch.Stop;
    var LRawTime := LStopWatch.ElapsedMilliseconds;

    // Show Results
    var LResultString := Format(cResultString,
      [cNumTests,
       LStreamReadData.FTotalSize, LStreamReadData.FLongestLine, LStreamTime,    // Steam Read Data
       LRawReadData.FTotalSize, LRawReadData.FLongestLine, LRawTime]);           // Raw Read Data
    (BorlandIDEServices as INTAIDEUIServices).MessageDlg(LResultString, mtInformation, [mbOK], -1);
  end;
end;

procedure TMenuManager.OnRawReadUpdate(Sender: TObject);
begin
  TAction(Sender).Enabled := FEditorServices.TopView <> nil;
end;

// GetLine is called once for each line in the file. ALineInfo.lineLength
// does not include the line ending. Use lineEnd to find what the line ending
// is used for the given line.
procedure GetLine(ALine: Longint; ALineInfo: POTALineInfo;
    AUserData: Pointer); {$IFDEF WIN32} pascal {$ENDIF}
const
  cLineEndSize:array of Integer = [2, 1, 1, 2, 2, 0];
var
  LEOLLen: Integer;
begin
  // Get line ending size
  LEOLLen := cLineEndSize[Integer(ALineInfo.lineEnd)];

  // Increase total size
  Inc(PResultRec(AUserData).FTotalSize, ALineInfo.lineLength + LEOLLen);

  // Check for longest line
  if ALineInfo.lineLength > PResultRec(AUserData).FLongestLine then
    PResultRec(AUserData).FLongestLine := ALineInfo.lineLength;
end;

procedure TMenuManager.RawReadGetFileData(const ABuffer: IOTAEditBuffer;
  var AResults: TResultRec);
var
  LRawRead: IOTARawEditReader;
begin
  //Initialize data
  AResults.FTotalSize := 0;
  AResults.FLongestLine := 0;

  if Supports(ABuffer, IOTARawEditReader, LRawRead) then
    // Get line data starting at line 1 and going until line MaxInt. If the
    // ending line is greater than total number of lines then the callback
    // stops at the last line.
    LRawRead.GetLineData(1, MaxInt, GetLine, @AResults);
end;

procedure TMenuManager.StreamReadGetFileData(const ABuffer: IOTAEditBuffer;
  var AResults: TResultRec);
var
  LIStream: IStream;
  LIMemStream: TIMemoryStream;
  LMemStream: TMemoryStream;
  LEditorContent: IOTAEditorContent;
  LFileContent: UTF8String;
  LList: TStringList;
  S: string;
begin
  //Initialize data
  AResults.FTotalSize := 0;
  AResults.FLongestLine := 0;

  //Get file content using existing tools api technique
  LEditorContent := ABuffer as IOTAEditorContent;
  LIStream := LEditorContent.Content;
  LIMemStream := LIStream as TIMemoryStream;
  LMemStream := LIMemStream.MemoryStream;
  SetLength(LFileContent, LMemStream.Size);
  LMemStream.Position := 0;
  if LMemStream.Size <> 0 then
    LMemStream.Read(LFileContent[1], Length(LFileContent));

  // Get File Size
  AResults.FTotalSize := Length(LFileContent);

  // Get Longest Line
  S := UTF8ToString(LFileContent);
  LList := TStringList.Create;
  try
    ExtractStrings([#13], [#10], PChar(S), LList);
    AResults.FLongestLine := 0;
    for S in LList do
      if Length(S) > AResults.FLongestLine then
        AResults.FLongestLine := Length(S);
  finally
    LList.Free;
  end;
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
end;

function TIDEWizard.GetIDString: string;
begin
  Result := '[962E9F98-B228-451B-B58E-07A2A5B3BC5E]';
end;

function TIDEWizard.GetName: string;
begin
  Result := 'Editor.RawRead.Demo';
end;

function TIDEWizard.GetState: TWizardState;
begin
  Result := [wsEnabled];
end;

end.
