//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SampleFormSplashScreen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void __fastcall TfrmSplashScreen::aimLogoForegroundAnimationFinish(
	TObject* Sender)
{
	fanFadeOut->Start();
}
//---------------------------------------------------------------------------

TAlphaColor TfrmSplashScreen::FormBackgroundColor()
{
	return inherited::FormBorderColor();
}
//---------------------------------------------------------------------------

bool TfrmSplashScreen::HasBottomContent()
{
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSplashScreen::rctContentPaint(TObject* Sender,
	TCanvas* Canvas, const TRectF& ARect)
{
	fanFadeIn->Enabled = true;
}
//---------------------------------------------------------------------------

