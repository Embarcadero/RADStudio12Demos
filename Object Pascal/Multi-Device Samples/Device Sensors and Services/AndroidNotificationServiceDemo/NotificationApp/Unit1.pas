//---------------------------------------------------------------------------
// Copyright (c) 2016 Embarcadero Technologies, Inc. All rights reserved.  
//
// This software is the copyrighted property of Embarcadero Technologies, Inc. 
// ("Embarcadero") and its licensors. You may only use this software if you 
// are an authorized licensee of Delphi, C++Builder or RAD Studio 
// (the "Embarcadero Products").  This software is subject to Embarcadero's 
// standard software license and support agreement that accompanied your 
// purchase of the Embarcadero Products and is considered a Redistributable, 
// as such term is defined thereunder. Your use of this software constitutes 
// your acknowledgement of your agreement to the foregoing software license 
// and support agreement. 
//---------------------------------------------------------------------------
unit Unit1;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs, FMX.Controls.Presentation, FMX.StdCtrls,
  System.Notification, FMX.ScrollBox, FMX.Memo, FMX.Memo.Types;

type
  TForm1 = class(TForm)
    Button1: TButton;
    NotificationCenter1: TNotificationCenter;
    Memo1: TMemo;
    Label1: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure NotificationCenter1ReceiveLocalNotification(Sender: TObject; ANotification: TNotification);
  private const
    ServiceName = 'NotificationService';
  end;

var
  Form1: TForm1;

implementation

{$R *.fmx}

uses
  System.Android.Service, System.Permissions,
  Androidapi.Helpers, Androidapi.JNI.JavaTypes, Androidapi.JNI.OS,
  FMX.DialogService;

procedure TForm1.Button1Click(Sender: TObject);
begin
  if TOSVersion.Check(13, 0) then
  begin
    PermissionsService.RequestPermissions([JStringToString(TJManifest_permission.JavaClass.POST_NOTIFICATIONS)],
      procedure(const APermissions: TClassicStringDynArray; const AGrantResults: TClassicPermissionStatusDynArray)
      begin
        if (Length(AGrantResults) = 1) and (AGrantResults[0] = TPermissionStatus.Granted) then
          TLocalServiceConnection.StartService(ServiceName);
      end,
      procedure(const APermissions: TClassicStringDynArray; const APostRationaleProc: TProc)
      begin
        TDialogService.ShowMessage('The app needs permission to post notifications',
          procedure(const AResult: TModalResult)
          begin
            APostRationaleProc;
          end);
      end);
  end
  else
    TLocalServiceConnection.StartService(ServiceName);
end;

procedure TForm1.NotificationCenter1ReceiveLocalNotification(Sender: TObject; ANotification: TNotification);
begin
  Memo1.Lines.Add('Notification received:');
  Memo1.Lines.Add(ANotification.AlertBody);
end;

end.
