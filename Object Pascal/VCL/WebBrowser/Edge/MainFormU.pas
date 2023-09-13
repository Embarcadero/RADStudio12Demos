unit MainFormU;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, System.UITypes, System.Types,
  Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.Menus, Vcl.ComCtrls, Vcl.ToolWin, Vcl.ExtCtrls,
  Vcl.Edge, Winapi.ActiveX, Winapi.WebView2;

type
  TfrmMain = class(TForm)
    tbToolbar: TToolBar;
    tbBack: TToolButton;
    tbForward: TToolButton;
    tbReload: TToolButton;
    tbCancel: TToolButton;
    edtAddress: TEdit;
    tbGo: TToolButton;
    dlgSaveScreenshot: TSaveDialog;
    dlgLocateWebView2Executable: TOpenDialog;
    dlgPrintToPDF: TSaveDialog;
    MainMenu: TMainMenu;
    mniFile: TMenuItem;
    mniFileSaveScreenShot: TMenuItem;
    mniFileGetDocumentTitle: TMenuItem;
    mniFilePrintBrowserUI: TMenuItem;
    mniFilePrintSystemUI: TMenuItem;
    mniFilePrintToPDF: TMenuItem;
    mniFileProxyServer: TMenuItem;
    mniScript: TMenuItem;
    mniScriptSubscribeToCDPEvent: TMenuItem;
    mniScriptInjectScript: TMenuItem;
    mniScriptOpenDevToolsWindow: TMenuItem;
    mniScriptOpenTaskManagerWindow: TMenuItem;
    mniWindow: TMenuItem;
    mniWindowCloseWebView: TMenuItem;
    mniWindowCreateWebView: TMenuItem;
    mniWindowCreateWebViewFixedVersion: TMenuItem;
    mniWindowCreateNewWindow: TMenuItem;
    mniWindowCloseWindow: TMenuItem;
    mniProcess: TMenuItem;
    mniProcessBrowserInfo: TMenuItem;
    mniProcessCrashBrowser: TMenuItem;
    mniSettings: TMenuItem;
    mniSettingsToggleStatusBar: TMenuItem;
    mniSettingsToggleFullscreen: TMenuItem;
    mniSettingsToggleDevTools: TMenuItem;
    mniSettingsToggleBlockImages: TMenuItem;
    mniSettingsJavaScriptDialogs: TMenuItem;
    mniSettingsJavaScriptDialogsDefault: TMenuItem;
    mniSettingsJavaScriptDialogsCustom: TMenuItem;
    mniView: TMenuItem;
    mniViewWebViewZoom: TMenuItem;
    mniViewWebViewZoom50Percent: TMenuItem;
    mniViewWebViewZoom100Percent: TMenuItem;
    mniViewWebViewZoom200Percent: TMenuItem;
    mniViewGetBounds: TMenuItem;
    mniViewWebViewArea: TMenuItem;
    mniViewWebViewArea25Percent: TMenuItem;
    mniViewWebViewArea50Percent: TMenuItem;
    mniViewWebViewArea75Percent: TMenuItem;
    mniViewWebViewArea100Percent: TMenuItem;
    mniViewSetFocus: TMenuItem;
    mniViewTabIn: TMenuItem;
    mniViewReverseTabIn: TMenuItem;
    mniScenario: TMenuItem;
    mniScenarioCustomDownload: TMenuItem;
    mniScenarioCustomDownloadDeferred: TMenuItem;
    mniScenarioDomContentLoaded: TMenuItem;
    mniScenarioNavigateWithWebResourceRequest: TMenuItem;
    EdgeBrowser: TEdgeBrowser;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure tbBackClick(Sender: TObject);
    procedure tbForwardClick(Sender: TObject);
    procedure tbReloadClick(Sender: TObject);
    procedure tbCancelClick(Sender: TObject);
    procedure edtAddressKeyPress(Sender: TObject; var Key: Char);
    procedure tbGoClick(Sender: TObject);
    procedure mniFileSaveScreenShotClick(Sender: TObject);
    procedure mniFileGetDocumentTitleClick(Sender: TObject);
    procedure mniFileGetBrowserVersionClick(Sender: TObject);
    procedure mniFilePrintBrowserUIClick(Sender: TObject);
    procedure mniFilePrintSystemUIClick(Sender: TObject);
    procedure mniFilePrintToPDFClick(Sender: TObject);
    procedure mniFileProxyServerClick(Sender: TObject);
    procedure mniScriptSubscribeToCDPEventClick(Sender: TObject);
    procedure mniScriptInjectScriptClick(Sender: TObject);
    procedure mniScriptOpenDevToolsWindowClick(Sender: TObject);
    procedure mniScriptOpenTaskManagerWindowClick(Sender: TObject);
    procedure mniWindowCloseWebViewClick(Sender: TObject);
    procedure mniWindowCreateWebViewClick(Sender: TObject);
    procedure mniWindowCreateNewWindowClick(Sender: TObject);
    procedure mniWindowCloseWindowClick(Sender: TObject);
    procedure mniWindowCreateWebViewFixedVersionClick(Sender: TObject);
    procedure mniProcessBrowserInfoClick(Sender: TObject);
    procedure mniProcessCrashBrowserClick(Sender: TObject);
    procedure mniSettingsToggleFullscreenClick(Sender: TObject);
    procedure mniSettingsToggleStatusBarClick(Sender: TObject);
    procedure mniSettingsToggleDevToolsClick(Sender: TObject);
    procedure mniSettingsToggleBlockImagesClick(Sender: TObject);
    procedure mniSettingsJavaScriptDialogsDefaultClick(Sender: TObject);
    procedure mniSettingsJavaScriptDialogsCustomClick(Sender: TObject);
    procedure mniViewWebViewZoom50PercentClick(Sender: TObject);
    procedure mniViewWebViewZoom100PercentClick(Sender: TObject);
    procedure mniViewWebViewZoom200PercentClick(Sender: TObject);
    procedure mniViewToggleVisibilityClick(Sender: TObject);
    procedure mniViewGetBoundsClick(Sender: TObject);
    procedure mniViewWebViewArea25PercentClick(Sender: TObject);
    procedure mniViewWebViewArea50PercentClick(Sender: TObject);
    procedure mniViewWebViewArea75PercentClick(Sender: TObject);
    procedure mniViewWebViewArea100PercentClick(Sender: TObject);
    procedure mniViewSetFocusClick(Sender: TObject);
    procedure mniViewTabInClick(Sender: TObject);
    procedure mniViewReverseTabInClick(Sender: TObject);
    procedure mniScenarioCustomDownloadDeferredClick(Sender: TObject);
    procedure mniScenarioDomContentLoadedClick(Sender: TObject);
    procedure mniScenarioNavigateWithWebResourceRequestClick(Sender: TObject);
    procedure EdgeBrowserCapturePreviewCompleted(Sender: TCustomEdgeBrowser; AResult: HResult);
    procedure EdgeBrowserContainsFullScreenElementChanged(Sender: TCustomEdgeBrowser;
      ContainsFullScreenElement: Boolean);
    procedure EdgeBrowserContentLoading(Sender: TCustomEdgeBrowser; IsErrorPage: Boolean; NavigationId: TUInt64);
    procedure EdgeBrowserCreateWebViewCompleted(Sender: TCustomEdgeBrowser; AResult: HResult);
    procedure EdgeBrowserDevToolsProtocolEventReceived(Sender: TCustomEdgeBrowser; const CDPEventName,
      AParameterObjectAsJson: string);
    procedure EdgeBrowserDocumentTitleChanged(Sender: TCustomEdgeBrowser; const ADocumentTitle: string);
    procedure EdgeBrowserDownloadStarting(Sender: TCustomEdgeBrowser; Args: TDownloadStartingEventArgs);
    procedure EdgeBrowserExecuteScript(Sender: TCustomEdgeBrowser; AResult: HResult; const AResultObjectAsJson: string);
    procedure EdgeBrowserFrameNavigationStarting(Sender: TCustomEdgeBrowser; Args: TNavigationStartingEventArgs);
    procedure EdgeBrowserHistoryChanged(Sender: TCustomEdgeBrowser);
    procedure EdgeBrowserNavigationStarting(Sender: TCustomEdgeBrowser; Args: TNavigationStartingEventArgs);
    procedure EdgeBrowserNavigationCompleted(Sender: TCustomEdgeBrowser; IsSuccess: Boolean;
      WebErrorStatus: COREWEBVIEW2_WEB_ERROR_STATUS);
    procedure EdgeBrowserNewWindowRequested(Sender: TCustomEdgeBrowser; Args: TNewWindowRequestedEventArgs);
    procedure EdgeBrowserPermissionRequested(Sender: TCustomEdgeBrowser; Args: TPermissionRequestedEventArgs);
    procedure EdgeBrowserProcessFailed(Sender: TCustomEdgeBrowser; FailureType: COREWEBVIEW2_PROCESS_FAILED_KIND);
    procedure EdgeBrowserScriptDialogOpening(Sender: TCustomEdgeBrowser; Args: TScriptDialogOpeningEventArgs);
    procedure EdgeBrowserSourceChanged(Sender: TCustomEdgeBrowser; IsNewDocument: Boolean);
    procedure EdgeBrowserWebMessageReceived(Sender: TCustomEdgeBrowser; Args: TWebMessageReceivedEventArgs);
    procedure EdgeBrowserWebResourceRequested(Sender: TCustomEdgeBrowser; Args: TWebResourceRequestedEventArgs);
    procedure EdgeBrowserWindowCloseRequested(Sender: TObject);
    procedure EdgeBrowserZoomFactorChanged(Sender: TCustomEdgeBrowser; AZoomFactor: Double);
    procedure EdgeBrowserFrameNavigationCompleted(Sender: TCustomEdgeBrowser; IsSuccess: Boolean;
      WebErrorStatus: COREWEBVIEW2_WEB_ERROR_STATUS);
  private
    { Private declarations }
    FAllowFullScreen: Boolean;
    FBlockImages: Boolean;
    FPostDataMemStream: TMemoryStream;
    FPostDataIStream: IStream;
    FWebResourceRequest: ICoreWebView2WebResourceRequest;
    FContentLoadingToken,
    FBytesReceivedChangedToken,
    FStateChangedToken,
    FDomContentLoadedToken: EventRegistrationToken;
    function ShouldBlockUri(const Uri: string): Boolean;
    procedure ActivateHintNOW(const Txt: string; Pt: TPoint);
    procedure UpdateDownloadProgress(const Download: ICoreWebView2DownloadOperation);
    procedure CompleteDownload(const Download: ICoreWebView2DownloadOperation);
  public
    { Public declarations }
  end;

var
  frmMain: TfrmMain;

implementation

uses
  IdURI, System.Math, System.StrUtils, System.Win.ComObj, System.IOUtils, System.NetEncoding, Winapi.EdgeUtils;

{$R *.dfm}

const
  SEnDisabled: array[Boolean] of string = ('disabled', 'enabled');

var
  HintWnd: THintWindow;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  FAllowFullScreen := True;
  FBlockImages := False;
  HintWnd := THintWindow.Create(Self);
  // This gets assigned in the deferred download scenario
  EdgeBrowser.OnDownloadStarting := nil;
  // Set a custom user data (cache) folder
  EdgeBrowser.UserDataFolder := TPath.Combine(TPath.GetDirectoryName(Application.ExeName), 'CustomCache');
  // Note: if you wish you can call EdgeBrowser.CreateWebView here
  // and initiate navigation with Sender.Navigate('http://bing.com') in the
  // OnCreateWebViewCompleted handler, TfrmMain.EdgeBrowserCreateWebViewCompleted

  //EdgeBrowser.AdditionalBrowserArguments := '--proxy-server=http://1.2.3.4:8888 --browser-startup-dialog';

  EdgeBrowser.Navigate('http://bing.com');
end;

procedure TfrmMain.FormDestroy(Sender: TObject);
begin
  EdgeBrowser.CloseWebView;
end;

procedure TfrmMain.FormResize(Sender: TObject);
begin
  edtAddress.Width := tbToolBar.ClientWidth - edtAddress.Left - tbGo.Width;
end;

procedure TfrmMain.mniFileSaveScreenShotClick(Sender: TObject);
begin
  if dlgSaveScreenshot.Execute then
    EdgeBrowser.CapturePreview(dlgSaveScreenshot.FileName)
end;

procedure TfrmMain.mniFileGetDocumentTitleClick(Sender: TObject);
begin
  Application.MessageBox(PChar(EdgeBrowser.DocumentTitle), 'Document Title', MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniFileGetBrowserVersionClick(Sender: TObject);
const
  SAfterBefore: array[Boolean] of string = ('Before', 'After');
begin
  var Msg := 'Browser Version Info ' + SAfterBefore[EdgeBrowser.WebViewCreated] + ' WebView Creation';
  Application.MessageBox(PChar(EdgeBrowser.BrowserVersionInfo), PChar(Msg), MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniFilePrintBrowserUIClick(Sender: TObject);
begin
  EdgeBrowser.ShowPrintUI(TEdgeBrowser.TPrintUIDialogKind.Browser);
end;

procedure TfrmMain.mniFilePrintSystemUIClick(Sender: TObject);
begin
  EdgeBrowser.ShowPrintUI(TEdgeBrowser.TPrintUIDialogKind.System);
end;

procedure TfrmMain.mniFilePrintToPDFClick(Sender: TObject);
const
  BOOL_TRUE = 1;
begin
  if dlgPrintToPDF.Execute then
  begin
    var PrintSettings := EdgeBrowser.CreatePrintSettings;
    PrintSettings.Set_ShouldPrintBackgrounds(BOOL_TRUE);
    EdgeBrowser.PrintToPDF(dlgPrintToPDF.FileName, PrintSettings)
  end;
end;

procedure TfrmMain.mniFileProxyServerClick(Sender: TObject);
var
  ProxyServer: string;
begin
  if InputQuery('Proxy Server', 'Enter proxy server:', ProxyServer) then
  begin
    // The correct format matches http://1.2.3.4:8888
    EdgeBrowser.AdditionalBrowserArguments := Format('--proxy-server=%s', [ProxyServer]);
    if EdgeBrowser.WebViewCreated then
    begin
      var CurrentURL := EdgeBrowser.LocationURL;
      EdgeBrowser.CloseWebView;
      EdgeBrowser.Navigate(CurrentURL);
    end;
  end;
end;

procedure TfrmMain.mniProcessBrowserInfoClick(Sender: TObject);
begin
  var ProcessID := EdgeBrowser.BrowserProcessID;
  var Msg := Format('Process ID: %u', [ProcessID]);
  Application.MessageBox(PChar(Msg), 'Process Info', MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniProcessCrashBrowserClick(Sender: TObject);
begin
  EdgeBrowser.Navigate('edge://inducebrowsercrashforrealz')
end;

procedure TfrmMain.mniScriptInjectScriptClick(Sender: TObject);
begin
  var Script: string := 'window.getComputedStyle(document.body).backgroundColor';
  if InputQuery('Inject Script',
      'Enter script code:'#10 +
      'Enter the JavaScript code to run in the WebView.', Script) then
    EdgeBrowser.ExecuteScript(Script)
end;

procedure TfrmMain.mniScriptOpenDevToolsWindowClick(Sender: TObject);
begin
  // Call ICoreWebView2.OpenDevToolsWindow
  // https://docs.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/icorewebview2?view=webview2-1.0.1210.39#opendevtoolswindow

  // EdgeBrowser.DefaultInterface gives us ICoreWebView2, of which OpenDevToolsWindow is a member
  EdgeBrowser.DefaultInterface.OpenDevToolsWindow
end;

procedure TfrmMain.mniScriptOpenTaskManagerWindowClick(Sender: TObject);
var
  WebView2_6: ICoreWebView2_6;
begin
  // Call ICoreWebView2_6.OpenTaskManagerWindow
  // https://docs.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/icorewebview2_6?view=webview2-1.0.1210.39#opentaskmanagerwindow

  // EdgeBrowser.DefaultInterface gives us ICoreWebView2, but OpenTaskManagerWindow is a member of ICoreWebView2_6
  if Supports(EdgeBrowser.DefaultInterface, ICoreWebView2_6, WebView2_6) then
    WebView2_6.OpenTaskManagerWindow
end;

procedure TfrmMain.mniScriptSubscribeToCDPEventClick(Sender: TObject);
begin
  var EventName := 'Log.entryAdded';
  if InputQuery('Subscribe to CDP Event',
      'CDP event name:'#10 +
      'Enter the name of the CDP event to subscribe to.'#10 +
      'You may also have to call the "enable" method of the'#10 +
      'event''s domain to receive events (for example "Log.enable").', EventName) then
    EdgeBrowser.SubscribeToCDPEvent(EventName)
end;

procedure TfrmMain.mniSettingsJavaScriptDialogsCustomClick(Sender: TObject);
begin
  var Settings := EdgeBrowser.SettingsInterface;
  if Settings <> nil then
  begin
    var DefaultCurrentlyEnabled: Integer;
    if Succeeded(Settings.Get_AreDefaultScriptDialogsEnabled(DefaultCurrentlyEnabled)) and
       LongBool(DefaultCurrentlyEnabled) then
    begin
      if Succeeded(Settings.Set_AreDefaultScriptDialogsEnabled(Integer(LongBool(False)))) then
        Application.MessageBox(
          'Custom script dialogs without deferral will be used after the next navigation.',
          'Settings change', MB_OK or MB_ICONINFORMATION);
    end;
  end;
end;

procedure TfrmMain.mniSettingsJavaScriptDialogsDefaultClick(Sender: TObject);
begin
  var Settings := EdgeBrowser.SettingsInterface;
  if Settings <> nil then
  begin
    var DefaultCurrentlyEnabled: Integer;
    if Succeeded(Settings.Get_AreDefaultScriptDialogsEnabled(DefaultCurrentlyEnabled)) and
       not LongBool(DefaultCurrentlyEnabled) then
    begin
      if Succeeded(Settings.Set_AreDefaultScriptDialogsEnabled(Integer(LongBool(True)))) then
        Application.MessageBox(
          'Default script dialogs will be used after the next navigation.',
          'Settings change', MB_OK or MB_ICONINFORMATION);
    end;
  end;
end;

procedure TfrmMain.mniSettingsToggleBlockImagesClick(Sender: TObject);
begin
  FBlockImages := not FBlockImages;
  Application.MessageBox(PChar(Format('Image blocking has been %s.', [SEnDisabled[FBlockImages]])),
    'Settings change', MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniSettingsToggleDevToolsClick(Sender: TObject);
begin
  var Settings := EdgeBrowser.SettingsInterface;
  if Settings <> nil then
  begin
    var AreDevToolsEnabled: Integer;
    if Succeeded(Settings.Get_AreDevToolsEnabled(AreDevToolsEnabled)) then
    begin
      var Toggled := Integer(LongBool(not LongBool(AreDevToolsEnabled)));
      if Succeeded(Settings.Set_AreDevToolsEnabled(Toggled)) then
        Application.MessageBox(PChar(Format('Dev tools will be %s after the next navigation.',
            [SEnDisabled[LongBool(Toggled)]])),
          'Settings change', MB_OK or MB_ICONINFORMATION);
    end;
  end;
end;

procedure TfrmMain.mniSettingsToggleFullscreenClick(Sender: TObject);
const
  SAllowedDisallowed: array[Boolean] of string = ('disallowed', 'allowed');
begin
  FAllowFullScreen := not FAllowFullScreen;
  Application.MessageBox(
    PChar(Format('Full screen is now %s.', [SAllowedDisallowed[FAllowFullScreen]])),
    'Settings change', MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniSettingsToggleStatusBarClick(Sender: TObject);
begin
  EdgeBrowser.StatusBarEnabled := not EdgeBrowser.StatusBarEnabled;
  Application.MessageBox(PChar(Format('Status bar will be %s after the next navigation.',
      [SEnDisabled[EdgeBrowser.StatusBarEnabled]])),
    'Settings change', MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniViewReverseTabInClick(Sender: TObject);
begin
  SelectNext(EdgeBrowser, False, True);
end;

procedure TfrmMain.mniViewGetBoundsClick(Sender: TObject);
begin
  // A couple of ways present themselves to get the bounding dimensions of the WebView2 browser control.
  // One uses the WebView2 interface, one uses VCL control methods
{$DEFINE ONE_POSSIBLE_WAY}
{$IFDEF ONE_POSSIBLE_WAY}
  var Bounds: tagRect;
  EdgeBrowser.ControllerInterface.Get_Bounds(Bounds);
{$ELSE}
  var Bounds := EdgeBrowser.BoundsRect;
  Bounds.TopLeft := EdgeBrowser.ClientToScreen(Bounds.TopLeft);
  Bounds.BottomRight := EdgeBrowser.ClientToScreen(Bounds.BottomRight);
{$ENDIF}
  Application.MessageBox(PChar(Format('Left:'#9'%d'#10'Top:'#9'%d'#10'Right:'#9'%d'#10'Bottom:'#9'%d'#10,
    [Bounds.Left, Bounds.Top, Bounds.Right, Bounds.Bottom])), 'WebView Bounds', MB_OK or MB_ICONINFORMATION);
end;

procedure TfrmMain.mniViewSetFocusClick(Sender: TObject);
begin
  EdgeBrowser.SetFocus
end;

procedure TfrmMain.mniViewToggleVisibilityClick(Sender: TObject);
begin
  EdgeBrowser.Visible := not EdgeBrowser.Visible
end;

procedure TfrmMain.mniViewWebViewArea25PercentClick(Sender: TObject);
begin
  EdgeBrowser.SizeRatio := 0.5
end;

procedure TfrmMain.mniViewWebViewArea50PercentClick(Sender: TObject);
begin
  EdgeBrowser.SizeRatio := 0.7071
end;

procedure TfrmMain.mniViewWebViewArea75PercentClick(Sender: TObject);
begin
  EdgeBrowser.SizeRatio := 0.866
end;

procedure TfrmMain.mniViewWebViewArea100PercentClick(Sender: TObject);
begin
  EdgeBrowser.SizeRatio := 1.0
end;

procedure TfrmMain.mniViewWebViewZoom50PercentClick(Sender: TObject);
begin
  EdgeBrowser.ZoomFactor := 0.5
end;

procedure TfrmMain.mniWindowCloseWebViewClick(Sender: TObject);
begin
  if EdgeBrowser.WebViewCreated then
    EdgeBrowser.CloseWebView
end;

procedure TfrmMain.mniWindowCreateNewWindowClick(Sender: TObject);
begin
  var Form := TfrmMain.Create(Application);
  // Bypass the default behaviour of any form being kept above the main form like a tool window.
  // However by so doing we lose the form if it gets minimised, so stop that possibility.
  SetWindowLongPtr(Form.Handle, GWLP_HWNDPARENT, Application.Handle);
  Form.BorderIcons := Form.BorderIcons - [biMinimize];
  Form.Show
end;

procedure TfrmMain.mniWindowCreateWebViewClick(Sender: TObject);
begin
  mniWindowCloseWebView.Click;
  EdgeBrowser.CreateWebView
end;

procedure TfrmMain.mniWindowCreateWebViewFixedVersionClick(Sender: TObject);
begin
  mniWindowCloseWebView.Click;
  if dlgLocateWebView2Executable.Execute then
    EdgeBrowser.BrowserExecutableFolder := TPath.GetDirectoryName(dlgLocateWebView2Executable.FileName);
  EdgeBrowser.CreateWebView
end;

procedure TfrmMain.mniWindowCloseWindowClick(Sender: TObject);
begin
  Close
end;

procedure TfrmMain.mniViewWebViewZoom100PercentClick(Sender: TObject);
begin
  EdgeBrowser.ZoomFactor := 1.0
end;

procedure TfrmMain.mniViewWebViewZoom200PercentClick(Sender: TObject);
begin
  EdgeBrowser.ZoomFactor := 2.0
end;

procedure TfrmMain.mniScenarioCustomDownloadDeferredClick(Sender: TObject);
const
  DemoURI = 'https://demo.smartscreen.msft.net/';
begin
  EdgeBrowser.OnDownloadStarting := EdgeBrowserDownloadStarting;

  // Turn off this scenario if we navigate away from the demo page.
  EdgeBrowser.DefaultInterface.add_ContentLoading(
    Callback<ICoreWebView2, ICoreWebView2ContentLoadingEventArgs>.CreateAs<ICoreWebView2ContentLoadingEventHandler>(
      function(const Sender: ICoreWebView2; const Args: ICoreWebView2ContentLoadingEventArgs): HResult stdcall
      var
        URI: PChar;
      begin
      {$IFDEF DEBUG}
        OutputDebugString('ICoreWebView2ContentLoadingEventHandler');
      {$ENDIF}

        Result := S_OK;
        Sender.Get_Source(URI);
        if URI <> DemoURI then
        begin
          EdgeBrowser.OnDownloadStarting := nil;
          EdgeBrowser.DefaultInterface.remove_ContentLoading(FContentLoadingToken);
        end;
      end
    ),
    FContentLoadingToken);
    // On this demo page scroll down and click on the green 'Known Good Program' section
    EdgeBrowser.Navigate(DemoURI);
end;

procedure TfrmMain.UpdateDownloadProgress(const Download: ICoreWebView2DownloadOperation);
begin
  Download.add_BytesReceivedChanged(
    Callback<ICoreWebView2DownloadOperation, IUnknown>.CreateAs<ICoreWebView2BytesReceivedChangedEventHandler>(
      function(const Download: ICoreWebView2DownloadOperation; const args: IUnknown): HResult stdcall
      var
        BytesReceived, TotalBytes: Int64;
      begin
      {$IFDEF DEBUG}
        OutputDebugString('ICoreWebView2DownloadOperation BytesReceivedChanged');
      {$ENDIF}

        Result := S_OK;
        // Here developer can update UI to show progress of a download using
        // Download.get_BytesReceived and Download.get_TotalBytesToReceive.
        // Note: the demo site Known Good Program is too small to trigger this event.
        // Try a link to a bigger download to see it in action
        Download.get_BytesReceived(BytesReceived);
        Download.get_TotalBytesToReceive(TotalBytes);
        Caption := Format('%d of %d received (%.2f%%)', [BytesReceived, TotalBytes, BytesReceived * 100 / TotalBytes]);
      end
    ),
    FBytesReceivedChangedToken);

  Download.add_StateChanged(
    Callback<ICoreWebView2DownloadOperation, IUnknown>.CreateAs<ICoreWebView2StateChangedEventHandler>(
      function(const Download: ICoreWebView2DownloadOperation; const args: IUnknown): HResult stdcall
      var
        DownloadState: COREWEBVIEW2_DOWNLOAD_STATE;
      begin
      {$IFDEF DEBUG}
        OutputDebugString('ICoreWebView2DownloadOperation StateChanged');
      {$ENDIF}

        Result := S_OK;
        Download.Get_State(DownloadState);
        case DownloadState of
          COREWEBVIEW2_DOWNLOAD_STATE_IN_PROGRESS: { nothing to do here };
          COREWEBVIEW2_DOWNLOAD_STATE_INTERRUPTED:
          begin
            // Here developers can take different actions based on Download.InterruptReason.
            // For example, show an error message to the end user.
            CompleteDownload(Download);
          end;
          COREWEBVIEW2_DOWNLOAD_STATE_COMPLETED:
            CompleteDownload(Download);
        end;
      end
    ),
    FStateChangedToken)
end;

procedure TfrmMain.CompleteDownload(const Download: ICoreWebView2DownloadOperation);
begin
  // Close download progress dialog here.

  // Unsubscribe from download events.
  Download.remove_BytesReceivedChanged(FBytesReceivedChangedToken);
  Download.remove_StateChanged(FStateChangedToken);
end;

procedure TfrmMain.mniScenarioDomContentLoadedClick(Sender: TObject);
var
  WebView2_2: ICoreWebView2_2;
begin
  if not Supports(EdgeBrowser.DefaultInterface, ICoreWebView2_2, WebView2_2) then
    Exit;
  WebView2_2.add_DOMContentLoaded(
    Callback<ICoreWebView2, ICoreWebView2DOMContentLoadedEventArgs>.CreateAs<ICoreWebView2DOMContentLoadedEventHandler>(
      function(const sender: ICoreWebView2; const args: ICoreWebView2DOMContentLoadedEventArgs): HResult stdcall
      begin
      {$IFDEF DEBUG}
        OutputDebugString('ICoreWebView2DOMContentLoaded');
      {$ENDIF}
        sender.ExecuteScript(
          'let content = document.createElement("h2");'#10 +
          'content.style.color = "blue";'#10 +
          'content.textContent = "This text was added by the host app";'#10 +
          'document.body.appendChild(content);',
          Callback<HResult, PChar>.CreateAs<ICoreWebView2ExecuteScriptCompletedHandler>(
            function(errorCode: HResult; id: PChar): HResult stdcall
            begin
            {$IFDEF DEBUG}
              OutputDebugString('ICoreWebView2ExecuteScriptCompleted');
            {$ENDIF}
              Result := S_OK;
            end));
        Result := S_OK;
        WebView2_2.remove_DOMContentLoaded(FDomContentLoadedToken);
      end
    ),
    FDomContentLoadedToken);
  EdgeBrowser.NavigateToString(
    '<!DOCTYPE html>'#10 +
    '<html>'#10 +
    '<head>'#10 +
        '<title>ScenarioDOMContentLoaded</title>'#10 +
    '</head>'#10 +
    '<body>'#10 +
        '<h1>DOMContentLoaded sample page</h1>'#10 +
    '</body>'#10 +
    '</html>');
end;

procedure TfrmMain.mniScenarioNavigateWithWebResourceRequestClick(Sender: TObject);
begin
  // Prepare post data as UTF-8 byte array and convert it to stream
  // as required by the application/x-www-form-urlencoded Content-Type
  var Input := 'Here is input from a Delphi sample app!';
  if InputQuery('Post data', 'Specify post data to submit to https://www.w3schools.com/action_page.php:', Input) then
  begin
    Input := 'input=' + TNetEncoding.URL.Encode(Input);
    if FPostDataMemStream = nil then
      FPostDataMemStream := TMemoryStream.Create;
    var LBytes := TEncoding.UTF8.GetBytes(Input);
    FPostDataMemStream.WriteData(LBytes, Length(LBytes));
    FPostDataIStream := TStreamAdapter.Create(FPostDataMemStream) as IStream;
    var WebViewEnvironment2: ICoreWebView2Environment2;
    // This acts as a form submit to https://www.w3schools.com/action_page.php
    if Supports(EdgeBrowser.EnvironmentInterface, ICoreWebView2Environment2, WebViewEnvironment2) and
       Succeeded(WebViewEnvironment2.CreateWebResourceRequest('https://www.w3schools.com/action_page.php', 'POST',
       FPostDataIStream, 'Content-Type: application/x-www-form-urlencoded', FWebResourceRequest)) then
      EdgeBrowser.NavigateWithWebResourceRequest(FWebResourceRequest)
    else
      Application.MessageBox('Web resource not created successfully', 'Web resource navigation', MB_OK or MB_ICONINFORMATION);
  end;
end;

procedure TfrmMain.tbBackClick(Sender: TObject);
begin
  EdgeBrowser.GoBack
end;

procedure TfrmMain.tbForwardClick(Sender: TObject);
begin
  EdgeBrowser.GoForward
end;

procedure TfrmMain.tbCancelClick(Sender: TObject);
begin
  EdgeBrowser.Stop
end;

procedure TfrmMain.tbReloadClick(Sender: TObject);
begin
  EdgeBrowser.Refresh
end;

procedure TfrmMain.edtAddressKeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #13 then
  begin
    Key := #0;
    tbGo.Click
  end;
end;

procedure TfrmMain.tbGoClick(Sender: TObject);
begin
  var URL := edtAddress.Text;
  // Ensure we have the protocol prefix
  if not StartsText('http', URL) then
    URL := 'http://' + URL;
  EdgeBrowser.Navigate(URL)
end;

procedure TfrmMain.mniViewTabInClick(Sender: TObject);
begin
  SelectNext(EdgeBrowser, True, True);
end;

procedure TfrmMain.EdgeBrowserCapturePreviewCompleted(Sender: TCustomEdgeBrowser; AResult: HResult);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnCapturePreviewCompleted');
{$ENDIF}
  if Succeeded(AResult) then
    Application.MessageBox('Preview captured successfully', 'Preview Capture', MB_OK or MB_ICONINFORMATION)
  else
    Application.MessageBox('Preview not captured successfully', 'Preview Capture', MB_OK or MB_ICONINFORMATION)
end;

procedure TfrmMain.EdgeBrowserContainsFullScreenElementChanged(Sender: TCustomEdgeBrowser;
  ContainsFullScreenElement: Boolean);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnContainsFullScreenElementChanged');
{$ENDIF}
  // Go to a web page that offers full-screen, e.g.
  // https://whatwebcando.today/fullscreen.html
  if FAllowFullScreen and ContainsFullScreenElement then
  begin
    BorderStyle := bsNone;
    WindowState := wsMaximized;
  end
  else
  begin
    WindowState := wsNormal;
    BorderStyle := bsSizeable;
  end;
end;

procedure TfrmMain.ActivateHintNOW(const Txt: string; Pt: TPoint);
begin
  if Txt <> '' then
  begin
    var Rect := HintWnd.CalcHintRect(Screen.Width, Txt, nil);
    Rect.Left := Rect.Left + Pt.X;
    Rect.Right := Rect.Right + Pt.X;
    Rect.Top := Rect.Top + Pt.Y;
    Rect.Bottom := Rect.Bottom + Pt.Y;
    HintWnd.ActivateHint(rect, Txt);
  end;
end;

procedure TfrmMain.EdgeBrowserContentLoading(Sender: TCustomEdgeBrowser; IsErrorPage: Boolean; NavigationId: TUInt64);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnContentLoading');
{$ENDIF}
  // Show a tooltip over the caption bar, just as a simple way of displaying the Navigation ID
  // Note: in this demo nothing takes that tooltip away...
  ActivateHintNOW(Format('Navigation ID: %d', [NavigationId]),
    ClientToScreen(Point(Width div 2,
      -GetSystemMetrics(SM_CYCAPTION) -GetSystemMetrics(SM_CYCAPTION))))
end;

procedure TfrmMain.EdgeBrowserCreateWebViewCompleted(Sender: TCustomEdgeBrowser; AResult: HResult);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnCreateWebViewCompleted');
{$ENDIF}
  if Succeeded(AResult) then
  begin
    tbCancel.Enabled := True;
    tbReload.Enabled := True;
    tbGo.Enabled := True;
    edtAddress.Enabled := True;
    Sender.AddWebResourceRequestedFilter('*', COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE);
  end
  else
  begin
    if AResult = HResultFromWin32(ERROR_FILE_NOT_FOUND) then
      Application.MessageBox('Could not find Edge installation. ' +
        'Do you have a version installed that''s compatible with this WebView2 SDK version?',
        'Edge initialisation error', MB_OK or MB_ICONERROR)
    else if AResult = E_FAIL then
      Application.MessageBox('Failed to initialise Edge loader', 'Edge initialisation error', MB_OK or MB_ICONERROR)
    else
      try
        OleCheck(AResult)
      except
        on E: Exception do
          Application.MessageBox(PChar(Format('Failed to initialise Edge: %s', [E.Message])),
            'Edge initialisation error', MB_OK or MB_ICONERROR)
      end;
  end;
end;

procedure TfrmMain.EdgeBrowserDevToolsProtocolEventReceived(Sender: TCustomEdgeBrowser; const CDPEventName,
  AParameterObjectAsJson: string);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnDevToolsProtocolEventReceived');
{$ENDIF}
  Application.MessageBox(PChar(AParameterObjectAsJson), PChar('CDP Event Fired: ' + CDPEventName), MB_OK);
end;

procedure TfrmMain.EdgeBrowserDocumentTitleChanged(Sender: TCustomEdgeBrowser; const ADocumentTitle: string);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnDocumentTitleChanged');
{$ENDIF}
  Caption := ADocumentTitle
end;

procedure TfrmMain.EdgeBrowserDownloadStarting(Sender: TCustomEdgeBrowser; Args: TDownloadStartingEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowserDownloadStarting');
{$ENDIF}

  // Obtain a deferral for the event so that the CoreWebView2
  // doesn't examine the properties we set on the event args until
  // after we call the Complete method asynchronously later.
  var Deferral: ICoreWebView2Deferral;
  if SUCCEEDED(Args.ArgsInterface.GetDeferral(Deferral)) then
  begin
    // We avoid potential reentrancy from running a message loop in the download
    // starting event handler by showing our download dialog later when we
    // complete the deferral asynchronously.
    // Note that a long running synchronous UI prompt or other blocking item on
    // the UI thread can potentially block the WebView2 from doing anything.
    var ArgsInterface := Args.ArgsInterface;
    TThread.ForceQueue(nil,
      procedure
      var
        Download: ICoreWebView2DownloadOperation;
        TotalBytesToReceive: Int64;
        URI, MimeType, ContentDisposition, ResultFilePath: PChar;
        FilePath: string;
      begin
        if Succeeded(ArgsInterface.Set_Handled(Integer(True))) and // Hide the default download dialog.
           Succeeded(ArgsInterface.Get_DownloadOperation(Download)) and
           Succeeded(Download.Get_TotalBytesToReceive(TotalBytesToReceive)) and
           Succeeded(Download.Get_uri(URI)) and
           Succeeded(Download.Get_MimeType(MimeType)) and
           Succeeded(Download.Get_ContentDisposition(ContentDisposition)) and
           Succeeded(Download.Get_ResultFilePath(ResultFilePath)) then
        begin
          var Description := Format('URI: %s'#13#10'Mime type: %s'#13#10, [URI, MimeType]);
          if TotalBytesToReceive > 0 then
            Description := Description + Format('Total bytes to receive: %u'#13#10, [TotalBytesToReceive]);
          Description := Description +
            'Enter result file path or select `OK` to use default path. Select `Cancel` to cancel the download.';
          FilePath := ResultFilePath;
          if InputQuery('Download Starting', Description, FilePath) then
          begin
            // If user selects OK, the download will complete normally.
            // Result file path will be updated if a new one was provided.
            ArgsInterface.Set_ResultFilePath(PChar(FilePath));
            UpdateDownloadProgress(Download);
          end
          else
          begin
            // If user selects Cancel, the download will be canceled.
            ArgsInterface.Set_Cancel(Integer(True));
          end;
        end;

        // Now complete the deferral
        Deferral.Complete;
      end)
  end
end;

procedure TfrmMain.EdgeBrowserExecuteScript(Sender: TCustomEdgeBrowser; AResult: HResult;
  const AResultObjectAsJson: string);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnExecuteScript');
{$ENDIF}
  var Msg := Format('The script has completed:'#10'Result = $%X'#10'ResultObject = %s', [AResult, AResultObjectAsJson]);
  Application.MessageBox(PChar(Msg), 'Script execution', MB_OK);
end;

function TfrmMain.ShouldBlockUri(const Uri: string): Boolean;
begin
  Result := False;
  var URICracker := TIdURI.Create(Uri);
  try
    var Host := URICracker.Host.ToLower;
    // For no particular reason, block Yahoo's main English sites
    if Host.EndsWith('yahoo.com') or Host.EndsWith('yahoo.co.uk') then
      Result := True;
  finally
    URICracker.Free
  end;
end;

// This handler will prevent a frame from navigating to a blocked domain.
procedure TfrmMain.EdgeBrowserFrameNavigationCompleted(Sender: TCustomEdgeBrowser; IsSuccess: Boolean;
  WebErrorStatus: COREWEBVIEW2_WEB_ERROR_STATUS);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnFrameNavigationCompleted');
{$ENDIF}
  if not IsSuccess and (WebErrorStatus = COREWEBVIEW2_WEB_ERROR_STATUS_DISCONNECTED) then
  begin
    // Do something here if you want to handle a specific error case.
    // In most cases this isn't necessary, because the WebView will
    // display its own error page automatically.
  end;
  tbCancel.Enabled := False;
end;

procedure TfrmMain.EdgeBrowserFrameNavigationStarting(Sender: TCustomEdgeBrowser;
  Args: TNavigationStartingEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnFrameNavigationStarting');
{$ENDIF}
  var Uri: PChar;
  if Succeeded(Args.ArgsInterface.Get_uri(Uri)) and ShouldBlockUri(Uri) then
    Args.ArgsInterface.Set_Cancel(Integer(LongBool(True)));
  CoTaskMemFree(Uri);
end;

procedure TfrmMain.EdgeBrowserHistoryChanged(Sender: TCustomEdgeBrowser);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnHistoryChanged');
{$ENDIF}
  tbBack.Enabled := EdgeBrowser.CanGoBack;
  tbForward.Enabled := EdgeBrowser.CanGoForward;
end;

procedure TfrmMain.EdgeBrowserNavigationCompleted(Sender: TCustomEdgeBrowser; IsSuccess: Boolean;
  WebErrorStatus: COREWEBVIEW2_WEB_ERROR_STATUS);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnNavigationCompleted');
{$ENDIF}
  if not IsSuccess and (WebErrorStatus = COREWEBVIEW2_WEB_ERROR_STATUS_DISCONNECTED) then
  begin
    // Do something here if you want to handle a specific error case.
    // In most cases this isn't necessary, because the WebView will
    // display its own error page automatically.
  end;
  tbCancel.Enabled := False;
  FPostDataIStream := nil;
  FreeAndNil(FPostDataMemStream);
  FWebResourceRequest := nil;
end;

procedure TfrmMain.EdgeBrowserNavigationStarting(Sender: TCustomEdgeBrowser;
  Args: TNavigationStartingEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnNavigationStarting');
{$ENDIF}
  tbCancel.Enabled := True;
  var Uri: PChar;
  if Succeeded(Args.ArgsInterface.Get_uri(Uri)) and ShouldBlockUri(Uri) then
  begin
    tbCancel.Enabled := False;
    Args.ArgsInterface.Set_Cancel(Integer(LongBool(True)));
    // UserInitiated is True on clicking a link, but False on use of the address bar
    var UserInitiated: Integer;
    if Succeeded(Args.ArgsInterface.Get_IsUserInitiated(UserInitiated)) and LongBool(UserInitiated) then
      Sender.NavigateToString(
        '<h1>Domain Blocked</h1>' +
        '<p>You''ve attempted to navigate to a domain in the blocked ' +
        'sites list. Press back to return to the previous page.</p>')
    else
      Sender.NavigateToString(
        '<h1>Domain Blocked</h1>' +
        '<p>That domain is in the blocked sites list. ' +
        'Press back to return to the previous page.</p>')
  end;
  CoTaskMemFree(Uri);
end;

procedure TfrmMain.EdgeBrowserNewWindowRequested(Sender: TCustomEdgeBrowser; Args: TNewWindowRequestedEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnNewWindowRequested');
{$ENDIF}
  if MessageDlg('Allow new window', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
    Args.ArgsInterface.Set_Handled(Integer(LongBool(True)))
end;

procedure TfrmMain.EdgeBrowserPermissionRequested(Sender: TCustomEdgeBrowser;
  Args: TPermissionRequestedEventArgs);

  function NameOfPermissionType(PermissionType: COREWEBVIEW2_PERMISSION_KIND): string;
  begin
    case PermissionType of
      COREWEBVIEW2_PERMISSION_KIND_MICROPHONE: Result := 'Microphone';
      COREWEBVIEW2_PERMISSION_KIND_CAMERA: Result := 'Camera';
      COREWEBVIEW2_PERMISSION_KIND_GEOLOCATION: Result := 'Geolocation';
      COREWEBVIEW2_PERMISSION_KIND_NOTIFICATIONS: Result := 'Notifications';
      COREWEBVIEW2_PERMISSION_KIND_OTHER_SENSORS: Result := 'Generic Sensors';
      COREWEBVIEW2_PERMISSION_KIND_CLIPBOARD_READ: Result := 'Clipboard Read';
    else
      Result := 'Unknown resources';
    end;
  end;

begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnPermissionRequested');
{$ENDIF}

  // Go to a web page that requests permissions, e.g.:
  // https://whatwebcando.today/permissions.html

  // NOTE: camera & notification permission requests do not come through here
  // Without the event handler in place, the requests do not appear on-screen in Edge.
  // This _looks_ like a bug in the (pre-release) version of WebView2 used to set up this demo.

  var Uri: PChar;
  var PermissionType: COREWEBVIEW2_PERMISSION_KIND;
  var UserInitiated: Integer;
  if Succeeded(Args.ArgsInterface.Get_uri(Uri)) and
     Succeeded(Args.ArgsInterface.Get_PermissionKind(PermissionType)) and
     Succeeded(Args.ArgsInterface.Get_IsUserInitiated(UserInitiated)) then
  begin
    var Msg := Format('Do you want to grant permission for %s to the website at %s?'#10#10,
      [NameOfPermissionType(PermissionType), Uri]);
    if LongBool(UserInitiated) then
      Msg := Msg + 'This request came from a user gesture.'
    else
      Msg := Msg + 'This request did not come from a user gesture.';
    var Response := Application.MessageBox(PChar(Msg), 'Permission Request', MB_YESNO or MB_ICONWARNING);
    var State: COREWEBVIEW2_PERMISSION_STATE;
    case Response of
      IDYES:
        State := COREWEBVIEW2_PERMISSION_STATE_ALLOW;
      else
        State := COREWEBVIEW2_PERMISSION_STATE_DENY;
    end;
    Args.ArgsInterface.Set_State(State);
    CoTaskMemFree(Uri);
  end;
end;

procedure TfrmMain.EdgeBrowserProcessFailed(Sender: TCustomEdgeBrowser; FailureType: COREWEBVIEW2_PROCESS_FAILED_KIND);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnProcessFailed');
{$ENDIF}
  if FailureType = COREWEBVIEW2_PROCESS_FAILED_KIND_BROWSER_PROCESS_EXITED then
  begin
    var Button := Application.MessageBox(
      'Browser process exited unexpectedly. Recreate webview?',
      'Browser process exited', MB_YESNO or MB_ICONQUESTION);
    if Button = IDYES then
      EdgeBrowser.ReinitializeWebView;
  end;
end;

procedure TfrmMain.EdgeBrowserScriptDialogOpening(Sender: TCustomEdgeBrowser;
  Args: TScriptDialogOpeningEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnScriptDialogOpening');
{$ENDIF}

  // Go to a page with Javascript dialogs, e.g.:
  // https://www.tutorialspoint.com/javascript/javascript_dialog_boxes.htm
  var Uri, Msg, DefaultText: PChar;
  var DialogType: COREWEBVIEW2_SCRIPT_DIALOG_KIND;
  if Succeeded(Args.ArgsInterface.Get_uri(Uri)) and
     Succeeded(Args.ArgsInterface.Get_Kind(DialogType)) and
     Succeeded(Args.ArgsInterface.Get_Message(Msg)) and
     Succeeded(Args.ArgsInterface.Get_DefaultText(DefaultText)) then
  begin
    var Prompt := Format('The page at ''%s'' says:'#10#10'%s', [Uri, Msg]);
    case DialogType of
      COREWEBVIEW2_SCRIPT_DIALOG_KIND_ALERT:
        Application.MessageBox(PChar(Prompt), 'Script Dialog', MB_OK or MB_ICONWARNING);
      COREWEBVIEW2_SCRIPT_DIALOG_KIND_CONFIRM:
        if Application.MessageBox(PChar(Prompt), 'Script Dialog', MB_YESNO or MB_ICONQUESTION) = IDYES then
          Args.ArgsInterface.Accept;
      COREWEBVIEW2_SCRIPT_DIALOG_KIND_PROMPT:
      begin
        var Value: string := DefaultText;
        if InputQuery('Script dialog', Prompt, Value) then
          if Succeeded(Args.ArgsInterface.Set_ResultText(PChar(Value))) then
            Args.ArgsInterface.Accept
      end;
    end;
    CoTaskMemFree(Uri);
    CoTaskMemFree(Msg);
    CoTaskMemFree(DefaultText);
  end;
end;

procedure TfrmMain.EdgeBrowserSourceChanged(Sender: TCustomEdgeBrowser; IsNewDocument: Boolean);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnSourceChanged');
{$ENDIF}
  edtAddress.Text := Sender.LocationURL
end;

procedure TfrmMain.EdgeBrowserWebMessageReceived(Sender: TCustomEdgeBrowser;
  Args: TWebMessageReceivedEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnWebMessageReceived');
{$ENDIF}

  // TODO: for the reader to complete using knowledge of sending / receiving web messages
end;

procedure TfrmMain.EdgeBrowserWebResourceRequested(Sender: TCustomEdgeBrowser;
  Args: TWebResourceRequestedEventArgs);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnWebResourceRequested');
{$ENDIF}
  // Go to any site that uses image references, e.g. google.com (but not bing.com)
  if FBlockImages then
  begin
    var ResourceContext: COREWEBVIEW2_WEB_RESOURCE_CONTEXT;
    if Succeeded(Args.ArgsInterface.Get_resourceContext(ResourceContext)) then
    begin
      // Ensure that the type is image
      if ResourceContext = COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE then
      begin
        // Override the response with an empty one to block the image.
        // If Set_Response is not called, the request will continue as normal.
        var Response: ICoreWebView2WebResourceResponse;
        if Succeeded(EdgeBrowser.EnvironmentInterface.CreateWebResourceResponse(
             nil, 403 { NoContent }, 'Blocked', '', Response)) then
          Args.ArgsInterface.Set_Response(Response)
      end;
    end;
  end;
end;

procedure TfrmMain.EdgeBrowserWindowCloseRequested(Sender: TObject);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnWindowCloseRequested');
{$ENDIF}

  // This one is tricky to test as it fires in response to window.close, but only on
  // a window that was seen to be opened through JavaScript, not through program control

  // A page with a Javascript call to window.close can be played with, e.g. the sample button on:
  // https://www.thesitewizard.com/javascripts/close-browser-tab-or-window.shtml
  // however due to the above that will not trigger this event handler

  Close;
end;

procedure TfrmMain.EdgeBrowserZoomFactorChanged(Sender: TCustomEdgeBrowser; AZoomFactor: Double);
begin
{$IFDEF DEBUG}
  OutputDebugString('EdgeBrowser OnZoomFactorChanged');
{$ENDIF}
  Caption := Format('EdgeBrowser (Zoom: %d%)', [Trunc(AZoomFactor * 100)])
end;

end.
