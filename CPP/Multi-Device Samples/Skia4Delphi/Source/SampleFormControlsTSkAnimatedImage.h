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

class TfrmTSkAnimatedImage : public TfrmBase
{
__published:
	TSpeedButton *btnAnimatedGIF;
	TSkLabel *lblAnimatedGIFTitle;
	TSkLabel *lblAnimatedGIFDescription;
	TSpeedButton *btnAnimatedWebP;
	TSkLabel *lblAnimatedWebPTitle;
	TSkLabel *lblAnimatedWebPDescription;
	TSpeedButton *btnLottieCheck;
	TSkLabel *lblLottieCheckTitle;
	TSkLabel *lblLottieCheckDescription;
	TSpeedButton *btnLottieLoadings;
	TSkLabel *lblLottieLoadingsTitle;
	TSkLabel *lblLottieLoadingsDescription;
	TSpeedButton *btnLottieRocket;
	TSkLabel *lblLottieRocketTitle;
	TSkLabel *lblLottieRocketDescription;
	TSpeedButton *btnTelegramStickers;
	TSkLabel *lblTelegramStickersTitle;
	TSkLabel *lblTelegramStickersDescription;
	TLayout *lytContentTopOffset;
	void __fastcall btnAnimatedGIFClick(TObject* Sender);
	void __fastcall btnAnimatedWebPClick(TObject* Sender);
	void __fastcall btnLottieCheckClick(TObject* Sender);
	void __fastcall btnLottieLoadingsClick(TObject* Sender);
	void __fastcall btnLottieRocketClick(TObject* Sender);
	void __fastcall btnTelegramStickersClick(TObject* Sender);
public:
	__fastcall TfrmTSkAnimatedImage(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
