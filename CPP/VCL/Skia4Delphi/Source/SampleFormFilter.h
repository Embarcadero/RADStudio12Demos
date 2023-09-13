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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBase.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmFilter : public TfrmBase
{
__published:
	TPanel *pnlVignette;
	TSkLabel *lblVignetteDescription;
	TSkLabel *lblVignetteTitle;
	TSkSvg *svgVignetteArrow;
	TPanel *pnlVignetteLine;
	TPanel *pnlHueSaturation;
	TSkLabel *lblHueSaturationDescription;
	TSkLabel *lblHueSaturationTitle;
	TSkSvg *svgHueSaturationArrow;
	TPanel *pnlHueSaturationLine;
	TPanel *pnlCommonColorFilter;
	TSkLabel *lblCommonColorFilterDescription;
	TSkLabel *lblCommonColorFilterTitle;
	TSkSvg *svgCommonColorFilterArrow;
	TPanel *pnlCommonColorFilterLine;
	TPanel *pnlBrightnessContrast;
	TSkLabel *lblBrightnessContrastDescription;
	TSkLabel *lblBrightnessContrastTitle;
	TSkSvg *svgBrightnessContrastArrow;
	TPanel *pnlBrightnessContrastLine;
	TPanel *pnlDropShadow;
	TSkLabel *lblDropShadowDescription;
	TSkLabel *lblDropShadowTitle;
	TSkSvg *svgDropShadowArrow;
	TPanel *pnlDropShadowLine;
	TPanel *pnlLightingEffects;
	TSkLabel *lblLightingEffectsDescription;
	TSkLabel *lblLightingEffectsTitle;
	TSkSvg *svgLightingEffectsArrow;
	TPanel *pnlLightingEffectsLine;
	void __fastcall pnlBrightnessContrastClick(TObject* Sender);
	void __fastcall pnlCommonColorFilterClick(TObject* Sender);
	void __fastcall pnlDropShadowClick(TObject* Sender);
	void __fastcall pnlHueSaturationClick(TObject* Sender);
	void __fastcall pnlLightingEffectsClick(TObject* Sender);
	void __fastcall pnlVignetteClick(TObject* Sender);
public:
	__fastcall TfrmFilter(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
