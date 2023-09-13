//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormViewerComparisonImageH
#define SampleFormViewerComparisonImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormViewerPaintBox.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmComparisonImageViewer : public TfrmPaintBoxViewer
{
	typedef TfrmPaintBoxViewer inherited;

__published:
public:
	__fastcall TfrmComparisonImageViewer(TComponent* Owner) override : TfrmPaintBoxViewer(Owner) {}
	HIDESBASE void Show(const String ATitle, const String ADescription, const String AImage1Text, const String AImage2Text, const TBytes AImageBytes1, const TBytes AImageBytes2);
};

#endif
