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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBase.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmRuntimeEffects : public TfrmBase
{
__published:
	TPanel *pnlShaderAnimation;
	TSkLabel *lblShaderAnimationDescription;
	TSkLabel *lblShaderAnimationTitle;
	TSkSvg *svgShaderAnimationArrow;
	TPanel *pnlShaderAnimationLine;
	TPanel *pnlShaderWithMouse;
	TSkLabel *lblShaderWithMouseDescription;
	TSkLabel *lblShaderWithMouseTitle;
	TSkSvg *svgShaderWithMouseArrow;
	TPanel *pnlShaderWithMouseLine;
	TPanel *pnlWavesShaderAnimation;
	TSkLabel *lblWavesShaderAnimationDescription;
	TSkLabel *lblWavesShaderAnimationTitle;
	TSkSvg *svgWavesShaderAnimationArrow;
	TPanel *pnlWavesShaderAnimationLine;
	void __fastcall pnlShaderAnimationClick(TObject* Sender);
	void __fastcall pnlShaderWithMouseClick(TObject* Sender);
	void __fastcall pnlWavesShaderAnimationClick(TObject* Sender);
public:
	__fastcall TfrmRuntimeEffects(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
