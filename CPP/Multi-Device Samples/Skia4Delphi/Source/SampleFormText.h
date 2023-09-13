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
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "SampleFormBase.h"
#include <FMX.Skia.hpp>
#include <System.Skia.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------

class TfrmText : public TfrmBase
{
__published:
	TSpeedButton *btnBasicTexts;
	TSkLabel *lblBasicTextsTitle;
	TSkLabel *lblBasicTextsDescription;
	TSpeedButton *btnCustomFont;
	TSkLabel *lblCustomFontTitle;
	TSkLabel *lblCustomFontDescription;
	TSpeedButton *btnParagraph;
	TSkLabel *lblParagraphTitle;
	TSkLabel *lblParagraphDescription;
	TSpeedButton *btnParagraphToPath;
	TSkLabel *lblParagraphToPathTitle;
	TSkLabel *lblParagraphToPathDescription;
	TSpeedButton *btnRTL;
	TSkLabel *lblRTLTitle;
	TSkLabel *lblRTLDescription;
	TSpeedButton *btnTSkLabel;
	TSkLabel *lblTSkLabelTitle;
	TSkLabel *lblTSkLabelDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnBasicTextsClick(TObject* Sender);
	void __fastcall btnCustomFontClick(TObject* Sender);
	void __fastcall btnParagraphClick(TObject* Sender);
	void __fastcall btnParagraphToPathClick(TObject* Sender);
	void __fastcall btnRTLClick(TObject* Sender);
	void __fastcall btnTSkLabelClick(TObject* Sender);
private:
public:
	__fastcall TfrmText(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
