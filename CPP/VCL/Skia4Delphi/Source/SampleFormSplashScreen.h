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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBase.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmSplashScreen : public TfrmBase
{
	typedef TfrmBase inherited;

__published:
	TGridPanel *gplBottomText;
	TSkLabel *lblBottomTextLeft;
	TSkLabel *lblBottomTextRight;
	TSkSvg *svgHeart;
	TSkSvg *svgLogoBackground;
	TSkAnimatedImage *aimLogoForeground;
	TPanel *pnlLogo;
	TSkAnimatedPaintBox *apbBackForm;
	void __fastcall aimLogoForegroundAnimationFinish(TObject* Sender);
	void __fastcall apbBackFormAnimationDraw(TObject* ASender, ISkCanvas* const ACanvas, const TRectF& ADest, const double AProgress, const float AOpacity);
	void __fastcall pnlContentAlignPosition(TWinControl* Sender, TControl* Control, int& NewLeft, int& NewTop, int& NewWidth, int& NewHeight, TRect& AlignRect, TAlignInfo& AlignInfo);
private:
	_di_ISkImage FBackFormImage;
	_di_ISkImage FFrontFormImage;
protected:
	TColor FormBackgroundColor() override;
public:
	__fastcall TfrmSplashScreen(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
