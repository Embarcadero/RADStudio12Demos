//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormViewerTImageH
#define SampleFormViewerTImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Skia.hpp>
#include <FMX.Skia.hpp>
#include "SampleFormBaseViewer.h"
//---------------------------------------------------------------------------

typedef std::function<void(TImage* AImage)> TImageEditProc;

class TfrmTImageViewer : public TfrmBaseViewer
{
	typedef TfrmBaseViewer inherited;

__published:
	TImage *imgImage;
public:
	__fastcall TfrmTImageViewer(TComponent* Owner) override : TfrmBaseViewer(Owner) {}
	HIDESBASE void Show(const String ATitle, const String ADescription, const TImageEditProc AImageEditProc);
};

#endif
