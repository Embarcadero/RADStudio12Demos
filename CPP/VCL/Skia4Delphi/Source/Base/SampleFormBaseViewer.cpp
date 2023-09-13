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

#include <System.UITypes.hpp>
#include <Vcl.WinXCtrls.hpp>
#include "SampleFormBaseViewer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

std::unique_ptr<TBitmap> TfrmBaseViewer::FChessBitmap;
_di_ISkRuntimeShaderBuilder TfrmBaseViewer::FChessEffectBuilder;

class TComboBoxSafe : public TComboBox
{
	typedef TComboBox inherited;

private:
	int FSafeItemIndex;
	DynamicArray<String> FSafeItems;
	int GetSafeItemIndex();
	DynamicArray<String> GetSafeItems();
	void SetSafeItemIndex(const int AValue);
	void SetSafeItems(const DynamicArray<String> AValue);
protected:
	void __fastcall CreateWnd() override;
	void __fastcall DestroyWnd() override;
public:
	__fastcall TComboBoxSafe(TComponent* Owner) override;
	__property int SafeItemIndex = {read=GetSafeItemIndex, write=SetSafeItemIndex};
	__property DynamicArray<String> SafeItems = {read=GetSafeItems, write=SetSafeItems};
};

String StringJoin(const String ASeparator, const DynamicArray<String> AValues)
{
	String Result = "";
	for (auto LItem : AValues) {
		if (Result != "")
			Result += ASeparator;
		Result += LItem;
	}
	return Result;
}
//---------------------------------------------------------------------------

__fastcall TComboBoxSafe::TComboBoxSafe(TComponent* Owner)
	: TComboBox(Owner)
{
	FSafeItemIndex = -1;
}
//---------------------------------------------------------------------------

void __fastcall TComboBoxSafe::CreateWnd()
{
	inherited::CreateWnd();
	TNotifyEvent LOnChange = OnChange;
	OnChange = nullptr;
	try {
		Items->Text = StringJoin(sLineBreak, FSafeItems);
		ItemIndex = FSafeItemIndex;
	} __finally {
		OnChange = LOnChange;
	}
}
//---------------------------------------------------------------------------

void __fastcall TComboBoxSafe::DestroyWnd()
{
	FSafeItemIndex = ItemIndex;
	FSafeItems = Items->ToStringArray();
	inherited::DestroyWnd();
}
//---------------------------------------------------------------------------

int TComboBoxSafe::GetSafeItemIndex()
{
	return WindowHandle != 0 ? ItemIndex : FSafeItemIndex;
}
//---------------------------------------------------------------------------

DynamicArray<String> TComboBoxSafe::GetSafeItems()
{
	return WindowHandle != 0 ? Items->ToStringArray() : FSafeItems;
}
//---------------------------------------------------------------------------

void TComboBoxSafe::SetSafeItemIndex(const int AValue)
{
	if (WindowHandle != 0)
		ItemIndex = AValue;
	else
		FSafeItemIndex = AValue;
}
//---------------------------------------------------------------------------

void TComboBoxSafe::SetSafeItems(const DynamicArray<String> AValue)
{
	if (WindowHandle != 0)
		Items->Text = StringJoin(sLineBreak, AValue);
	else
		FSafeItems = AValue;
}
//---------------------------------------------------------------------------

TViewerOptions::TViewerOptions()
{
	FControl = new TPanel((TComponent*) nullptr);
	FControl->BevelOuter = TPanelBevel::bvNone;
	FControl->ShowCaption = false;
	FControl->Color = TfrmBaseViewer::FormBorderColor();
	FControl->StyleElements = FControl->StyleElements >> seClient;
	FControl->Height = 0;
	FControl->OnResize = ControlResized;
}
//---------------------------------------------------------------------------

TViewerOptions::~TViewerOptions()
{
	delete FControl;
}
//---------------------------------------------------------------------------

void TViewerOptions::AddBoolean(const System::String AName, const bool ACurrentValue)
{
	static const TToggleSwitchState SwitchState[] = {TToggleSwitchState::tssOff, TToggleSwitchState::tssOn};
	TToggleSwitch* LSwitch = new TToggleSwitch(FControl);
	LSwitch->Align = alLeft;
	LSwitch->Cursor = crHandPoint;
	LSwitch->ShowStateCaption = false;
	LSwitch->State = SwitchState[(int) ACurrentValue];
	LSwitch->ThumbWidth = 20;
	LSwitch->Margins->SetBounds(0, 12, 0, 11);
	LSwitch->SwitchWidth = 40;
	LSwitch->AlignWithMargins = true;
	LSwitch->OnClick = OnSwitchClick;
	AddItem(AName, new TIntValue((int) ACurrentValue), LSwitch,
		[this](TControl* AControl, const TAnyValue* AValue)
		{
			TToggleSwitch* LSwitch = (TToggleSwitch*) AControl;
			LSwitch->OnClick = nullptr;
			try {
				LSwitch->State = SwitchState[AValue->AsBool()];
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
	const TUpdateSelectControlProc& AUpdateSelectControl,
  const std::function<float(int APosition)> ATrackBarPositionToValue)
{
	const static int HorizontalMargin = 20;
	const static int ItemHeight = 44;
	const static TColor LineColor = TColor{0x00ECE8E6};

	TPanel* LPanel = new TPanel(FControl);
	LPanel->Align = alTop;
	LPanel->BevelOuter = TPanelBevel::bvNone;
	LPanel->ShowCaption = false;
	LPanel->Color = TfrmBaseViewer::FormBorderColor();
	LPanel->StyleElements = LPanel->StyleElements >> seClient;
	LPanel->Height = ItemHeight;
	LPanel->Width = FControl->Width;

	TPanel* LLine = new TPanel(LPanel);
	LLine->Align = alTop;
	LLine->BevelOuter = TPanelBevel::bvNone;
	LLine->ShowCaption = false;
	LLine->Color = LineColor;
	LLine->StyleElements = LLine->StyleElements >> seClient;
	LLine->Height = 1;
	LLine->Parent = LPanel;

	TSkLabel* LLabel = new TSkLabel(LPanel);
	LLabel->TextSettings->MaxLines = 1;
	LLabel->Align = alLeft;
	LLabel->Margins->SetBounds(HorizontalMargin, 0, 0, 0);
	LLabel->AlignWithMargins = true;
	LLabel->TextSettings->Font->Weight = TSkFontComponent::TSkFontWeight::Medium;
	LLabel->TextSettings->Font->Size = 11;
	LLabel->TextSettings->FontColor = 0xFFA0A0A1;
	LLabel->Caption = AName;
	LLabel->Parent = LPanel;
	LLabel->OnResize = ControlResized;

	ASelectControl->Margins->Left = HorizontalMargin;
	ASelectControl->Margins->Right = HorizontalMargin;
	ASelectControl->Tag = FItems.Length;
	ASelectControl->Parent = LPanel;

	LPanel->Top = FControl->Height;
	LPanel->Parent = FControl;

	FItems.Length = FItems.Length + 1;
	TItem& LItem = FItems[FItems.High];
	LItem.Data.Name = AName;
	LItem.Data.Value = std::shared_ptr<TAnyValue>(ACurrentValue);
	LItem.LabelControl = LLabel;
	LItem.SelectControl = ASelectControl;
	LItem.UpdateSelectControl = AUpdateSelectControl;
	LItem.TrackBarPositionToValue = ATrackBarPositionToValue;
	FControl->Height = FControl->Height + LPanel->Height;
}
//---------------------------------------------------------------------------

void TViewerOptions::AddStrings(const System::String AName,
	const DynamicArray<System::String>& AStrings, const int ACurrentIndexValue)
{
	TComboBoxSafe* LComboBox = new TComboBoxSafe(FControl);
	LComboBox->Align = alClient;
	LComboBox->Style = TComboBoxStyle::csDropDownList;
	LComboBox->Margins->SetBounds(0, 8, 0, 8);
	LComboBox->AlignWithMargins = true;
	LComboBox->Cursor = crHandPoint;
	LComboBox->SafeItems = AStrings;
	LComboBox->SafeItemIndex = ACurrentIndexValue;
	LComboBox->OnChange = OnComboBoxChange;
	AddItem(AName, new TIntValue(ACurrentIndexValue), LComboBox,
		[this](TControl* AControl, const TAnyValue* AValue)
		{
			TComboBoxSafe* LComboBox = (TComboBoxSafe*) AControl;
			LComboBox->OnClick = nullptr;
			try {
				LComboBox->SafeItemIndex = AValue->AsInt();
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
	LTrackBar->Align = alClient;
	LTrackBar->Margins->SetBounds(0, 10, 0, 11);
	LTrackBar->AlignWithMargins = true;
	LTrackBar->Cursor = crHandPoint;
	LTrackBar->Min = 0;
	if (SameValue(AFrequency, 0.f, (float) TEpsilon_Matrix))
		LTrackBar->Max = 200;
	else
		LTrackBar->Max = round((AMaxValue - AMinValue) / AFrequency);
	LTrackBar->Position = round(((LValue - AMinValue) / (AMaxValue - AMinValue)) * LTrackBar->Max);
	LTrackBar->Frequency = 1;
	LTrackBar->TickStyle = TTickStyle::tsNone;
	LTrackBar->OnChange = OnTrackBarChange;
	AddItem(AName, new TFloatValue(LValue), LTrackBar,
		[this, AMinValue, AMaxValue](TControl* AControl, const TAnyValue* AValue)
		{
			TTrackBar* LTrackBar = (TTrackBar*) AControl;
			LTrackBar->OnChange = nullptr;
			try {
				float LValue = EnsureRange(AValue->AsFloat(), AMinValue, AMaxValue);
				LTrackBar->Position = round(((LValue - AMinValue) / (AMaxValue - AMinValue)) * LTrackBar->Max);
			} __finally {
				LTrackBar->OnChange = OnTrackBarChange;
			}
		},
		[=](int APosition)
		{
			float LRealPosition = (((float) APosition / LTrackBar->Max) * (AMaxValue - AMinValue)) + AMinValue;
			if (SameValue(AFrequency, 1.f, (float) TEpsilon_Position))
				return round(LRealPosition);
			return LRealPosition;
		});
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::ControlResized(TObject* ASender)
{
	float LMaxTextWidth = 0;
	for (int i = FItems.Low; i <= FItems.High; i++)
		LMaxTextWidth = Max((float) FItems[i].LabelControl->Width, LMaxTextWidth);
	for (int i = FItems.Low; i <= FItems.High; i++)
		FItems[i].LabelControl->Margins->Right = round(Max(LMaxTextWidth - FItems[i].LabelControl->Width, 0.f));
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
	TComboBoxSafe* LComboBox = (TComboBoxSafe*) ASender;
	dynamic_cast<TIntValue*>(FItems[LComboBox->Tag].Data.Value.get())->Value = LComboBox->SafeItemIndex;
	if (FOnChange)
		FOnChange(nullptr);
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::OnSwitchClick(TObject* ASender)
{
	TToggleSwitch* LSwitch = (TToggleSwitch*) ASender;
	dynamic_cast<TIntValue*>(FItems[LSwitch->Tag].Data.Value.get())->Value = LSwitch->State == TToggleSwitchState::tssOn;
	if (FOnChange)
		FOnChange(nullptr);
}
//---------------------------------------------------------------------------

void __fastcall TViewerOptions::OnTrackBarChange(TObject* ASender)
{
	TTrackBar* LTrackBar = (TTrackBar*) ASender;
	dynamic_cast<TFloatValue*>(FItems[LTrackBar->Tag].Data.Value.get())->Value = FItems[LTrackBar->Tag].TrackBarPositionToValue(LTrackBar->Position);
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

void TfrmBaseViewer::CreateChessEffect()
{
	auto LChessEffect = TSkRuntimeEffect::MakeForShader(
		"uniform float4 iOddSquareColor, iEvenSquareColor;                     \
		 uniform float2 iSquareSize;                                           \
		 half4 main(float2 fragCoord) {                                        \
			bool p = mod(fragCoord.x/iSquareSize.x, 2.0) < 1.0;                \
			bool q = mod(fragCoord.y/iSquareSize.y, 2.0) > 1.0;                \
			if ((p && q) || !(p || q))                                         \
				return iOddSquareColor;                                        \
			return iEvenSquareColor;}");
	FChessEffectBuilder = SkRuntimeShaderBuilder(LChessEffect);
	FChessEffectBuilder->SetUniform("iOddSquareColor", TAlphaColorF::Create(0.8f, 0.8f, 0.8f));
	FChessEffectBuilder->SetUniform("iEvenSquareColor", TAlphaColorF::Create(TAlphaColors::White));
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::DoSetOptions(TViewerOptions* AOptions)
{
	if (AOptions) {
		AOptions->Control->Align = alBottom;
		AOptions->Control->Parent = pnlContent;
		pnlTip->Top = AOptions->Control->BoundsRect.Bottom;
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

void TfrmBaseViewer::pnlContentResize(TObject* ASender)
{
	inherited::pnlContentResize(ASender);
	sbxContent->Invalidate();
}
//---------------------------------------------------------------------------

// A fast way to draw the chess background
void TfrmBaseViewer::ScrollBoxEraseBackground(TObject* ASender, const HDC ADC)
{
	::TScrollBox* LScrollBox = (::TScrollBox*) ASender;
	switch (FBackgroundKind) {
		case TBackgroundKind::Chess:
			if ((FChessBitmap == nullptr) || (FChessBitmap->Width < LScrollBox->Width) || (FChessBitmap->Height < LScrollBox->Height))
				UpdateChessBitmap();
			if (HWND(WindowFromDC(ADC)) == sbxContent->Handle) {
				for (int i = 0; i < LScrollBox->ControlCount; i++) {
					TRect LRect = LScrollBox->Controls[i]->BoundsRect;
					ExcludeClipRect(ADC, LRect.Left, LRect.Top, LRect.Right, LRect.Bottom);
				}
				BitBlt(ADC, 0, 0, LScrollBox->Width, LScrollBox->Height, FChessBitmap->Canvas->Handle, 0, 0, SRCCOPY);
				SelectClipRgn(ADC, HRGN(nullptr));
			} else
				BitBlt(ADC, 0, 0, LScrollBox->Width, LScrollBox->Height, FChessBitmap->Canvas->Handle, 0, 0, SRCCOPY);
			break;
		case TBackgroundKind::Solid:
			inherited::ScrollBoxEraseBackground(ASender, ADC);
			break;
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
	lblTitle->Caption = ATitle;
	lblTipDescription->Caption = ADescription;
	inherited::Show();
}
//---------------------------------------------------------------------------

void TfrmBaseViewer::UpdateChessBitmap()
{
	if (FChessEffectBuilder == nullptr)
		CreateChessEffect();
	FChessEffectBuilder->SetUniform("iSquareSize", PointF(8.f, 8.f) * pnlContent->ScaleFactor);
	if (FChessBitmap == nullptr)
		FChessBitmap = std::make_unique<TBitmap>();
	FChessBitmap->SetSize(Min(Screen->Width, Max(pnlContent->Width * 2, 300)), Min(Screen->Height, Max(pnlContent->Height * 2, 300)));
	SkiaDraw(FChessBitmap.get(),
		[this](const _di_ISkCanvas ACanvas) {
			auto LPaint = SkPaint();
			LPaint->Shader = this->FChessEffectBuilder->MakeShader();
			ACanvas->DrawPaint(LPaint);
		}, true);
}
//---------------------------------------------------------------------------
