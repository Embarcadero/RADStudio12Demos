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
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "SampleFormBase.h"
//---------------------------------------------------------------------------

class TfrmMain : public TfrmBase
{
__published:
    TPanel *pnlBasics;
    TSkLabel *lblBasicsDescription;
    TSkLabel *lblBasicsTitle;
    TSkSvg *svgBasicsArrow;
    TPanel *pnlBasicsLine;
    TPanel *pnlControls;
    TSkLabel *lblControlsDescription;
    TSkLabel *lblControlsTitle;
    TSkSvg *svgControlsArrow;
    TPanel *pnlControlsLine;
    TPanel *pnlDocuments;
    TSkLabel *lblDocumentsDescription;
    TSkLabel *lblDocumentsTitle;
    TSkSvg *svgDocumentsArrow;
    TPanel *pnlDocumentsLine;
    TPanel *pnlImage;
    TSkLabel *lblImageDescription;
    TSkLabel *lblImageTitle;
    TSkSvg *svgImageArrow;
    TPanel *pnlImageLine;
    TPanel *pnlPathsAndEffects;
    TSkLabel *lblPathsAndEffectsDescription;
    TSkLabel *lblPathsAndEffectsTitle;
    TSkSvg *svgPathsAndEffectsArrow;
    TPanel *pnlPathsAndEffectsLine;
    TPanel *pnlRuntimeEffects;
    TSkLabel *lblRuntimeEffectsDescription;
    TSkLabel *lblRuntimeEffectsTitle;
    TSkSvg *svgRuntimeEffectsArrow;
    TPanel *pnlRuntimeEffectsLine;
    TPanel *pnlText;
    TSkLabel *lblTextDescription;
    TSkLabel *lblTextTitle;
    TSkSvg *svgTextArrow;
    TPanel *pnlTextLine;
    TPanel *pnlUnicode;
    TSkLabel *lblUnicodeDescription;
    TSkLabel *lblUnicodeTitle;
    TSkSvg *svgUnicodeArrow;
    TPanel *pnlUnicodeLine;
    TPanel *pnlTransforms;
    TSkLabel *lblTransformsDescription;
    TSkLabel *lblTransformsTitle;
    TSkSvg *svgTransformsArrow;
    TPanel *pnlFilter;
    TSkLabel *lblFilterDescription;
    TSkLabel *lblFilterTitle;
    TSkSvg *svgFilterArrow;
    TPanel *pnlFilterLine;
    TPanel *pnlTransformsLine;
    void __fastcall FormShow(TObject* Sender);
    void __fastcall pnlBasicsClick(TObject* Sender);
    void __fastcall pnlControlsClick(TObject* Sender);
    void __fastcall pnlDocumentsClick(TObject* Sender);
    void __fastcall pnlFilterClick(TObject* Sender);
    void __fastcall pnlImageClick(TObject* Sender);
    void __fastcall pnlPathsAndEffectsClick(TObject* Sender);
    void __fastcall pnlRuntimeEffectsClick(TObject* Sender);
    void __fastcall pnlTextClick(TObject* Sender);
    void __fastcall pnlTransformsClick(TObject* Sender);
    void __fastcall pnlUnicodeClick(TObject* Sender);
public:
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
