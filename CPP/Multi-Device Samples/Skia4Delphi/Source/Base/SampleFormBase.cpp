//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.DialogService.hpp>
#include "SampleFormBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

std::vector<TfrmBase*> TfrmBase::FCreatedFormsList;
std::vector<TfrmBase*> TfrmBase::FShowingFormsList;

class TControlAccess : TControl
{
	friend TfrmBase;
};

void __fastcall ::TScrollBox::DoUpdateAniCalculations(TScrollCalculations* const AAniCalculations)
{
	Layouts::TScrollBox::DoUpdateAniCalculations(AAniCalculations);
	AAniCalculations->BoundsAnimation = AAniCalculations->BoundsAnimation && dynamic_cast<TfrmBase*>(Owner)->AllowScrollBoundsAnimation;
}
//---------------------------------------------------------------------------

__fastcall TfrmBase::TfrmBase(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::btnBackClick(TObject* Sender)
{
	#pragma region " - Workaround RSP-36959"
	// - -----------------------------------------------------------------------
	// - WORKAROUND
	// - -----------------------------------------------------------------------
	// -
	// - Description:
	// -   This code is a workaround intended to fix an access violation that
	// -   occurs in iOS when the TComboBox is detroyed when its DroppedDown is
	// -   true, that is, with the picker of TComboBox opened.
	// -
	// - Bug report:
	// -   https://quality.embarcadero.com/browse/RSP-36959
	// -
	// - -----------------------------------------------------------------------
	#if __BCPLUSPLUS__ > 0x0770
		#warning Check if the issue has been fixed
	#endif
	// - -----------------------------------------------------------------------
	#if defined(TARGET_OS_IPHONE)
	if (Application->MainForm->Focused != nullptr) {
		auto LFocusedComboBox = dynamic_cast<TCustomComboBox*>(Application->MainForm->Focused->GetObject());
		if (LFocusedComboBox && LFocusedComboBox->DroppedDown) {
			Application->MainForm->Focused = nullptr;
			TThread::CreateAnonymousThread(
				[this] {
					Sleep(500);
					TThread::Queue(nullptr, [this]{ btnBackClick(nullptr); });
				})->Start();
			return;
		}
	}
	#endif
	// - -----------------------------------------------------------------------
	#pragma end_region

	TThread::ForceQueue(nullptr, [this]{ TfrmBase::CloseForm(this); });
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
		_di_IRoot root;
		if (Supports(Application->MainForm, __uuidof(IRoot), (void*)&root))
			root->SetCaptured(nullptr);
		LFormIndex = find(FCreatedFormsList.begin(), FCreatedFormsList.end(), AForm);
		assert(LFormIndex != FCreatedFormsList.end());
		for (auto it = prev(FCreatedFormsList.end()); it != prev(LFormIndex); ) {
			auto LIndex = find(FShowingFormsList.begin(), FShowingFormsList.end(), *it);
			if (LIndex != FShowingFormsList.end())
				FShowingFormsList.erase(LIndex);
			delete *it;
			FCreatedFormsList.erase(it--);
		}
		FShowingFormsList.back()->rctContent->Enabled = true;
		FShowingFormsList.back()->rctContent->Visible = true;
		FShowingFormsList.back()->rctContent->BringToFront();
		if (FShowingFormsList.size() > 1)
			FShowingFormsList[FShowingFormsList.size() - 2]->rctContent->Visible = true;
		Application->MainForm->BiDiMode = (FShowingFormsList.back() == Application->MainForm ? Application->BiDiMode : FShowingFormsList.back()->BiDiMode);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::DoShow()
{
	rctTip->Visible = !lblTipDescription->Text.IsEmpty();
	if (rctTip->Visible) {
		rctTip->Position->Y = -100;
	}
	if (this == Application->MainForm) {
		btnBack->Visible = false;
		FShowingFormsList.push_back(this);
		DoSystemBarsInsetsChange();
	} else {
		DoSystemBarsInsetsChange();
		if (Application->MainForm != nullptr) {
			//StyleBook = Application->MainForm->StyleBook;
			Application->MainForm->BiDiMode = BiDiMode;
		}
		if (!FShowingFormsList.empty()) {
			FShowingFormsList.back()->rctContent->Visible = false;
			((TControlAccess*)FShowingFormsList.back()->rctContent)->DisabledOpacity = 1;
			FShowingFormsList.back()->rctContent->Enabled = false;
			if (FShowingFormsList.size() > 1)
				FShowingFormsList[FShowingFormsList.size() - 2]->rctContent->Visible = false;
		}
		FShowingFormsList.push_back(this);
		rctContent->Parent = Application->MainForm;
		rctContent->BringToFront();
		if (FShowingFormsList.size() > 1)
			FShowingFormsList[FShowingFormsList.size() - 2]->rctContent->Visible = true;
	}
	inherited::DoShow();
	rctContentResized(nullptr);
}
//---------------------------------------------------------------------------

void TfrmBase::DoSystemBarsInsetsChange()
{
	rctStatusBar->Height = 0;
	rctNavigationBar->Height = 0;
	#if defined(TARGET_OS_IPHONE)
	rctGestureBar->Height = HasBottomContent() ? 34 : 0;
	#else
	rctGestureBar->Height = 0;
	#endif
}
//---------------------------------------------------------------------------

TAlphaColor TfrmBase::FormBackgroundColor()
{
	#if defined(_Windows)
	return 0xFFFBFBFB; // Mica material
	#else
	return 0xFFF2F2F7;
	#endif
}
//---------------------------------------------------------------------------

TAlphaColor TfrmBase::FormBorderColor()
{
	#if defined(_Windows)
	return 0xFFF2F3F6; // Mica material
	#else
	return TAlphaColors::White;
	#endif
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::FormCreate(TObject *Sender)
{
	#if defined(__ANDROID__) || defined(TARGET_OS_IPHONE)
	rctHeader->Height = 48;
	#endif
	Fill->Color = FormBackgroundColor();
	rctContent->Fill->Color = FormBackgroundColor();
	rctHeader->Fill->Color = FormBorderColor();
	rctTip->Fill->Color = FormBorderColor();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::FormKeyDown(TObject* Sender, WORD& Key,
	System::WideChar& KeyChar, TShiftState Shift)
{
	switch (Key) {
		case vkEscape:
		case vkBack:
		case vkHardwareBack:
			if ((GetCurrentForm() != Application->MainForm) && GetCurrentForm()->btnBack->ParentedVisible) {
				CloseForm(GetCurrentForm());
				Key = 0;
			}
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------

String TfrmBase::GetAssetsPath()
{
	String Result;
	#if defined(_Windows)
	Result = Ioutils::TPath::GetFullPath("..\\..\\..\\..\\..\\..\\Assets\\");
	#elif defined(TARGET_OS_IPHONE) || defined(__ANDROID__)
	Result = Ioutils::TPath::GetDocumentsPath();
	#elif defined(__APPLE__)
	Result = Ioutils::TPath::GetFullPath("../Resources/");
	#else
	Result = ExtractFilePath(ParamStr(0));
	#endif
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
	String Result;
	#if defined(_Windows)
	Result = ExtractFilePath(ParamStr(0));
	#elif defined(__APPLE__) && !defined(TARGET_OS_IPHONE)
	Result = Ioutils::TPath::GetTempPath();
	#else
	Result = GetAssetsPath();
	#endif
	if (!Result.IsEmpty() && (*Result.LastChar() != PathDelim))
		Result = Result + PathDelim;
	return Result;
}
//---------------------------------------------------------------------------

bool TfrmBase::HasBottomContent()
{
	return rctTip->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::PaintBackground()
{
	// Specific workaround of this project to a known issue (RSP-34435)
	if (!ComponentState.Contains(csDesigning) && (Fill->Kind == TBrushKind::Solid) && !Transparency)
		Canvas->Clear(Fill->Color);
	else
		inherited::PaintBackground();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBase::rctContentResized(TObject* Sender)
{
	if (rctTip->Visible && (rctTip->Height != lblTipDescription->Height + 16)) {
		rctTip->Height = lblTipDescription->Height + 16;
		TThread::ForceQueue(nullptr,
			[this] {
				((TControlAccess*)rctTip)->Realign();
				((TControlAccess*)rctContent)->Realign();
			});
	}
}
//---------------------------------------------------------------------------

void TfrmBase::SetAllowScrollBoundsAnimation(const bool AValue)
{
	if (FAllowScrollBoundsAnimation != AValue) {
		FAllowScrollBoundsAnimation = AValue;
		sbxContent->UpdateAniCalculations();
	}
}
//---------------------------------------------------------------------------

void TfrmBase::Show()
{
	DoShow();
}
//---------------------------------------------------------------------------

void TfrmBase::ShowMessage(const String AMessage)
{
	TDialogService::MessageDialog(AMessage, TMsgDlgType::mtInformation, TMsgDlgButtons() << TMsgDlgBtn::mbOK, TMsgDlgBtn::mbOK, 0, nullptr);
}
//---------------------------------------------------------------------------
