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
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmControlViewer::FormClose(TObject* Sender, TCloseAction& Action)
{
	inherited::FormClose(Sender, Action);
	if (Action != TCloseAction::caNone)
		FreeAndNil(FControl);
}
//---------------------------------------------------------------------------

void TfrmControlViewer::OptionsChanged()
{
	inherited::OptionsChanged();
	FreeAndNil(FControl);
	FControl = FControlCreationFunc();
	FControl->Parent = sbxContent;
	if (FControl->Align != TAlign::alNone)
		sbxContent->Realign();
}
//---------------------------------------------------------------------------

HIDESBASE void TfrmControlViewer::Show(const String ATitle,
	const String ADescription,
	const std::function<TControl*()> AControlCreationFunc,
	TBackgroundKind ABackgroundKind, TViewerOptions* AOptions)
{
	BackgroundKind = ABackgroundKind;
	Options = AOptions;
	FControlCreationFunc = AControlCreationFunc;
	FControl = FControlCreationFunc();
	FControl->Parent = sbxContent;
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------
