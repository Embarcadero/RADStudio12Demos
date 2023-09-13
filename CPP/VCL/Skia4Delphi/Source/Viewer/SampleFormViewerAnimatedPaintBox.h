//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormViewerAnimatedPaintBoxH
#define SampleFormViewerAnimatedPaintBoxH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SampleFormBaseViewer.h"
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

typedef std::function<void(ISkCanvas* const ACanvas, const TRectF& ADest, const double ASeconds)> TAnimatedPaintBoxDrawProc;
typedef std::function<void(const float AX, const float AY)> TMouseMoveProc;

class TfrmAnimatedPaintBoxViewer : public TfrmBaseViewer
{
	typedef TfrmBaseViewer inherited;

__published:
  TSkAnimatedPaintBox* apbDraw;
  void __fastcall apbDrawAnimationDraw(TObject* ASender, ISkCanvas* const ACanvas, const TRectF& ADest, const double AProgress, const float AOpacity);
  void __fastcall apbDrawMouseMove(TObject* Sender, TShiftState Shift, int X, int Y);
  void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
private:
	TAnimatedPaintBoxDrawProc FDrawProc;
	TMouseMoveProc FOnMouseMove;
	TSize GetDrawSize();
	void SetDrawSize(const TSize& AValue);
public:
	__fastcall TfrmAnimatedPaintBoxViewer(TComponent* Owner) override : TfrmBaseViewer(Owner) {}
	HIDESBASE void Show(const String ATitle, const String ADescription, int ADrawWidth, int ADrawHeight, const TAnimatedPaintBoxDrawProc ADrawProc, TViewerOptions* AOptions = nullptr);
	HIDESBASE void Show(const String ATitle, const String ADescription, const TAnimatedPaintBoxDrawProc ADrawProc, TViewerOptions* AOptions = nullptr);
	__property TSize DrawSize = {read=GetDrawSize, write=SetDrawSize};
	__property TMouseMoveProc OnMouseMove = {read=FOnMouseMove, write=FOnMouseMove};
	__property OnOptionsChange;
};

#endif
