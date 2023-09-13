//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormRuntimeEffectsH
#define SampleFormRuntimeEffectsH
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

class TfrmRuntimeEffects : public TfrmBase
{
__published:
	TSpeedButton *btnShaderAnimation;
	TSkLabel *lblShaderAnimationTitle;
	TSkLabel *lblShaderAnimationDescription;
	TSpeedButton *btnShaderWithMouse;
	TSkLabel *lblShaderWithMouseTitle;
	TSkLabel *lblShaderWithMouseDescription;
	TSpeedButton *btnWavesShaderAnimation;
	TSkLabel *lblWavesShaderAnimationTitle;
	TSkLabel *lblWavesShaderAnimationDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnShaderAnimationClick(TObject* Sender);
	void __fastcall btnShaderWithMouseClick(TObject* Sender);
	void __fastcall btnWavesShaderAnimationClick(TObject* Sender);
public:
	__fastcall TfrmRuntimeEffects(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
