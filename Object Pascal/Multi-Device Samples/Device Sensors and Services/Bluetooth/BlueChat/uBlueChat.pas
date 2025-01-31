//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

unit uBlueChat;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs, FMX.ListBox, FMX.StdCtrls, FMX.Edit,
  FMX.Layouts, FMX.Memo, System.Bluetooth, uChatManager, FMX.Controls.Presentation, uPairDevices,
  FMX.ScrollBox, FMX.Memo.Types, FMX.Objects;

type
  TFrmMainChatForm = class(TForm)
    MmReceived: TMemo;
    EdNewText: TEdit;
    BtSend: TButton;
    PnSelectDevice: TPanel;
    CbDevices: TComboBox;
    BtnUpdate: TButton;
    PnSend: TPanel;
    BtnFindNew: TButton;
    PnMain: TPanel;
    BackgroundImage: TImage;
    PanelLock: TPanel;
    LabelLock: TLabel;
    StyleBook1: TStyleBook;
    procedure FormShow(Sender: TObject);
    procedure BtnUpdateClick(Sender: TObject);
    procedure BtSendClick(Sender: TObject);
    procedure CbDevicesChange(Sender: TObject);
    procedure EdNewTextKeyUp(Sender: TObject; var Key: Word; var KeyChar: Char; Shift: TShiftState);
    procedure BtnFindNewClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormVirtualKeyboardShown(Sender: TObject; KeyboardVisible: Boolean; const Bounds: TRect);
    procedure FormVirtualKeyboardHidden(Sender: TObject; KeyboardVisible: Boolean; const Bounds: TRect);
{$IFDEF ANDROID}
  private const
    LOCATION_PERMISSION = 'android.permission.ACCESS_FINE_LOCATION';
    BLUETOOTH_SCAN_PERMISSION = 'android.permission.BLUETOOTH_SCAN';
    BLUETOOTH_CONNECT_PERMISSION = 'android.permission.BLUETOOTH_CONNECT';
{$ENDIF}
  private
    FChatManager: TChatManager;
    FLastName: string;
    procedure InitBluetoothWork;
    procedure OnNewText(const Sender: TObject; const AText: string; const aDeviceName: string);
  end;

var
  FrmMainChatForm: TFrmMainChatForm;

implementation

uses
  System.Permissions;

{$R *.fmx}

procedure TFrmMainChatForm.BtSendClick(Sender: TObject);
begin
  if cbDevices.Selected <> nil then
  begin
    FChatManager.SendText(EdNewText.Text);
    EdNewText.Text := '';
  end;
end;

procedure TFrmMainChatForm.BtnFindNewClick(Sender: TObject);
begin
  FrmPairdevices.Show;
end;

procedure TFrmMainChatForm.CbDevicesChange(Sender: TObject);
begin
  FChatManager.SelectedDevice := CbDevices.Selected.Index;
end;

procedure TFrmMainChatForm.EdNewTextKeyUp(Sender: TObject; var Key: Word; var KeyChar: Char; Shift: TShiftState);
begin
  if key = vkReturn then
    BtSendClick(BtSend);
end;

procedure TFrmMainChatForm.FormShow(Sender: TObject);
{$IFDEF ANDROID}
var
  Permissions: TArray<string>;
begin
  if TOSVersion.Check(12) then
    Permissions := [LOCATION_PERMISSION, BLUETOOTH_SCAN_PERMISSION, BLUETOOTH_CONNECT_PERMISSION]
  else
    Permissions := [LOCATION_PERMISSION];

  PermissionsService.RequestPermissions(Permissions,
    procedure(const APermissions: TClassicStringDynArray; const AGrantResults: TClassicPermissionStatusDynArray)
    begin
      for var GrantResult in AGrantResults do
        if GrantResult <> TPermissionStatus.Granted then
          Exit;

      InitBluetoothWork;
    end);
end;
{$ELSE}
begin
  InitBluetoothWork;
end;
{$ENDIF}

procedure TFrmMainChatForm.FormVirtualKeyboardHidden(Sender: TObject; KeyboardVisible: Boolean; const Bounds: TRect);
begin
  PnMain.align := TAlignLayout.Client;
end;

procedure TFrmMainChatForm.FormVirtualKeyboardShown(Sender: TObject; KeyboardVisible: Boolean; const Bounds: TRect);
begin
  PnMain.align := TAlignLayout.Top;
  PnMain.Height := ClientHeight - Bounds.Height;
  MmReceived.GoToTextEnd;
end;

procedure TFrmMainChatForm.InitBluetoothWork;
begin
  PanelLock.Visible := False;

  FChatManager := TChatManager.Create;
  if not FChatManager.HasBluetoothDevice then
  begin
    ShowMessage('You don''t have a bluetooth adapter');
    Application.Terminate;
  end;
  FChatManager.OnTextReceived := OnNewText;
  FChatManager.OnTextSent := OnNewText;

  FrmPairdevices.ChatManager := FChatManager;
  FrmPairdevices.OnHide := BtnUpdateClick;

  BtnUpdateClick(nil);
end;

procedure TFrmMainChatForm.OnNewText(const Sender: TObject; const AText, aDeviceName: string);
begin
  TThread.Synchronize(nil,
    procedure begin
      if FLastName <> aDeviceName then
      begin
        MmReceived.Lines.Add(' ' + aDeviceName + ' :');
        FLastName := aDeviceName;
      end;
      MmReceived.Lines.Add('     ' + AText);
      MmReceived.GoToTextEnd;
    end);
end;

procedure TFrmMainChatForm.BtnUpdateClick(Sender: TObject);
var
  I: Integer;
begin
  FChatManager.UpdateKnownDevices;
  CbDevices.Clear;
  if FChatManager.KnownDevices <> nil then
    for I := 0 to FChatManager.KnownDevices.Count - 1 do
      CbDevices.Items.Add(FChatManager.KnownDevices[I].DeviceName);
end;

procedure TFrmMainChatForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  FreeAndNil(FChatManager);
end;

end.
