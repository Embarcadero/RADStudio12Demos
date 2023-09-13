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

#include "SampleFormViewerTImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void TfrmTImageViewer::Show(const String ATitle, const String ADescription,
	const TImageEditProc AImageEditProc)
{
	if (AImageEditProc) {
		AImageEditProc(imgImage);
		float LSceneScale;
		if (imgImage->Scene != nullptr)
			LSceneScale = imgImage->Scene->GetSceneScale();
		else
			LSceneScale = 1;
		imgImage->Width = imgImage->Bitmap->Width / (imgImage->AbsoluteScale.X * LSceneScale);
		imgImage->Height = imgImage->Bitmap->Height / (imgImage->AbsoluteScale.Y * LSceneScale);
	} else
		imgImage->SetBounds(imgImage->Position->X, imgImage->Position->Y, 0, 0);
	inherited::Show(ATitle, ADescription);
}
//---------------------------------------------------------------------------

