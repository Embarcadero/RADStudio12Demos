object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'Main Form'
  ClientHeight = 291
  ClientWidth = 633
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  Position = poDefault
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  TextHeight = 16
  object tbToolbar: TToolBar
    Left = 0
    Top = 0
    Width = 633
    Height = 29
    ButtonHeight = 24
    ButtonWidth = 55
    Caption = 'tbToolbar'
    ParentShowHint = False
    ShowCaptions = True
    ShowHint = False
    TabOrder = 0
    Wrapable = False
    object tbBack: TToolButton
      Left = 0
      Top = 0
      Caption = 'Back'
      Enabled = False
      OnClick = tbBackClick
    end
    object tbForward: TToolButton
      Left = 55
      Top = 0
      Caption = 'Forward'
      Enabled = False
      OnClick = tbForwardClick
    end
    object tbReload: TToolButton
      Left = 110
      Top = 0
      Caption = 'Reload'
      Enabled = False
      OnClick = tbReloadClick
    end
    object tbCancel: TToolButton
      Left = 165
      Top = 0
      Caption = 'Cancel'
      Enabled = False
      OnClick = tbCancelClick
    end
    object edtAddress: TEdit
      Left = 220
      Top = 0
      Width = 121
      Height = 24
      Enabled = False
      TabOrder = 0
      OnKeyPress = edtAddressKeyPress
    end
    object tbGo: TToolButton
      Left = 341
      Top = 0
      Caption = 'Go'
      Enabled = False
      ImageIndex = 0
      OnClick = tbGoClick
    end
  end
  object EdgeBrowser: TEdgeBrowser
    Left = 0
    Top = 29
    Width = 633
    Height = 262
    Align = alClient
    TabOrder = 1
    TabStop = True
    AllowSingleSignOnUsingOSPrimaryAccount = False
    TargetCompatibleBrowserVersion = '101.0.1210.39'
    UserDataFolder = '%LOCALAPPDATA%\bds.exe.WebView2'
    OnCapturePreviewCompleted = EdgeBrowserCapturePreviewCompleted
    OnContainsFullScreenElementChanged = EdgeBrowserContainsFullScreenElementChanged
    OnContentLoading = EdgeBrowserContentLoading
    OnCreateWebViewCompleted = EdgeBrowserCreateWebViewCompleted
    OnDevToolsProtocolEventReceived = EdgeBrowserDevToolsProtocolEventReceived
    OnDocumentTitleChanged = EdgeBrowserDocumentTitleChanged
    OnDownloadStarting = EdgeBrowserDownloadStarting
    OnExecuteScript = EdgeBrowserExecuteScript
    OnFrameNavigationStarting = EdgeBrowserFrameNavigationStarting
    OnFrameNavigationCompleted = EdgeBrowserFrameNavigationCompleted
    OnHistoryChanged = EdgeBrowserHistoryChanged
    OnNavigationStarting = EdgeBrowserNavigationStarting
    OnNavigationCompleted = EdgeBrowserNavigationCompleted
    OnNewWindowRequested = EdgeBrowserNewWindowRequested
    OnPermissionRequested = EdgeBrowserPermissionRequested
    OnProcessFailed = EdgeBrowserProcessFailed
    OnScriptDialogOpening = EdgeBrowserScriptDialogOpening
    OnSourceChanged = EdgeBrowserSourceChanged
    OnWebMessageReceived = EdgeBrowserWebMessageReceived
    OnWebResourceRequested = EdgeBrowserWebResourceRequested
    OnWindowCloseRequested = EdgeBrowserWindowCloseRequested
    OnZoomFactorChanged = EdgeBrowserZoomFactorChanged
  end
  object MainMenu: TMainMenu
    Left = 272
    Top = 88
    object mniFile: TMenuItem
      Caption = '&File'
      object mniFileSaveScreenShot: TMenuItem
        Caption = 'Save Screenshot'
        ShortCut = 16467
        OnClick = mniFileSaveScreenShotClick
      end
      object mniFileGetDocumentTitle: TMenuItem
        Caption = 'Get Document Title'
        OnClick = mniFileGetDocumentTitleClick
      end
      object mniFileGetBrowserVersion: TMenuItem
        Caption = 'Get Browser Version'
        OnClick = mniFileGetBrowserVersionClick
      end
      object mniFilePrintBrowserUI: TMenuItem
        Caption = 'Print (browser UI)'
        OnClick = mniFilePrintBrowserUIClick
      end
      object mniFilePrintSystemUI: TMenuItem
        Caption = 'Print (system UI)'
        OnClick = mniFilePrintSystemUIClick
      end
      object mniFilePrintToPDF: TMenuItem
        Caption = 'Print To PDF'
        OnClick = mniFilePrintToPDFClick
      end
      object mniFileProxyServer: TMenuItem
        Caption = 'Proxy Server'
        OnClick = mniFileProxyServerClick
      end
    end
    object mniScript: TMenuItem
      Caption = '&Script'
      object mniScriptInjectScript: TMenuItem
        Caption = 'Inject script'
        OnClick = mniScriptInjectScriptClick
      end
      object mniScriptSubscribeToCDPEvent: TMenuItem
        Caption = 'Subscribe to CDP event'
        OnClick = mniScriptSubscribeToCDPEventClick
      end
      object mniScriptOpenDevToolsWindow: TMenuItem
        Caption = 'Open DevTools Window'
        OnClick = mniScriptOpenDevToolsWindowClick
      end
      object mniScriptOpenTaskManagerWindow: TMenuItem
        Caption = 'Open Task Manager Window'
        OnClick = mniScriptOpenTaskManagerWindowClick
      end
    end
    object mniWindow: TMenuItem
      Caption = '&Window'
      object mniWindowCloseWebView: TMenuItem
        Caption = 'Close WebView'
        ShortCut = 16471
        OnClick = mniWindowCloseWebViewClick
      end
      object mniWindowCreateWebView: TMenuItem
        Caption = 'Create WebView'
        OnClick = mniWindowCreateWebViewClick
      end
      object mniWindowCreateWebViewFixedVersion: TMenuItem
        Caption = 'Create WebView from Fixed Version distribution'
        OnClick = mniWindowCreateWebViewFixedVersionClick
      end
      object mniWindowCloseWindow: TMenuItem
        Caption = 'Close Window'
        ShortCut = 16465
        OnClick = mniWindowCloseWindowClick
      end
      object mniWindowCreateNewWindow: TMenuItem
        Caption = 'Create New Window'
        ShortCut = 16462
        OnClick = mniWindowCreateNewWindowClick
      end
    end
    object mniProcess: TMenuItem
      Caption = '&Process'
      object mniProcessBrowserInfo: TMenuItem
        Caption = 'Browser Process Info'
        OnClick = mniProcessBrowserInfoClick
      end
      object mniProcessCrashBrowser: TMenuItem
        Caption = 'Crash Browser Process'
        OnClick = mniProcessCrashBrowserClick
      end
    end
    object mniSettings: TMenuItem
      Caption = 'S&ettings'
      object mniSettingsToggleFullscreen: TMenuItem
        Caption = 'Toggle Fullscreen allowed'
        OnClick = mniSettingsToggleFullscreenClick
      end
      object mniSettingsToggleStatusBar: TMenuItem
        Caption = 'Toggle Status Bar enabled'
        OnClick = mniSettingsToggleStatusBarClick
      end
      object mniSettingsToggleDevTools: TMenuItem
        Caption = 'Toggle Dev Tools enabled'
        OnClick = mniSettingsToggleDevToolsClick
      end
      object mniSettingsToggleBlockImages: TMenuItem
        Caption = 'Toggle Block images'
        OnClick = mniSettingsToggleBlockImagesClick
      end
      object mniSettingsJavaScriptDialogs: TMenuItem
        Caption = 'JavaScript Dialogs'
        object mniSettingsJavaScriptDialogsDefault: TMenuItem
          Caption = 'Use Default Script Dialogs'
          OnClick = mniSettingsJavaScriptDialogsDefaultClick
        end
        object mniSettingsJavaScriptDialogsCustom: TMenuItem
          Caption = 'Use Custom Script Dialogs'
          OnClick = mniSettingsJavaScriptDialogsCustomClick
        end
      end
    end
    object mniView: TMenuItem
      Caption = '&View'
      object mniViewGetBounds: TMenuItem
        Caption = 'Get WebView Bounds'
        OnClick = mniViewGetBoundsClick
      end
      object mniViewWebViewArea: TMenuItem
        Caption = 'WebView Area'
        object mniViewWebViewArea25Percent: TMenuItem
          Caption = '25%'
          OnClick = mniViewWebViewArea25PercentClick
        end
        object mniViewWebViewArea50Percent: TMenuItem
          Caption = '50%'
          OnClick = mniViewWebViewArea50PercentClick
        end
        object mniViewWebViewArea75Percent: TMenuItem
          Caption = '75%'
          OnClick = mniViewWebViewArea75PercentClick
        end
        object mniViewWebViewArea100Percent: TMenuItem
          Caption = '100%'
          OnClick = mniViewWebViewArea100PercentClick
        end
      end
      object mniViewWebViewZoom: TMenuItem
        Caption = 'WebView Zoom'
        object mniViewWebViewZoom50Percent: TMenuItem
          Caption = '0.5x'
          OnClick = mniViewWebViewZoom50PercentClick
        end
        object mniViewWebViewZoom100Percent: TMenuItem
          Caption = '1.0x'
          OnClick = mniViewWebViewZoom100PercentClick
        end
        object mniViewWebViewZoom200Percent: TMenuItem
          Caption = '2.0x'
          OnClick = mniViewWebViewZoom200PercentClick
        end
      end
      object mniViewSetFocus: TMenuItem
        Caption = 'Set Focus'
        OnClick = mniViewSetFocusClick
      end
      object mniViewTabIn: TMenuItem
        Caption = 'Tab In'
        OnClick = mniViewTabInClick
      end
      object mniViewReverseTabIn: TMenuItem
        Caption = 'Reverse Tab In'
        OnClick = mniViewReverseTabInClick
      end
    end
    object mniScenario: TMenuItem
      Caption = 'S&cenario'
      object mniScenarioCustomDownload: TMenuItem
        Caption = 'Custom Download Experience'
        object mniScenarioCustomDownloadDeferred: TMenuItem
          Caption = 'Use Deferred Download Dialog'
          OnClick = mniScenarioCustomDownloadDeferredClick
        end
      end
      object mniScenarioDomContentLoaded: TMenuItem
        Caption = 'DOM Content Loaded'
        OnClick = mniScenarioDomContentLoadedClick
      end
      object mniScenarioNavigateWithWebResourceRequest: TMenuItem
        Caption = 'NavigateWithWebResourceRequest'
        OnClick = mniScenarioNavigateWithWebResourceRequestClick
      end
    end
  end
  object dlgSaveScreenshot: TSaveDialog
    FileName = 'WebView2_Screenshot.png'
    Filter = 'PNG File|*.png'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = 'Screenshot file'
    Left = 368
    Top = 77
  end
  object dlgLocateWebView2Executable: TOpenDialog
    DefaultExt = '*.exe'
    FileName = 'msedgewebview2.exe'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofShareAware, ofEnableSizing]
    Title = 'Locate msedgewebview2.exe in a Fixed Distribution Folder'
    Left = 488
    Top = 88
  end
  object dlgPrintToPDF: TSaveDialog
    FileName = 'print.pdf'
    Filter = 'PDF File|*.pdf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = 'Print to PDF file'
    Left = 368
    Top = 149
  end
end
