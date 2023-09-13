//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormBasicsH
#define SampleFormBasicsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.Skia.hpp>
#include <FMX.Skia.hpp>
#include "SampleFormBase.h"
//---------------------------------------------------------------------------

class TfrmBasics : public TfrmBase
{
__published:
	TSpeedButton* btnTransformations;
	TSkLabel* lblTransformationsTitle;
	TSkLabel* lblTransformationsDescription;
	TSpeedButton* btnCurves;
	TSkLabel* lblCurvesTitle;
	TSkLabel* lblCurvesDescription;
	TSpeedButton* btnEllipsesAndRectangles;
	TSkLabel* lblEllipsesAndRectanglesTitle;
	TSkLabel* lblEllipsesAndRectanglesDescription;
	TSpeedButton* btnHatching;
	TSkLabel* lblHatchingTitle;
	TSkLabel* lblHatchingDescription;
	TLayout* lytContentTopOffset;
	void __fastcall btnCurvesClick(TObject* Sender);
	void __fastcall btnEllipsesAndRectanglesClick(TObject* Sender);
	void __fastcall btnHatchingClick(TObject* Sender);
	void __fastcall btnTransformationsClick(TObject* Sender);
public:
	__fastcall TfrmBasics(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
