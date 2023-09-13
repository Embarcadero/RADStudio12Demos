//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormBasicsH
#define SampleFormBasicsH
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

class TfrmBasics : public TfrmBase
{
__published:
	TPanel *pnlEllipsesAndRectangles;
	TSkLabel *lblEllipsesAndRectanglesDescription;
	TSkLabel *lblEllipsesAndRectanglesTitle;
	TSkSvg *svgEllipsesAndRectanglesArrow;
	TPanel *pnlEllipsesAndRectanglesLine;
	TPanel *pnlCurves;
	TSkLabel *lblCurvesDescription;
	TSkLabel *lblCurvesTitle;
	TSkSvg *svgCurvesArrow;
	TPanel *pnlCurvesLine;
	TPanel *pnlTransformations;
	TSkLabel *lblTransformationsDescription;
	TSkLabel *lblTransformationsTitle;
	TSkSvg *svgTransformationsArrow;
	TPanel *pnlTransformationsLine;
	TPanel *pnlHatching;
	TSkLabel *lblHatchingDescription;
	TSkLabel *lblHatchingTitle;
	TSkSvg *svgHatchingArrow;
	TPanel *pnlHatchingLine;
	void __fastcall pnlCurvesClick(TObject* Sender);
	void __fastcall pnlEllipsesAndRectanglesClick(TObject* Sender);
	void __fastcall pnlHatchingClick(TObject* Sender);
	void __fastcall pnlTransformationsClick(TObject* Sender);
public:
	__fastcall TfrmBasics(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
