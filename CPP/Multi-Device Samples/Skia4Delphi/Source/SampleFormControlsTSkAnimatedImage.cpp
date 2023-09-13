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

#include "SampleFormViewerControl.h"
#include "SampleFormControlsTSkAnimatedImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::btnAnimatedGIFClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Animated GIF", "",
	   [this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(nullptr);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "animated.gif");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::btnAnimatedWebPClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Animated WebP", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(nullptr);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "rocket.webp");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::btnLottieCheckClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Lottie - check.json", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(nullptr);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "check.json");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::btnLottieLoadingsClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Lottie - Loadings", "",
		[this]() {
			TGridPanelLayout* LGrid = new TGridPanelLayout(nullptr);
			LGrid->Align = TAlignLayout::Client;
			LGrid->HitTest = false;
			LGrid->RowCollection->BeginUpdate();
			try {
				LGrid->RowCollection->Items[0]->Value = 33.333333333333333333f;
				LGrid->RowCollection->Items[1]->Value = 33.333333333333333333f;
				LGrid->RowCollection->Add()->Value = 33.333333333333333333f;
			} __finally {
				LGrid->RowCollection->EndUpdate();
			}

			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->Rect = RectF(10, 10, 10, 10);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading1.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->Rect = RectF(10, 10, 10, 10);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading2.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->Rect = RectF(10, 10, 10, 10);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading3.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->Rect = RectF(10, 10, 10, 10);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading4.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->Rect = RectF(10, 10, 10, 10);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading5.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->Rect = RectF(10, 10, 10, 10);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading6.json");
			LAnimatedImage->Parent = LGrid;

			return LGrid;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::btnLottieRocketClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Lottie - rocket.json", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(nullptr);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "rocket.json");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::btnTelegramStickersClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Telegram Sticker", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(nullptr);
			LAnimatedImage->Align = TAlignLayout::Client;
			LAnimatedImage->LoadFromFile(AssetsPath + "telegram-sticker.tgs");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

