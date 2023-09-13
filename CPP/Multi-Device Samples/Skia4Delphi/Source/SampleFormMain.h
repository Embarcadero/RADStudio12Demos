//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

// Style created by https://www.delphistyles.com/

#ifndef SampleFormMainH
#define SampleFormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.Skia.hpp>
#include <FMX.Skia.hpp>
#include "SampleFormBase.h"
//---------------------------------------------------------------------------

class TfrmMain : public TfrmBase
{
__published:
	TSpeedButton *btnBasics;
	TSkLabel *lblBasicsTitle;
	TSkLabel *lblBasicsDescription;
	TSpeedButton *btnControls;
	TSkLabel *lblControlsTitle;
	TSkLabel *lblControlsDescription;
	TSpeedButton *btnDocuments;
	TSkLabel *lblDocumentsTitle;
	TSkLabel *lblDocumentsDescription;
	TSpeedButton *btnFilter;
	TSkLabel *lblFilterTitle;
	TSkLabel *lblFilterDescription;
	TSpeedButton *btnImage;
	TSkLabel *lblImageTitle;
	TSkLabel *lblImageDescription;
	TSpeedButton *btnPathsAndEffects;
	TSkLabel *lblPathsAndEffectsDescription;
	TSkLabel *lblPathsAndEffectsTitle;
	TSpeedButton *btnRuntimeEffects;
	TSkLabel *lblRuntimeEffectsTitle;
	TSkLabel *lblRuntimeEffectsDescription;
	TSpeedButton *btnText;
	TSkLabel *lblTextTitle;
	TSkLabel *lblTextDescription;
	TSpeedButton *btnTransforms;
	TSkLabel *lblTransformsTitle;
	TSkLabel *lblTransformsDescription;
	TSpeedButton *btnUnicode;
	TSkLabel *lblUnicodeTitle;
	TSkLabel *lblUnicodeDescription;
	TLayout *lytContentTopOffset;
	TStyleBook *stbStyle;
	void __fastcall btnBasicsClick(TObject* Sender);
	void __fastcall btnControlsClick(TObject* Sender);
	void __fastcall btnDocumentsClick(TObject* Sender);
	void __fastcall btnFilterClick(TObject* Sender);
	void __fastcall btnImageClick(TObject* Sender);
	void __fastcall btnPathsAndEffectsClick(TObject* Sender);
	void __fastcall btnRuntimeEffectsClick(TObject* Sender);
	void __fastcall btnTextClick(TObject* Sender);
	void __fastcall btnTransformsClick(TObject* Sender);
	void __fastcall btnUnicodeClick(TObject* Sender);
	void __fastcall FormShow(TObject *Sender);
public:
	__fastcall TfrmMain(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
