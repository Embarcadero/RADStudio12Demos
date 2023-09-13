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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBase.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmTransforms : public TfrmBase
{
__published:
	TPanel *pnlTaperTransform;
	TSkLabel *lblTaperTransformDescription;
	TSkLabel *lblTaperTransformTitle;
	TSkSvg *svgTaperTransformArrow;
	TPanel *pnlTaperTransformLine;
	TPanel *pnlStrechedCorners;
	TSkLabel *lblStrechedCornersDescription;
	TSkLabel *lblStrechedCornersTitle;
	TSkSvg *svgStrechedCornersArrow;
	TPanel *pnlStrechedCornersLine;
	TPanel *pnl3DRotation;
	TSkLabel *lbl3DRotationDescription;
	TSkLabel *lbl3DRotationTitle;
	TSkSvg *svg3DRotationArrow;
	TPanel *pnl3DRotationLine;
	void __fastcall pnl3DRotationClick(TObject* Sender);
	void __fastcall pnlStrechedCornersClick(TObject* Sender);
	void __fastcall pnlTaperTransformClick(TObject* Sender);
public:
	__fastcall TfrmTransforms(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
