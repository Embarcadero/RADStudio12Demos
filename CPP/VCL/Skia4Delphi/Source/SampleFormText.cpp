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
#include "SampleFormControlsTSkLabel.h"
#include "SampleFormText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmText::pnlBasicTextsClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Basic Texts", "",
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LTypeface = TSkTypeface::MakeFromName("Monospace", TSkFontStyle::Normal());
			auto LFont1 = SkFont(LTypeface, 64, 1, 0);
			auto LFont2 = SkFont(LTypeface, 64, 1.5, 0);
			LFont1->Edging = TSkFontEdging::AntiAlias;
			LFont2->Edging = TSkFontEdging::AntiAlias;

			auto LBlob1 = TSkTextBlob::MakeFromText("Skia", LFont1);
			auto LBlob2 = TSkTextBlob::MakeFromText("Skia", LFont2);

			auto LPaint1 = SkPaint();
			LPaint1->AntiAlias = true;
			LPaint1->SetARGB(0xFF, 0x42, 0x85, 0xF4);

			auto LPaint2 = SkPaint(TSkPaintStyle::Stroke);
			LPaint2->AntiAlias = true;
			LPaint2->SetARGB(0xFF, 0xDB, 0x44, 0x37);
			LPaint2->StrokeWidth = 3;

			auto LPaint3 = SkPaint();
			LPaint3->AntiAlias = true;
			LPaint3->SetARGB(0xFF, 0x0F, 0x9D, 0x58);

			ACanvas->DrawTextBlob(LBlob1, 20, 64, LPaint1);
			ACanvas->DrawSimpleText("Skia", 20, 154, LFont1, LPaint2);
			ACanvas->DrawTextBlob(LBlob2, 20, 244, LPaint3);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmText::pnlCustomFontClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Basic Texts", "",
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LPaint = SkPaint();
			LPaint->Color = 0x8FFFFFFF;
			ACanvas->DrawRect(ADest, LPaint);
			LPaint->Reset();

			auto LFont = SkFont(TSkTypeface::MakeFromFile(AssetsPath + "nunito-extrabold.ttf"), 23, 1, 0);
			LPaint->Shader = TSkShader::MakeGradientLinear(PointF(0, 0), PointF(256, 145), 0xFFFF5F5F, 0xFF5B8DFE, TSkTileMode::Clamp);

			ACanvas->DrawSimpleText("\"Each dream that you", 2, 25, LFont, LPaint);
			ACanvas->DrawSimpleText("leave behind is a part", 2, 55, LFont, LPaint);
			ACanvas->DrawSimpleText("of your future that will", 2, 85, LFont, LPaint);
			ACanvas->DrawSimpleText("no longer exist.\"", 2, 115, LFont, LPaint);

			LFont = SkFont(TSkTypeface::MakeFromFile(AssetsPath + "bonheur-royale-regular.ttf"), 28, 1, 0);
			LPaint->Shader = nullptr;
			LPaint->Color = 0xFF5B8DFE;
			ACanvas->DrawSimpleText("(Steve Jobs)", 2, 150, LFont, LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmText::pnlParagraphClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Paragraph", "", 440, 440,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LParagraphStyle = SkParagraphStyle();
			LParagraphStyle->MaxLines = 3;
			LParagraphStyle->Ellipsis = "...";
			auto LBuilder = SkParagraphBuilder(LParagraphStyle);

			auto LTextStyle = SkTextStyle();
			LTextStyle->Color = TAlphaColors::Black;
			LTextStyle->FontSize = 28;
			LTextStyle->FontStyle = TSkFontStyle(TSkFontWeight::Light, TSkFontWidth::Normal, TSkFontSlant::Upright);
			LBuilder->PushStyle(LTextStyle);
			LBuilder->AddText(U"English English 字典 字典 😀😅😂😂");

			LTextStyle = SkTextStyle();
			LTextStyle->Color = TAlphaColors::Crimson;
			LTextStyle->FontSize = 22;
			LTextStyle->FontStyle = TSkFontStyle(TSkFontWeight::SemiBold, TSkFontWidth::Normal, TSkFontSlant::Upright);
			LBuilder->PushStyle(LTextStyle);
			LBuilder->AddText(U" !سلام دنیا");

			LTextStyle = SkTextStyle();
			LTextStyle->Color = TAlphaColors::Blueviolet;
			LTextStyle->FontSize = 30;
			LTextStyle->FontStyle = TSkFontStyle(TSkFontWeight::ExtraBold, TSkFontWidth::Normal, TSkFontSlant::Italic);
			LBuilder->PushStyle(LTextStyle);
			LBuilder->AddText(" World domination is such an ugly phrase - I prefer to call it world optimisation.");

			auto LParagraph = LBuilder->Build();
			LParagraph->Layout(ADest.Width());
			LParagraph->Paint(ACanvas, 0, 0);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmText::pnlParagraphToPathClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Paragraph to Path", "", 440, 440,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LParagraphStyle = SkParagraphStyle();
			LParagraphStyle->MaxLines = 3;
			LParagraphStyle->Ellipsis = "...";
			auto LBuilder = SkParagraphBuilder(LParagraphStyle);

			auto LTextStyle = SkTextStyle();
			LTextStyle->Color = TAlphaColors::Black;
			LTextStyle->FontSize = 28;
			LTextStyle->FontStyle = TSkFontStyle(TSkFontWeight::Light, TSkFontWidth::Normal, TSkFontSlant::Upright);
			LBuilder->PushStyle(LTextStyle);
			LBuilder->AddText(U"English English 字典 字典");

			LTextStyle = SkTextStyle();
			LTextStyle->Color = TAlphaColors::Crimson;
			LTextStyle->FontSize = 22;
			LTextStyle->FontStyle = TSkFontStyle(TSkFontWeight::SemiBold, TSkFontWidth::Normal, TSkFontSlant::Upright);
			LBuilder->PushStyle(LTextStyle);
			LBuilder->AddText(U" !سلام دنیا");

			LTextStyle = SkTextStyle();
			LTextStyle->Color = TAlphaColors::Blueviolet;
			LTextStyle->FontSize = 30;
			LTextStyle->FontStyle = TSkFontStyle(TSkFontWeight::ExtraBold, TSkFontWidth::Normal, TSkFontSlant::Italic);
			LBuilder->PushStyle(LTextStyle);
			LBuilder->AddText(" World domination is such an ugly phrase - I prefer to call it world optimisation.");

			auto LParagraph = LBuilder->Build();
			LParagraph->Layout(ADest.Width());

			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;
			LPaint->Color = TAlphaColors::Black;

			ACanvas->DrawPath(LParagraph->ToPath(), LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmText::pnlRTLClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("Right-to-left", "", 256, 256,
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LFont = SkFont(TSkTypeface::MakeDefault(), 55, 1, 0);
			auto LShaper = SkShaper();
			auto LBlob = LShaper->Shape(U"سلام دنیا!", LFont, false, std::numeric_limits<float>::max());

			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;
			LPaint->Color = TAlphaColors::Tomato;

			ACanvas->DrawTextBlob(LBlob, 0, 0, LPaint);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmText::pnlTSkLabelClick(TObject* Sender)
{
	ChildForm<TfrmTSkLabel>()->Show();
}
//---------------------------------------------------------------------------
