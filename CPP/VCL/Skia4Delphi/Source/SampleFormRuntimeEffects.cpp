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

#include <System.IOUtils.hpp>
#include "SampleFormViewerAnimatedPaintBox.h"
#include "SampleFormRuntimeEffects.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmRuntimeEffects::pnlStarNestShaderAnimationClick(TObject* Sender)
{
	auto LEffect = TSkRuntimeEffect::MakeForShader(TFile::ReadAllText(AssetsPath + Ioutils::TPath::Combine("RuntimeEffects Shaders", "star-nest.sksl")));
	auto LEffectBuilder = SkRuntimeShaderBuilder(LEffect);
	
	ChildForm<TfrmAnimatedPaintBoxViewer>()->OnMouseMove =
		[this, LEffectBuilder](const float AX, const float AY) {
			LEffectBuilder->SetUniform("iMouse", PointF(AX, AY));
		};
	
	ChildForm<TfrmAnimatedPaintBoxViewer>()->Show("Star Nest Shader Animation", "Shader that varies with time (iTime uniform) and mouse position (iMouse uniform)",
		[this, LEffectBuilder](ISkCanvas* const ACanvas, const TRectF& ADest, const Double ASeconds) {
			LEffectBuilder->SetUniform("iResolution", PointF(ADest.Width(), ADest.Height()));
			LEffectBuilder->SetUniform("iTime", (float) ASeconds);
			auto LPaint = SkPaint();
			LPaint->Shader = LEffectBuilder->MakeShader();
			ACanvas->DrawPaint(LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmRuntimeEffects::pnlShaderWithMouseClick(TObject* Sender)
{
	auto LEffect = TSkRuntimeEffect::MakeForShader(TFile::ReadAllText(AssetsPath + Ioutils::TPath::Combine("RuntimeEffects Shaders", "mouse.sksl")));
	auto LEffectBuilder = SkRuntimeShaderBuilder(LEffect);

	ChildForm<TfrmAnimatedPaintBoxViewer>()->OnMouseMove =
		[this, LEffectBuilder](const float AX, const float AY) {
			LEffectBuilder->SetUniform("iMouse", PointF(AX, AY));
		};

	ChildForm<TfrmAnimatedPaintBoxViewer>()->Show("Shader with Mouse", "Shader that varies with mouse position (iMouse uniform)",
		[this, LEffectBuilder](ISkCanvas* const ACanvas, const TRectF& ADest, const Double ASeconds) {
			LEffectBuilder->SetUniform("iResolution", PointF(ADest.Width(), ADest.Height()));
			auto LPaint = SkPaint();
			LPaint->Shader = LEffectBuilder->MakeShader();
			ACanvas->DrawPaint(LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmRuntimeEffects::pnlTimeVaryingShaderClick(TObject* Sender)
{
	auto LEffect = TSkRuntimeEffect::MakeForShader(TFile::ReadAllText(AssetsPath + Ioutils::TPath::Combine("RuntimeEffects Shaders", "time.sksl")));
	auto LEffectBuilder = SkRuntimeShaderBuilder(LEffect);
	LEffectBuilder->SetUniform("iColor1", TAlphaColorF::Create(0xffa22a2a));
	LEffectBuilder->SetUniform("iColor2", TAlphaColorF::Create(0xff187735));
	ChildForm<TfrmAnimatedPaintBoxViewer>()->Show("Time-varying Shader", "Example of a simple shader varying the color according to time (iTime uniform)",
		[this, LEffectBuilder](ISkCanvas* const ACanvas, const TRectF& ADest, const Double ASeconds) {
			LEffectBuilder->SetUniform("iTime", (float) ASeconds);
			auto LPaint = SkPaint();
			LPaint->Shader = LEffectBuilder->MakeShader();
			ACanvas->DrawPaint(LPaint);
		});
}
//---------------------------------------------------------------------------
