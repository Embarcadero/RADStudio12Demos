//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormControlsTSkPaintBoxH
#define SampleFormControlsTSkPaintBoxH
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

class TfrmTSkPaintBox : public TfrmBase
{
__published:
	TSpeedButton *btnFreehand;
	TSkLabel *lblFreehandTitle;
	TSkLabel *lblFreehandDescription;
	TSpeedButton *btnSweepGradient;
	TSkLabel *lblSweepGradientTitle;
	TSkLabel *lblSweepGradientDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnFreehandClick(TObject* Sender);
	void __fastcall btnSweepGradientClick(TObject* Sender);
private:
	void __fastcall OnSweepGradientDraw(TObject* ASender, const _di_ISkCanvas ACanvas, const TRectF& ADest, const float AOpacity);
public:
	__fastcall TfrmTSkPaintBox(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
