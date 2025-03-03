//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#include <fmx.h>
#include <System.Permissions.hpp>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button1Click(TObject *Sender)
{
  if (FisScanning)
  {
	FBeaconManager->StopScan();
	Button1->Text = "START";
	FisScanning = False;
  }
  else
  {
	StartScan();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormShow(TObject *Sender)
{
  if (!FBeaconManager)
  {
    FBeaconManager = TBeaconManager::GetBeaconManager(TBeaconScanMode::Standard);
    FBeaconManager->OnBeaconProximity = BeaconProximity;
  }

  TGUID GUID = StringToGUID("{B9407F30-F5F8-466E-AFF9-25556B57FE6D}");

  FBeaconManager->RegisterBeacon(GUID);
  FBeaconManager->CalcMode = TBeaconCalcMode::Raw;
  FBeaconManager->ScanningTime = 109;
  FBeaconManager->ScanningSleepingTime = 15;

  StartScan();
}
//---------------------------------------------------------------------------

MyThreadProcedure::MyThreadProcedure(_di_IBeacon const _ABeacon, TBeaconProximity _Proximity) :
	ABeacon(_ABeacon),
	Proximity(_Proximity)
{
}

void __fastcall MyThreadProcedure::Invoke(void)
{
	switch (ABeacon->Major)
	{
	  case 10: Form5->Fill->Color = (TAlphaColor)TAlphaColorRec::Springgreen; break;
	  case 20: Form5->Fill->Color = (TAlphaColor)TAlphaColorRec::Slateblue; break;
	  case 30: Form5->Fill->Color = (TAlphaColor)TAlphaColorRec::Aqua; break;
	}
	Form5->Company->Text = "Estimote";
	Form5->BeaconType->Text = "iBeacon";
	Form5->MajorMinor->Text = "Major: " + IntToStr(ABeacon->Major) + " Minor: " + IntToStr(ABeacon->Minor);
}


void __fastcall TForm5::BeaconProximity(System::TObject* const Sender, _di_IBeacon const ABeacon, TBeaconProximity Proximity)
{
  if (Proximity == TBeaconProximity::Immediate)
  {
	_di_TThreadProcedure mtp = new MyThreadProcedure(ABeacon, Proximity);
	System::Classes::TThread::Synchronize(NULL, mtp);
  }
}
//---------------------------------------------------------------------------
void TForm5::StartScan()
{
  DynamicArray<UnicodeString> permissions;

  if (TOSVersion::Check(12))
  {
    permissions = { LOCATION_PERMISSION, BLUETOOTH_SCAN_PERMISSION, BLUETOOTH_CONNECT_PERMISSION };
  }
  else
  {
    permissions = { LOCATION_PERMISSION };
  }

  PermissionsService()->RequestPermissions(permissions,
    [this](const TClassicStringDynArray Permissions, const TClassicPermissionStatusDynArray GrantResults)
    {
      if ((GrantResults.Length == 3 && GrantResults[0] == TPermissionStatus::Granted
                                    && GrantResults[1] == TPermissionStatus::Granted
                                    && GrantResults[2] == TPermissionStatus::Granted) ||
          (GrantResults.Length == 1 && GrantResults[0] == TPermissionStatus::Granted))
      {
        FBeaconManager->StartScan();
        Button1->Text = "STOP";
        FisScanning = True;
      }
    });
}
//---------------------------------------------------------------------------
