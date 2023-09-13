//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormTextH
#define SampleFormTextH
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

class TfrmText : public TfrmBase
{
__published:
	TPanel *pnlBasicTexts;
	TSkLabel *lblBasicTextsDescription;
	TSkLabel *lblBasicTextsTitle;
	TSkSvg *svgBasicTextsArrow;
	TPanel *pnlBasicTextsLine;
	TPanel *pnlRTL;
	TSkLabel *lblRTLDescription;
	TSkLabel *lblRTLTitle;
	TSkSvg *svgRTLArrow;
	TPanel *pnlRTLLine;
	TPanel *pnlParagraph;
	TSkLabel *lblParagraphDescription;
	TSkLabel *lblParagraphTitle;
	TSkSvg *svgParagraphArrow;
	TPanel *pnlParagraphLine;
	TPanel *pnlCustomFont;
	TSkLabel *lblCustomFontDescription;
	TSkLabel *lblCustomFontTitle;
	TSkSvg *svgCustomFontArrow;
	TPanel *pnlCustomFontLine;
	TPanel *pnlParagraphToPath;
	TSkLabel *lblParagraphToPathDescription;
	TSkLabel *lblParagraphToPathTitle;
	TSkSvg *svgParagraphToPathArrow;
	TPanel *pnlParagraphToPathLine;
	TPanel *pnlTSkLabel;
	TSkLabel *lblTSkLabelDescription;
	TSkLabel *lblTSkLabelTitle;
	TSkSvg *svgTSkLabelArrow;
	TPanel *pnlTSkLabelLine;
	void __fastcall pnlBasicTextsClick(TObject* Sender);
	void __fastcall pnlCustomFontClick(TObject* Sender);
	void __fastcall pnlParagraphClick(TObject* Sender);
	void __fastcall pnlParagraphToPathClick(TObject* Sender);
	void __fastcall pnlRTLClick(TObject* Sender);
	void __fastcall pnlTSkLabelClick(TObject* Sender);
public:
	__fastcall TfrmText(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
