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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBase.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmPathsAndEffects : public TfrmBase
{
__published:
	TPanel *pnlDiscretePathEffect;
	TSkLabel *lblDiscretePathEffectDescription;
	TSkLabel *lblDiscretePathEffectTitle;
	TSkSvg *svgDiscretePathEffectArrow;
	TPanel *pnlDiscretePathEffectLine;
	TPanel *pnlComposedPathEffect;
	TSkLabel *lblComposedPathEffectDescription;
	TSkLabel *lblComposedPathEffectTitle;
	TSkSvg *svgComposedPathEffectArrow;
	TPanel *pnlComposedPathEffectLine;
	TPanel *pnlSumPathEffect;
	TSkLabel *lblSumPathEffectDescription;
	TSkLabel *lblSumPathEffectTitle;
	TSkSvg *svgSumPathEffectArrow;
	TPanel *pnlSumPathEffectLine;
	TPanel *pnlShaders;
	TSkLabel *lblShadersDescription;
	TSkLabel *lblShadersTitle;
	TSkSvg *svgShadersArrow;
	TPanel *pnlShadersLine;
	TPanel *pnlPathFillTypes;
	TSkLabel *lblPathFillTypesDescription;
	TSkLabel *lblPathFillTypesTitle;
	TSkSvg *svgPathFillTypesArrow;
	TPanel *pnlPathFillTypesLine;
	TPanel *pnlRoundingSharpCorners;
	TSkLabel *lblRoundingSharpCornersDescription;
	TSkLabel *lblRoundingSharpCornersTitle;
	TSkSvg *svgRoundingSharpCornersArrow;
	TPanel *pnlRoundingSharpCornersLine;
	void __fastcall pnlComposedPathEffectClick(TObject* Sender);
	void __fastcall pnlDiscretePathEffectClick(TObject* Sender);
	void __fastcall pnlPathFillTypesClick(TObject* Sender);
	void __fastcall pnlRoundingSharpCornersClick(TObject* Sender);
	void __fastcall pnlShadersClick(TObject* Sender);
	void __fastcall pnlSumPathEffectClick(TObject* Sender);
public:
	__fastcall TfrmPathsAndEffects(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
