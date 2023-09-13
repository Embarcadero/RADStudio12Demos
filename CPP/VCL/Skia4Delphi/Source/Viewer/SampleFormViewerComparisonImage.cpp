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

#include "SampleFormViewerComparisonImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void DoDraw(ISkCanvas* const ACanvas, ISkImage* const AImage, const String AText)
{
	static const int TitleHeight = 40;
	static const int TitleX = 10;
	static const int TitleY = 26;
	static const int TextSize = 26;

	auto LBackPaint = SkPaint();
	LBackPaint->Color = TAlphaColors::Black;
	LBackPaint->AlphaF = 0.5;

	auto LFrontPaint = SkPaint();
	LFrontPaint->Color = TAlphaColors::White;

	ACanvas->DrawImage(AImage, 0, 0);
	ACanvas->DrawRect(RectF(0, 0, AImage->Width, TitleHeight), LBackPaint);
	auto LTypeface = TSkTypeface::MakeFromName("Monospace", TSkFontStyle::Normal());
	auto LFont = SkFont(LTypeface, TextSize, 1, 0);

	ACanvas->DrawSimpleText(AText, TitleX, TitleY, LFont, LFrontPaint);
}
//---------------------------------------------------------------------------

void TfrmComparisonImageViewer::Show(const String ATitle, const String ADescription,
	const String AImage1Text, const String AImage2Text, const TBytes AImageBytes1,
	const TBytes AImageBytes2)
{
	static const int BitmapsOffset = 20;
	auto LImage1 = TSkImage::MakeFromEncoded(AImageBytes1);
	auto LImage2 = TSkImage::MakeFromEncoded(AImageBytes2);
	inherited::Show(ATitle, ADescription,
		round(Max(LImage1->Width, LImage2->Width) / pbxDraw->ScaleFactor),
		round((LImage1->Height + BitmapsOffset + LImage2->Height) / pbxDraw->ScaleFactor),
		[this, LImage1, LImage2, AImage1Text, AImage2Text](ISkCanvas* const ACanvas, const TRectF& ADest) {
			TPointF LScale = ACanvas->GetLocalToDeviceAs3x3().ExtractScale();
			ACanvas->Scale(1./LScale.X, 1./LScale.Y);
			DoDraw(ACanvas, LImage1, AImage1Text);
			ACanvas->Translate(0, LImage1->Height + BitmapsOffset);
			DoDraw(ACanvas, LImage2, AImage2Text);
		});
}
//---------------------------------------------------------------------------
