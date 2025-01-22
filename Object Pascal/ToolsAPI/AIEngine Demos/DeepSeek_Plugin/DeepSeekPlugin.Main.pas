unit DeepSeekPlugin.Main;

interface

uses
  ToolsAPI, ToolsAPI.AI, System.Win.Registry, Winapi.Windows, System.SysUtils, System.Classes,
  DeepSeekPlugin.Controller, DeepSeekPlugin.Consts, DeepSeekPlugin.Setting;

type
  TDeepSeekPlugin = class(TDeepSeekAIRestClient, IOTAAIPlugin)
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
  DeepSeekPlugin: TDeepSeekPlugin;

procedure Register;

implementation

procedure Register;
begin
  if AIEngineService <> nil then
  begin
    DeepSeekPlugin := TDeepSeekPlugin.Create;
    PluginIndex := AIEngineService.RegisterPlugin(DeepSeekPlugin);
  end;
end;

{ TDeepSeekPlugin }

procedure TDeepSeekPlugin.Cancel;
begin
  DoCancel;
end;

function TDeepSeekPlugin.Chat(const AQuestion: string): TGUID;
begin
  LoadSetting;
  Result := TGUID.NewGuid;
  DoChat(AQuestion, Result);
end;

function TDeepSeekPlugin.GenerateImage(const APrompt, ASize, AFormat: string): TGUID;
begin
//Not used.
end;

function TDeepSeekPlugin.GenerateSpeechFromText(const AText, AVoice: string): TGUID;
begin
//Not used.
end;

function TDeepSeekPlugin.GenerateTextFromAudioFile(const AAudioFilePath: string): TGUID;
begin
//Not used.
end;

function TDeepSeekPlugin.GetEnabled: Boolean;
var
  LReg: TRegistry;
begin
  Result := False;
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(TFrame_Setting.GetRegKey, False) then
    begin
      if LReg.ValueExists(cDeepSeekAI_RegKey_Enabled) then
        Result := LReg.ReadBool(cDeepSeekAI_RegKey_Enabled);
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;
end;

function TDeepSeekPlugin.GetFeatures: TAIFeatures;
begin
  Result := [afChat];
end;

function TDeepSeekPlugin.GetName: string;
begin
  Result := cDeepSeekAI_name;
end;

function TDeepSeekPlugin.GetSettingFrame(AOwner: TComponent): IOTAAIPluginSetting;
begin
  Result := TFrame_Setting.Create(AOwner);
end;

function TDeepSeekPlugin.Instruction(const AInput, AInstruction: string): TGUID;
begin
//Not used.
end;

function TDeepSeekPlugin.LoadModels: TGUID;
begin
//Not used.
end;

procedure TDeepSeekPlugin.LoadSetting;
var
  LReg: TRegistry;
begin
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(TFrame_Setting.GetRegKey, False) then
    begin
      if LReg.ValueExists(cDeepSeekAI_RegKey_BaseURL) then
        FBaseURL := LReg.ReadString(cDeepSeekAI_RegKey_BaseURL);
      if LReg.ValueExists(cDeepSeekAI_RegKey_Model) then
        FModel := LReg.ReadString(cDeepSeekAI_RegKey_Model);
      if LReg.ValueExists(cDeepSeekAI_RegKey_ApiKey) then
        FApiKey := LReg.ReadString(cDeepSeekAI_RegKey_ApiKey);
      if LReg.ValueExists(cDeepSeekAI_RegKey_Timeout) then
        FTimeOut := LReg.ReadInteger(cDeepSeekAI_RegKey_Timeout);
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;
end;

function TDeepSeekPlugin.Moderation(const AInput: string): TGUID;
begin
//Not used.
end;

initialization

finalization
  if (AIEngineService <> nil) and (PluginIndex <> -1) then
    AIEngineService.UnregisterPlugin(PluginIndex);

  DeepSeekPlugin := nil;
end.
