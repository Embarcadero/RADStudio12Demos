//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

unit uMain_frm;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.StrUtils, System.Variants, System.Classes,
  Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Data.DB,
  Vcl.ExtCtrls, Vcl.ComCtrls, System.DateUtils, Vcl.Grids, Vcl.DBGrids, System.IniFiles,
  Vcl.Imaging.pngimage, Datasnap.DBClient, Datasnap.Provider, System.Generics.Collections,
  REST.Types, REST.Authenticator.OAuth.WebForm.Win, Data.Bind.EngExt,
  Vcl.Bind.DBEngExt, System.Rtti, System.Bindings.Outputs, Vcl.Bind.Editors,
  Data.Bind.Components, REST.Authenticator.Basic, REST.Client,
  REST.Authenticator.OAuth, Data.Bind.ObjectScope, REST.Response.Adapter,
  Vcl.Mask, System.Net.HttpClient;

type
  Tfrm_Main = class(TForm)
    btn_DelphiPRAXiS: TButton;
    Button3: TButton;
    pc_Demos: TPageControl;
    ts_DelphiPRAXiS: TTabSheet;
    pnl_Header: TPanel;
    Splitter1: TSplitter;
    memo_Desc_DP: TMemo;
    edt_DP_BaseURL: TLabeledEdit;
    edt_DP_ResourcePath: TLabeledEdit;
    edt_DP_Username: TLabeledEdit;
    edt_DP_Password: TLabeledEdit;
    pc_Data: TPageControl;
    ts_ResponseData: TTabSheet;
    memo_ResponseData: TMemo;
    Label1: TLabel;
    Label2: TLabel;
    ts_GoogleTasks: TTabSheet;
    memo_Desc_GoogleTasks: TMemo;
    btn_GoogleTasks_FetchAuthToken: TButton;
    edt_GoogleTasks_BaseURL: TLabeledEdit;
    edt_GoogleTasks_AccessToken: TLabeledEdit;
    edt_GoogleTasks_ClientID: TLabeledEdit;
    edt_GoogleTasks_ClientSecret: TLabeledEdit;
    edt_GoogleTasks_RefreshToken: TLabeledEdit;
    btn_GoogleTasks_FetchLists: TButton;
    ts_Facebook: TTabSheet;
    memo_Desc_Facebook: TMemo;
    edt_Facebook_BaseURL: TLabeledEdit;
    btn_Facebook_FetchAuthToken: TButton;
    edt_Facebook_AppID: TLabeledEdit;
    edt_Facebook_AppSecret: TLabeledEdit;
    edt_FaceBook_AccessToken: TLabeledEdit;
    btn_Facebook_FetchData: TButton;
    Image1: TImage;
    edt_Facebook_ResourceURI: TLabeledEdit;
    edt_GoogleTasks_ResourceURI: TLabeledEdit;
    ts_DataSet: TTabSheet;
    memo_Desc_DataSet: TMemo;
    edt_DataSet_BaseURL: TLabeledEdit;
    edt_DataSet_ResourceURI: TLabeledEdit;
    btn_DataSet_FetchData: TButton;
    DBGrid1: TDBGrid;
    DataSource: TDataSource;
    RESTResponseDataSetAdapter: TRESTResponseDataSetAdapter;
    RESTClient: TRESTClient;
    RESTResponse: TRESTResponse;
    tc_OpenMeteo: TTabSheet;
    edt_openmeteo_latitude: TLabeledEdit;
    edt_openmeteo_url: TLabeledEdit;
    edt_openmeteo_resource: TLabeledEdit;
    ButtonOpenMeteo: TButton;
    Memo1: TMemo;
    Lbl_Temperature: TLabel;
    ts_DropBox: TTabSheet;
    memo_Desc_DropBox: TMemo;
    edt_DropBox_ClientSecret: TLabeledEdit;
    edt_DropBox_ClientID: TLabeledEdit;
    edt_DropBox_BaseURL: TLabeledEdit;
    edt_DropBox_ResourceURI: TLabeledEdit;
    btn_DropBox_FetchAuthCode: TButton;
    btn_DropBox_FetchData: TButton;
    edt_DropBox_AccessToken: TLabeledEdit;
    OAuth2_GoogleTasks: TOAuth2Authenticator;
    OAuth2_Facebook: TOAuth2Authenticator;
    ClientDataSet: TClientDataSet;
    edt_openmeteo_longitude: TLabeledEdit;
    OAuth2_Dropbox: TOAuth2Authenticator;
    RESTRequest: TRESTRequest;
    HTTPBasic_DelphiPRAXiS: THTTPBasicAuthenticator;
    Panel1: TPanel;
    lbl_status: TLabel;
    BindingsList1: TBindingsList;
    LinkControlToField1: TLinkControlToField;
    LinkControlToField2: TLinkControlToField;
    Label3: TLabel;
    Lbl_Folders: TLabel;
    Label5: TLabel;
    Lbl_Files: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure btn_DelphiPRAXiSClick(Sender: TObject);
    procedure btn_GoogleTasks_FetchAuthTokenClick(Sender: TObject);
    procedure btn_GoogleTasks_FetchListsClick(Sender: TObject);
    procedure btn_Facebook_FetchAuthTokenClick(Sender: TObject);
    procedure btn_Facebook_FetchDataClick(Sender: TObject);
    procedure btn_DataSet_FetchDataClick(Sender: TObject);
    procedure ButtonOpenMeteoClick(Sender: TObject);
    procedure edt_DropBox_FetchAuthCodeClick(Sender: TObject);
    procedure edt_DropBox_FetchDataClick(Sender: TObject);
    procedure RESTRequestAfterExecute(Sender: TCustomRESTRequest);
    procedure RESTRequestHTTPProtocolError(Sender: TCustomRESTRequest);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
    FINIFilename: string;

    procedure LoadConnectionData(const AFilename: string);
    procedure SaveConnectionData(const AFilename: string);

    procedure ClearMemos;
    procedure ResetRESTComponentsToDefaults;
  public
    { Public declarations }
  end;

var
  frm_Main: Tfrm_Main;

implementation

uses
  System.UITypes, System.JSON, REST.Json, Winapi.EdgeUtils;

{$R *.dfm}

// -----------------------------------------------------------------------
// Delphi Praxis

procedure Tfrm_Main.btn_DelphiPRAXiSClick(Sender: TObject);
begin
  ResetRESTComponentsToDefaults;

  HTTPBasic_DelphiPRAXiS.Username := edt_DP_Username.Text;
  HTTPBasic_DelphiPRAXiS.Password := edt_DP_Password.Text;

  RESTClient.BaseURL := edt_DP_BaseURL.Text;
  RESTClient.Authenticator := HTTPBasic_DelphiPRAXiS;

  RESTRequest.Resource := edt_DP_ResourcePath.Text;
  RESTRequest.Execute;
end;

// -----------------------------------------------------------------------
// Google

procedure Tfrm_Main.btn_GoogleTasks_FetchAuthTokenClick(Sender: TObject);
begin
  edt_GoogleTasks_AccessToken.Text := '';
  edt_GoogleTasks_RefreshToken.Text := '';

  OAuth2_GoogleTasks.ResetToDefaults;
  OAuth2_GoogleTasks.Provider := 'google';
  OAuth2_GoogleTasks.ClientID := edt_GoogleTasks_ClientID.Text;
  OAuth2_GoogleTasks.ClientSecret := edt_GoogleTasks_ClientSecret.Text;
  OAuth2_GoogleTasks.Scope := 'https://www.googleapis.com/auth/tasks';
  OAuth2_GoogleTasks.Authenticate(RESTRequest);

  edt_GoogleTasks_AccessToken.Text := OAuth2_GoogleTasks.AccessToken;
  edt_GoogleTasks_RefreshToken.Text := OAuth2_GoogleTasks.RefreshToken;
end;

procedure Tfrm_Main.btn_GoogleTasks_FetchListsClick(Sender: TObject);
begin
  ResetRESTComponentsToDefaults;
  OAuth2_GoogleTasks.AccessToken := edt_GoogleTasks_AccessToken.Text;
  OAuth2_GoogleTasks.RefreshToken := edt_GoogleTasks_RefreshToken.Text;

  RESTClient.Authenticator := OAuth2_GoogleTasks;
  // https://www.googleapis.com/tasks/v1/
  RESTClient.BaseURL := edt_GoogleTasks_BaseURL.Text;

  // users/@me/lists
  RESTRequest.Resource := edt_GoogleTasks_ResourceURI.Text;
  RESTRequest.Execute;
end;

// -----------------------------------------------------------------------
// Facebook

procedure Tfrm_Main.btn_Facebook_FetchAuthTokenClick(Sender: TObject);
begin
  edt_FaceBook_AccessToken.Text := '';

  OAuth2_Facebook.ResetToDefaults;
  OAuth2_Facebook.Provider := 'facebook';
  OAuth2_Facebook.ClientID := edt_Facebook_AppID.Text;
  OAuth2_Facebook.ClientSecret := edt_Facebook_AppSecret.Text;
  OAuth2_Facebook.Scope := 'user_birthday,user_friends,user_gender';
  OAuth2_Facebook.Authenticate(RESTRequest);

  edt_FaceBook_AccessToken.Text := OAuth2_Facebook.AccessToken;
end;

procedure Tfrm_Main.btn_Facebook_FetchDataClick(Sender: TObject);
begin
  ResetRESTComponentsToDefaults;
  OAuth2_Facebook.AccessToken := edt_FaceBook_AccessToken.Text;

  RESTClient.Authenticator := OAuth2_Facebook;
  RESTClient.BaseURL := edt_Facebook_BaseURL.Text;

  RESTRequest.Resource := edt_Facebook_ResourceURI.Text;
  RESTRequest.Execute;
end;

// -----------------------------------------------------------------------
// Fetch to DataSet

procedure Tfrm_Main.btn_DataSet_FetchDataClick(Sender: TObject);
begin
  ResetRESTComponentsToDefaults;

  RESTResponseDataSetAdapter.Response := RESTResponse;
  RESTResponseDataSetAdapter.Dataset := ClientDataSet;
  RESTResponseDataSetAdapter.RootElement := 'results';

  RESTClient.BaseURL := edt_DataSet_BaseURL.Text;

  RESTRequest.Resource := edt_DataSet_ResourceURI.Text;
  RESTRequest.Execute;
end;

// -----------------------------------------------------------------------
// OpenMeteo

procedure Tfrm_Main.ButtonOpenMeteoClick(Sender: TObject);
begin
  ResetRESTComponentsToDefaults;
  RESTClient.BaseURL := edt_openmeteo_url.Text;
  RESTClient.SecureProtocols := [THTTPSecureProtocol.TLS11, THTTPSecureProtocol.TLS12];

  RESTRequest.Resource := edt_openmeteo_resource.Text;
  RESTRequest.Params.AddItem('LAT', edt_openmeteo_latitude.Text, TRESTRequestParameterKind.pkURLSEGMENT);
  RESTRequest.Params.AddItem('LONG', edt_openmeteo_longitude.Text, TRESTRequestParameterKind.pkURLSEGMENT);
  RESTRequest.Execute;

  // Parse for temperature
  Lbl_Temperature.Caption :=
    RESTRequest.Response.JSONValue.GetValue<string>('current_weather.temperature') + ' C';
end;

// -----------------------------------------------------------------------
// DropBox

procedure Tfrm_Main.edt_DropBox_FetchAuthCodeClick(Sender: TObject);
begin
  edt_DropBox_AccessToken.Text := '';

  OAuth2_Dropbox.ResetToDefaults;
  OAuth2_Dropbox.Provider := 'dropbox';
  OAuth2_Dropbox.ClientID := edt_DropBox_ClientID.Text;
  OAuth2_Dropbox.ClientSecret := edt_DropBox_ClientSecret.Text;
  OAuth2_Dropbox.Scope := 'files.metadata.read';
  OAuth2_Dropbox.Authenticate(RESTRequest);

  edt_DropBox_AccessToken.Text := OAuth2_Dropbox.AccessToken;
end;

procedure Tfrm_Main.edt_DropBox_FetchDataClick(Sender: TObject);
var
  LFolderCount, LFileCount: Integer;
  LEntries: TJSONArray;
  LFile: TJSONValue;
begin
  // https://www.dropbox.com/developers/documentation/http/documentation#files-list_folder
  ResetRESTComponentsToDefaults;
  OAuth2_Dropbox.AccessToken := edt_DropBox_AccessToken.Text;

  RESTClient.Authenticator := OAuth2_Dropbox;
  RESTClient.BaseURL := edt_DropBox_BaseURL.Text;

  RESTRequest.Method := TRESTRequestMethod.rmPOST;
  RESTRequest.Resource := edt_DropBox_ResourceURI.Text;
  // specify the path, empty string for '/' (root)
  RESTRequest.AddBody(TJSONObject.Create(TJSONPair.Create('path', '')), ooREST);
  RESTRequest.Execute;

  // Parse for files and folders
  LFolderCount := 0;
  LFileCount := 0;
  LEntries := RESTRequest.Response.JSONValue.P['entries'] as TJSONArray;
  for LFile in LEntries do
  begin
    if (LFile as TJSONObject).GetValue('.tag').Value = 'folder' then
      Inc(LFolderCount)
    else if (LFile as TJSONObject).GetValue('.tag').Value = 'file' then
      Inc(LFileCount);
  end;
  Lbl_Folders.Caption := LFolderCount.ToString;
  Lbl_Files.Caption := LFileCount.ToString;
end;

// -----------------------------------------------------------------------
// Utilities

procedure Tfrm_Main.ClearMemos;
begin
  memo_ResponseData.Clear;
end;

procedure Tfrm_Main.FormCreate(Sender: TObject);
begin
  // Optionally specify path to WebView2Loader.dll
  // SetWebView2Path('C:\Documents and Settings\User\Local Settings\Microsoft\OneDrive\23.169.0813.0001\WebView2Loader.dll');
  FINIFilename := ChangeFileExt(Application.ExeName, '.ini');
  LoadConnectionData(FINIFilename);

  pc_Demos.ActivePage := ts_GoogleTasks;
  pc_Data.ActivePage := ts_ResponseData;
  ClearMemos;
end;

procedure Tfrm_Main.FormDestroy(Sender: TObject);
begin
  SaveConnectionData(FINIFilename);
end;

procedure Tfrm_Main.LoadConnectionData(const AFilename: string);
var
  LINIFile: TMemIniFile;
begin
  if not FileExists(AFilename) then
    Exit;

  LINIFile := TMemIniFile.Create(AFilename);
  try
    // load data for example "googletasks"
    edt_GoogleTasks_ClientID.Text := LINIFile.ReadString('googletasks', 'clientid', edt_GoogleTasks_ClientID.Text);
    edt_GoogleTasks_ClientSecret.Text := LINIFile.ReadString('googletasks', 'clientsecret', edt_GoogleTasks_ClientSecret.Text);
    edt_GoogleTasks_AccessToken.Text := LINIFile.ReadString('googletasks', 'accesstoken', edt_GoogleTasks_AccessToken.Text);
    edt_GoogleTasks_RefreshToken.Text := LINIFile.ReadString('googletasks', 'refreshtoken', edt_GoogleTasks_RefreshToken.Text);

    // load data for example "facebook"
    edt_Facebook_AppID.Text := LINIFile.ReadString('facebook', 'clientid', edt_Facebook_AppID.Text);
    edt_Facebook_AppSecret.Text := LINIFile.ReadString('facebook', 'clientsecret', edt_Facebook_AppSecret.Text);
    edt_FaceBook_AccessToken.Text := LINIFile.ReadString('facebook', 'accesstoken', edt_FaceBook_AccessToken.Text);

    // load data for example "dropbox"
    edt_DropBox_ClientID.Text := LINIFile.ReadString('dropbox', 'clientid', edt_DropBox_ClientID.Text);
    edt_DropBox_ClientSecret.Text := LINIFile.ReadString('dropbox', 'clientsecret', edt_DropBox_ClientSecret.Text);
    edt_DropBox_AccessToken.Text := LINIFile.ReadString('dropbox', 'accesstoken', edt_DropBox_AccessToken.Text);
  finally
    FreeAndNil(LINIFile);
  end;
end;

procedure Tfrm_Main.SaveConnectionData(const AFilename: string);
var
  LINIFile: TMemIniFile;
begin
  LINIFile := TMemIniFile.Create(AFilename);
  try
    // save data for example "googletasks"
    LINIFile.WriteString('googletasks', 'clientid', edt_GoogleTasks_ClientID.Text);
    LINIFile.WriteString('googletasks', 'clientsecret', edt_GoogleTasks_ClientSecret.Text);
    LINIFile.WriteString('googletasks', 'accesstoken', edt_GoogleTasks_AccessToken.Text);
    LINIFile.WriteString('googletasks', 'refreshtoken', edt_GoogleTasks_RefreshToken.Text);

    // save data for example "facebook"
    LINIFile.WriteString('facebook', 'clientid', edt_Facebook_AppID.Text);
    LINIFile.WriteString('facebook', 'clientsecret', edt_Facebook_AppSecret.Text);
    LINIFile.WriteString('facebook', 'accesstoken', edt_FaceBook_AccessToken.Text);

    // save data for example "dropbox"
    LINIFile.WriteString('dropbox', 'clientid', edt_DropBox_ClientID.Text);
    LINIFile.WriteString('dropbox', 'clientsecret', edt_DropBox_ClientSecret.Text);
    LINIFile.WriteString('dropbox', 'accesstoken', edt_DropBox_AccessToken.Text);

    LINIFile.UpdateFile;
  finally
    FreeAndNil(LINIFile);
  end;
end;

procedure Tfrm_Main.ResetRESTComponentsToDefaults;
begin
  // reset all of the rest-components for a complete
  // new request
  //
  // --> we do not clear the private data from the
  // individual authenticators.
  //
  RESTRequest.ResetToDefaults;
  RESTClient.ResetToDefaults;
  RESTResponse.ResetToDefaults;
  RESTResponseDataSetAdapter.ResetToDefaults;
end;

procedure Tfrm_Main.RESTRequestAfterExecute(Sender: TCustomRESTRequest);
begin
  ClearMemos;
  lbl_status.Caption := 'URI: ' + Sender.GetFullRequestURL + ' Execution time: ' +
    IntToStr(Sender.ExecutionPerformance.TotalExecutionTime) + 'ms';
  if assigned(RESTResponse.JSONValue) then
    memo_ResponseData.Lines.Text := RESTResponse.JSONValue.Format()
  else
    memo_ResponseData.Lines.Add(RESTResponse.Content);
end;

procedure Tfrm_Main.RESTRequestHTTPProtocolError(Sender: TCustomRESTRequest);
begin
  // show error
  memo_ResponseData.Lines.Add(Sender.Response.StatusText);
  memo_ResponseData.Lines.Add(Sender.Response.Content);
end;

end.

