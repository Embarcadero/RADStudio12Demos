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

#include "SampleFormBasics.h"
#include "SampleFormViewerPaintBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmBasics::pnlCurvesClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Curves", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LPaint = SkPaint(TSkPaintStyle::Stroke);
			LPaint->StrokeWidth = 8;
			LPaint->Color = 0xFF4285F4;
			LPaint->AntiAlias = true;
			LPaint->StrokeCap = TSkStrokeCap::Round;

			auto LPathBuilder = SkPathBuilder();
			LPathBuilder->MoveTo(10, 10);
			LPathBuilder->QuadTo(256, 64, 128, 128);
			LPathBuilder->QuadTo(10, 192, 250, 250);
			auto LPath = LPathBuilder->Detach();
			ACanvas->DrawPath(LPath, LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmBasics::pnlEllipsesAndRectanglesClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Ellipses & Rectangles", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;

			LPaint->Color = 0xFF4285F4;
			TRectF LRect = TRectF(PointF(10, 10), 100, 160);
			ACanvas->DrawRect(LRect, LPaint);

			auto LOval = SkRoundRect();
			LOval->SetOval(LRect);
			LOval->Offset(40, 80);
			LPaint->Color = 0xFFDB4437;
			ACanvas->DrawRoundRect(LOval, LPaint);

			LPaint->Color = 0xFF0F9D58;
			ACanvas->DrawCircle(180, 50, 25, LPaint);

			LRect.Offset(80, 50);
			LPaint->Color = 0xFFF4B400;
			LPaint->Style = TSkPaintStyle::Stroke;
			LPaint->StrokeWidth = 4;
			ACanvas->DrawRoundRect(LRect, 10, 10, LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmBasics::pnlHatchingClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Hatching", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			static const float LinesDegree = 45.0f;
			static const int LinesDistance = 8;
			static const int LineSize = 1;

			TMatrix LLattice = TMatrix::CreateRotation(DegToRad(LinesDegree)) * TMatrix::CreateScaling(LinesDistance, LinesDistance);
			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;

			LPaint->PathEffect = TSkPathEffect::Make2DLine(LineSize, LLattice);
			TRectF LDest = ADest;
			ACanvas->Save();
			try {
				ACanvas->ClipRect(LDest);
				LDest.Inflate(LinesDistance, LinesDistance);
				ACanvas->DrawRect(LDest, LPaint);
			} __finally {
				ACanvas->Restore();
			}
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBasics::pnlTransformationsClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Translations & Rotations", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			ACanvas->Translate(128, 0);
			ACanvas->Rotate(60);
			TRectF LRect = RectF(0, 0, 200, 100);

			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;
			LPaint->Color = 0xFF4285F4;
			ACanvas->DrawRect(LRect, LPaint);

			ACanvas->Rotate(20);
			LPaint->Color = 0xFFDB4437;
			ACanvas->DrawRect(LRect, LPaint);
		});
}
//---------------------------------------------------------------------------
