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
#include "SampleFormPathsAndEffects.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

_di_ISkPath StarPath()
{
	static const float C = 128.0;
	static const float R = 115.2;
	auto LPathBuilder = SkPathBuilder();
	LPathBuilder->MoveTo(C + R, C);
	for (int i = 1; i <= 7; i++) {
		float A = 2.6927937 * i;
		LPathBuilder->LineTo(C + R * Cos(A), C + R * Sin(A));
	}
	return LPathBuilder->Detach();
}
//---------------------------------------------------------------------------

_di_ISkPath HeptagonPath(const TRectF ABounds)
{
	static const int VerticesCount = 7;

	float LRadius = 0.45 * Min(ABounds.Width(), ABounds.Height());
	TPolygon LPolygon;
	LPolygon.Length = VerticesCount;
	double LVertexAngle = -0.5 * M_PI;
	for (int i = 0; i < LPolygon.Length; i++) {
		LPolygon[i] = PointF(LRadius * Cos(LVertexAngle), LRadius * Sin(LVertexAngle));
		LVertexAngle = LVertexAngle + (2 * M_PI / VerticesCount);
	}

	auto LPathBuilder = SkPathBuilder();
	LPathBuilder->AddPolygon(LPolygon, True);
	LPathBuilder->Offset(ABounds.CenterPoint().X, ABounds.CenterPoint().Y);
	return LPathBuilder->Detach();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPathsAndEffects::btnComposedPathEffectClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Composed Path Effect", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LDashPathEffect = TSkPathEffect::MakeDash({10, 5, 2, 5}, 0);
			auto LDiscretePathEffect = TSkPathEffect::MakeDiscrete(10, 4);
			auto LPaint = SkPaint(TSkPaintStyle::Stroke);
			LPaint->PathEffect = TSkPathEffect::MakeCompose(LDashPathEffect, LDiscretePathEffect);
			LPaint->StrokeWidth = 2;
			LPaint->AntiAlias = true;
			LPaint->Color = 0xFF4285F4;
			ACanvas->DrawPath(StarPath(), LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmPathsAndEffects::btnDiscretePathEffectClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Discrete Path Effect", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LPaint = SkPaint(TSkPaintStyle::Stroke);
			LPaint->PathEffect = TSkPathEffect::MakeDiscrete(10, 4);
			LPaint->StrokeWidth = 2;
			LPaint->AntiAlias = true;
			LPaint->Color = 0xFF4285F4;
			ACanvas->DrawPath(StarPath(), LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmPathsAndEffects::btnPathFillTypesClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Path Fill Types", "Example with EvenOdd fill type",
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			float LRadius = Min(ADest.Width(), ADest.Height()) / 4.f;

			auto LPathBuilder = SkPathBuilder(TSkPathFillType::EvenOdd);
			LPathBuilder->AddCircle(ADest.CenterPoint().X - LRadius / 2.f, ADest.CenterPoint().Y - LRadius / 2.f, LRadius);
			LPathBuilder->AddCircle(ADest.CenterPoint().X - LRadius / 2.f, ADest.CenterPoint().Y + LRadius / 2.f, LRadius);
			LPathBuilder->AddCircle(ADest.CenterPoint().X + LRadius / 2.f, ADest.CenterPoint().Y - LRadius / 2.f, LRadius);
			LPathBuilder->AddCircle(ADest.CenterPoint().X + LRadius / 2.f, ADest.CenterPoint().Y + LRadius / 2.f, LRadius);
			auto LPath = LPathBuilder->Detach();

			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;
			LPaint->Color = TAlphaColors::Cadetblue;
			ACanvas->DrawPath(LPath, LPaint);

			LPaint->Style = TSkPaintStyle::Stroke;
			LPaint->StrokeWidth = 8;
			LPaint->Color = TAlphaColors::Chocolate;
			ACanvas->DrawPath(LPath, LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmPathsAndEffects::btnRoundingSharpCornersClick(TObject* Sender)
{
   TViewerOptions* LOptions = new TViewerOptions();
   LOptions->AddFloat("Corner radius", 0, 1, 0.3);

   ChildForm<TfrmPaintBoxViewer>()->Show("Rounding Sharp Corners", "",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LPaint = SkPaint(TSkPaintStyle::Stroke);
			LPaint->Color = TAlphaColors::Indigo;
			LPaint->StrokeWidth = 6;
			LPaint->AntiAlias = true;
			LPaint->PathEffect = TSkPathEffect::MakeCorner(LOptions->Float["Corner radius"] * Min(ADest.Width(), ADest.Height()) / 4.f);
			ACanvas->DrawPath(HeptagonPath(ADest), LPaint);
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPathsAndEffects::btnShadersClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Shaders", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LPaint = SkPaint();
			LPaint->PathEffect = TSkPathEffect::MakeDiscrete(10, 4);
			LPaint->Shader = TSkShader::MakeGradientLinear(PointF(0, 0), PointF(256, 256), 0xFF4285F4, 0xFF0F9D58, TSkTileMode::Clamp);
			LPaint->AntiAlias = true;
			ACanvas->DrawPath(StarPath(), LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmPathsAndEffects::btnSumPathEffectClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Sum Path Effect", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LDashPathEffect1 = TSkPathEffect::MakeDiscrete(10, 4);
			auto LDashPathEffect2 = TSkPathEffect::MakeDiscrete(10, 4, 1245);
			auto LPaint = SkPaint(TSkPaintStyle::Stroke);
			LPaint->PathEffect = TSkPathEffect::MakeSum(LDashPathEffect1, LDashPathEffect2);
			LPaint->StrokeWidth = 2;
			LPaint->AntiAlias = true;
			LPaint->Color = 0xFF4285F4;
			ACanvas->DrawPath(StarPath(), LPaint);
		});
}
//---------------------------------------------------------------------------

