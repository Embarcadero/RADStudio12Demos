//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormControlsTSkPaintBoxH
#define SampleFormControlsTSkPaintBoxH
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

class TfrmTSkPaintBox : public TfrmBase
{
__published:
	TPanel *pnlFreehand;
	TSkLabel *lblFreehandDescription;
	TSkLabel *lblFreehandTitle;
	TSkSvg *svgFreehandArrow;
	TPanel *pnlFreehandLine;
	TPanel *pnlSweepGradient;
	TSkLabel *lblSweepGradientDescription;
	TSkLabel *lblSweepGradientTitle;
	TSkSvg *svgSweepGradientArrow;
	TPanel *pnlSweepGradientLine;
	void __fastcall pnlFreehandClick(TObject* Sender);
	void __fastcall pnlSweepGradientClick(TObject* Sender);
private:
	void __fastcall OnSweepGradientDraw(TObject* ASender, const _di_ISkCanvas ACanvas, const TRectF& ADest, const float AOpacity);
public:
	__fastcall TfrmTSkPaintBox(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
