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

#include "SampleFormViewerPaintBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::FormClose(TObject* Sender,
	TCloseAction& Action)
{
	FDrawProc = nullptr;
	FOnMouseDown = nullptr;
	FOnMouseMove = nullptr;
	FOnMouseUp = nullptr;
	inherited::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void TfrmPaintBoxViewer::OptionsChanged()
{
	inherited::OptionsChanged();
	pbxDraw->Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::pbxDrawDraw(TObject* ASender,
	ISkCanvas* const ACanvas, const TRectF& ADest, const float AOpacity)
{
	if (FDrawProc)
		FDrawProc(ACanvas, ADest);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::pbxDrawMouseDown(TObject* Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	FIsMouseDown = true;
	if (FOnMouseDown) {
		bool LShouldRedraw = false;
		FOnMouseDown(PointF(X, Y) / pbxDraw->ScaleFactor, LShouldRedraw);
		if (LShouldRedraw)
			pbxDraw->Redraw();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::pbxDrawMouseMove(TObject* Sender,
	TShiftState Shift, int X, int Y)
{
	if (FOnMouseMove) {
		bool LShouldRedraw = false;
		FOnMouseMove(PointF(X, Y) / pbxDraw->ScaleFactor, FIsMouseDown, LShouldRedraw);
		if (LShouldRedraw)
			pbxDraw->Redraw();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::pbxDrawMouseUp(TObject* Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (FIsMouseDown && FOnMouseUp) {
		bool LShouldRedraw = false;
		FOnMouseUp(PointF(X, Y) / pbxDraw->ScaleFactor, LShouldRedraw);
		if (LShouldRedraw)
			pbxDraw->Redraw();
	}
}
//---------------------------------------------------------------------------

void TfrmPaintBoxViewer::Show(const String ATitle, const String ADescription,
	const TPaintBoxDrawProc ADrawProc, TBackgroundKind ABackgroundKind,
	TViewerOptions* AOptions)
{
	BackgroundKind = ABackgroundKind;
	Options = AOptions;
	FDrawProc = ADrawProc;
	pbxDraw->Align = alClient;
	pbxDraw->Redraw();
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------

void TfrmPaintBoxViewer::Show(const String ATitle, const String ADescription,
	const int ADrawWidth, const int ADrawHeight,
	const TPaintBoxDrawProc ADrawProc, TBackgroundKind ABackgroundKind,
	TViewerOptions* AOptions)
{
	BackgroundKind = ABackgroundKind;
	Options = AOptions;
	FDrawProc = ADrawProc;
	pbxDraw->Align = alNone;
	pbxDraw->Width = round(ADrawWidth * pbxDraw->ScaleFactor);
	pbxDraw->Height = round(ADrawHeight * pbxDraw->ScaleFactor);
	pbxDraw->Redraw();
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------
