//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormImageH
#define SampleFormImageH
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

class TfrmImage : public TfrmBase
{
__published:
	TPanel *pnlEncodeWebpVsJpeg;
	TSkLabel *lblEncodeWebpVsJpegDescription;
	TSkLabel *lblEncodeWebpVsJpegTitle;
	TSkSvg *svgEncodeWebpVsJpegArrow;
	TPanel *pnlEncodeWebpVsJpegLine;
	TPanel *pnlNinePatch;
	TSkLabel *lblNinePatchDescription;
	TSkLabel *lblNinePatchTitle;
	TSkSvg *svgNinePatchArrow;
	TPanel *pnlNinePatchLine;
	TPanel *pnlWebpInImage;
	TSkLabel *lblWebpInImageDescription;
	TSkLabel *lblWebpInImageTitle;
	TSkSvg *svgWebpInImageArrow;
	TPanel *pnlWebpInImageLine;
	void __fastcall pnlEncodeWebpVsJpegClick(TObject* Sender);
	void __fastcall pnlNinePatchClick(TObject* Sender);
	void __fastcall pnlWebpInImageClick(TObject* Sender);
public:
	__fastcall TfrmImage(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
