//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormViewerControlH
#define SampleFormViewerControlH
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

class TfrmControlViewer : public TfrmBaseViewer
{
	typedef TfrmBaseViewer inherited;

__published:
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
private:
	TControl* FControl;
	std::function<TControl*()> FControlCreationFunc;
protected:
	void OptionsChanged() override;
public:
	__fastcall TfrmControlViewer(TComponent* Owner) override : TfrmBaseViewer(Owner) {}
	HIDESBASE void Show(const String ATitle, const String ADescription, const std::function<TControl*()> AControlCreationFunc, TBackgroundKind ABackgroundKind = TBackgroundKind::Chess, TViewerOptions* AOptions = nullptr);
};

#endif
