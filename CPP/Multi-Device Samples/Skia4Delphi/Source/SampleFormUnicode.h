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

class TfrmUnicode : public TfrmBase
{
__published:
	TSpeedButton *btnBiDiIterator;
	TSkLabel *lblBiDiIteratorTitle;
	TSkLabel *lblBiDiIteratorDescription;
	TSpeedButton *btnGraphemeIterator;
	TSkLabel *lblGraphemeIteratorTitle;
	TSkLabel *lblGraphemeIteratorDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnBiDiIteratorClick(TObject* Sender);
	void __fastcall btnGraphemeIteratorClick(TObject* Sender);
public:
	__fastcall TfrmUnicode(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
