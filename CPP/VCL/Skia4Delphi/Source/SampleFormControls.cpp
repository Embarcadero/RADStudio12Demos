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

#include "SampleFormControls.h"
#include "SampleFormControlsTSkAnimatedImage.h"
#include "SampleFormControlsTSkLabel.h"
#include "SampleFormControlsTSkPaintBox.h"
#include "SampleFormControlsTSkSVG.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void __fastcall TfrmControls::pnlTSkAnimatedImageClick(TObject* Sender)
{
	ChildForm<TfrmTSkAnimatedImage>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmControls::pnlTSkLabelClick(TObject* Sender)
{
	ChildForm<TfrmTSkLabel>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmControls::pnlTSkPaintBoxClick(TObject* Sender)
{
	ChildForm<TfrmTSkPaintBox>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmControls::pnlTSkSVGClick(TObject* Sender)
{
	ChildForm<TfrmTSkSVG>()->Show();
}
//---------------------------------------------------------------------------
