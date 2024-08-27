unit CoherePlugin.Setting;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes,
  Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Mask,
  Vcl.ExtCtrls, System.Win.Registry, ToolsAPI.AI, CoherePlugin.Consts;

type
  TFrame_Setting = class(TFrame, IOTAAIPluginSetting)
    Chk_Enabled: TCheckBox;
    Edt_ApiKey: TLabeledEdit;
    Edt_BaseURL: TLabeledEdit;
    Edt_MaxToken: TLabeledEdit;
    Edt_Model: TLabeledEdit;
    Edt_Temperature: TLabeledEdit;
    Edt_Timeout: TLabeledEdit;
  private
    FInitialEnabled: Boolean;
    FInitialBaseURL: string;
    FInitialModel: string;
    FInitialApiKey: string;
    FInitialMaxToken: string;
    FInitialTemperature: string;
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
            (Edt_MaxToken.Text <> FInitialMaxToken) or
            (Edt_Temperature.Text <> FInitialTemperature) or
            (Edt_Timeout.Text <> FInitialTimeout);
end;

class function TFrame_Setting.GetRegKey: string;
begin
  Result := cCohereAI_RegKey;
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
      if LReg.ValueExists(cCohereAI_RegKey_Enabled) then
        Chk_Enabled.Checked := LReg.ReadBool(cCohereAI_RegKey_Enabled);
      if LReg.ValueExists(cCohereAI_RegKey_BaseURL) then
        Edt_BaseURL.Text := LReg.ReadString(cCohereAI_RegKey_BaseURL);
      if LReg.ValueExists(cCohereAI_RegKey_Model) then
        Edt_Model.Text := LReg.ReadString(cCohereAI_RegKey_Model);
      if LReg.ValueExists(cCohereAI_RegKey_ApiKey) then
        Edt_ApiKey.Text := LReg.ReadString(cCohereAI_RegKey_ApiKey); //Decrypt if you have already stored the encrypted value.
      if LReg.ValueExists(cCohereAI_RegKey_MaxToken) then
        Edt_MaxToken.Text := LReg.ReadInteger(cCohereAI_RegKey_MaxToken).ToString;
      if LReg.ValueExists(cCohereAI_RegKey_Temperature) then
        Edt_Temperature.Text := LReg.ReadFloat(cCohereAI_RegKey_Temperature).ToString;
      if LReg.ValueExists(cCohereAI_RegKey_Timeout) then
        Edt_Timeout.Text := LReg.ReadInteger(cCohereAI_RegKey_Timeout).ToString;
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;

  FInitialEnabled := Chk_Enabled.Checked;
  FInitialBaseURL := Edt_BaseURL.Text;
  FInitialModel := Edt_Model.Text;
  FInitialApiKey := Edt_ApiKey.Text;
  FInitialMaxToken := Edt_MaxToken.Text;
  FInitialTemperature := Edt_Temperature.Text;
  FInitialTimeout := Edt_Timeout.Text;
end;

function TFrame_Setting.ParameterValidations(var AErrorMsg: string): Boolean;
begin
  AErrorMsg := EmptyStr;
  if Edt_BaseURL.EditText.Trim.IsEmpty then
    AErrorMsg := cCohereAI_Msg_BaseURL
  else if Edt_ApiKey.EditText.Trim.IsEmpty then
    AErrorMsg := cCohereAI_Msg_APIKey
  else if Edt_Model.EditText.Trim.IsEmpty then
    AErrorMsg := cCohereAI_Msg_Model
  else if Edt_MaxToken.EditText.Trim.IsEmpty then
    AErrorMsg := cCohereAI_Msg_MaxToken
  else if Edt_Temperature.EditText.Trim.IsEmpty then
    AErrorMsg := cCohereAI_Msg_Temperature;

  Result := AErrorMsg.IsEmpty;
end;

procedure TFrame_Setting.SaveSettings;
var
  LReg: TRegistry;
begin
  LReg := TRegistry.Create;
  try
    LReg.RootKey := HKEY_CURRENT_USER;
    if LReg.OpenKey(GetRegKey, True) then
    begin
      LReg.WriteBool(cCohereAI_RegKey_Enabled, Chk_Enabled.Checked);
      LReg.WriteString(cCohereAI_RegKey_BaseURL, Edt_BaseURL.Text);
      LReg.WriteString(cCohereAI_RegKey_Model, Edt_Model.Text);
      LReg.WriteString(cCohereAI_RegKey_ApiKey, Edt_ApiKey.Text); //It could be encrypted for the safety of sensitive data.
      LReg.WriteInteger(cCohereAI_RegKey_MaxToken, StrToIntDef(Edt_MaxToken.Text, cCohereAI_Def_MaxTokens));
      LReg.WriteFloat(cCohereAI_RegKey_Temperature, StrToFloatDef(Edt_Temperature.Text, cCohereAI_Def_Temp));
      LReg.WriteInteger(cCohereAI_RegKey_Timeout, StrToIntDef(Edt_Timeout.Text, cCohereAI_Def_Timeout));
      LReg.CloseKey;
    end;
  finally
    LReg.Free;
  end;
end;

end.
