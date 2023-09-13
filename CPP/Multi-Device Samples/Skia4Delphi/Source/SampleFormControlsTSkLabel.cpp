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

#include <System.IOUtils.hpp>
#include "SampleFormViewerControl.h"
#include "SampleFormControlsTSkLabel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnCustomFontFamilyClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Custom Font", "The custom font will be available only inside the app, without extra configs like installation (Windows) or config info.plist (iOS).",
		[this]() {
			// It is preferable to register only once at startup.
			TSkDefaultProviders::RegisterTypeface(AssetsPath + "bonheur-royale-regular.ttf");
			TSkDefaultProviders::RegisterTypeface(AssetsPath + "nunito-extrabold.ttf");

			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = TAlignLayout::Top;
			LLabel->Words->Add("\"Each dream that you leave behind is a part of your future that will no longer exist.\"" + String(sLineBreak),
				0xFFFF5F5F, 23, TFontWeight::UltraBold)->Font->Families = "Nunito";
			LLabel->Words->Add("(Steve Jobs)", 0xFF5B8DFE, 28)->Font->Families = "Bonheur Royale";
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnFamiliesFallbacksClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Families Fallbacks", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = TAlignLayout::Top;
			LLabel->TextSettings->Font->Families = "Poppins, Nunito, Tenorite, Roboto, Segoe UI";
			LLabel->TextSettings->Font->Size = 20;
			LLabel->Text = Format("Text with font families fallbacks, that is, in the font family property there is a list of families separated by comma where the first family available on the device will be considered. " + String(sLineBreak) + String(sLineBreak) +
				"In this label, the families list is \"%s\"", ARRAYOFCONST((LLabel->TextSettings->Font->Families)));
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnFontWeightClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Font Weight", "",
		[this]() {
			static const char* FontWeightName[] = { "Thin", "UltraLight", "Light", "SemiLight", "Regular", "Medium", "Semibold", "Bold", "UltraBold", "Black", "UltraBlack" };

			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Margins->Left = 10;
			LLabel->Align = TAlignLayout::Top;
			for (const auto LFontWeight : {
				TFontWeight::Thin, TFontWeight::UltraLight, TFontWeight::Light,
				TFontWeight::SemiLight, TFontWeight::Regular, TFontWeight::Medium,
				TFontWeight::Semibold, TFontWeight::Bold, TFontWeight::UltraBold,
				TFontWeight::Black, TFontWeight::UltraBlack })
			{
				LLabel->Words->Add(String(sLineBreak) + FontWeightName[(int) LFontWeight], TAlphaColors::Black, 34, LFontWeight);
			}
			return LLabel;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnJustifiedTextClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Justified Text", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Margins->Rect = RectF(10, 10, 10, 10);
			LLabel->Align = TAlignLayout::Top;
			LLabel->Text = TFile::ReadAllText(AssetsPath + "lorem-ipsum.txt");
			LLabel->TextSettings->HorzAlign = TSkTextHorzAlign::Justify;
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnMaxLinesClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Maximum Lines", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = TAlignLayout::Top;
			LLabel->TextSettings->MaxLines = 3;
			LLabel->Text = "This is a text that is limited to 3 lines in maximum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
			LLabel->TextSettings->Font->Size = 32;
			return LLabel;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnMultiStyleClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Multiple Styles", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = TAlignLayout::Top;
			LLabel->Words->Add(U"English English 字典 字典 😀😅😂😂", TAlphaColors::Black, 28, TFontWeight::Light);
			LLabel->Words->Add(U" !سلام دنیا", TAlphaColors::Crimson, 22, TFontWeight::Semibold);
			LLabel->Words->Add(" World domination is such an ugly phrase - I prefer to call it world optimisation.",
				TAlphaColors::Blueviolet, 30, TFontWeight::UltraBold, TFontSlant::Italic);
			return LLabel;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnRTLClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Right-to-left", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Margins->Rect = RectF(10, 10, 10, 10);
			LLabel->Align = TAlignLayout::Top;
			LLabel->TextSettings->Font->Size = 18;
			LLabel->Text = TFile::ReadAllText(AssetsPath + "persian-lorem-ipsum.txt");
			ChildForm<TfrmControlViewer>()->BiDiMode = bdRightToLeft;
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::btnWordOnClickEventClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Word OnClick Event", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = TAlignLayout::Top;
			LLabel->HitTest = true;
			LLabel->Words->Add("Click on the following text: ", TAlphaColors::Black, 20);
			TSkLabel::TCustomWordsItem* LItem = LLabel->Words->Add("this is just an item of a TSkLabel",
				TAlphaColors::Darkgoldenrod, 20, TFontWeight::Semibold);
			LItem->Cursor = crHandPoint;
			LItem->Decorations->Decorations = TSkTextDecorations() << TSkTextDecoration::Underline;
			LItem->OnClick = OnWordClick;
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::OnWordClick(TObject* Sender)
{
	TSkLabel::TCustomWordsItem* LItem = (TSkLabel::TCustomWordsItem*) Sender;
	ShowMessage(Format("Clicked text: \"%s\"", ARRAYOFCONST((LItem->Text))));
}
//---------------------------------------------------------------------------

