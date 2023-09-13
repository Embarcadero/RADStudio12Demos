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

#include "SampleFormMain.h"
#include "SampleFormBasics.h"
#include "SampleFormControls.h"
#include "SampleFormDocuments.h"
#include "SampleFormFilter.h"
#include "SampleFormImage.h"
#include "SampleFormPathsAndEffects.h"
#include "SampleFormRuntimeEffects.h"
#include "SampleFormSplashScreen.h"
#include "SampleFormText.h"
#include "SampleFormTransforms.h"
#include "SampleFormUnicode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------

__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TfrmBase(Owner) {}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
	ChildForm<TfrmSplashScreen>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlBasicsClick(TObject* Sender)
{
	ChildForm<TfrmBasics>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlControlsClick(TObject* Sender)
{
	ChildForm<TfrmControls>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlDocumentsClick(TObject* Sender)
{
	ChildForm<TfrmDocuments>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlFilterClick(TObject* Sender)
{
	ChildForm<TfrmFilter>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlImageClick(TObject* Sender)
{
	ChildForm<TfrmImage>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlPathsAndEffectsClick(TObject* Sender)
{
	ChildForm<TfrmPathsAndEffects>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlRuntimeEffectsClick(TObject* Sender)
{
	ChildForm<TfrmRuntimeEffects>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlTextClick(TObject* Sender)
{
	ChildForm<TfrmText>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlTransformsClick(TObject* Sender)
{
	ChildForm<TfrmTransforms>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::pnlUnicodeClick(TObject* Sender)
{
	ChildForm<TfrmUnicode>()->Show();
}
//---------------------------------------------------------------------------
