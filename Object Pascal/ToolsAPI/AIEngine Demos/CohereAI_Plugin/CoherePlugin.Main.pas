unit CoherePlugin.Main;

interface

uses
  ToolsAPI, ToolsAPI.AI, System.Win.Registry, Winapi.Windows, System.SysUtils, System.Classes,
  CoherePlugin.Controller, CoherePlugin.Consts, CoherePlugin.Setting;

type
  TCoherePlugin = class(TCohereAIRestClient, IOTAAIPlugin)
  private
    procedure LoadSetting;
    {IOTAAIPlugin}
    function GetName: string;
    function GetFeatures: TAIFeatures;
    function GetEnabled: Boolean;
  public
    {IOTAAIPlugin}
    function Chat(const AQuestion: string): TGUID;
    function LoadModels: TGUID;
    function Instruction(const AInput: string; const AInstruction: string): TGUID;
    function Moderation(const AInput: string): TGUID;
    function GenerateImage(const APrompt: string; const ASize: string; const AFormat: string): TGUID;
    function GenerateSpeechFromText(const AText: string; const AVoice: string): TGUID;
    function GenerateTextFromAudioFile(const AAudioFilePath: string): TGUID;
    function GetSettingFrame(AOwner: TComponent): IOTAAIPluginSetting;
    procedure Cancel;

    property AvailableFeatures: TAIFeatures read GetFeatures;
    property Enabled: Boolean read GetEnabled;
    property Name: string read GetName;
  end;

var
  PluginIndex: Integer = -1;
  CoherePlugin: TCoherePlugin;

procedure Register;

implementation

procedure Register;
begin
  if AIEngineService <> nil then
  begin
    CoherePlugin := TCoherePlugin.Create;
    PluginIndex := AIEngineService.RegisterPlugin(CoherePlugin);
  end;
end;

{ TCoherePlugin }

procedure TCoherePlugin.Cancel;
begin
  DoCancel;
end;

function TCoherePlugin.Chat(const AQuestion: string): TGUID;
begin
  LoadSetting;
  Result := TGUID.NewGuid;
  DoChat(AQuestion, Result);
end;

function TCoherePlugin.GenerateImage(const APrompt, ASize, AFormat: string): TGUID;
begin
//Not used.
end;

function TCoherePlugin.GenerateSpeechFromText(const AText, AVoice: string): TGUID;
begin
//Not used.
end;

function TCoherePlugin.GenerateTextFromAudioFile(const AAudioFilePath: string): TGUID;
begin
//Not used.
end;

function TCoherePlugin.GetEnabled: Boolean;
var
  LReg: TRegistry;
begin
  Result := False;
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(TFrame_Setting.GetRegKey, False) then
    begin
      if LReg.ValueExists(cCohereAI_RegKey_Enabled) then
        Result := LReg.ReadBool(cCohereAI_RegKey_Enabled);
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;
end;

function TCoherePlugin.GetFeatures: TAIFeatures;
begin
  Result := [afChat];
end;

function TCoherePlugin.GetName: string;
begin
  Result := cCohereAI_name;
end;

function TCoherePlugin.GetSettingFrame(AOwner: TComponent): IOTAAIPluginSetting;
begin
  Result := TFrame_Setting.Create(AOwner);
end;

function TCoherePlugin.Instruction(const AInput, AInstruction: string): TGUID;
begin
//Not used.
end;

function TCoherePlugin.LoadModels: TGUID;
begin
//Not used.
end;

procedure TCoherePlugin.LoadSetting;
var
  LReg: TRegistry;
begin
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(TFrame_Setting.GetRegKey, False) then
    begin
      if LReg.ValueExists(cCohereAI_RegKey_BaseURL) then
        FBaseURL := LReg.ReadString(cCohereAI_RegKey_BaseURL);
      if LReg.ValueExists(cCohereAI_RegKey_Model) then
        FModel := LReg.ReadString(cCohereAI_RegKey_Model);
      if LReg.ValueExists(cCohereAI_RegKey_ApiKey) then
        FApiKey := LReg.ReadString(cCohereAI_RegKey_ApiKey);
      if LReg.ValueExists(cCohereAI_RegKey_MaxToken) then
        FMaxTokens := LReg.ReadInteger(cCohereAI_RegKey_MaxToken);
      if LReg.ValueExists(cCohereAI_RegKey_Temperature) then
        FTemperature := LReg.ReadFloat(cCohereAI_RegKey_Temperature);
      if LReg.ValueExists(cCohereAI_RegKey_Timeout) then
        FTimeOut := LReg.ReadInteger(cCohereAI_RegKey_Timeout);
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;
end;

function TCoherePlugin.Moderation(const AInput: string): TGUID;
begin
//Not used.
end;

initialization

finalization
  if (AIEngineService <> nil) and (PluginIndex <> -1) then
    AIEngineService.UnregisterPlugin(PluginIndex);

  CoherePlugin := nil;
end.
