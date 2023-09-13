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

class TfrmTSkLabel : public TfrmBase
{
__published:
	TSpeedButton *btnCustomFontFamily;
	TSkLabel *lvlCustomFontFamilyTitle;
	TSkLabel *lblCustomFontFamilyDescription;
	TSpeedButton *btnFamiliesFallbacks;
	TSkLabel *lblFamiliesFallbacksTitle;
	TSkLabel *lblFamiliesFallbacksDescription;
	TSpeedButton *btnFontWeight;
	TSkLabel *lblFontWeightTitle;
	TSkLabel *lblFontWeightDescription;
	TSpeedButton *btnJustifiedText;
	TSkLabel *lblJustifiedTextTitle;
	TSkLabel *lblJustifiedTextDescription;
	TSpeedButton *btnMaxLines;
	TSkLabel *lblMaxLinesTitle;
	TSkLabel *lblMaxLinesDescription;
	TSpeedButton *btnMultiStyle;
	TSkLabel *lblMultiStyleTitle;
	TSkLabel *lblMultiStyleDescription;
	TSpeedButton *btnRTL;
	TSkLabel *lblRTLTitle;
	TSkLabel *lblRTLDescription;
	TSpeedButton *btnWordOnClickEvent;
	TSkLabel *lblWordOnClickEventTitle;
	TSkLabel *lblWordOnClickEventDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnCustomFontFamilyClick(TObject* Sender);
	void __fastcall btnFamiliesFallbacksClick(TObject* Sender);
	void __fastcall btnFontWeightClick(TObject* Sender);
	void __fastcall btnJustifiedTextClick(TObject* Sender);
	void __fastcall btnMaxLinesClick(TObject* Sender);
	void __fastcall btnMultiStyleClick(TObject* Sender);
	void __fastcall btnRTLClick(TObject* Sender);
	void __fastcall btnWordOnClickEventClick(TObject* Sender);
private:
	void __fastcall OnWordClick(TObject* Sender);
public:
	__fastcall TfrmTSkLabel(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
