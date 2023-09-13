//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#include <fmx.h>
#include <FMX.DialogService.hpp>
#ifdef __ANDROID__
#include <Androidapi.Helpers.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <System.Permissions.hpp>
#endif
#pragma hdrstop

#include "LocationDemoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
#ifdef __ANDROID__
	FPermissionAccessCoarseLocation = JStringToString(TJManifest_permission::JavaClass->ACCESS_COARSE_LOCATION);
	FPermissionAccessFineLocation = JStringToString(TJManifest_permission::JavaClass->ACCESS_FINE_LOCATION);
#endif
}
#ifdef __ANDROID__
//---------------------------------------------------------------------------
void __fastcall TForm2::PermissionRequestResult(TObject *Sender, const TClassicStringDynArray APermissions, const TClassicPermissionStatusDynArray AGrantResults)
{
	if ((AGrantResults.Length == 2) &&
		(AGrantResults[0] == TPermissionStatus::Granted) &&
		(AGrantResults[1] == TPermissionStatus::Granted)) {
		LocationSensor1->Active = Switch1->IsChecked;
	} else {
		Switch1->IsChecked = False;
		TDialogService::ShowMessage("Cannot define an location, because the required permissions are not all granted");
	}
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::DisplayRationale(TObject *Sender, const TClassicStringDynArray APermissions, const _di_TProc APostRationaleProc)
{
	String RationaleMsg;
	for (int i = 0; i < APermissions.Length; i++)
	{
		if (APermissions[i] == FPermissionAccessCoarseLocation)
			RationaleMsg = RationaleMsg + "The app needs to access the CoarseLocation for defining location" + sLineBreak + sLineBreak;
		else if (APermissions[i] == FPermissionAccessFineLocation)
			RationaleMsg = RationaleMsg + "The app needs to access the FineLocation for defining location";
	}

	// Show an explanation to the user *asynchronously* - don't block this thread waiting for the user's response!
	// After the user sees the explanation, invoke the post-rationale routine to request the permissions
	TDialogService::ShowMessage(RationaleMsg,
		[APostRationaleProc](TModalResult AKey)
		{
        	APostRationaleProc->Invoke();
		});
}
#endif
// ---------------------------------------------------------------------------
void __fastcall TForm2::Switch1Switch(TObject *Sender)
{
#ifdef __ANDROID__
	if (Switch1->IsChecked) {
		DynamicArray<String> permissions { FPermissionAccessCoarseLocation, FPermissionAccessFineLocation };
		PermissionsService()->RequestPermissions(permissions, PermissionRequestResult, DisplayRationale);
	} else {
		LocationSensor1->Active = false;
	}
#else
	LocationSensor1->Active = Switch1->IsChecked;
#endif
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OnGeocodeReverseEvent(TCivicAddress* const Address)
{
	if (Address != NULL){
		ListBoxItemAdminArea->ItemData->Detail       = Address->AdminArea;
		ListBoxItemCountryCode->ItemData->Detail     = Address->CountryCode;
		ListBoxItemCountryName->ItemData->Detail     = Address->CountryName;
		ListBoxItemFeatureName->ItemData->Detail     = Address->FeatureName;
		ListBoxItemLocality->ItemData->Detail        = Address->Locality;
		ListBoxItemPostalCode->ItemData->Detail      = Address->PostalCode;
		ListBoxItemSubAdminArea->ItemData->Detail    = Address->SubAdminArea;
		ListBoxItemSubLocality->ItemData->Detail     = Address->SubLocality;
		ListBoxItemSubThoroughfare->ItemData->Detail = Address->SubThoroughfare;
		ListBoxItemThoroughfare->ItemData->Detail    = Address->Thoroughfare;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm2::LocationSensor1LocationChanged(TObject *Sender, const TLocationCoord2D &OldLocation,
          const TLocationCoord2D &NewLocation)
{
	char LDecSeparator = FormatSettings.DecimalSeparator;
	FormatSettings.DecimalSeparator = '.';
	// Show current location
	ListBoxItemLatitude->ItemData->Detail =
		ListBoxItemLatitude->ItemData->Detail.sprintf(L"%2.6f", NewLocation.Latitude);
	ListBoxItemLongitude->ItemData->Detail =
		ListBoxItemLongitude->ItemData->Detail.sprintf(L"%2.6f", NewLocation.Longitude);
	// Show Map using Google Maps
	String LLongitude = FloatToStr(NewLocation.Longitude, FormatSettings);
	String URLString = "";
	URLString = URLString.sprintf(L"https://maps.google.com/maps?q=%2.6f,%2.6f",
		NewLocation.Latitude, NewLocation.Longitude);

	FormatSettings.DecimalSeparator = LDecSeparator;
	WebBrowser1->Navigate(URLString);

	// Setup an instance of TGeocoder
	try {

		if (FGeocoder == NULL) {
			if (TGeocoder::Current != NULL) {
				FGeocoder = (TGeocoder*)new TGeocoderClass(TGeocoder::Current);
			}
			if (FGeocoder != NULL) {
				FGeocoder->OnGeocodeReverse = OnGeocodeReverseEvent;
			}
		}
		// Translate location to address
		if ((FGeocoder != NULL) && (!(FGeocoder->Geocoding()))) {
			FGeocoder->GeocodeReverse(NewLocation);
		}
	} catch (...) {
        ListBoxGroupHeader1->Text = "Geocoder service error";
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
	MultiView1->HideMaster();
}
//---------------------------------------------------------------------------

