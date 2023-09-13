//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormSplashScreenH
#define SampleFormSplashScreenH
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
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------

class TfrmSplashScreen : public TfrmBase
{
	typedef TfrmBase inherited;

__published:
    TSkSvg *svgLogoBackground;
    TSkAnimatedImage *aimLogoForeground;
    TGridPanelLayout *gplBottomText;
    TSkSvg *svgHeart;
    TSkLabel *lblBottomTextLeft;
    TSkLabel *lblBottomTextRight;
    TFloatAnimation *fanFadeOut;
    TLayout *lytSplashContent;
    TFloatAnimation *fanFadeIn;
	void __fastcall aimLogoForegroundAnimationFinish(TObject* Sender);
	void __fastcall rctContentPaint(TObject* Sender, TCanvas* Canvas, const TRectF& ARect);
protected:
	TAlphaColor FormBackgroundColor() override;
    bool HasBottomContent() override;
public:
    __fastcall TfrmSplashScreen(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
