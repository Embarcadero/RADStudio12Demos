//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

unit FlashLightU;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants, System.Permissions,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Dialogs, FMX.StdCtrls, FMX.Effects,
  FMX.Objects, FMX.Layouts, FMX.Media;

type
  TFlashLightForm = class(TForm)
    FlashLight: TImage;
    ImageOn: TImage;
    FlashLightShadow: TShadowEffect;
    Light: TImage;
    ImageOff: TImage;
    ContainerLayout: TLayout;
    Camera: TCameraComponent;
    GlowEffect1: TGlowEffect;
    LayoutButtons: TLayout;
    procedure ImageOffClick(Sender: TObject);
    procedure ImageOnClick(Sender: TObject);
{$IF Defined(ANDROID)}
  private const
    CameraPermission = 'android.permission.CAMERA';
{$ENDIF}
  private
    procedure SetFlashlightState(Active: Boolean);
{$IF Defined(ANDROID)}
    procedure ActivateCameraPermissionRequestResult(Sender: TObject; const APermissions: TClassicStringDynArray; const AGrantResults: TClassicPermissionStatusDynArray);
    procedure DisplayRationale(Sender: TObject; const APermissions: TClassicStringDynArray; const APostRationaleProc: TProc);
{$ENDIF}
    procedure SetFlashlightOn;
  public
    { Public declarations }
  end;

var
  FlashLightForm: TFlashLightForm;

implementation

uses
  FMX.DialogService;

{$R *.fmx}
{$R *.LgXhdpiPh.fmx ANDROID}

procedure TFlashLightForm.SetFlashlightState(Active: Boolean);
begin
  if Active then
    Camera.TorchMode := TTorchMode.ModeOn
  else
    Camera.TorchMode := TTorchMode.ModeOff;
end;

{$IF Defined(ANDROID)}
procedure TFlashLightForm.ActivateCameraPermissionRequestResult(Sender: TObject; const APermissions: TClassicStringDynArray; const AGrantResults: TClassicPermissionStatusDynArray);
begin
  // 1 permission involved: CAMERA
  if (Length(AGrantResults) = 1) and (AGrantResults[0] = TPermissionStatus.Granted) then
    SetFlashlightOn
  else
    TDialogService.ShowMessage('Cannot access the camera flashlight because the required permission has not been granted');
end;

// Optional rationale display routine to display permission requirement rationale to the user
procedure TFlashLightForm.DisplayRationale(Sender: TObject; const APermissions: TClassicStringDynArray; const APostRationaleProc: TProc);
begin
  // Show an explanation to the user *asynchronously* - don't block this thread waiting for the user's response!
  // After the user sees the explanation, invoke the post-rationale routine to request the permissions
  TDialogService.ShowMessage('The app needs to access the camera in order to work',
    procedure(const AResult: TModalResult)
    begin
      APostRationaleProc;
    end)
end;
{$ENDIF}

procedure TFlashLightForm.ImageOffClick(Sender: TObject);
begin
{$IF Defined(ANDROID)}
  PermissionsService.RequestPermissions([CameraPermission], ActivateCameraPermissionRequestResult, DisplayRationale);
{$ELSE}
  SetFlashlightOn;
{$ENDIF}
end;

procedure TFlashLightForm.SetFlashlightOn;
begin
  if Camera.HasFlash then
  begin
    Camera.Active := True;
    ImageOff.Visible := False;
    ImageOn.Visible := True;
    SetFlashlightState(True);
    Light.Visible := True;
  end
  else
  begin
    ImageOff.Enabled := False;

    TDialogService.ShowMessage('Cannot turn the camera flashlight on');
  end;
end;

procedure TFlashLightForm.ImageOnClick(Sender: TObject);
begin
  ImageOff.Visible := True;
  ImageOn.Visible := False;
  SetFlashlightState(False);
  Light.Visible := False;
end;

end.
