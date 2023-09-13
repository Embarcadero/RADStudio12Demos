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
#include "SampleFormControlsTSkSVG.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmTSkSVG::pnlCBuilderClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("c++builder.svg", "",
		[this]() {
			TSkSvg* LSvgControl = new TSkSvg(nullptr);
			LSvgControl->Align = alClient;
			LSvgControl->Svg->Source = TFile::ReadAllText(AssetsPath + "c++builder.svg");
			return LSvgControl;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkSVG::pnlCustomColorClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddBoolean("Show original", false);

	ChildForm<TfrmControlViewer>()->Show("Custom Color", "",
		[this, LOptions]() {
			TSkSvg* LSvgControl = new TSkSvg(nullptr);
			LSvgControl->Align = alClient;
			if (!LOptions->Bool["Show original"])
				LSvgControl->Svg->OverrideColor = TAlphaColors::Blueviolet;
			LSvgControl->Svg->Source = TFile::ReadAllText(AssetsPath + "tesla.svg");
			return LSvgControl;
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkSVG::pnlEditingElementClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddBoolean("Show original", false);

	ChildForm<TfrmControlViewer>()->Show("Editing an SVG Element", "Editing the eyes of the android svg to red color",
		[this, LOptions]() {
			TSkSvg* LSvgControl = new TSkSvg(nullptr);
			LSvgControl->Align = alClient;
			LSvgControl->Svg->Source = TFile::ReadAllText(AssetsPath + "android.svg");
			if (!LOptions->Bool["Show original"])
				LSvgControl->Svg->DOM->FindNodeById("eyes")->TrySetAttribute("fill", "red");
			return LSvgControl;
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkSVG::pnlGorillaClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("gorilla.svg", "",
		[this]() {
			TSkSvg* LSvgControl = new TSkSvg(nullptr);
			LSvgControl->Align = alClient;
			LSvgControl->Svg->Source = TFile::ReadAllText(AssetsPath + "gorilla.svg");
			return LSvgControl;
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTSkSVG::pnlTileWrapModeClick(TObject* Sender)
{
	ChildForm<TfrmControlViewer>()->Show("Tile Wrap Mode", "",
		[this]() {
			TSkSvg* LSvgControl = new TSkSvg(nullptr);
			LSvgControl->Align = alClient;
			LSvgControl->Svg->WrapMode = TSkSvgWrapMode::Tile;
			LSvgControl->Svg->Source = TFile::ReadAllText(AssetsPath + "anchors-away.svg");
			return LSvgControl;
		}, TBackgroundKind::Solid);
}
//---------------------------------------------------------------------------
