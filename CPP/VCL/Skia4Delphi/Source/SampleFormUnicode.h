//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormUnicodeH
#define SampleFormUnicodeH
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

class TfrmUnicode : public TfrmBase
{
__published:
	TPanel *pnlGraphemeIterator;
	TSkLabel *lblGraphemeIteratorDescription;
	TSkLabel *lblGraphemeIteratorTitle;
	TSkSvg *svgGraphemeIteratorArrow;
	TPanel *pnlGraphemeIteratorLine;
	TPanel *pnlBiDiIterator;
	TSkLabel *lblBiDiIteratorDescription;
	TSkLabel *lblBiDiIteratorTitle;
	TSkSvg *svgBiDiIteratorArrow;
	TPanel *pnlBiDiIteratorLine;
	void __fastcall pnlBiDiIteratorClick(TObject* Sender);
	void __fastcall pnlGraphemeIteratorClick(TObject* Sender);
public:
	__fastcall TfrmUnicode(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
