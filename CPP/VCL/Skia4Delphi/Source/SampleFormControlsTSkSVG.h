//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormControlsTSkSVGH
#define SampleFormControlsTSkSVGH
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

class TfrmTSkSVG : public TfrmBase
{
__published:
	TPanel *pnlPanda;
	TSkLabel *lblPandaDescription;
	TSkLabel *lblPandaTitle;
	TSkSvg *svgPandaArrow;
	TPanel *pnlPandaLine;
	TPanel *pnlCBuilder;
	TSkLabel *lblCBuilderDescription;
	TSkLabel *lblCBuilderTitle;
	TSkSvg *svgCBuilderArrow;
	TPanel *pnlCBuilderLine;
	TPanel *pnlEditingElement;
	TSkLabel *lblEditingElementDescription;
	TSkLabel *lblEditingElementTitle;
	TSkSvg *svgEditingElementArrow;
	TPanel *pnlEditingElementLine;
	TPanel *pnlCustomColor;
	TSkLabel *lblCustomColorDescription;
	TSkLabel *lblCustomColorTitle;
	TSkSvg *svgCustomColorArrow;
	TPanel *pnlCustomColorLine;
	TPanel *pnlTileWrapMode;
	TSkLabel *lblTileWrapModeDescription;
	TSkLabel *lblTileWrapModeTitle;
	TSkSvg *svgTileWrapModeArrow;
	TPanel *pnlTileWrapModeLine;
	void __fastcall pnlCBuilderClick(TObject* Sender);
	void __fastcall pnlCustomColorClick(TObject* Sender);
	void __fastcall pnlEditingElementClick(TObject* Sender);
	void __fastcall pnlPandaClick(TObject* Sender);
	void __fastcall pnlTileWrapModeClick(TObject* Sender);
public:
	__fastcall TfrmTSkSVG(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
