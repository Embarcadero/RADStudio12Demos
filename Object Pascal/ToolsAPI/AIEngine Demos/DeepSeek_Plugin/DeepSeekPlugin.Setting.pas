unit DeepSeekPlugin.Setting;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes,
  Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Mask,
  Vcl.ExtCtrls, System.Win.Registry, ToolsAPI.AI, DeepSeekPlugin.Consts, System.RegularExpressions;

type
  TFrame_Setting = class(TFrame, IOTAAIPluginSetting)
    Chk_Enabled: TCheckBox;
    Edt_ApiKey: TLabeledEdit;
    Edt_BaseURL: TLabeledEdit;
    Edt_Model: TLabeledEdit;
    Edt_Timeout: TLabeledEdit;
  private
    FInitialEnabled: Boolean;
    FInitialBaseURL: string;
    FInitialModel: string;
    FInitialApiKey: string;
    FInitialTimeout: string;
    {IOTAAIPluginSetting}
    function GetModified: Boolean;
    function GetPluginEnabled: Boolean;
  public
    class function GetRegKey: string;
    {IOTAAIPluginSetting}
    procedure LoadSettings;
    procedure SaveSettings;
    function ParameterValidations(var AErrorMsg: string): Boolean;
    property Modified: Boolean read GetModified;
    property PluginEnabled: Boolean read GetPluginEnabled;
  end;

implementation

{$R *.dfm}

{ TFrame_Setting }

function TFrame_Setting.GetPluginEnabled: Boolean;
begin
  Result := Chk_Enabled.Checked;
end;

function TFrame_Setting.GetModified: Boolean;
begin
  Result := (Chk_Enabled.Checked <> FInitialEnabled) or
            (Edt_BaseURL.Text <> FInitialBaseURL) or
            (Edt_Model.Text <> FInitialModel) or
            (Edt_ApiKey.Text <> FInitialApiKey) or
            (Edt_Timeout.Text <> FInitialTimeout);
end;

class function TFrame_Setting.GetRegKey: string;
begin
  Result := cDeepSeekAI_RegKey;
end;

procedure TFrame_Setting.LoadSettings;
var
  LReg: TRegistry;
begin
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(GetRegKey, False) then
    begin
      if LReg.ValueExists(cDeepSeekAI_RegKey_Enabled) then
        Chk_Enabled.Checked := LReg.ReadBool(cDeepSeekAI_RegKey_Enabled);
      if LReg.ValueExists(cDeepSeekAI_RegKey_BaseURL) then
        Edt_BaseURL.Text := LReg.ReadString(cDeepSeekAI_RegKey_BaseURL);
      if LReg.ValueExists(cDeepSeekAI_RegKey_Model) then
        Edt_Model.Text := LReg.ReadString(cDeepSeekAI_RegKey_Model);
      if LReg.ValueExists(cDeepSeekAI_RegKey_ApiKey) then
        Edt_ApiKey.Text := LReg.ReadString(cDeepSeekAI_RegKey_ApiKey); //Decrypt if you have already stored the encrypted value.
      if LReg.ValueExists(cDeepSeekAI_RegKey_Timeout) then
        Edt_Timeout.Text := LReg.ReadInteger(cDeepSeekAI_RegKey_Timeout).ToString;
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;

  FInitialEnabled := Chk_Enabled.Checked;
  FInitialBaseURL := Edt_BaseURL.Text;
  FInitialModel := Edt_Model.Text;
  FInitialApiKey := Edt_ApiKey.Text;
  FInitialTimeout := Edt_Timeout.Text;
end;

function TFrame_Setting.ParameterValidations(var AErrorMsg: string): Boolean;
begin
  Result := False;
  AErrorMsg := EmptyStr;

  // Validate BaseURL
  if Edt_BaseURL.EditText.Trim.IsEmpty then
  begin
    AErrorMsg := cDeepSeekAI_Msg_BaseURL;
    Exit;
  end;

  if not TRegEx.IsMatch(Edt_BaseURL.EditText.Trim, cDeepSeekAI_URLRegex) then
  begin
    AErrorMsg := cDeepSeekAI_Msg_InvalidURL;
    Exit;
  end;

  // Validate ApiKey
  if Edt_ApiKey.EditText.Trim.IsEmpty then
  begin
    AErrorMsg := cDeepSeekAI_Msg_APIKey;
    Exit;
  end;

  // Validate Model
  if Edt_Model.EditText.Trim.IsEmpty then
  begin
    AErrorMsg := cDeepSeekAI_Msg_Model;
    Exit;
  end;

  //Validate Timeout
  if Edt_Timeout.EditText.Trim.IsEmpty then
  begin
    AErrorMsg := cDeepSeekAI_Msg_Timeout;
    Exit;
  end;

  Result := True;end;

procedure TFrame_Setting.SaveSettings;
var
  LReg: TRegistry;
begin
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(GetRegKey, True) then
    begin
      LReg.WriteBool(cDeepSeekAI_RegKey_Enabled, Chk_Enabled.Checked);
      LReg.WriteString(cDeepSeekAI_RegKey_BaseURL, Edt_BaseURL.Text);
      LReg.WriteString(cDeepSeekAI_RegKey_Model, Edt_Model.Text);
      LReg.WriteString(cDeepSeekAI_RegKey_ApiKey, Edt_ApiKey.Text); //It could be encrypted for the safety of sensitive data.
      LReg.WriteInteger(cDeepSeekAI_RegKey_Timeout, StrToIntDef(Edt_Timeout.Text, cDeepSeekAI_Def_Timeout));
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;
end;

end.
