//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormFilterH
#define SampleFormFilterH
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

class TfrmFilter : public TfrmBase
{
__published:
	TSpeedButton *btnBrightnessContrast;
	TSkLabel *lblBrightnessContrastTitle;
	TSkLabel *lblBrightnessContrastDescription;
	TSpeedButton *btnCommonColorFilter;
	TSkLabel *lblCommonColorFilterTitle;
	TSkLabel *lblCommonColorFilterDescription;
	TSpeedButton *btnDropShadow;
	TSkLabel *lblDropShadowTitle;
	TSkLabel *lblDropShadowDescription;
	TSpeedButton *btnHueSaturation;
	TSkLabel *lblHueSaturationTitle;
	TSkLabel *lblHueSaturationDescription;
	TSpeedButton *btnLightingEffects;
	TSkLabel *lblLightingEffectsTitle;
	TSkLabel *lblLightingEffectsDescription;
	TSpeedButton *btnVignette;
	TSkLabel *lblVignetteTitle;
	TSkLabel *lblVignetteDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnBrightnessContrastClick(TObject* Sender);
	void __fastcall btnCommonColorFilterClick(TObject* Sender);
	void __fastcall btnDropShadowClick(TObject* Sender);
	void __fastcall btnHueSaturationClick(TObject* Sender);
	void __fastcall btnLightingEffectsClick(TObject* Sender);
	void __fastcall btnVignetteClick(TObject* Sender);
public:
	__fastcall TfrmFilter(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
