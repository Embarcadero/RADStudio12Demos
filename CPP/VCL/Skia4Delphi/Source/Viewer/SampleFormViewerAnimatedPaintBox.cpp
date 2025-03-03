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

#include "SampleFormViewerAnimatedPaintBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmAnimatedPaintBoxViewer::apbDrawAnimationDraw(TObject* ASender,
	  ISkCanvas* const ACanvas, const TRectF& ADest, const double AProgress,
	  const float AOpacity)
{
	if (FDrawProc)
		FDrawProc(ACanvas, ADest, apbDraw->Animation->CurrentTime);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAnimatedPaintBoxViewer::apbDrawMouseMove(TObject* Sender,
	TShiftState Shift, int X, int Y)
{
	if (FOnMouseMove)
		FOnMouseMove(X / apbDraw->ScaleFactor, Y / apbDraw->ScaleFactor);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAnimatedPaintBoxViewer::FormClose(TObject* Sender,
	TCloseAction& Action)
{
	inherited::FormClose(Sender, Action);
	if (Action != TCloseAction::caNone) {
		apbDraw->Animation->StopAtCurrent();
		FDrawProc = nullptr;
		FOnMouseMove = nullptr;
	};
}
//---------------------------------------------------------------------------

TSize TfrmAnimatedPaintBoxViewer::GetDrawSize()
{
	return apbDraw->BoundsRect.Size;
}
//---------------------------------------------------------------------------

void TfrmAnimatedPaintBoxViewer::SetDrawSize(const TSize& AValue)
{
	apbDraw->SetBounds(0, 0, round(AValue.Width * apbDraw->ScaleFactor), round(AValue.Height * apbDraw->ScaleFactor));
}
//---------------------------------------------------------------------------

void TfrmAnimatedPaintBoxViewer::Show(const String ATitle,
	const String ADescription, const TAnimatedPaintBoxDrawProc ADrawProc,
	TViewerOptions* AOptions)
{
	Options = AOptions;
	FDrawProc = ADrawProc;
	apbDraw->Align = alClient;
	apbDraw->Redraw();
	apbDraw->Animation->Enabled = true;
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------

void TfrmAnimatedPaintBoxViewer::Show(const String ATitle,
	const String ADescription, int ADrawWidth, int ADrawHeight,
	const TAnimatedPaintBoxDrawProc ADrawProc, TViewerOptions* AOptions)
{
	Options = AOptions;
	FDrawProc = ADrawProc;
	apbDraw->Align = alNone;
	DrawSize = TSize(ADrawWidth, ADrawHeight);
	apbDraw->Redraw();
	apbDraw->Animation->Enabled = true;
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------
