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
#include "SampleFormViewerControl.h"
#include "SampleFormControlsTSkLabel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::OnWordClick(TObject* Sender)
{
	TSkLabel::TCustomWordsItem* LItem = (TSkLabel::TCustomWordsItem*) Sender;
	ShowMessage(Format("Clicked text: \"%s\"", ARRAYOFCONST((LItem->Caption))));
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlCustomFontFamilyClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Custom Font", "The custom font will be available only inside the app, without extra configs like installation in Windows.",
		[this]() {
			// It is preferable to register only once at startup.
			TSkDefaultProviders::RegisterTypeface(AssetsPath + "bonheur-royale-regular.ttf");
			TSkDefaultProviders::RegisterTypeface(AssetsPath + "nunito-extrabold.ttf");

			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = alTop;
			LLabel->Words->Add("\"Each dream that you leave behind is a part of your future that will no longer exist.\"" + String(sLineBreak),
				0xFFFF5F5F, 23, TSkFontComponent::TSkFontWeight::UltraBold)->Font->Families = "Nunito";
			LLabel->Words->Add("(Steve Jobs)", 0xFF5B8DFE, 28)->Font->Families = "Bonheur Royale";
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlFamiliesFallbacksClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Families Fallbacks", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = alTop;
			LLabel->TextSettings->Font->Families = "Poppins, Nunito, Tenorite, Roboto, Segoe UI";
			LLabel->TextSettings->Font->Size = 20;
			LLabel->Caption = Format("Text with font families fallbacks, that is, in the font family property there is a list of families separated by comma where the first family available on the device will be considered. " + String(sLineBreak) + String(sLineBreak) +
				"In this label, the families list is \"%s\"", ARRAYOFCONST((LLabel->TextSettings->Font->Families)));
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlFontWeightClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Font Weight", "",
		[this]() {
			static const char* FontWeightName[] = { "Thin", "UltraLight", "Light", "SemiLight", "Regular", "Medium", "Semibold", "Bold", "UltraBold", "Black", "UltraBlack" };

			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Margins->Left = 10;
      LLabel->AlignWithMargins = true;
			LLabel->Align = alTop;
			for (const auto LFontWeight : {
				TSkFontComponent::TSkFontWeight::Thin, TSkFontComponent::TSkFontWeight::UltraLight, TSkFontComponent::TSkFontWeight::Light,
				TSkFontComponent::TSkFontWeight::SemiLight, TSkFontComponent::TSkFontWeight::Regular, TSkFontComponent::TSkFontWeight::Medium,
				TSkFontComponent::TSkFontWeight::Semibold, TSkFontComponent::TSkFontWeight::Bold, TSkFontComponent::TSkFontWeight::UltraBold,
				TSkFontComponent::TSkFontWeight::Black, TSkFontComponent::TSkFontWeight::UltraBlack })
			{
				LLabel->Words->Add(String(sLineBreak) + FontWeightName[(int) LFontWeight], TAlphaColors::Black, 34, LFontWeight);
			}
			return LLabel;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlJustifiedTextClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Justified Text", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Margins->SetBounds(10, 10, 10, 10);
      LLabel->AlignWithMargins = true;
			LLabel->Align = alTop;
			LLabel->Caption = TFile::ReadAllText(AssetsPath + "lorem-ipsum.txt");
			LLabel->TextSettings->HorzAlign = TSkTextHorzAlign::Justify;
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlMaxLinesClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Maximum Lines", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = alTop;
			LLabel->TextSettings->MaxLines = 3;
			LLabel->Caption = "This is a text that is limited to 3 lines in maximum. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
			LLabel->TextSettings->Font->Size = 32;
			return LLabel;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlMultiStyleClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Multiple Styles", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = alTop;
			LLabel->Words->Add(U"English English 字典 字典 😀😅😂😂", TAlphaColors::Black, 28, TSkFontComponent::TSkFontWeight::Light);
			LLabel->Words->Add(U" !سلام دنیا", TAlphaColors::Crimson, 22, TSkFontComponent::TSkFontWeight::Semibold);
			LLabel->Words->Add(" World domination is such an ugly phrase - I prefer to call it world optimisation.",
				TAlphaColors::Blueviolet, 30, TSkFontComponent::TSkFontWeight::UltraBold, TSkFontComponent::TSkFontSlant::Italic);
			return LLabel;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlRTLClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Right-to-left", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Margins->SetBounds(10, 10, 10, 10);
      LLabel->AlignWithMargins = true;
			LLabel->Align = alTop;
			LLabel->TextSettings->Font->Size = 18;
			LLabel->Caption = TFile::ReadAllText(AssetsPath + "persian-lorem-ipsum.txt");
			ChildForm<TfrmControlViewer>()->BiDiMode = bdRightToLeft;
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkLabel::pnlWordOnClickEventClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Word OnClick Event", "",
		[this]() {
			TSkLabel* LLabel = new TSkLabel(nullptr);
			LLabel->Align = alTop;
			LLabel->Words->Add("Click on the following text: ", TAlphaColors::Black, 20);
			TSkLabel::TCustomWordsItem* LItem = LLabel->Words->Add("this is just an item of a TSkLabel",
				TAlphaColors::Darkgoldenrod, 20, TSkFontComponent::TSkFontWeight::Semibold);
			LItem->Cursor = crHandPoint;
			LItem->Decorations->Decorations = TSkTextDecorations() << TSkTextDecoration::Underline;
			LItem->OnClick = OnWordClick;
			return LLabel;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------
