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

class TfrmTSkSVG : public TfrmBase
{
__published:
	TSpeedButton *btnCustomColor;
	TSkLabel *lblCustomColorTitle;
	TSkLabel *lblCustomColorDescription;
	TSpeedButton *btnCBuilder;
	TSkLabel *lblCBuilderTitle;
	TSkLabel *lblCBuilderDescription;
	TSpeedButton *btnEditingElement;
	TSkLabel *lblEditingElementTitle;
	TSkLabel *lblEditingElementDescription;
	TSpeedButton *btnGorilla;
	TSkLabel *lblGorillaTitle;
	TSkLabel *lblGorillaDescription;
	TSpeedButton *btnTileWrapMode;
	TSkLabel *lblTileWrapModeTitle;
	TSkLabel *lblTileWrapModeDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnCBuilderClick(TObject* Sender);
	void __fastcall btnCustomColorClick(TObject* Sender);
	void __fastcall btnEditingElementClick(TObject* Sender);
	void __fastcall btnGorillaClick(TObject* Sender);
	void __fastcall btnTileWrapModeClick(TObject* Sender);
public:
	__fastcall TfrmTSkSVG(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
