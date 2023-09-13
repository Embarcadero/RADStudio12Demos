//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormViewerUnicodeBiDiH
#define SampleFormViewerUnicodeBiDiH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBaseViewer.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmUnicodeBiDiViewer : public TfrmBaseViewer
{
	typedef TfrmBaseViewer inherited;

__published:
	TSkLabel *lblResult;
public:
	__fastcall TfrmUnicodeBiDiViewer(TComponent* Owner) override : TfrmBaseViewer(Owner) {}
	HIDESBASE void Show(const String ATitle, const String ADescription, const String AText, const String ABiDiRegionDescription);
};

#endif
