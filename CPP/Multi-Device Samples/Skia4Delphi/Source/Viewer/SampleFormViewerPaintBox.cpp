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

#include "SampleFormViewerPaintBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
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

void __fastcall TfrmPaintBoxViewer::FormCreate(TObject* Sender)
{
    inherited::FormCreate(Sender);
	pbxDraw->AutoCapture = true;
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
	TMouseButton Button, TShiftState Shift, float X, float Y)
{
	FIsMouseDown = true;
	if (FOnMouseDown) {
		bool LShouldRedraw = false;
		FOnMouseDown(PointF(X, Y), LShouldRedraw);
		if (LShouldRedraw)
			pbxDraw->Redraw();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::pbxDrawMouseMove(TObject* Sender,
	TShiftState Shift, float X, float Y)
{
	if (FOnMouseMove) {
		bool LShouldRedraw = false;
		FOnMouseMove(PointF(X, Y), FIsMouseDown, LShouldRedraw);
		if (LShouldRedraw)
			pbxDraw->Redraw();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPaintBoxViewer::pbxDrawMouseUp(TObject* Sender,
	TMouseButton Button, TShiftState Shift, float X, float Y)
{
	if (FIsMouseDown && FOnMouseUp) {
		bool LShouldRedraw = false;
		FOnMouseUp(PointF(X, Y), LShouldRedraw);
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
	pbxDraw->Align = TAlignLayout::Client;
	pbxDraw->Redraw();
	AllowScrollBoundsAnimation = !(FOnMouseDown || FOnMouseMove || FOnMouseUp);
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------

void TfrmPaintBoxViewer::Show(const String ATitle, const String ADescription,
	const float ADrawWidth, const float ADrawHeight,
	const TPaintBoxDrawProc ADrawProc, TBackgroundKind ABackgroundKind,
	TViewerOptions* AOptions)
{
	BackgroundKind = ABackgroundKind;
	Options = AOptions;
	FDrawProc = ADrawProc;
	pbxDraw->Align = TAlignLayout::None;
	pbxDraw->Width = ADrawWidth;
	pbxDraw->Height = ADrawHeight;
	pbxDraw->Redraw();
	AllowScrollBoundsAnimation = !(FOnMouseDown || FOnMouseMove || FOnMouseUp);
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------

