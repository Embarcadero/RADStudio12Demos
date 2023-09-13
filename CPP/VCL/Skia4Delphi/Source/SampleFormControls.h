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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBase.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmControls : public TfrmBase
{
__published:
	TPanel *pnlTSkAnimatedImage;
	TSkLabel *lblTSkAnimatedImageDescription;
	TSkLabel *lblTSkAnimatedImageTitle;
	TSkSvg *svgTSkAnimatedImageArrow;
	TPanel *pnlTSkAnimatedImageLine;
	TPanel *pnlTSkLabel;
	TSkLabel *lblTSkLabelDescription;
	TSkLabel *lblTSkLabelTitle;
	TSkSvg *svgTSkLabelArrow;
	TPanel *pnlTSkLabelLine;
	TPanel *pnlTSkPaintBox;
	TSkLabel *lblTSkPaintBoxDescription;
	TSkLabel *lblTSkPaintBoxTitle;
	TSkSvg *svgTSkPaintBoxArrow;
	TPanel *pnlTSkPaintBoxLine;
	TPanel *pnlTSkSVG;
	TSkLabel *lblTSkSVGDescription;
	TSkLabel *lblTSkSVGTitle;
	TSkSvg *svgTSkSVGArrow;
	TPanel *pnlTSkSVGLine;
	void __fastcall pnlTSkAnimatedImageClick(TObject* Sender);
	void __fastcall pnlTSkLabelClick(TObject* Sender);
	void __fastcall pnlTSkPaintBoxClick(TObject* Sender);
	void __fastcall pnlTSkSVGClick(TObject* Sender);
public:
	__fastcall TfrmControls(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
