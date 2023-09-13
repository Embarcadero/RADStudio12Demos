//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormControlsTSkLabelH
#define SampleFormControlsTSkLabelH
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

class TfrmTSkLabel : public TfrmBase
{
__published:
	TPanel *pnlMultiStyle;
	TSkLabel *lblMultiStyleDescription;
	TSkLabel *lblMultiStyleTitle;
	TSkSvg *svgMultiStyleArrow;
	TPanel *pnlMultiStyleLine;
	TPanel *pnlRTL;
	TSkLabel *lblRTLDescription;
	TSkLabel *lblRTLTitle;
	TSkSvg *svgRTLArrow;
	TPanel *pnlRTLLine;
	TPanel *pnlFontWeight;
	TSkLabel *lblFontWeightDescription;
	TSkLabel *lblFontWeightTitle;
	TSkSvg *svgFontWeightArrow;
	TPanel *pnlFontWeightLine;
	TPanel *pnlMaxLines;
	TSkLabel *lblMaxLinesDescription;
	TSkLabel *lblMaxLinesTitle;
	TSkSvg *svgMaxLinesArrow;
	TPanel *pnlMaxLinesLine;
	TPanel *pnlWordOnClickEvent;
	TSkLabel *lblWordOnClickEventDescription;
	TSkLabel *lblWordOnClickEventTitle;
	TSkSvg *svgWordOnClickEventArrow;
	TPanel *pnlWordOnClickEventLine;
	TPanel *pnlFamiliesFallbacks;
	TSkLabel *lblFamiliesFallbacksDescription;
	TSkLabel *lblFamiliesFallbacksTitle;
	TSkSvg *svgFamiliesFallbacksArrow;
	TPanel *pnlFamiliesFallbacksLine;
	TPanel *pnlJustifiedText;
	TSkLabel *lblJustifiedTextDescription;
	TSkLabel *lblJustifiedTextTitle;
	TSkSvg *svgJustifiedTextArrow;
	TPanel *pnlJustifiedTextLine;
	TPanel *pnlCustomFontFamily;
	TSkLabel *lblCustomFontFamilyDescription;
	TSkLabel *lblCustomFontFamilyTitle;
	TSkSvg *svgCustomFontFamilyArrow;
	TPanel *pnlCustomFontFamilyLine;
	void __fastcall pnlFamiliesFallbacksClick(TObject* Sender);
	void __fastcall pnlFontWeightClick(TObject* Sender);
	void __fastcall pnlJustifiedTextClick(TObject* Sender);
	void __fastcall pnlMaxLinesClick(TObject* Sender);
	void __fastcall pnlMultiStyleClick(TObject* Sender);
	void __fastcall pnlRTLClick(TObject* Sender);
	void __fastcall pnlWordOnClickEventClick(TObject* Sender);
	void __fastcall pnlCustomFontFamilyClick(TObject* Sender);
private:
	void __fastcall OnWordClick(TObject* Sender);
public:
	__fastcall TfrmTSkLabel(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
