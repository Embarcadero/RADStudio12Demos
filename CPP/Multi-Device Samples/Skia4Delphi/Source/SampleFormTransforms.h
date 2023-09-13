//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormTransformsH
#define SampleFormTransformsH
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

class TfrmTransforms : public TfrmBase
{
__published:
	TSpeedButton *btn3DRotation;
	TSkLabel *lbl3DRotationTitle;
	TSkLabel *lbl3DRotationDescription;
	TSpeedButton *btnStrechedCorners;
	TSkLabel *lblStrechedCornersTitle;
	TSkLabel *lblStrechedCornersDescription;
	TSpeedButton *btnTaperTransform;
	TSkLabel *lblTaperTransformTitle;
	TSkLabel *lblTaperTransformDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btn3DRotationClick(TObject* Sender);
	void __fastcall btnStrechedCornersClick(TObject* Sender);
	void __fastcall btnTaperTransformClick(TObject* Sender);
public:
	__fastcall TfrmTransforms(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
