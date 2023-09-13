//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormDocumentsH
#define SampleFormDocumentsH
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

class TfrmDocuments : public TfrmBase
{
__published:
	TPanel *pnlCreatePDFDrawingSVG;
	TSkLabel *lblCreatePDFDrawingSVGDescription;
	TSkLabel *lblCreatePDFDrawingSVGTitle;
	TSkSvg *svgCreatePDFDrawingSVGArrow;
	TPanel *pnlCreatePDFDrawingSVGLine;
	TPanel *pnlCreateXPSDrawingSVG;
	TSkLabel *lblCreateXPSDrawingSVGDescription;
	TSkLabel *lblCreateXPSDrawingSVGTitle;
	TSkSvg *svgCreateXPSDrawingSVGArrow;
	TPanel *pnlCreateXPSDrawingSVGLine;
	void __fastcall pnlCreatePDFDrawingSVGClick(TObject* Sender);
	void __fastcall pnlCreateXPSDrawingSVGClick(TObject* Sender);
private:
	void ViewPDF(String AFileName);
public:
	__fastcall TfrmDocuments(TComponent* Owner) override : TfrmBase(Owner) {}
};

#endif
