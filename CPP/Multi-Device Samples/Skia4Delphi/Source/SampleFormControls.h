//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormControlsH
#define SampleFormControlsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "SampleFormBase.h"
#include <FMX.Skia.hpp>
#include <System.Skia.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------

class TfrmControls : public TfrmBase
{
__published:
	TSpeedButton* btnTSkSVG;
	TSkLabel* lblTSkSVGTitle;
	TSkLabel* lblTSkSVGDescription;
	TSpeedButton* btnTSkPaintBox;
	TSkLabel* lblTSkPaintBoxTitle;
	TSkLabel* lblTSkPaintBoxDescription;
	TSpeedButton* btnTSkLabel;
	TSkLabel* lblTSkLabelTitle;
	TSkLabel* lblTSkLabelDescription;
	TSpeedButton* btnTSkAnimatedImage;
	TSkLabel* lblTSkAnimatedImageTitle;
	TSkLabel* lblTSkAnimatedImageDescription;
	TLayout* lytContentTopOffset;
	void __fastcall btnTSkAnimatedImageClick(TObject* Sender);
	void __fastcall btnTSkLabelClick(TObject* Sender);
	void __fastcall btnTSkPaintBoxClick(TObject* Sender);
	void __fastcall btnTSkSVGClick(TObject* Sender);
public:
	__fastcall TfrmControls(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
