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
#include "SampleFormFilter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

static const String PhotoFileName = "photo.webp";

void __fastcall TfrmFilter::btnBrightnessContrastClick(TObject* Sender)
{
/* Using SkColorFilter is the simplest way of this example, but using shaders is the fastest way, so here
  we've added the "Brightness & Contrast" example using both, but in the demo we are using the faster way (shaders).
  Example of brightness and contrast using SkColorFilter:

	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("Brightness", -1, 1, 0, 0.01);
	LOptions->AddFloat("Contrast", -1, 1, 0, 0.01);
	LOptions->Bool["IsMouseDown"] = false;

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Brightness & Contrast", "Press the photo to show the original",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {

			TSkColorMatrix LBrightnessMatrix = TSkColorMatrix::Identity();
			LBrightnessMatrix.M15 = LOptions->Float["Brightness"];
			LBrightnessMatrix.M25 = LBrightnessMatrix.M15;
			LBrightnessMatrix.M35 = LBrightnessMatrix.M15;
			auto LBrightnessFilter = TSkColorFilter::MakeMatrix(LBrightnessMatrix);
			auto LContrastFilter = TSkColorFilter::MakeHighContrast(TSkHighContrastConfig(false, TSkContrastInvertStyle::NoInvert, LOptions->Float["Contrast"]));

			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + PhotoFileName);
			auto LImageDest = RectF(0, 0, LImage->Width, LImage->Height).FitInto(ADest);
			auto LPaint = SkPaint();

			if (!LOptions->Bool["IsMouseDown"])
				LPaint->ColorFilter = TSkColorFilter::MakeCompose(LContrastFilter, LBrightnessFilter);
			ACanvas->DrawImageRect(LImage, LImageDest, TSkSamplingOptions::Medium(), LPaint);
		}, TBackgroundKind::Chess, LOptions);
*/

	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("Brightness", -1, 1, 0, 0.01);
	LOptions->AddFloat("Contrast", -1, 1, 0, 0.01);
	LOptions->Bool["IsMouseDown"] = false;

	auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + PhotoFileName);
	auto LEffect = TSkRuntimeEffect::MakeForShader(
		"uniform shader texture;                                        \
		 uniform float brightness;                                      \
		 uniform float contrast;                                        \
		 half4 main(vec2 fragCoord) {                                   \
			vec4 color = texture.eval(fragCoord);                       \
			color.rgb += brightness;                                    \
			if (contrast > 0.0) {                                       \
				color.rgb = (color.rgb - 0.5) / (1.0 - contrast) + 0.5; \
			} else {                                                    \
				color.rgb = (color.rgb - 0.5) * (1.0 + contrast) + 0.5; \
			}                                                           \
			return color;                                               \
		 }");
	auto LEffectBuilder = SkRuntimeShaderBuilder(LEffect);
	LEffectBuilder->SetChild("texture", LImage->MakeShader(TSkSamplingOptions::Medium()));

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Brightness & Contrast", "Press the photo to show the original",
		[this, LOptions, LImage, LEffectBuilder](ISkCanvas* const ACanvas, const TRectF& ADest) {
			if (LOptions->Bool["IsMouseDown"]) {
				LEffectBuilder->SetUniform("brightness", 0);
				LEffectBuilder->SetUniform("contrast", 0);
			} else {
				LEffectBuilder->SetUniform("brightness", LOptions->Float["Brightness"]);
				LEffectBuilder->SetUniform("contrast", LOptions->Float["Contrast"]);
			}
			float LRatio;
			auto LImageDest = RectF(0, 0, LImage->Width, LImage->Height).FitInto(ADest, LRatio);
			ACanvas->Save();
			try {
				ACanvas->ClipRect(LImageDest);
				ACanvas->Scale(1.0 / LRatio, 1.0 / LRatio);
				ACanvas->Translate(LImageDest.Left * LRatio, LImageDest.Top * LRatio);
				auto LPaint = SkPaint();
				LPaint->Shader = LEffectBuilder->MakeShader();
				ACanvas->DrawPaint(LPaint);
			} __finally {
				ACanvas->Restore();
			}
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmFilter::btnCommonColorFilterClick(TObject* Sender)
{
	struct TFilterInfo {
		String Name;
		TSkColorMatrix Matrix;
	};
	static const DynamicArray<TFilterInfo> Filters {
		{ "None", { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Warm", { 1.06, 0, 0, 0, 0, 0, 1.01, 0, 0, 0, 0, 0, 0.93, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Cool", { 0.99, 0, 0, 0, 0, 0, 0.93, 0, 0, 0, 0, 0, 1.08, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Protanomaly", { 0.817, 0.183, 0, 0, 0, 0.333, 0.667, 0, 0, 0, 0, 0.125, 0.875, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Deuteranomaly", { 0.8, 0.2, 0, 0, 0, 0.258, 0.742, 0, 0, 0, 0, 0.142, 0.858, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Tritanomaly", { 0.967, 0.033, 0, 0, 0, 0, 0.733, 0.267, 0, 0, 0, 0.183, 0.817, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Protanopia", { 0.567, 0.433, 0, 0, 0, 0.558, 0.442, 0, 0, 0, 0, 0.242, 0.758, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Deuteranopia", { 0.625, 0.375, 0, 0, 0, 0.7, 0.3, 0, 0, 0, 0, 0.3, 0.7, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Tritanopia", { 0.95, 0.05, 0, 0, 0, 0, 0.433, 0.567, 0, 0, 0, 0.475, 0.525, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Achromatomaly", { 0.618, 0.320, 0.062, 0, 0, 0.163, 0.775, 0.062, 0, 0, 0.163, 0.320, 0.516, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Polaroid", { 1.438, -0.062, -0.062, 0, 0, -0.122, 1.378, -0.122, 0, 0, -0.016, -0.016, 1.483, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Koda Chrome", { 1.128, -0.396, -0.039, 0, 0.250, -0.164, 1.083, -0.054, 0, 0.097, -0.167, -0.560, 1.601, 0, 0.139, 0, 0, 0, 1, 0 } },
		{ "LOMO", { 1.2, 0.1, 0.1, 0, -0.287, 0, 1.2, 0.1, 0, -0.287, 0, 0.1, 1.1, 0, -0.287, 0, 0, 0, 1, 0 } },
		{ "Gothic", { 1.9, -0.3, -0.2, 0, -0.341, -0.2, 1.7, -0.1, 0, -0.341, -0.1, -0.6, 2.0, 0, -0.341, 0, 0, 0, 1.0, 0 } },
		{ "Elegant", { 0.6, 0.3, 0.1, 0, 0.287, 0.2, 0.7, 0.1, 0, 0.287, 0.2, 0.3, 0.4, 0, 0.287, 0, 0, 0, 1, 0 } },
		{ "Wine Red", { 1.2, 0, 0, 0, 0, 0, 0.9, 0, 0, 0, 0, 0, 0.8, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Qingning", { 0.9, 0, 0, 0, 0, 0, 1.1, 0, 0, 0, 0, 0, 0.9, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Halo", { 0.9, 0, 0, 0, 0.247, 0, 0.9, 0, 0, 0.247, 0, 0, 0.9, 0, 0.247, 0, 0, 0, 1, 0 } },
		{ "Fantasy", { 0.8, 0.3, 0.1, 0, 0.182, 0.1, 0.9, 0, 0, 0.182, 0.1, 0.3, 0.7, 0, 0.182, 0, 0, 0, 1, 0 } },
		{ "Sepia", { 0.393, 0.769, 0.189, 0, 0, 0.349, 0.686, 0.168, 0, 0, 0.272, 0.534, 0.131, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Browni", { 0.599, 0.345, -0.271, 0, 0.186, -0.038, 0.861, 0.150, 0, -0.145, 0.241, -0.074, 0.44972182064877153, 0, -0.030, 0, 0, 0, 1, 0 } },
		{ "Retro", { 0.2, 0.5, 0.1, 0, 0.16, 0.2, 0.5, 0.1, 0, 0.16, 0.2, 0.5, 0.1, 0, 0.16, 0, 0, 0, 1, 0 } },
		{ "Vintage", { 0.628, 0.320, -0.040, 0, 0.038, 0.026, 0.644, 0.033, 0, 0.029, 0.047, -0.085, 0.524, 0, 0.020, 0, 0, 0, 1, 0 } },
		{ "Grayscale", { 0.299, 0.587, 0.114, 0, 0, 0.299, 0.587, 0.114, 0, 0, 0.299, 0.587, 0.114, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Black and White", { 1.5, 1.5, 1.5, 0, 0, 1.5, 1.5, 1.5, 0, 0, 1.5, 1.5, 1.5, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Technicolor", { 1.912, -0.854, -0.091, 0, 0.046, -0.308, 1.765, -0.106, 0, -0.275, -0.231, -0.750, 1.847, 0, 0.121, 0, 0, 0, 1, 0 } },
		{ "Sharpen", { 4.8, -1.0, -0.1, 0, -1.523, -0.5, 4.4, -0.1, 0, -1.523, -0.5, -1.0, 5.2, 0, -1.523, 0, 0, 0, 1, 0 } },
		{ "LSD", { 2, -0.4, 0.5, 0, 0, -0.5, 2, -0.4, 0, 0, -0.4, -0.5, 3, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Night Vision", { 0.1, 0.4, 0, 0, 0, 0.3, 1, 0.3, 0, 0, 0, 0.4, 0.1, 0, 0, 0, 0, 0, 1, 0 } },
		{ "Luminance to Alpha", { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.2125, 0.7154, 0.0721, 0, 0 } },
		{ "Invert", { -1, 0, 0, 0, 1, 0, -1, 0, 0, 1, 0, 0, -1, 0, 1, 0, 0, 0, 1, 0 } }
	};

	DynamicArray<String> LNames;
	LNames.Length = Filters.Length;
	for (int i = 0; i < LNames.Length; i++)
		LNames[i] = Filters[i].Name;

	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddStrings("Color filter", LNames, 0);
	LOptions->Bool["IsMouseDown"] = false;

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Common Color Filter", "Press the photo to show the original",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + PhotoFileName);
			auto LImageDest = RectF(0, 0, LImage->Width, LImage->Height).FitInto(ADest);
			auto LPaint = SkPaint();
			if (!LOptions->Bool["IsMouseDown"])
				LPaint->ColorFilter = TSkColorFilter::MakeMatrix(Filters[LOptions->Int["Color filter"]].Matrix);
			ACanvas->DrawImageRect(LImage, LImageDest, TSkSamplingOptions::Medium(), LPaint);
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmFilter::btnDropShadowClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("DeltaX", -25, 25, 6, 0.25);
	LOptions->AddFloat("DeltaY", -25, 25, 6, 0.25);
	LOptions->AddFloat("SigmaX", 0, 10, 4, 0.05);
	LOptions->AddFloat("SigmaY", 0, 10, 4, 0.05);
	LOptions->Bool["IsMouseDown"] = false;

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Drop Shadow", "Press the picture to show the original",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			_di_ISkPaint LPaint = nullptr;
			if (!LOptions->Bool["IsMouseDown"]) {
				LPaint = SkPaint();
				LPaint->ImageFilter = TSkImageFilter::MakeDropShadow(LOptions->Float["DeltaX"], LOptions->Float["DeltaY"],
					LOptions->Float["SigmaX"], LOptions->Float["SigmaY"], TAlphaColors::Black);
			}

			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "chat-bubble.png");
			auto LImageDest = RectF(0, 0, Max(ADest.Width() - 160, 50.f), Max(ADest.Height() - 400, 50.f));
			RectCenter(LImageDest, ADest);
			ACanvas->DrawImageNine(LImage, TRect(39, 36, 40, 37), LImageDest, TSkFilterMode::Linear, LPaint);
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmFilter::btnHueSaturationClick(TObject* Sender)
// The implementation used here was using shader as it is the fastest way, but it is also possible to use
// SkColorFilter.MakeMatrix passing the Hue rotation matrix or the Saturation matrix. Here's how to calculate this matrix:
// https://github.com/pixijs/pixijs/blob/f2731251b1600fa4e310cf2fb27820aa85b8074e/packages/filters/filter-color-matrix/src/ColorMatrixFilter.ts#L210
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("Hue", -1, 1, 0, 0.01);
	LOptions->AddFloat("Saturation", -1, 1, 0, 0.01);
	LOptions->Bool["IsMouseDown"] = false;

	auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + PhotoFileName);
	auto LEffect = TSkRuntimeEffect::MakeForShader(
		"uniform shader texture;                                                                 \
		 uniform float hue;                                                                      \
		 uniform float saturation;                                                               \
		 vec4 main(vec2 fragCoord) {                                                             \
			 vec4 color = texture.eval(fragCoord);                                               \
			 /* hue adjustment, wolfram alpha: RotationTransform[angle, {1, 1, 1}][{x, y, z}] */ \
			 float angle = hue * 3.14159265;                                                     \
			 float s = sin(angle), c = cos(angle);                                               \
			 vec3 weights = (vec3(2.0 * c, -sqrt(3.0) * s - c, sqrt(3.0) * s - c) + 1.0) / 3.0;  \
			 float len = length(color.rgb);                                                      \
			 color.rgb = vec3(                                                                   \
				 dot(color.rgb, weights.xyz),                                                    \
				 dot(color.rgb, weights.zxy),                                                    \
				 dot(color.rgb, weights.yzx)                                                     \
			 );                                                                                  \
			 /* saturation adjustment */                                                         \
			 float average = (color.r + color.g + color.b) / 3.0;                                \
			 if (saturation > 0.0) {                                                             \
				 color.rgb += (average - color.rgb) * (1.0 - 1.0 / (1.001 - saturation));        \
			 } else {                                                                            \
				 color.rgb += (average - color.rgb) * (-saturation);                             \
			 }                                                                                   \
			 return color;                                                                       \
		 }");
	auto LEffectBuilder = SkRuntimeShaderBuilder(LEffect);
	LEffectBuilder->SetChild("texture", LImage->MakeShader(TSkSamplingOptions::Medium()));

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Hue & Saturation", "Press the photo to show the original",
		[this, LOptions, LEffectBuilder, LImage](ISkCanvas* const ACanvas, const TRectF& ADest) {
			if (LOptions->Bool["IsMouseDown"]) {
				LEffectBuilder->SetUniform("hue", 0);
				LEffectBuilder->SetUniform("saturation", 0);
			} else {
				LEffectBuilder->SetUniform("hue", LOptions->Float["Hue"]);
				LEffectBuilder->SetUniform("saturation", LOptions->Float["Saturation"]);
			}
			float LRatio;
			auto LImageDest = RectF(0, 0, LImage->Width, LImage->Height).FitInto(ADest, LRatio);
			ACanvas->Save();
			try {
				ACanvas->ClipRect(LImageDest);
				ACanvas->Scale(1.0 / LRatio, 1.0 / LRatio);
				ACanvas->Translate(LImageDest.Left * LRatio, LImageDest.Top * LRatio);
				auto LPaint = SkPaint();
				LPaint->Shader = LEffectBuilder->MakeShader();
				ACanvas->DrawPaint(LPaint);
			} __finally {
				ACanvas->Restore();
			}
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmFilter::btnLightingEffectsClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("Z", 0, 10, 1.5, 0.05);
	LOptions->AddFloat("Surface Scale", -1, 1, 0.2, 0.01);
	LOptions->AddFloat("Light Constant", 0, 1, 0.6, 0.005);
	LOptions->Bool["IsMouseDown"] = false;

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Lighting Effects", "Press the picture to show the original",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			_di_ISkPaint LPaint = nullptr;
			if (!LOptions->Bool["IsMouseDown"]) {
				LPaint = SkPaint();
				TPoint3D LDirection = {2.f, 3.f, LOptions->Float["Z"]};
				LPaint->ImageFilter = TSkImageFilter::MakeDistantLitDiffuse(LDirection,
					TAlphaColors::White, LOptions->Float["Surface Scale"], LOptions->Float["Light Constant"]);
			}

			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "chat-bubble.png");
			auto LImageDest = RectF(0, 0, Max(ADest.Width() - 160, 50.f), Max(ADest.Height() - 400, 50.f));
			RectCenter(LImageDest, ADest);
			ACanvas->DrawImageNine(LImage, TRect(39, 36, 40, 37), LImageDest, TSkFilterMode::Linear, LPaint);
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmFilter::btnVignetteClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("Size", 0, 1, 0.5, 0.005);
	LOptions->AddFloat("Amount", 0, 1, 0, 0.005);
	LOptions->Bool["IsMouseDown"] = false;

	auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + PhotoFileName);
	auto LEffect = TSkRuntimeEffect::MakeForShader(
		"uniform shader texture;                                                 \
		 uniform float2 resolution;                                              \
		 uniform float size;                                                     \
		 uniform float amount;                                                   \
		 vec4 main(vec2 fragCoord) {                                             \
			 vec4 color = texture.eval(fragCoord);                               \
			 float dist = distance(fragCoord / resolution, vec2(0.5, 0.5));      \
			 color.rgb *= smoothstep(0.8, size * 0.799, dist * (amount + size)); \
			 return color;                                                       \
		 }");
	auto LEffectBuilder = SkRuntimeShaderBuilder(LEffect);
	LEffectBuilder->SetChild("texture", LImage->MakeShader(TSkSamplingOptions::Medium()));

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = true;
			AShouldRedraw = true;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF& APoint, bool& AShouldRedraw) {
			LOptions->Bool["IsMouseDown"] = false;
			AShouldRedraw = true;
		};

	ChildForm<TfrmPaintBoxViewer>()->Show("Vignette", "Press the photo to show the original",
		[this, LOptions, LEffectBuilder, LImage](ISkCanvas* const ACanvas, const TRectF& ADest) {
			LEffectBuilder->SetUniform("size", LOptions->Float["Size"]);
			if (LOptions->Bool["IsMouseDown"])
				LEffectBuilder->SetUniform("amount", 0);
			else
				LEffectBuilder->SetUniform("amount", LOptions->Float["Amount"]);
			float LRatio;
			auto LImageDest = RectF(0, 0, LImage->Width, LImage->Height).FitInto(ADest, LRatio);
			ACanvas->Save();
			try {
				ACanvas->ClipRect(LImageDest);
				ACanvas->Scale(1 / LRatio, 1 / LRatio);
				ACanvas->Translate(LImageDest.Left * LRatio, LImageDest.Top * LRatio);
				LEffectBuilder->SetUniform("resolution", PointF(LImageDest.Width(), LImageDest.Height()) * LRatio);
				auto LPaint = SkPaint();
				LPaint->Shader = LEffectBuilder->MakeShader();
				ACanvas->DrawPaint(LPaint);
			} __finally {
				ACanvas->Restore();
			}
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

