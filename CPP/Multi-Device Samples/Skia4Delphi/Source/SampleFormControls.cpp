//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SampleFormControls.h"
#include "SampleFormControlsTSkAnimatedImage.h"
#include "SampleFormControlsTSkLabel.h"
#include "SampleFormControlsTSkPaintBox.h"
#include "SampleFormControlsTSkSVG.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void __fastcall TfrmControls::btnTSkAnimatedImageClick(TObject* Sender)
{
	ChildForm<TfrmTSkAnimatedImage>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmControls::btnTSkLabelClick(TObject* Sender)
{
	ChildForm<TfrmTSkLabel>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmControls::btnTSkPaintBoxClick(TObject* Sender)
{
	ChildForm<TfrmTSkPaintBox>()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmControls::btnTSkSVGClick(TObject* Sender)
{
	ChildForm<TfrmTSkSVG>()->Show();
}
//---------------------------------------------------------------------------

