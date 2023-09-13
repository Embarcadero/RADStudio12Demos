//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormControlsTSkAnimatedImageH
#define SampleFormControlsTSkAnimatedImageH
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

class TfrmTSkAnimatedImage : public TfrmBase
{
__published:
	TPanel *pnlLottieLoadings;
	TSkLabel *lblLottieLoadingsDescription;
	TSkLabel *lblLottieLoadingsTitle;
	TSkSvg *svgLottieLoadingsArrow;
	TPanel *pnlLottieLoadingsLine;
	TPanel *pnlAnimatedGIF;
	TSkLabel *lblAnimatedGIFDescription;
	TSkLabel *lblAnimatedGIFTitle;
	TSkSvg *svgAnimatedGIFArrow;
	TPanel *pnlAnimatedGIFLine;
	TPanel *pnlTelegramStickers;
	TSkLabel *lblTelegramStickersDescription;
	TSkLabel *lblTelegramStickersTitle;
	TSkSvg *svgTelegramStickersArrow;
	TPanel *pnlTelegramStickersLine;
	TPanel *pnlAnimatedWebP;
	TSkLabel *lblAnimatedWebPDescription;
	TSkLabel *lblAnimatedWebPTitle;
	TSkSvg *svgAnimatedWebPArrow;
	TPanel *pnlAnimatedWebPLine;
	TPanel *pnlLottieRocket;
	TSkLabel *lblLottieRocketDescription;
	TSkLabel *lblLottieRocketTitle;
	TSkSvg *svgLottieRocketArrow;
	TPanel *pnlLottieRocketLine;
	TPanel *pnlLottieCheck;
	TSkLabel *lblLottieCheckDescription;
	TSkLabel *lblLottieCheckTitle;
	TSkSvg *svgLottieCheckArrow;
	TPanel *pnlLottieCheckLine;
	void __fastcall pnlAnimatedGIFClick(TObject* Sender);
	void __fastcall pnlAnimatedWebPClick(TObject* Sender);
	void __fastcall pnlLottieCheckClick(TObject* Sender);
	void __fastcall pnlLottieLoadingsClick(TObject* Sender);
	void __fastcall pnlLottieRocketClick(TObject* Sender);
	void __fastcall pnlTelegramStickersClick(TObject* Sender);
public:
	__fastcall TfrmTSkAnimatedImage(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
