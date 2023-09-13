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
#include "SampleFormControlsTSkAnimatedImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::pnlAnimatedGIFClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Animated GIF", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage((TComponent*) nullptr);
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "animated.gif");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::pnlAnimatedWebPClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Animated WebP", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage((TComponent*) nullptr);
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "rocket.webp");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::pnlLottieCheckClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Lottie - check.json", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage((TComponent*) nullptr);
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "check.json");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::pnlLottieLoadingsClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Lottie - Loadings", "",
		[this]() {
			TGridPanel* LGrid = new TGridPanel((TComponent*) nullptr);
			LGrid->Align = alClient;
			LGrid->RowCollection->BeginUpdate();
			try {
				LGrid->RowCollection->Items[0]->Value = 33.333333333333333333f;
				LGrid->RowCollection->Items[1]->Value = 33.333333333333333333f;
				LGrid->RowCollection->Add()->Value = 33.333333333333333333f;
			} __finally {
				LGrid->RowCollection->EndUpdate();
			}

			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->SetBounds(10, 10, 10, 10);
			LAnimatedImage->AlignWithMargins = true;
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading1.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->SetBounds(10, 10, 10, 10);
			LAnimatedImage->AlignWithMargins = true;
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading2.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->SetBounds(10, 10, 10, 10);
			LAnimatedImage->AlignWithMargins = true;
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading3.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->SetBounds(10, 10, 10, 10);
			LAnimatedImage->AlignWithMargins = true;
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading4.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->SetBounds(10, 10, 10, 10);
			LAnimatedImage->AlignWithMargins = true;
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading5.json");
			LAnimatedImage->Parent = LGrid;

			LAnimatedImage = new TSkAnimatedImage(LGrid);
			LAnimatedImage->Margins->SetBounds(10, 10, 10, 10);
			LAnimatedImage->AlignWithMargins = true;
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "loading6.json");
			LAnimatedImage->Parent = LGrid;

			return LGrid;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::pnlLottieRocketClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Lottie - rocket.json", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage((TComponent*) nullptr);
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "rocket.json");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkAnimatedImage::pnlTelegramStickersClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Telegram Sticker", "",
		[this]() {
			TSkAnimatedImage* LAnimatedImage = new TSkAnimatedImage((TComponent*) nullptr);
			LAnimatedImage->Align = alClient;
			LAnimatedImage->LoadFromFile(AssetsPath + "telegram-sticker.tgs");
			return LAnimatedImage;
		});
}
//---------------------------------------------------------------------------
