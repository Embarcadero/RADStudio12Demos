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

#include "SampleFormViewerControl.h"
#include "SampleFormControlsTSkPaintBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

class TFreehandRender
{
private:
	_di_ISkPath FCurrentPath;
	TPointF FLastPoint;
	DynamicArray<_di_ISkPath> FOldPaths;
	_di_ISkPathBuilder FPathBuilder;
	bool FPressed;
public:
	void __fastcall OnDraw(TObject* ASender, const _di_ISkCanvas ACanvas, const TRectF& ADest, const float AOpacity);
	void __fastcall OnMouseDown(TObject* ASender, TMouseButton AButton, TShiftState AShift, int X, int Y);
	void __fastcall OnMouseLeave(TObject* ASender);
	void __fastcall OnMouseMove(TObject* ASender, TShiftState AShift, int X, int Y);
	void __fastcall OnMouseUp(TObject* ASender, TMouseButton AButton, TShiftState AShift, int X, int Y);
};

static std::unique_ptr<TFreehandRender> FFreehandRender;

void __fastcall TfrmTSkPaintBox::OnSweepGradientDraw(TObject* ASender,
	const _di_ISkCanvas ACanvas, const TRectF& ADest, const float AOpacity)
{
	auto LPaint = SkPaint();
	LPaint->Shader = TSkShader::MakeGradientSweep(ADest.CenterPoint(), {0xFFFCE68D, 0xFFF7CAA5, 0xFF2EBBC1, 0xFFFCE68D});
	ACanvas->DrawPaint(LPaint);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkPaintBox::pnlFreehandClick(TObject* Sender)
{
	FFreehandRender = std::unique_ptr<TFreehandRender>(new TFreehandRender());
	ChildForm<TfrmControlViewer>()->Show("Freehand / Signature", "Touch or click in screen and move to draw",
		[this]() {
			TSkPaintBox* LPaintBox = new TSkPaintBox(nullptr);
			LPaintBox->Align = alClient;
			LPaintBox->OnDraw = FFreehandRender->OnDraw;
			LPaintBox->OnMouseDown = FFreehandRender->OnMouseDown;
			LPaintBox->OnMouseMove = FFreehandRender->OnMouseMove;
			LPaintBox->OnMouseUp = FFreehandRender->OnMouseUp;
			LPaintBox->OnMouseLeave = FFreehandRender->OnMouseLeave;
			return LPaintBox;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkPaintBox::pnlSweepGradientClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Sweep Gradient", "",
		[this]() {
			TSkPaintBox* LPaintBox = new TSkPaintBox(nullptr);
			LPaintBox->Align = alClient;
			LPaintBox->OnDraw = OnSweepGradientDraw;
			return LPaintBox;
		});
}
//---------------------------------------------------------------------------

void __fastcall TFreehandRender::OnDraw(TObject* ASender,
	const _di_ISkCanvas ACanvas, const TRectF& ADest, const float AOpacity)
{
	ACanvas->Save();
	try {
		ACanvas->ClipRect(ADest);
		auto LPaint = SkPaint(TSkPaintStyle::Stroke);
		LPaint->AntiAlias = true;
		LPaint->Color = TAlphaColors::Royalblue;
		LPaint->SetPathEffect(TSkPathEffect::MakeCorner(50));
		LPaint->StrokeCap = TSkStrokeCap::Round;
		LPaint->StrokeWidth = 4;

		for (auto LPath : FOldPaths)
			ACanvas->DrawPath(LPath, LPaint);
		if ((FPathBuilder) && !(FCurrentPath))
			FCurrentPath = FPathBuilder->Snapshot();
		if (FCurrentPath)
			ACanvas->DrawPath(FCurrentPath, LPaint);
	} __finally {
		ACanvas->Restore();
	};
}
//---------------------------------------------------------------------------

void __fastcall TFreehandRender::OnMouseDown(TObject* ASender,
	TMouseButton AButton, TShiftState AShift, int X, int Y)
{
	FPressed = true;
	FPathBuilder = SkPathBuilder();
	FLastPoint = PointF(X, Y) / ((TSkPaintBox*) ASender)->ScaleFactor;
	FPathBuilder->MoveTo(FLastPoint.X, FLastPoint.Y);
	FCurrentPath = nullptr;
}
//---------------------------------------------------------------------------

void __fastcall TFreehandRender::OnMouseLeave(TObject* ASender)
{
	if (FPathBuilder) {
		if (!FCurrentPath)
			FCurrentPath = FPathBuilder->Snapshot();
		FOldPaths.Length = FOldPaths.Length + 1;
		FOldPaths[FOldPaths.High] = FCurrentPath;
		FPathBuilder = nullptr;
		FCurrentPath = nullptr;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFreehandRender::OnMouseMove(TObject* ASender,
	TShiftState AShift, int X, int Y)
{
	static const int MinPointsDistance = 5;
	TPointF LPoint = PointF(X, Y) / ((TSkPaintBox*) ASender)->ScaleFactor;
	if (FPressed && (FPathBuilder) && (FLastPoint.Distance(LPoint) >= MinPointsDistance)) {
		FCurrentPath = nullptr;
		FPathBuilder->LineTo(LPoint.X, LPoint.Y);
		FLastPoint = LPoint;
		((TSkPaintBox*) ASender)->Redraw();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFreehandRender::OnMouseUp(TObject* ASender,
	TMouseButton AButton, TShiftState AShift, int X, int Y)
{
	OnMouseLeave(ASender);
}
//---------------------------------------------------------------------------
