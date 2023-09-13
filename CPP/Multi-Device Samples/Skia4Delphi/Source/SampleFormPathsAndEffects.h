//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormPathsAndEffectsH
#define SampleFormPathsAndEffectsH
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

class TfrmPathsAndEffects : public TfrmBase
{
__published:
	TSpeedButton *btnComposedPathEffect;
	TSkLabel *lblComposedPathEffectTitle;
	TSkLabel *lblComposedPathEffectDescription;
	TSpeedButton *btnDiscretePathEffect;
	TSkLabel *lblDiscretePathEffectTitle;
	TSkLabel *lblDiscretePathEffectDescription;
	TSpeedButton *btnPathFillTypes;
	TSkLabel *lblPathFillTypesTitle;
	TSkLabel *lblPathFillTypesDescription;
	TSpeedButton *btnRoundingSharpCorners;
	TSkLabel *lblRoundingSharpCornersTitle;
	TSkLabel *lblRoundingSharpCornersDescription;
	TSpeedButton *btnShaders;
	TSkLabel *lblShadersTitle;
	TSkLabel *lblShadersDescription;
	TSpeedButton *btnSumPathEffect;
	TSkLabel *lblSumPathEffectTitle;
	TSkLabel *lblSumPathEffectDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnComposedPathEffectClick(TObject* Sender);
	void __fastcall btnDiscretePathEffectClick(TObject* Sender);
	void __fastcall btnPathFillTypesClick(TObject* Sender);
	void __fastcall btnRoundingSharpCornersClick(TObject* Sender);
	void __fastcall btnShadersClick(TObject* Sender);
	void __fastcall btnSumPathEffectClick(TObject* Sender);
public:
	__fastcall TfrmPathsAndEffects(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
