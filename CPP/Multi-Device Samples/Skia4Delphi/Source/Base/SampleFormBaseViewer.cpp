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

#include "SampleFormBaseViewer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

_di_ISkImage TfrmBaseViewer::FChessImage;
_di_ISkPaint TfrmBaseViewer::FChessPaint;

TViewerOptions::TViewerOptions()
{
	FControl = new TLayout(nullptr);
	FControl->Height = 0;
	FControl->OnResized = ControlResized;
}
//---------------------------------------------------------------------------

TViewerOptions::~TViewerOptions()
{
	delete FControl;
}
//---------------------------------------------------------------------------

void TViewerOptions::AddBoolean(const System::String AName, const bool ACurrentValue)
{
	TSwitch* LSwitch = new TSwitch(FControl);
	LSwitch->Align = TAlignLayout::Left;
	LSwitch->Cursor = crHandPoint;
	LSwitch->IsChecked = ACurrentValue;
	LSwitch->Margins->Rect = RectF(0, 8, 0, 8);
	LSwitch->Width = 78;
	LSwitch->OnClick = OnSwitchClick;
	AddItem(AName, new TIntValue((int) ACurrentValue), LSwitch,
		[this](TControl* AControl, const TAnyValue* AValue)
		{
			TSwitch* LSwitch = (TSwitch*) AControl;
			LSwitch->OnClick = nullptr;
			try {
				LSwitch->IsChecked = AValue->AsBool();
			} __finally {
				LSwitch->OnClick = OnSwitchClick;
			}
		});
}
//---------------------------------------------------------------------------

void TViewerOptions::AddEnum(const System::String AName,
	const PTypeInfo ATypeInfo, const int ACurrentValue)
{
	if (ATypeInfo->Kind != tkEnumeration)
		throw Exception("Invalid type");
	DynamicArray<System::String> LStrings;
	for (int LEnumValue = GetTypeData(ATypeInfo)->MinValue; LEnumValue <= GetTypeData(ATypeInfo)->MaxValue; LEnumValue++) {
		LStrings.Length = LStrings.Length + 1;
		LStrings[LStrings.High] = GetEnumName(ATypeInfo, LEnumValue);
	}
	AddStrings(AName, LStrings, ACurrentValue - GetTypeData(ATypeInfo)->MinValue);
}
//---------------------------------------------------------------------------

void TViewerOptions::AddFloat(const System::String AName, const float AMinValue,
	const float AMaxValue, const float ACurrentValue,
	const float AFrequencyValue)
{
	AddTrackField(AName, AMinValue, AMaxValue, ACurrentValue, AFrequencyValue);
}
//---------------------------------------------------------------------------

void TViewerOptions::AddInteger(const System::String AName, const int AMinValue,
	const int AMaxValue, const int ACurrentValue)
{
	AddTrackField(AName, AMinValue, AMaxValue, ACurrentValue, 1);
}
//---------------------------------------------------------------------------

void TViewerOptions::AddItem(const System::String AName,
	TAnyValue* ACurrentValue, TControl* ASelectControl,
	const TUpdateSelectControlProc& AUpdateSelectControl)
{
	const static int HorizontalMargin = 20;
	const static int ItemHeight = 44;
	const static System::String LabelStyleLookup = "sklabelstyle_options";
	const static TAlphaColor LineColor = 0xFFECE8E6;

	TRectangle* LRectangle = new TRectangle(FControl);
	LRectangle->Align = TAlignLayout::Top;
	LRectangle->Fill->Color = TfrmBaseViewer::FormBorderColor();
	LRectangle->Sides = TSides() << TSide::Top;
	LRectangle->Stroke->Color = LineColor;
	LRectangle->Height = ItemHeight;
	LRectangle->Width = FControl->Width;

	TSkLabel* LLabel = new TSkLabel(LRectangle);
	LLabel->TextSettings->MaxLines = 1;
	LLabel->Align = TAlignLayout::MostLeft;
	LLabel->Margins->Left = HorizontalMargin;
	LLabel->StyleLookup = LabelStyleLookup;
	LLabel->Text = AName;
	LLabel->Parent = LRectangle;
	LLabel->OnResized = ControlResized;

	ASelectControl->Margins->Left = HorizontalMargin;
	ASelectControl->Margins->Right = HorizontalMargin;
	ASelectControl->Tag = FItems.Length;
	ASelectControl->Parent = LRectangle;

	LRectangle->Position->Y = FControl->Height;
	LRectangle->Parent = FControl;

	FItems.Length = FItems.Length + 1;
	TItem& LItem = FItems[FItems.High];
	LItem.Data.Name = AName;
	LItem.Data.Value = std::shared_ptr<TAnyValue>(ACurrentValue);
	LItem.LabelControl = LLabel;
	LItem.SelectControl = ASelectControl;
	LItem.UpdateSelectControl = AUpdateSelectControl;

	FControl->Height = FControl->Height + LRectangle->Height;
}
//---------------------------------------------------------------------------

void TViewerOptions::AddStrings(const System::String AName,
	const DynamicArray<System::String>& AStrings, const int ACurrentIndexValue)
{
	TComboBox* LComboBox = new TComboBox(FControl);
	LComboBox->Align = TAlignLayout::Client;
	LComboBox->Margins->Rect = RectF(0, 8, 0, 8);
	LComboBox->Cursor = crHandPoint;
	LComboBox->Items->AddStrings(AStrings);
	LComboBox->ItemIndex = ACurrentIndexValue;
	LComboBox->OnChange = OnComboBoxChange;
	AddItem(AName, new TIntValue(ACurrentIndexValue), LComboBox,
		[this](TControl* AControl, const TAnyValue* AValue)
		{
			TComboBox* LComboBox = (TComboBox*) AControl;
			LComboBox->OnClick = nullptr;
			try {
				LComboBox->ItemIndex = AValue->AsInt();
			} __finally {
				LComboBox->OnClick = OnComboBoxChange;
			}
		});
}
//---------------------------------------------------------------------------

void TViewerOptions::AddTrackField(const System::String AName, const float AMinValue,
	const float AMaxValue, const float ACurrentValue, const float AFrequency)
{
	float LValue = EnsureRange(ACurrentValue, AMinValue, AMaxValue);
	TTrackBar* LTrackBar = new TTrackBar(FControl);
	LTrackBar->Align = TAlignLayout::Client;
	LTrackBar->Cursor = crHandPoint;
	LTrackBar->Min = AMinValue;
	LTrackBar->Max = AMaxValue;
	LTrackBar->Value = LValue;
	LTrackBar->Frequency = AFrequency;
	LTrackBar->OnChange = OnTrackBarChange;
	AddItem(AName, new TFloatValue(LValue), LTrackBar,
		[this, AMinValue, AMaxValue](TControl* AControl, const TAnyValue* AValue)
		{
			TTrackBar* LTrackBar = (TTrackBar*) AControl;
			LTrackBar->OnChange = nullptr;
			try {
				LTrackBar->Value = EnsureRange(AValue->AsFloat(), AMinValue, AMaxValue);
			} __finally {
				LTrackBar->OnChange = OnTrackBarChange;
			}
		});
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::ControlResized(TObject* ASender)
{
	float LMaxTextWidth = 0;
	for (int i = FItems.Low; i <= FItems.High; i++)
		LMaxTextWidth = Max(FItems[i].LabelControl->Width, LMaxTextWidth);
	for (int i = FItems.Low; i <= FItems.High; i++)
		FItems[i].LabelControl->Margins->Right = Max(LMaxTextWidth - FItems[i].LabelControl->Width, 0.f);
}
//---------------------------------------------------------------------------

TViewerOptions::TAnyValue* TViewerOptions::GetAnyValue(const System::String AName) const
{
	for (int i = FItems.Low; i <= FItems.High; i++)
		if (SameText(FItems[i].Data.Name, AName))
			return FItems[i].Data.Value.get();
	for (int i = FHiddenItems.Low; i <= FHiddenItems.High; i++)
		if (SameText(FHiddenItems[i].Name, AName))
			return FHiddenItems[i].Value.get();
	return nullptr;
}
//---------------------------------------------------------------------------

float TViewerOptions::GetFloat(const System::String AName) const
{
	if (auto LAnyValue = GetAnyValue(AName))
		return LAnyValue->AsFloat();
	return 0.f;
}
//---------------------------------------------------------------------------

int TViewerOptions::GetInt(const System::String AName) const
{
	if (auto LAnyValue = GetAnyValue(AName))
		return LAnyValue->AsInt();
	return 0;
}
//---------------------------------------------------------------------------

System::String TViewerOptions::GetString(const System::String AName) const
{
	if (auto LAnyValue = GetAnyValue(AName))
		return LAnyValue->AsString();
	return "";
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::OnComboBoxChange(TObject* ASender)
{
	TComboBox* LComboBox = (TComboBox*) ASender;
	dynamic_cast<TIntValue*>(FItems[LComboBox->Tag].Data.Value.get())->Value = LComboBox->ItemIndex;
	if (FOnChange)
		FOnChange(nullptr);
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::OnSwitchClick(TObject* ASender)
{
	TThread::CreateAnonymousThread(
		[this, ASender] {
				TThread::Queue(nullptr,
					[this, ASender]{
						TSwitch* LSwitch = (TSwitch*) ASender;
						dynamic_cast<TIntValue*>(FItems[LSwitch->Tag].Data.Value.get())->Value = (int) LSwitch->IsChecked;
						if (FOnChange)
							FOnChange(nullptr);
					});
		})->Start();
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::OnTrackBarChange(TObject* ASender)
{
	TTrackBar* LTrackBar = (TTrackBar*) ASender;
	if (SameValue(LTrackBar->Frequency, 1.f, (float) TEpsilon_Position))
		dynamic_cast<TFloatValue*>(FItems[LTrackBar->Tag].Data.Value.get())->Value = round(LTrackBar->Value);
	else
		dynamic_cast<TFloatValue*>(FItems[LTrackBar->Tag].Data.Value.get())->Value = LTrackBar->Value;
	if (FOnChange)
		FOnChange(nullptr);
}
//---------------------------------------------------------------------------

void TViewerOptions::SetAnyValue(const System::String AName,
	TAnyValue* AValue)
{
	for (int i = FItems.Low; i <= FItems.High; i++) {
		if (SameText(FItems[i].Data.Name, AName)) {
			FItems[i].Data.Value = std::shared_ptr<TAnyValue>(AValue);
			FItems[i].UpdateSelectControl(FItems[i].SelectControl, AValue);
			return;
		}
	}
	for (int i = FHiddenItems.Low; i <= FHiddenItems.High; i++) {
		if (SameText(FHiddenItems[i].Name, AName)) {
			FHiddenItems[i].Value = std::shared_ptr<TAnyValue>(AValue);
			return;
		}
	}
	FHiddenItems.Length = FHiddenItems.Length + 1;
	FHiddenItems[FHiddenItems.High].Name = AName;
	FHiddenItems[FHiddenItems.High].Value = std::shared_ptr<TAnyValue>(AValue);
}
//---------------------------------------------------------------------------

void TViewerOptions::SetFloat(const System::String AName, const float AValue)
{
	if (auto LAnyValue = dynamic_cast<TFloatValue*>(GetAnyValue(AName)))
		LAnyValue->Value = AValue;
	else
		SetAnyValue(AName, new TFloatValue(AValue));
}
//---------------------------------------------------------------------------

void TViewerOptions::SetInt(const System::String AName, const int AValue)
{
	if (auto LAnyValue = dynamic_cast<TIntValue*>(GetAnyValue(AName)))
		LAnyValue->Value = AValue;
	else
		SetAnyValue(AName, new TIntValue(AValue));
}
//---------------------------------------------------------------------------

void TViewerOptions::SetString(const System::String AName,
	const System::String AValue)
{
	if (auto LAnyValue = dynamic_cast<TStringValue*>(GetAnyValue(AName)))
		LAnyValue->Value = AValue;
	else
		SetAnyValue(AName, new TStringValue(AValue));
}
//---------------------------------------------------------------------------

__fastcall TfrmBaseViewer::TfrmBaseViewer(TComponent* Owner) : TfrmBase(Owner) {}
//---------------------------------------------------------------------------

_di_ISkPaint TfrmBaseViewer::CreateChessPaint()
{
	FChessImage = BitmapToSkImage(rctBackgroundChess->Fill->Bitmap->Bitmap);
	auto Result = SkPaint();
	Result->Shader = FChessImage->MakeShader(TSkTileMode::Repeat, TSkTileMode::Repeat);
	return Result;
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::DoSetOptions(TViewerOptions* AOptions)
{
	if (AOptions) {
		AOptions->Control->Align = TAlignLayout::Bottom;
		AOptions->Control->Parent = rctContent;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseViewer::FormClose(TObject* Sender, TCloseAction& Action)
{
	if (Action != TCloseAction::caNone) {
		FOnOptionsChange = nullptr;
		Options = nullptr;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseViewer::FormDestroy(TObject* Sender)
{
	Options = nullptr;
}
//---------------------------------------------------------------------------

bool TfrmBaseViewer::HasBottomContent()
{
	return inherited::HasBottomContent() || FOptions;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseViewer::OptionsChange(TObject* ASender)
{
	OptionsChanged();
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::OptionsChanged()
{
	if (FOnOptionsChange)
		FOnOptionsChange();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBaseViewer::pbxBackgroundChessDraw(TObject* ASender,
	ISkCanvas* const ACanvas, const TRectF& ADest, const float AOpacity)
{
	if (FChessPaint == nullptr)
		FChessPaint = CreateChessPaint();
	ACanvas->DrawRect(ACanvas->GetLocalClipBounds(), FChessPaint);
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::SetBackgroundKind(const TBackgroundKind AValue)
{
	FBackgroundKind = AValue;
	// Just avoinding a know bug of TCanvasGpu drawing tile bitmap
	if (TCanvasManager::DefaultCanvas->ClassName() == "TCanvasGpu") {
		pbxBackgroundChess->SendToBack();
		pbxBackgroundChess->Visible = FBackgroundKind == TBackgroundKind::Chess;
	} else {
		rctBackgroundChess->SendToBack();
		rctBackgroundChess->Visible = FBackgroundKind == TBackgroundKind::Chess;
	}
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::SetOptions(TViewerOptions* AOptions)
{
	if (FOptions != AOptions) {
		if (FOptions) {
			FOptions->OnChange = nullptr;
			FOptions->Control->Parent = nullptr;
			delete FOptions;
		}
		FOptions = AOptions;
		DoSetOptions(FOptions);
		if (FOptions)
			FOptions->OnChange = OptionsChange;
	}
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::Show(String ATitle, String ADescription)
{
	lblTitle->Text = ATitle;
	lblTipDescription->Text = ADescription;
	BackgroundKind = FBackgroundKind;
	inherited::Show();
}
//---------------------------------------------------------------------------
