//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormViewerPaintBoxH
#define SampleFormViewerPaintBoxH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "SampleFormBaseViewer.h"
#include <FMX.Skia.hpp>
#include <System.Skia.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------

typedef std::function<void(ISkCanvas* const ACanvas, const TRectF& ADest)> TPaintBoxDrawProc;
typedef std::function<void(const TPointF& APoint, bool& AShouldRedraw)> TMouseDownProc;
typedef std::function<void(const TPointF& APoint, const bool AIsMouseDown, bool& AShouldRedraw)> TMouseMoveProc;
typedef std::function<void(const TPointF& APoint, bool& AShouldRedraw)> TMouseUpProc;

class TfrmPaintBoxViewer : public TfrmBaseViewer
{
	typedef TfrmBaseViewer inherited;

__published:
	TSkPaintBox *pbxDraw;
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall pbxDrawDraw(TObject* ASender, ISkCanvas* const ACanvas, const TRectF& ADest, const float AOpacity);
	void __fastcall pbxDrawMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall pbxDrawMouseMove(TObject* Sender, TShiftState Shift, float X, float Y);
	void __fastcall pbxDrawMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
private:
	TPaintBoxDrawProc FDrawProc;
	bool FIsMouseDown;
	TMouseDownProc FOnMouseDown;
	TMouseMoveProc FOnMouseMove;
	TMouseUpProc FOnMouseUp;
protected:
	void OptionsChanged() override;
public:
	__fastcall TfrmPaintBoxViewer(TComponent* Owner) override : TfrmBaseViewer(Owner) {}
	HIDESBASE void Show(const String ATitle, const String ADescription, const TPaintBoxDrawProc ADrawProc, TBackgroundKind ABackgroundKind = TBackgroundKind::Chess, TViewerOptions* AOptions = nullptr);
	HIDESBASE void Show(const String ATitle, const String ADescription, const float ADrawWidth, const float ADrawHeight, const TPaintBoxDrawProc ADrawProc, TBackgroundKind ABackgroundKind = TBackgroundKind::Chess, TViewerOptions* AOptions = nullptr);
	__property TMouseDownProc OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property TMouseMoveProc OnMouseMove = {read=FOnMouseMove, write=FOnMouseMove};
	__property TMouseUpProc OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
};

#endif
