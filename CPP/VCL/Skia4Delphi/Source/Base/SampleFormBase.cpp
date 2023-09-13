//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include "SampleFormBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

std::vector<TfrmBase*> TfrmBase::FCreatedFormsList;
std::vector<TfrmBase*> TfrmBase::FShowingFormsList;

__fastcall TfrmBase::TfrmBase(TComponent* Owner)
	: TForm(Owner)
{
	if (Application->MainForm == nullptr)
		TStyleManager::TrySetStyle("Windows11 Modern Light", false);
}
//---------------------------------------------------------------------------

void TfrmBase::BeginUpdate()
{
	SendMessage(Application->MainForm->Handle, WM_SETREDRAW, int(false), 0);
	Application->MainForm->DisableAlign();
}
//---------------------------------------------------------------------------

void TfrmBase::CloseForm(TfrmBase* AForm)
{
	auto LFormIndex = find(FShowingFormsList.begin(), FShowingFormsList.end(), AForm);
	if (LFormIndex == FShowingFormsList.end())
		return;
	TCloseAction LAction = TCloseAction::caFree;
	AForm->DoClose(LAction);
	if (LAction == TCloseAction::caNone)
		return;
	if (LFormIndex == FShowingFormsList.begin()) {
		Application->Terminate();
	} else {
		LFormIndex = find(FCreatedFormsList.begin(), FCreatedFormsList.end(), AForm);
		assert(LFormIndex != FCreatedFormsList.end());
		((TfrmBase*) Application->MainForm)->BeginUpdate();
		try {
			for (auto it = prev(FCreatedFormsList.end()); it != prev(LFormIndex); ) {
				auto LIndex = find(FShowingFormsList.begin(), FShowingFormsList.end(), *it);
				if (LIndex != FShowingFormsList.end())
					FShowingFormsList.erase(LIndex);
				(*it)->Free();
				FCreatedFormsList.erase(it--);
			}
		  FShowingFormsList.back()->pnlContent->Visible = true;
		} __finally {
		  ((TfrmBase*) Application->MainForm)->EndUpdate();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::CMBiDiModeChanged(TMessage& AMessage)
{
	inherited::Dispatch(&AMessage);
	pnlContent->BiDiMode = BiDiMode;
	pnlContent->ParentBiDiMode = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::DoShow()
{
	bool LPreventUpdates = (Application->MainForm != nullptr) && Application->MainForm->Active;
	if (LPreventUpdates)
		BeginUpdate();
	try {
		pnlTip->Visible = !lblTipDescription->Caption.IsEmpty();
		if (this == Application->MainForm) {
			pnlBack->Visible = false;
			FShowingFormsList.push_back(this);
		} else {
			if (FShowingFormsList.size() > 0)
				FShowingFormsList.back()->pnlContent->Visible = false;
			FShowingFormsList.push_back(this);
			pnlContent->Parent = Application->MainForm;
		}
		inherited::DoShow();
		pnlContentResize(nullptr);
	} __finally {
		if (LPreventUpdates)
			EndUpdate();
	}
}
//---------------------------------------------------------------------------

void TfrmBase::EndUpdate()
{
	Application->MainForm->EnableAlign();
	SendMessage(Application->MainForm->Handle, WM_SETREDRAW, int(true), 0);
	RedrawWindow(Application->MainForm->Handle, nullptr, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
}
//---------------------------------------------------------------------------

TColor TfrmBase::FormBackgroundColor()
{
	return TColor{0x00FBFBFB}; // Mica material
}
//---------------------------------------------------------------------------

TColor TfrmBase::FormBorderColor()
{
	return TColor{0x00F6F3F2}; // Mica material
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::FormCreate(TObject* Sender)
{
	Color = FormBackgroundColor();
	pnlContent->Color = FormBackgroundColor();
	sbxContent->Color = FormBackgroundColor();
	pnlTitle->Color = FormBorderColor();
	pnlTip->Color = FormBorderColor();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::FormKeyDown(TObject* Sender, WORD& Key,
	TShiftState Shift)
{
	switch (Key) {
		case vkEscape:
		case vkBack:
		case vkHardwareBack:
			if ((GetCurrentForm() != Application->MainForm) && GetCurrentForm()->pnlBack->Showing) {
				TThread::ForceQueue(nullptr, [this]{ TfrmBase::CloseForm(GetCurrentForm()); });
				Key = 0;
			}
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::FormMouseWheel(TObject* Sender, TShiftState Shift,
	int WheelDelta, TPoint& MousePos, bool& Handled)
{
	if (this != GetCurrentForm())
		GetCurrentForm()->DoMouseWheel(Shift, WheelDelta, MousePos);
	else {
		sbxContent->VertScrollBar->Position = sbxContent->VertScrollBar->Position - WheelDelta;
		Handled = true;
	}
}
//---------------------------------------------------------------------------

String TfrmBase::GetAssetsPath()
{
	String Result = Ioutils::TPath::GetFullPath("..\\..\\..\\..\\..\\..\\Assets\\");
	if (!Result.IsEmpty() && (*Result.LastChar() != PathDelim))
		Result = Result + PathDelim;
	return Result;
}
//---------------------------------------------------------------------------

TfrmBase* TfrmBase::GetCurrentForm()
{
	return FShowingFormsList.back();
}
//---------------------------------------------------------------------------

String TfrmBase::GetOutputPath()
{
	String Result = ExtractFilePath(ParamStr(0));
	if (!Result.IsEmpty() && (*Result.LastChar() != PathDelim))
		Result = Result + PathDelim;
	return Result;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::pnlBackClick(TObject* Sender)
{
	TThread::ForceQueue(nullptr, [this]{ TfrmBase::CloseForm(this); });
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::pnlContentResize(TObject* Sender)
{
	if (pnlTip->Visible)
		pnlTip->Height = lblTipDescription->Height + 16;
}
//---------------------------------------------------------------------------

void TfrmBase::ScrollBoxChanged(TObject* ASender)
{
	((::TScrollBox*) ASender)->Repaint();
}
//---------------------------------------------------------------------------

void TfrmBase::ScrollBoxEraseBackground(TObject* ASender, const HDC ADC)
{
}
//---------------------------------------------------------------------------

void TfrmBase::Show()
{
	DoShow();
}
//---------------------------------------------------------------------------

void TfrmBase::ShowMessage(const String AMessage)
{
	MessageDlg(AMessage, TMsgDlgType::mtInformation, TMsgDlgButtons() << TMsgDlgBtn::mbOK, 0);
}
//---------------------------------------------------------------------------

int __fastcall TfrmBase::ShowModal()
{
	Show();
	return 0;
}
//---------------------------------------------------------------------------

void __fastcall ::TScrollBox::WMEraseBkgnd(TWMEraseBkgnd& AMessage)
{
	inherited::Dispatch(&AMessage);
	if (!ComponentState.Contains(csDestroying))
		dynamic_cast<TfrmBase*>(Owner)->ScrollBoxEraseBackground(this, AMessage.DC);
}
//---------------------------------------------------------------------------

void __fastcall ::TScrollBox::WMHScroll(TWMHScroll& AMessage)
{
	inherited::Dispatch(&AMessage);
	dynamic_cast<TfrmBase*>(Owner)->ScrollBoxChanged(this);
}
//---------------------------------------------------------------------------

void __fastcall ::TScrollBox::WMVScroll(TWMVScroll& AMessage)
{
	inherited::Dispatch(&AMessage);
	dynamic_cast<TfrmBase*>(Owner)->ScrollBoxChanged(this);
}
//---------------------------------------------------------------------------
