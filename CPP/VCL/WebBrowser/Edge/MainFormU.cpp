#include <vcl.h>
#pragma hdrstop

#include "MainFormU.h"
#include <windows.h>
#include <IdURI.hpp>
#include <System.StrUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.NetEncoding.hpp>
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
THintWindow *HintWnd;

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
    FAllowFullScreen = true;
    FBlockImages = false;
    HintWnd = new THintWindow(this);
      // This gets assigned in the deferred download scenario
    EdgeBrowser->OnDownloadStarting = NULL;
    // Set a custom user data (cache) folder
    EdgeBrowser->UserDataFolder = TPath::Combine(TPath::GetDirectoryName(Application->ExeName), "CustomCache");
    // Note: if you wish you can call EdgeBrowser->CreateWebView() here
    // and initiate navigation with Sender->Navigate(L"http://bing.com") in the
    // OnCreateWebViewCompleted handler, TfrmMain::EdgeBrowserCreateWebViewCompleted
    EdgeBrowser->Navigate(L"http://bing.com");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
  EdgeBrowser->CloseWebView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject *Sender)
{
    edtAddress->Width = tbToolbar->ClientWidth - edtAddress->Left - tbGo->Width;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edtAddressKeyPress(TObject *Sender, System::WideChar &Key)
{
    if (Key == 13)
    {
        Key = 0;
        tbGo->Click();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbBackClick(TObject *Sender)
{
    EdgeBrowser->GoBack();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbForwardClick(TObject *Sender)
{
    EdgeBrowser->GoForward();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbReloadClick(TObject *Sender)
{
    EdgeBrowser->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbCancelClick(TObject *Sender)
{
    EdgeBrowser->Stop();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbGoClick(TObject *Sender)
{
    String URL = edtAddress->Text;
    // Ensure we have the protocol prefix
    if (!StartsText(L"http", URL))
        URL = L"http://" + URL;
    EdgeBrowser->Navigate(URL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFileSaveScreenShotClick(TObject *Sender)
{
    if (dlgSaveScreenshot->Execute())
        EdgeBrowser->CapturePreview(dlgSaveScreenshot->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFileGetDocumentTitleClick(TObject *Sender)
{
    Application->MessageBox(EdgeBrowser->DocumentTitle.c_str(), L"Document Title", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFileGetBrowserVersionClick(TObject *Sender)
{
    String Msg;
    if (EdgeBrowser->WebViewCreated)
        Msg = L"Browser Version Info After WebView Creation";
    else
        Msg = L"Browser Version Info Before WebView Creation";
    Application->MessageBox(EdgeBrowser->BrowserVersionInfo.c_str(), Msg.c_str(), MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFilePrintBrowserUIClick(TObject *Sender)
{
    EdgeBrowser->ShowPrintUI(TEdgeBrowser::TPrintUIDialogKind::Browser);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFilePrintSystemUIClick(TObject *Sender)
{
    EdgeBrowser->ShowPrintUI(TEdgeBrowser::TPrintUIDialogKind::System);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFilePrintToPDFClick(TObject *Sender)
{
    if (dlgPrintToPDF->Execute())
    {
        _di_ICoreWebView2PrintSettings PrintSettings = EdgeBrowser->CreatePrintSettings();
        PrintSettings->Set_ShouldPrintBackgrounds(true);
        EdgeBrowser->PrintToPDF(dlgPrintToPDF->FileName, PrintSettings);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniFileProxyServerClick(TObject *Sender)
{
    String ProxyServer;
    if (InputQuery("Proxy Server", "Enter proxy server:", ProxyServer))
    {
        // The correct format matches http://1.2.3.4:8888
        EdgeBrowser->AdditionalBrowserArguments =
        #if defined(__clang__)
            Format("--proxy-server=%ls", ProxyServer);
        #else
            String().sprintf(L"--proxy-server=%ls", ProxyServer.c_str());
        #endif
        if (EdgeBrowser->WebViewCreated)
        {
            String CurrentURL = EdgeBrowser->LocationURL;
            EdgeBrowser->CloseWebView();
            EdgeBrowser->Navigate(CurrentURL);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniScriptInjectScriptClick(TObject *Sender)
{
    String Script = L"window.getComputedStyle(document.body).backgroundColor";
    if (InputQuery(L"Inject Script",
            L"Enter script code:\n"
            L"Enter the JavaScript code to run in the WebView.", Script))
        EdgeBrowser->ExecuteScript(Script);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniScriptSubscribeToCDPEventClick(TObject *Sender)
{
    String EventName = L"Log.entryAdded";
    if (InputQuery(L"Subscribe to CDP Event",
            L"CDP event name:\n"
            L"Enter the name of the CDP event to subscribe to.\n"
            L"You may also have to call the \"enable\" method of the\n"
            L"event's domain to receive events (for example \"Log.enable\").", EventName))
        EdgeBrowser->SubscribeToCDPEvent(EventName);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniScriptOpenDevToolsWindowClick(TObject *Sender)
{
    // Call ICoreWebView2.OpenDevToolsWindow
    // https://docs.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/icorewebview2?view=webview2-1.0.1210.39#opendevtoolswindow

    // EdgeBrowser->DefaultInterface gives us ICoreWebView2, of which OpenDevToolsWindow is a member
    EdgeBrowser->DefaultInterface->OpenDevToolsWindow();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniScriptOpenTaskManagerWindowClick(TObject *Sender)
{
    // Call ICoreWebView2_6.OpenTaskManagerWindow
    // https://docs.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/icorewebview2_6?view=webview2-1.0.1210.39#opentaskmanagerwindow

    // EdgeBrowser->DefaultInterface gives us ICoreWebView2, but OpenTaskManagerWindow is a member of ICoreWebView2_6
    _di_ICoreWebView2_6 WebView2_6;
    if (EdgeBrowser->DefaultInterface->Supports<ICoreWebView2_6>(WebView2_6))
        WebView2_6->OpenTaskManagerWindow();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniWindowCloseWebViewClick(TObject *Sender)
{
    if (EdgeBrowser->WebViewCreated)
        EdgeBrowser->CloseWebView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniWindowCreateWebViewClick(TObject *Sender)
{
    mniWindowCloseWebView->Click();
    EdgeBrowser->CreateWebView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniWindowCreateWebViewFixedVersionClick(TObject *Sender)
{
    mniWindowCloseWebView->Click();
    if (dlgLocateWebView2Executable->Execute())
        EdgeBrowser->BrowserExecutableFolder = TPath::GetDirectoryName(dlgLocateWebView2Executable->FileName);
    EdgeBrowser->CreateWebView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniWindowCloseWindowClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniWindowCreateNewWindowClick(TObject *Sender)
{
    TForm *Form = new TfrmMain(Application);
    // Bypass the default behaviour of any form being kept above the main form like a tool window.
    // However by so doing we lose the form if it gets minimised, so stop that possibility.
    SetWindowLongPtr(Form->Handle, GWLP_HWNDPARENT, (LONG_PTR)(Application->Handle));
    Form->BorderIcons = TBorderIcons(Form->BorderIcons) >> biMinimize;
    Form->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewGetBoundsClick(TObject *Sender)
{
    // A couple of ways present themselves to get the bounding dimensions of the WebView2 browser control.
    // One uses the WebView2 interface, one uses VCL control methods
#define ONE_POSSIBLE_WAY
#ifdef ONE_POSSIBLE_WAY
    tagRECT Bounds;
    EdgeBrowser->ControllerInterface->Get_Bounds(Bounds);
    String Msg = String().sprintf(L"Left:\t%d\nTop:\t%d\nRight:\t%d\nBottom:\t%d\n",
        Bounds.left, Bounds.top, Bounds.right, Bounds.bottom);
    Application->MessageBox(Msg.c_str(), L"WebView Bounds", MB_OK | MB_ICONINFORMATION);
#else
    TRect Bounds = EdgeBrowser->BoundsRect;
    TSize Size = Bounds.Size;
    Bounds.Location = EdgeBrowser->ClientToScreen(Bounds.Location);
    Bounds.Size = Size;
    String Msg = String().sprintf(L"Left:\t%d\nTop:\t%d\nRight:\t%d\nBottom:\t%d\n",
        Bounds.Left, Bounds.Top, Bounds.Right, Bounds.Bottom);
    Application->MessageBox(Msg.c_str(), L"WebView Bounds", MB_OK | MB_ICONINFORMATION);
#endif
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewArea25PercentClick(TObject *Sender)
{
    EdgeBrowser->SizeRatio = 0.5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewArea50PercentClick(TObject *Sender)
{
    EdgeBrowser->SizeRatio = 0.7071;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewArea75PercentClick(TObject *Sender)
{
    EdgeBrowser->SizeRatio = 0.866;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewArea100PercentClick(TObject *Sender)
{
    EdgeBrowser->SizeRatio = 1.0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewZoom50PercentClick(TObject *Sender)
{
    EdgeBrowser->ZoomFactor = 0.5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewZoom100PercentClick(TObject *Sender)
{
    EdgeBrowser->ZoomFactor = 1.0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewWebViewZoom200PercentClick(TObject *Sender)
{
    EdgeBrowser->ZoomFactor = 2.0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewSetFocusClick(TObject *Sender)
{
    EdgeBrowser->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewTabInClick(TObject *Sender)
{
    SelectNext(EdgeBrowser, true, true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniViewReverseTabInClick(TObject *Sender)
{
    SelectNext(EdgeBrowser, false, true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniProcessBrowserInfoClick(TObject *Sender)
{
    // Show the WebView's PID to the user.
    DWORD ProcessId = EdgeBrowser->BrowserProcessID;
    String Msg = String().sprintf(L"Process ID: %u\n", ProcessId);
    Application->MessageBox(Msg.c_str(), L"Process Info", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniProcessCrashBrowserClick(TObject *Sender)
{
    // Crash the browser's process on command, to test crash handlers.
    EdgeBrowser->Navigate(L"edge://inducebrowsercrashforrealz");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSettingsToggleFullscreenClick(TObject *Sender)
{
    FAllowFullScreen = !FAllowFullScreen;
    Application->MessageBox(
        String().sprintf(L"Full screen is now %s.", FAllowFullScreen ? L"allowed" : L"disallowed").c_str(),
        L"Settings change", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSettingsToggleStatusBarClick(TObject *Sender)
{
    EdgeBrowser->StatusBarEnabled = !EdgeBrowser->StatusBarEnabled;
    Application->MessageBox(
        String().sprintf(L"Status bar will be %s after the next navigation.",
            EdgeBrowser->StatusBarEnabled ? L"enabled" : L"disabled").c_str(),
        L"Settings change", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSettingsToggleDevToolsClick(TObject *Sender)
{
    if (EdgeBrowser->SettingsInterface)
    {
        BOOL AreDevToolsEnabled = FALSE;
        EdgeBrowser->SettingsInterface->Get_AreDevToolsEnabled(AreDevToolsEnabled);
        EdgeBrowser->SettingsInterface->Set_AreDevToolsEnabled(!AreDevToolsEnabled);
        Application->MessageBox(String().sprintf(
           L"Dev tools will be %s after the next navigation.", !AreDevToolsEnabled ? L"enabled" : L"disabled").c_str(),
           L"Settings change", MB_OK);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSettingsToggleBlockImagesClick(TObject *Sender)
{
    FBlockImages = !FBlockImages;
    Application->MessageBox(String().sprintf(
        L"Image blocking has been %s.", FBlockImages ? L"enabled" : L"disabled").c_str(),
        L"Settings change", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSettingsJavaScriptDialogsDefaultClick(TObject *Sender)
{
    if (EdgeBrowser->SettingsInterface)
    {
        BOOL DefaultCurrentlyEnabled;
        EdgeBrowser->SettingsInterface->Get_AreDefaultScriptDialogsEnabled(DefaultCurrentlyEnabled);
        if (!DefaultCurrentlyEnabled)
        {
            EdgeBrowser->SettingsInterface->Set_AreDefaultScriptDialogsEnabled(TRUE);
            Application->MessageBox(
                L"Default script dialogs will be used after the next navigation.",
                L"Settings change", MB_OK);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniSettingsJavaScriptDialogsCustomClick(TObject *Sender)
{
    if (EdgeBrowser->SettingsInterface)
    {
        BOOL DefaultCurrentlyEnabled;
        EdgeBrowser->SettingsInterface->Get_AreDefaultScriptDialogsEnabled(DefaultCurrentlyEnabled);
        if (DefaultCurrentlyEnabled)
        {
            EdgeBrowser->SettingsInterface->Set_AreDefaultScriptDialogsEnabled(FALSE);
            Application->MessageBox(
                L"Custom script dialogs without deferral will be used after the next navigation.",
                L"Settings change", MB_OK);
        }
    }
}
//---------------------------------------------------------------------------

const String DemoURI = L"https://demo.smartscreen.msft.net/";

#pragma region "Simple class to implement ICoreWebView2ContentLoadingEventHandler"
class TContentLoading : public TCppInterfacedObject<ICoreWebView2ContentLoadingEventHandler>
{
private:
    TCustomEdgeBrowser *FBrowser;
    EventRegistrationToken *FEventRegistrationToken;
public:
    TContentLoading(TCustomEdgeBrowser *Browser, EventRegistrationToken *PEventRegistrationToken)
    {
        FBrowser = Browser;
        // This field is a pointer as during construction of this handler we do not have an event registration token yet
        FEventRegistrationToken = PEventRegistrationToken;
    }

    HRESULT __stdcall Invoke(const _di_ICoreWebView2 sender, const _di_ICoreWebView2ContentLoadingEventArgs args)
    {
    #ifdef _DEBUG
        OutputDebugString(L"ICoreWebView2ContentLoadingEventHandler");
    #endif

        wchar_t *URI;
        sender->Get_Source(URI);
        // Turn off the custom download scenario if we navigate away from the demo page
        if (URI != DemoURI)
        {
            FBrowser->OnDownloadStarting = NULL;
            FBrowser->DefaultInterface->remove_ContentLoading(*FEventRegistrationToken);
        }

        return S_OK;
    }
};
#pragma end_region

void __fastcall TfrmMain::mniScenarioCustomDownloadDeferredClick(TObject *Sender)
{
    EdgeBrowser->OnDownloadStarting = EdgeBrowserDownloadStarting;
    EdgeBrowser->DefaultInterface->add_ContentLoading(
        _di_ICoreWebView2ContentLoadingEventHandler(new TContentLoading(EdgeBrowser, &FContentLoadingToken)),
        FContentLoadingToken);
    // On this demo page scroll down and click on the green 'Known Good Program' section
    EdgeBrowser->Navigate(DemoURI);
}
//---------------------------------------------------------------------------

#pragma region "Simple class to implement ICoreWebView2DOMContentLoadedEventHandler"
class TDOMContentLoaded : public TCppInterfacedObject<ICoreWebView2DOMContentLoadedEventHandler>
{
private:
    _di_ICoreWebView2_2 FWebView2_2;
    EventRegistrationToken *FEventRegistrationToken;
public:
    TDOMContentLoaded(_di_ICoreWebView2_2 WebView2_2, EventRegistrationToken *EventRegistrationToken)
    {
        FWebView2_2 = WebView2_2;
        // This field is a pointer as during construction of this handler we do not have an event registration token yet
        FEventRegistrationToken = EventRegistrationToken;
    }

    HRESULT __stdcall Invoke(const _di_ICoreWebView2 sender, const _di_ICoreWebView2DOMContentLoadedEventArgs args)
    {
    #ifdef _DEBUG
        OutputDebugString(L"ICoreWebView2DOMContentLoadedEventHandler");
    #endif
        sender->ExecuteScript((wchar_t *)
            L"let content = document.createElement(\"h2\");\n"
            "content.style.color = 'blue';\n"
            "content.textContent = \"This text was added by the host app\";\n"
            "document.body.appendChild(content);",
            NULL);
        FWebView2_2->remove_DOMContentLoaded(*FEventRegistrationToken);
        return S_OK;
    }
};
#pragma end_region

void __fastcall TfrmMain::mniScenarioDOMContentLoadedClick(TObject *Sender)
{
    _di_ICoreWebView2_2 WebView2_2;
    if (!EdgeBrowser->DefaultInterface->Supports<ICoreWebView2_2>(WebView2_2))
        return;
    WebView2_2->add_DOMContentLoaded(
        _di_ICoreWebView2DOMContentLoadedEventHandler(new TDOMContentLoaded(WebView2_2, &FDomContentLoadedToken)),
        FDomContentLoadedToken);
    EdgeBrowser->NavigateToString(
        L"<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
            "<title>ScenarioDOMContentLoaded</title>\n"
        "</head>\n"
        "<body>\n"
            "<h1>DOMContentLoaded sample page</h1>\n"
        "</body>\n"
        "</html>");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mniScenarioNavigateWithWebResourceRequestClick(TObject *Sender)
{
    // Prepare post data as UTF-8 byte array and convert it to stream
    // as required by the application/x-www-form-urlencoded Content-Type
    String Input = L"Here is input from a C++Builder sample app!";
    if (InputQuery(L"Post data", L"Specify post data to submit to https://www.w3schools.com/action_page.php:", Input))
    {
        Input = L"input=" + TNetEncoding::URL->Encode(Input);
        if (!FPostDataMemStream)
            FPostDataMemStream = new TMemoryStream();
        TByteDynArray LBytes = TEncoding::UTF8->GetBytes(Input);
        FPostDataMemStream->WriteData(LBytes, LBytes.Length);
        TStreamAdapter *StreamAdapter = new TStreamAdapter((TStream *)FPostDataMemStream, soReference);
        FPostDataIStream = *StreamAdapter;
        _di_ICoreWebView2Environment2 WebViewEnvironment2;
        // This acts as a form submit to https://www.w3schools.com/action_page.php
        if (EdgeBrowser->EnvironmentInterface->Supports<ICoreWebView2Environment2>(WebViewEnvironment2) &&
            SUCCEEDED(WebViewEnvironment2->CreateWebResourceRequest(
                (wchar_t *)L"https://www.w3schools.com/action_page.php", (wchar_t *)L"POST", FPostDataIStream,
                (wchar_t *)L"Content-Type: application/x-www-form-urlencoded", FWebResourceRequest)))
            EdgeBrowser->NavigateWithWebResourceRequest(FWebResourceRequest);
        else
            Application->MessageBox(L"Web resource not created successfully", L"Web resource navigation", MB_OK);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EdgeBrowserCapturePreviewCompleted(TCustomEdgeBrowser* Sender, HRESULT AResult)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnCapturePreviewCompleted");
#endif
    if (SUCCEEDED(AResult))
        Application->MessageBox(L"Preview captured successfully", L"Preview Capture", MB_OK | MB_ICONINFORMATION);
    else
        Application->MessageBox(L"Preview not captured successfully", L"Preview Capture", MB_OK | MB_ICONINFORMATION);
}

void __fastcall TfrmMain::EdgeBrowserContainsFullScreenElementChanged(TCustomEdgeBrowser* Sender,
    bool ContainsFullScreenElement)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnContainsFullScreenElementChanged");
#endif
    // Go to a web page that offers full-screen, e.g.
    // https://www.davidwalsh.name/demo/fullscreen.php
    if (FAllowFullScreen && ContainsFullScreenElement)
    {
        BorderStyle = bsNone;
        WindowState = wsMaximized;
    }
    else
    {
        WindowState = wsNormal;
        BorderStyle = bsSizeable;
    }
}

void TfrmMain::ActivateHintNOW(String Txt, TPoint Pt)
{
    if (Txt.Length())
    {
        TRect Rect = HintWnd->CalcHintRect(Screen->Width, Txt, NULL);
        Rect.Left = Rect.Left + Pt.X;
        Rect.Right = Rect.Right + Pt.X;
        Rect.Top = Rect.Top + Pt.Y;
        Rect.Bottom = Rect.Bottom + Pt.Y;
        HintWnd->ActivateHint(Rect, Txt);
    }
}

void __fastcall TfrmMain::EdgeBrowserContentLoading(TCustomEdgeBrowser* Sender, bool IsErrorPage, unsigned __int64 NavigationID)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnContentLoading");
#endif
    // Show a tooltip over the caption bar, just as a simple way of displaying the Navigation ID
    // Note: in this demo nothing takes that tooltip away...
    ActivateHintNOW(String().sprintf(L"Navigation ID: %lu", NavigationID),
        ClientToScreen(Point(Width / 2,
            -GetSystemMetrics(SM_CYCAPTION) -GetSystemMetrics(SM_CYCAPTION))));
}

void __fastcall TfrmMain::EdgeBrowserCreateWebViewCompleted(TCustomEdgeBrowser* Sender, HRESULT AResult)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnCreateWebViewCompleted");
#endif
    if (SUCCEEDED(AResult))
    {
        tbCancel->Enabled = true;
        tbReload->Enabled = true;
        tbGo->Enabled = true;
        edtAddress->Enabled = true;
    }
    else
    {
        if (AResult == HResultFromWin32(ERROR_FILE_NOT_FOUND))
            Application->MessageBox(L"Could not find Edge installation. "
                "Do you have a version installed that''s compatible with this WebView2 SDK version?",
                L"Edge initialisation error", MB_OK | MB_ICONERROR);
        else if (AResult == E_FAIL)
            Application->MessageBox(L"Failed to initialise Edge loader",
                L"Edge initialisation error", MB_OK | MB_ICONERROR);
        else
            try
            {
                OleCheck(AResult);
            }
            catch (Exception &e)
            {
                String msg;
                msg.sprintf(L"Failed to initialise Edge: %s", e.Message.c_str());
                Application->MessageBox(
                    msg.c_str(),
                    L"Edge initialisation error", MB_OK | MB_ICONERROR);
            }
    }
}

void __fastcall TfrmMain::EdgeBrowserDevToolsProtocolEventReceived(TCustomEdgeBrowser* Sender, const String CDPEventName, const String ParameterObjectAsJson)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnDevToolsProtocolEventReceived");
#endif
    Application->MessageBox(ParameterObjectAsJson.c_str(), (L"CDP Event Fired: " + CDPEventName).c_str(), MB_OK);
}

void __fastcall TfrmMain::EdgeBrowserDocumentTitleChanged(TCustomEdgeBrowser* Sender, const String ADocumentTitle)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnDocumentTitleChanged");
#endif
    Caption = ADocumentTitle;
}

#pragma region "Simple class to implement ICoreWebView2BytesReceivedChangedEventHandler"
class TBytesReceivedChanged : public TCppInterfacedObject<ICoreWebView2BytesReceivedChangedEventHandler>
{
private:
    TfrmMain *FForm;
    EventRegistrationToken *FEventRegistrationToken;
public:
    TBytesReceivedChanged(TfrmMain *Form, EventRegistrationToken *EventRegistrationToken)
    {
        FForm = Form;
        // This field is a pointer as during construction of this handler we do not have an event registration token yet
        FEventRegistrationToken = EventRegistrationToken;
    }

    HRESULT __stdcall Invoke(const _di_ICoreWebView2DownloadOperation sender, const System::_di_IInterface args)
    {
    #ifdef _DEBUG
        OutputDebugString(L"ICoreWebView2BytesReceivedChangedEventHandler");
    #endif
        // Here developer can update UI to show progress of a download using
        // Download.get_BytesReceived and Download.get_TotalBytesToReceive.
        // Note: the demo site Known Good Program is too small to trigger this event.
        // Try a link to a bigger download to see it in action
        __int64 BytesReceived, TotalBytes;
        sender->Get_BytesReceived(BytesReceived);
        sender->Get_TotalBytesToReceive(TotalBytes);
        FForm->Caption = String().sprintf(L"%d of %d received (%.2f%%)", BytesReceived, TotalBytes, BytesReceived * 100 / TotalBytes);
        sender->remove_BytesReceivedChanged(*FEventRegistrationToken);
        return S_OK;
    }
};
#pragma end_region

void TfrmMain::CompleteDownload(_di_ICoreWebView2DownloadOperation Download)
{
    // Close download progress dialog here.

    // Unsubscribe from download events.
    Download->remove_BytesReceivedChanged(FBytesReceivedChangedToken);
    Download->remove_StateChanged(FStateChangedToken);
}

#pragma region "Simple class to implement ICoreWebView2StateChangedEventHandler"
class TStateChanged : public TCppInterfacedObject<ICoreWebView2StateChangedEventHandler>
{
private:
    TfrmMain *FForm;
    EventRegistrationToken *FEventRegistrationToken;
public:
    TStateChanged(TfrmMain *Form, EventRegistrationToken *EventRegistrationToken)
    {
        FForm = Form;
        // This field is a pointer as during construction of this handler we do not have an event registration token yet
        FEventRegistrationToken = EventRegistrationToken;
    }

    HRESULT __stdcall Invoke(const _di_ICoreWebView2DownloadOperation sender, const System::_di_IInterface args)
    {
    #ifdef _DEBUG
        OutputDebugString(L"ICoreWebView2StateChangedEventHandler");
    #endif
        COREWEBVIEW2_DOWNLOAD_STATE DownloadState;
        sender->Get_State(DownloadState);
        switch (DownloadState)
        {
        case COREWEBVIEW2_DOWNLOAD_STATE_IN_PROGRESS:
            // nothing to do here
            break;
        case COREWEBVIEW2_DOWNLOAD_STATE_INTERRUPTED:
            // Here developers can take different actions based on Download.InterruptReason.
            // For example, show an error message to the end user.
            FForm->CompleteDownload(sender);
            break;
        case COREWEBVIEW2_DOWNLOAD_STATE_COMPLETED:
            FForm->CompleteDownload(sender);
            break;
        }
        return S_OK;
    }
};
#pragma end_region

void TfrmMain::UpdateDownloadProgress(_di_ICoreWebView2DownloadOperation Download)
{
    Download->add_BytesReceivedChanged(new TBytesReceivedChanged(this, &FBytesReceivedChangedToken), FBytesReceivedChangedToken);
    Download->add_StateChanged(new TStateChanged(this, &FStateChangedToken), FStateChangedToken);
}

#ifndef __clang__
// Classic compiler version of Delphi anonymous method, as per:
//  http://docwiki.embarcadero.com/RADStudio/en/How_to_Handle_Delphi_Anonymous_Methods_in_C%2B%2B
class TDownloadDialog : public TCppInterfacedObject<TThreadProcedure>
{
private:
    TfrmMain *FForm;
    _di_ICoreWebView2Deferral FDeferral;
    _di_ICoreWebView2DownloadStartingEventArgs FArgsInterface;
public:
    TDownloadDialog(TfrmMain *Form, _di_ICoreWebView2Deferral Deferral, _di_ICoreWebView2DownloadStartingEventArgs ArgsInterface)
    {
        FForm = Form;
        FDeferral = Deferral;
        FArgsInterface = ArgsInterface;
    }

    void __fastcall Invoke()
    {
        _di_ICoreWebView2DownloadOperation Download;
        __int64 TotalBytesToReceive;
        wchar_t *URI;
        wchar_t *MimeType;
        wchar_t *ContentDisposition;
        wchar_t *ResultFilePath;
        if (SUCCEEDED(FArgsInterface->Set_Handled(true)) &&
            SUCCEEDED(FArgsInterface->Get_DownloadOperation(Download)) &&
            SUCCEEDED(Download->Get_TotalBytesToReceive(TotalBytesToReceive)) &&
            SUCCEEDED(Download->Get_uri(URI)) &&
            SUCCEEDED(Download->Get_MimeType(MimeType)) &&
            SUCCEEDED(Download->Get_ContentDisposition(ContentDisposition)) &&
            SUCCEEDED(Download->Get_ResultFilePath(ResultFilePath))
        )
        {
            String Description = String().sprintf(L"URI: %s\r\nMime type: %s\r\n", URI, MimeType);
            if (TotalBytesToReceive > 0)
                Description += String().sprintf(L"Total bytes to receive: %u\r\n", TotalBytesToReceive);
              Description +=
                L"Enter result file path or select `OK` to use default path. Select `Cancel` to cancel the download.";
            String FilePath = ResultFilePath;
            if (InputQuery(L"Download Starting", Description, FilePath))
            {
                // If user selects OK, the download will complete normally.
                // Result file path will be updated if a new one was provided.
                FArgsInterface->Set_ResultFilePath(FilePath.w_str());
                FForm->UpdateDownloadProgress(Download);
            }
            else
            {
                // If user selects Cancel, the download will be canceled.
                FArgsInterface->Set_Cancel(true);
            }
        }
        // Now complete the deferral
        FDeferral->Complete();
    }
};
#endif

void __fastcall TfrmMain::EdgeBrowserDownloadStarting(TCustomEdgeBrowser *Sender, TDownloadStartingEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowserDownloadStarting");
#endif
    _di_ICoreWebView2Deferral Deferral;
    if (SUCCEEDED(Args->ArgsInterface->GetDeferral(Deferral)))
    {
        _di_ICoreWebView2DownloadStartingEventArgs ArgsInterface = Args->ArgsInterface;
        // We avoid potential reentrancy from running a message loop in the download
        // starting event handler by showing our download dialog later when we
        // complete the deferral asynchronously.
        // Note that a long running synchronous UI prompt or other blocking item on
        // the UI thread can potentially block the WebView2 from doing anything.
        TThread::ForceQueue(NULL,
        #ifdef __clang__
            // Use a lambda
            [this, Deferral, ArgsInterface]()
            {
                _di_ICoreWebView2DownloadOperation Download;
                __int64 TotalBytesToReceive;
                wchar_t *URI;
                wchar_t *MimeType;
                wchar_t *ContentDisposition;
                wchar_t *ResultFilePath;
                if (SUCCEEDED(ArgsInterface->Set_Handled(true)) &&
                    SUCCEEDED(ArgsInterface->Get_DownloadOperation(Download)) &&
                    SUCCEEDED(Download->Get_TotalBytesToReceive(TotalBytesToReceive)) &&
                    SUCCEEDED(Download->Get_uri(URI)) &&
                    SUCCEEDED(Download->Get_MimeType(MimeType)) &&
                    SUCCEEDED(Download->Get_ContentDisposition(ContentDisposition)) &&
                    SUCCEEDED(Download->Get_ResultFilePath(ResultFilePath))
                )
                {
                    String Description = String().sprintf(L"URI: %s\r\nMime type: %s\r\n", URI, MimeType);
                    if (TotalBytesToReceive > 0)
                        Description += String().sprintf(L"Total bytes to receive: %u\r\n", TotalBytesToReceive);
                      Description +=
                        L"Enter result file path or select `OK` to use default path. Select `Cancel` to cancel the download.";
                    String FilePath = ResultFilePath;
                    if (InputQuery(L"Download Starting", Description, FilePath))
                    {
                        // If user selects OK, the download will complete normally.
                        // Result file path will be updated if a new one was provided.
                        ArgsInterface->Set_ResultFilePath(FilePath.w_str());
                        UpdateDownloadProgress(Download);
                    }
                    else
                    {
                        // If user selects Cancel, the download will be canceled.
                        ArgsInterface->Set_Cancel(true);
                    }
                }
                // Now complete the deferral
                Deferral->Complete();
            }
        #else
            _di_TThreadProcedure(new TDownloadDialog(this, Deferral, ArgsInterface))
        #endif
          );
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EdgeBrowserExecuteScript(TCustomEdgeBrowser* Sender, HRESULT AResult, const System::UnicodeString AResultObjectAsJson)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnExecuteScript");
#endif
    String Msg = String().sprintf(L"'The script has completed:\nResult = 0x%X\nResultObject = %s",
        AResult, AResultObjectAsJson.c_str());
    Application->MessageBox(Msg.c_str(), L"Script execution", MB_OK);
}

bool ShouldBlockURI(String Uri)
{
    std::unique_ptr<TIdURI> URI(new TIdURI(Uri));
    // For no particular reason, block Google's main English sites
    String Host = URI->Host.LowerCase();
    if (EndsStr(L"yahoo.com", Host) || EndsStr(L"yahoo.co.uk", Host))
        return true;
    return false;
}

// This handler will prevent a frame from navigating to a blocked domain.
void __fastcall TfrmMain::EdgeBrowserFrameNavigationStarting(TCustomEdgeBrowser* Sender,
   TNavigationStartingEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnFrameNavigationStarting");
#endif
    WideChar *Uri;
    if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) && ShouldBlockURI(Uri))
        Args->ArgsInterface->Set_Cancel(TRUE);
    CoTaskMemFree(Uri);
}

void __fastcall TfrmMain::EdgeBrowserFrameNavigationCompleted(TCustomEdgeBrowser *Sender, bool IsSuccess, COREWEBVIEW2_WEB_ERROR_STATUS WebErrorStatus)

{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnFrameNavigationCompleted");
#endif
    if (!IsSuccess && WebErrorStatus == COREWEBVIEW2_WEB_ERROR_STATUS_DISCONNECTED)
    {
        // Do something here if you want to handle a specific error case.
        // In most cases this isn't necessary, because the WebView will
        // display its own error page automatically.
    }
    tbCancel->Enabled = False;
}

void __fastcall TfrmMain::EdgeBrowserHistoryChanged(TCustomEdgeBrowser* Sender)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnHistoryChanged");
#endif
    tbBack->Enabled = EdgeBrowser->CanGoBack;
    tbForward->Enabled = EdgeBrowser->CanGoForward;
}

void __fastcall TfrmMain::EdgeBrowserNavigationStarting(TCustomEdgeBrowser* Sender,
    TNavigationStartingEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnNavigationStarting");
#endif
    tbCancel->Enabled = true;
    WideChar *Uri;
    if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) && ShouldBlockURI(Uri))
    {
        tbCancel->Enabled = false;
        Args->ArgsInterface->Set_Cancel(true);
        // UserInitiated is true on clicking a link, but false on use of the address bar
        BOOL UserInitiated;
        if (SUCCEEDED(Args->ArgsInterface->Get_IsUserInitiated(UserInitiated)) && UserInitiated)
            Sender->NavigateToString(
                L"<h1>Domain Blocked</h1>"
                L"<p>You've attempted to navigate to a domain in the blocked "
                L"sites list. Press back to return to the previous page.</p>");
        else
            Sender->NavigateToString(
                L"<h1>Domain Blocked</h1>"
                L"<p>That domain is in the blocked sites list. "
                L"Press back to return to the previous page.</p>");
    }
    else
        Args->ArgsInterface->Set_Cancel(false);
    if (String(Uri) == L"about:blank")
        edtAddress->Text = L"";
    else
        edtAddress->Text = Uri;
    CoTaskMemFree(Uri);
}

void __fastcall TfrmMain::EdgeBrowserNavigationCompleted(TCustomEdgeBrowser* Sender,
    bool IsSuccess, COREWEBVIEW2_WEB_ERROR_STATUS WebErrorStatus)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnNavigationCompleted");
#endif
    if (!IsSuccess && WebErrorStatus == COREWEBVIEW2_WEB_ERROR_STATUS_DISCONNECTED)
    {
        // Do something here if you want to handle a specific error case.
        // In most cases this isn't necessary, because the WebView will
        // display its own error page automatically.
    }
    tbCancel->Enabled = False;
    FPostDataIStream = NULL;
    if (FPostDataMemStream)
    {
        delete FPostDataMemStream;
        FPostDataMemStream = NULL;
    }
    FWebResourceRequest = NULL;
}

void __fastcall TfrmMain::EdgeBrowserNewWindowRequested(TCustomEdgeBrowser* Sender,
    TNewWindowRequestedEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnNewWindowRequested");
#endif
    if (MessageDlg("Allow new window", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) != mrYes)
        Args->ArgsInterface->Set_Handled(true);
}

static PCWSTR NameOfPermissionType(COREWEBVIEW2_PERMISSION_KIND type)
{
    switch (type)
    {
    case COREWEBVIEW2_PERMISSION_KIND_MICROPHONE:
        return L"Microphone";
    case COREWEBVIEW2_PERMISSION_KIND_CAMERA:
        return L"Camera";
    case COREWEBVIEW2_PERMISSION_KIND_GEOLOCATION:
        return L"Geolocation";
    case COREWEBVIEW2_PERMISSION_KIND_NOTIFICATIONS:
        return L"Notifications";
    case COREWEBVIEW2_PERMISSION_KIND_OTHER_SENSORS:
        return L"Generic Sensors";
    case COREWEBVIEW2_PERMISSION_KIND_CLIPBOARD_READ:
        return L"Clipboard Read";
    default:
        return L"Unknown resources";
    }
}

void __fastcall TfrmMain::EdgeBrowserPermissionRequested(TCustomEdgeBrowser* Sender,
    TPermissionRequestedEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnPermissionRequested");
#endif

    // Go to a web page that requests permissions, e.g.:
    // https://whatwebcando.today/permissions.html

    // NOTE: camera & notification permission requests do not come through here
    // Without the event handler in place, the requests do not appear on-screen in Edge.
    // This _looks_ like a bug in the (pre-release) version of WebView2 used to set up this demo.

    WideChar *Uri;
    COREWEBVIEW2_PERMISSION_KIND Kind = COREWEBVIEW2_PERMISSION_KIND_UNKNOWN_PERMISSION;
    BOOL UserInitiated = FALSE;

    if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) &&
        SUCCEEDED(Args->ArgsInterface->Get_PermissionKind(Kind)) &&
        SUCCEEDED(Args->ArgsInterface->Get_IsUserInitiated(UserInitiated)))
    {
        String Msg = L"Do you want to grant permission for ";
        Msg += NameOfPermissionType(Kind);
        Msg += L" to the website at ";
        Msg += Uri;
        Msg += L"?\n\n";
        Msg += (UserInitiated
            ? L"This request came from a user gesture."
            : L"This request did not come from a user gesture.");
        int Response = Application->MessageBox(Msg.c_str(), L"Permission Request",
                                   MB_YESNO | MB_ICONWARNING);
        COREWEBVIEW2_PERMISSION_STATE State =
            Response == IDYES
              ? COREWEBVIEW2_PERMISSION_STATE_ALLOW
              : COREWEBVIEW2_PERMISSION_STATE_DENY;
        Args->ArgsInterface->Set_State(State);
        CoTaskMemFree(Uri);
    }
}

void __fastcall TfrmMain::EdgeBrowserProcessFailed(TCustomEdgeBrowser* Sender,
    COREWEBVIEW2_PROCESS_FAILED_KIND FailureType)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnProcessFailed");
#endif
    if (FailureType == COREWEBVIEW2_PROCESS_FAILED_KIND_BROWSER_PROCESS_EXITED)
    {
        int button = Application->MessageBox(
            L"Browser process exited unexpectedly. Recreate webview?",
            L"Browser process exited",
            MB_YESNO | MB_ICONQUESTION);
        if (button == IDYES)
            EdgeBrowser->ReinitializeWebView();
    }
}

void __fastcall TfrmMain::EdgeBrowserScriptDialogOpening(TCustomEdgeBrowser* Sender,
    TScriptDialogOpeningEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnScriptDialogOpening");
#endif

    // Go to a page with Javascript dialogs, e.g.:
    // https://www.tutorialspoint.com/javascript/javascript_dialog_boxes.htm
    WideChar *Uri;
    COREWEBVIEW2_SCRIPT_DIALOG_KIND Type;
    WideChar *Message;
    WideChar *DefaultText;

    if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) &&
        SUCCEEDED(Args->ArgsInterface->Get_Kind(Type)) &&
        SUCCEEDED(Args->ArgsInterface->Get_Message(Message)) &&
        SUCCEEDED(Args->ArgsInterface->Get_DefaultText(DefaultText)))
    {
        String Prompt = String().sprintf(L"The page at '%s' says:\n\n%s", Uri, Message);
        switch (Type)
        {
        case COREWEBVIEW2_SCRIPT_DIALOG_KIND_ALERT:
            Application->MessageBox(Prompt.c_str(), L"Script Dialog", MB_OK | MB_ICONWARNING);
            break;
        case COREWEBVIEW2_SCRIPT_DIALOG_KIND_CONFIRM:
            if (Application->MessageBox(Prompt.c_str(), L"Script Dialog",
                    MB_YESNO | MB_ICONQUESTION) == IDYES)
                Args->ArgsInterface->Accept();
            break;
        case COREWEBVIEW2_SCRIPT_DIALOG_KIND_PROMPT:
        {
            String Value = DefaultText;
            if (InputQuery(L"Script dialog", Prompt, Value))
                if (SUCCEEDED(Args->ArgsInterface->Set_ResultText(Value.c_str())))
                    Args->ArgsInterface->Accept();
        }
            break;
        }
        CoTaskMemFree(Uri);
        CoTaskMemFree(Message);
        CoTaskMemFree(DefaultText);
    }
}

void __fastcall TfrmMain::EdgeBrowserSourceChanged(TCustomEdgeBrowser* Sender, bool IsNewDocument)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnSourceChanged");
#endif
    edtAddress->Text = Sender->LocationURL;
}

void __fastcall TfrmMain::EdgeBrowserWebMessageReceived(TCustomEdgeBrowser* Sender,
    TWebMessageReceivedEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnWebMessageReceived");
#endif
    // TODO: for the reader to complete using knowledge of sending / receiving web messages
}

void __fastcall TfrmMain::EdgeBrowserWebResourceRequested(TCustomEdgeBrowser* Sender,
    TWebResourceRequestedEventArgs *Args)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnWebResourceRequested");
#endif
    // Go to any site that uses image references (e.g. google.com, not bing.com)
    if (FBlockImages)
    {
        COREWEBVIEW2_WEB_RESOURCE_CONTEXT ResourceContext;
        if (SUCCEEDED(
            Args->ArgsInterface->Get_ResourceContext(ResourceContext)))
        {
            // Ensure that the type is image
            if (ResourceContext != COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE)
                return;
            // Override the response with an empty one to block the image.
            // If Set_Response is not called, the request will continue as normal.
            _di_ICoreWebView2WebResourceResponse Response;
            if (SUCCEEDED(EdgeBrowser->EnvironmentInterface->CreateWebResourceResponse(
                NULL, 403 /*NoContent*/, (wchar_t *)L"Blocked", (wchar_t *)L"", Response)))
                Args->ArgsInterface->Set_Response(Response);
        }
    }
}

void __fastcall TfrmMain::EdgeBrowserWindowCloseRequested(TObject *Sender)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnWindowCloseRequested");
#endif

    // This one is tricky to test as it fires in response to window.close, but only on
    // a window that was seen to be opened through JavaScript, not through program control

    // A page with a Javascript call to window.close can be played with, e.g. the sample button on:
    // https://www.thesitewizard.com/javascripts/close-browser-tab-or-window.shtml
    // however due to the above that will not trigger this event handler
    Close();
}

void __fastcall TfrmMain::EdgeBrowserZoomFactorChanged(TCustomEdgeBrowser* Sender, double AZoomFactor)
{
#ifdef _DEBUG
    OutputDebugString(L"EdgeBrowser OnZoomFactorChanged");
#endif
    Caption = String().sprintf(L"WebView2APISample (Zoom: %d%)", (int)AZoomFactor * 100);
}

