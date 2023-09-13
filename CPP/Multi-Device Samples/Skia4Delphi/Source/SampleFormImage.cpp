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
#include "SampleFormViewerComparisonImage.h"
#include "SampleFormViewerTImage.h"
#include "SampleFormImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

String FormatBytes(const int64_t ABytesCount)
{
	static const float KiloByte = 1024.f;
	return Format("%s KB", ARRAYOFCONST((FormatFloat("0.#", ABytesCount / KiloByte))));
}
//---------------------------------------------------------------------------

void __fastcall TfrmImage::btnEncodeWebpVsJpegClick(TObject* Sender)
{
	static const int Quality = 80;
	auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "kung-fu-panda.png");
	TBytes LBytesWebP = LImage->Encode(TSkEncodedImageFormat::WEBP, Quality);
	TBytes LBytesJpeg = LImage->Encode(TSkEncodedImageFormat::JPEG, Quality);

	ChildForm<TfrmComparisonImageViewer>()->Show("Encode WebP vs JPEG", "",
		Format("WebP - %s quality - %s", ARRAYOFCONST((IntToStr(Quality) + "%", FormatBytes(LBytesWebP.Length)))),
		Format("Jpeg - %s quality - %s", ARRAYOFCONST((IntToStr(Quality) + "%", FormatBytes(LBytesJpeg.Length)))),
		LBytesWebP, LBytesJpeg);
}
//---------------------------------------------------------------------------

void __fastcall TfrmImage::btnNinePatchClick(TObject* Sender)
{
	ChildForm<TfrmPaintBoxViewer>()->Show("9-Patch", "",
		[this](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "chat-bubble.png");
			auto LImageDest = RectF(0, 0, Max(ADest.Width() - 160, 50.f), Max(ADest.Height() - 400, 50.f));
			RectCenter(LImageDest, ADest);
			ACanvas->DrawImageNine(LImage, TRect(39, 36, 40, 37), LImageDest);
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmImage::btnWebpInImageClick(TObject* Sender)
{
	ChildForm<TfrmTImageViewer>()->Show("Loading .WebP in TImage", "Skia4Delphi adds support for new formats to TBitmap: .bmp, .gif, .ico, .webp, .wbmp and raw images (.arw, .cr2, .dng, .nef, .nrw, .orf, .raf, .rw2, .pef and .srw)",
		[this](TImage* AImage) {
			AImage->Bitmap->LoadFromFile(AssetsPath + "kung-fu-panda.webp");
		});
}
//---------------------------------------------------------------------------

