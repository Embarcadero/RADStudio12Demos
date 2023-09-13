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

#include "SampleFormViewerTImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

void TfrmTImageViewer::Show(const String ATitle, const String ADescription,
	const TImageEditProc AImageEditProc)
{
	if (AImageEditProc) {
		AImageEditProc(imgImage);
		imgImage->Width = imgImage->Picture->Width;
		imgImage->Height = imgImage->Picture->Height;
	} else
		imgImage->SetBounds(imgImage->Left, imgImage->Top, 0, 0);
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------
