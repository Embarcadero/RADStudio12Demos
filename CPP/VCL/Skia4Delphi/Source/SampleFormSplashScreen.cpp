//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SampleFormSplashScreen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void PaintControl(TWinControl* AControl, TCanvas* const ACanvas,
	const TPoint& AOffset)
{
	SaveDC(ACanvas->Handle);
	try {
		SetWindowOrgEx(ACanvas->Handle, -(AControl->Left + AOffset.X), -(AControl->Top + AOffset.Y), nullptr);
		AControl->Perform(WM_PRINT, (NativeUInt) ACanvas->Handle, PRF_CHILDREN | PRF_CLIENT | PRF_ERASEBKGND);
	} __finally {
		RestoreDC(ACanvas->Handle, -1);
	}
}
//---------------------------------------------------------------------------

_di_ISkImage MakeScreenshot(TfrmBase* AForm)
{
	TBitmap* LBitmap = new TBitmap();
	try {
		LBitmap->SetSize(AForm->pnlContent->Width, AForm->pnlContent->Height);
		LBitmap->Canvas->Lock();
		try {
			PaintControl(AForm->pnlContent, LBitmap->Canvas, Point(0, 0));
		} __finally {
			LBitmap->Canvas->Unlock();
		}
		return BitmapToSkImage(LBitmap);
	} __finally {
		delete LBitmap;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSplashScreen::aimLogoForegroundAnimationFinish(
	TObject* Sender)
{
	TfrmBase* MainForm = (TfrmBase*) Application->MainForm;
	FFrontFormImage = MakeScreenshot(this);
	MainForm->pnlContent->Visible = true;
	try {
		FBackFormImage = MakeScreenshot(MainForm);
	} __finally {
		MainForm->pnlContent->Visible = false;
	}
	BeginUpdate();
	try {
		apbBackForm->BoundsRect = Rect(0, 0, pnlContent->Width, pnlContent->Height);
		apbBackForm->Align = alClient;
		apbBackForm->Parent = pnlContent->Parent;
		pnlContent->Visible = false;
		apbBackForm->Visible = true;
	} __finally {
		EndUpdate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSplashScreen::apbBackFormAnimationDraw(TObject* ASender,
	ISkCanvas* const ACanvas, const TRectF& ADest, const double AProgress,
	const float AOpacity)
{
	ACanvas->Save();
	try {
		ACanvas->Scale(1 / ((TSkAnimatedPaintBox*) ASender)->ScaleFactor, 1 / ((TSkAnimatedPaintBox*) ASender)->ScaleFactor);
		ACanvas->DrawImage(FBackFormImage, 0, 0);
		ACanvas->SaveLayerAlpha(round(255 * (1 - AProgress)));
		try {
			ACanvas->DrawImage(FFrontFormImage, 0, 0);
		} __finally {
			ACanvas->Restore();
		}
	} __finally {
		ACanvas->Restore();
	}
}
//---------------------------------------------------------------------------

TColor TfrmSplashScreen::FormBackgroundColor()
{
	return FormBorderColor();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSplashScreen::pnlContentAlignPosition(TWinControl* Sender,
	TControl* Control, int& NewLeft, int& NewTop, int& NewWidth, int& NewHeight,
	TRect& AlignRect, TAlignInfo& AlignInfo)
{
	if (Control == pnlLogo) {
		NewLeft = AlignRect.Left + ((AlignRect.Width() - Control->Width) / 2);
		NewTop = AlignRect.Top + ((AlignRect.Height() - Control->Height) / 2);
	}
}
//---------------------------------------------------------------------------
