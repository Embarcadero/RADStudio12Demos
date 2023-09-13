//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormBaseViewerH
#define SampleFormBaseViewerH
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

enum class TBackgroundKind { Chess, Solid };

class TViewerOptions
{
private:
	class TAnyValue
	{
	public:
		TAnyValue() {};
		virtual float AsFloat() const { return 0.f; };
		virtual int AsInt() const { return 0; };
		bool AsBool() const { return (bool) AsInt(); };
		virtual String AsString() const { return ""; };
	};

	template<typename T> class TAnyContainer: public TAnyValue
	{
	public:
		T Value;
		TAnyContainer(T const AValue) : TAnyValue() { Value = AValue; };
	};

	class TFloatValue: public TAnyContainer<float>
	{
	public:
		TFloatValue(float AValue) : TAnyContainer(AValue) {};
		virtual float AsFloat() const { return Value; };
		virtual int AsInt() const { return round(Value); };
	};

	class TIntValue: public TAnyContainer<int>
	{
	public:
		TIntValue(int AValue) : TAnyContainer(AValue) {};
		virtual float AsFloat() const { return Value; };
		virtual int AsInt() const { return Value; };
	};

	class TStringValue: public TAnyContainer<String>
	{
	public:
		TStringValue(const String AValue) : TAnyContainer(AValue) {};
		virtual String AsString() const { return Value; };
	};

	typedef std::function<void(TControl* AControl, const TAnyValue* AValue)> TUpdateSelectControlProc;

	struct TItemData {
		String Name;
		std::shared_ptr<TAnyValue> Value;
	};

	struct TItem {
		TItemData Data;
		TControl* LabelControl;
		TControl* SelectControl;
		TUpdateSelectControlProc UpdateSelectControl;
		std::function<float(int APosition)> TrackBarPositionToValue;
	};

	TPanel* FControl;
	DynamicArray<TItemData> FHiddenItems;
	DynamicArray<TItem> FItems;
	TNotifyEvent FOnChange;

	void AddEnum(const String AName, const PTypeInfo ATypeInfo, const int ACurrentValue);
	void AddItem(const String AName, TAnyValue* ACurrentValue, TControl* ASelectControl, const TUpdateSelectControlProc& AUpdateSelectControl, const std::function<float(int APosition)> ATrackBarPositionToValue = nullptr);
	void AddTrackField(const String AName, const float AMinValue, const float AMaxValue, const float ACurrentValue, const float AFrequency);
	void __fastcall ControlResized(TObject* ASender);
	TAnyValue* GetAnyValue(const String AName) const;
	bool GetBool(const String AName) const { return (bool) GetInt(AName); };
	float GetFloat(const String AName) const;
	int GetInt(const String AName) const;
	String GetString(const String AName) const;
	void __fastcall OnComboBoxChange(TObject* ASender);
	void __fastcall OnSwitchClick(TObject* ASender);
	void __fastcall OnTrackBarChange(TObject* ASender);
	void SetAnyValue(const String AName, TAnyValue* AValue);
	void SetBool(const String AName, const bool AValue) { SetInt(AName, (int) AValue); };
	void SetFloat(const String AName, const float AValue);
	void SetInt(const String AName, const int AValue);
	void SetString(const String AName, const String AValue);
public:
	TViewerOptions();
	~TViewerOptions();
	void AddBoolean(const String AName, const bool ACurrentValue);
	template<typename T> void AddEnum(const String AName, const T ACurrentValue) { AddEnum(AName, __delphirtti(T), (int) ACurrentValue); };
	void AddFloat(const String AName, const float AMinValue, const float AMaxValue, const float ACurrentValue, const float AFrequencyValue = 0);
	void AddInteger(const String AName, const int AMinValue, const int AMaxValue, const int ACurrentValue);
	void AddStrings(const String AName, const DynamicArray<String>& AStrings, const int ACurrentIndexValue);
	template<typename T> T GetValue(const String AName) const { return dynamic_cast<TAnyContainer<T>*>(GetAnyValue(AName))->Value; };
	template<typename T> void SetValue(const String AName, T const AValue) {
		if (auto LAnyValue = dynamic_cast<TAnyContainer<T>*>(GetAnyValue(AName)))
			LAnyValue->Value = AValue;
		else
			SetAnyValue(AName, new TAnyContainer<T>(AValue));
	};
	__property TControl* Control = {read=FControl};
	__property bool Bool[const String AName] = {read=GetBool, write=SetBool};
	__property float Float[const String AName] = {read=GetFloat, write=SetFloat};
	__property int Int[const String AName] = {read=GetInt, write=SetInt};
	__property System::String String[const System::String AName] = {read=GetString, write=SetString};
	__property TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};

class TfrmBaseViewer : public TfrmBase
{
	typedef TfrmBase inherited;
    friend TViewerOptions;

__published:
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall pnlContentResize(TObject* Sender);
private:
	static std::unique_ptr<TBitmap> FChessBitmap;
	static _di_ISkRuntimeShaderBuilder FChessEffectBuilder;
	TBackgroundKind FBackgroundKind;
	std::function<void()> FOnOptionsChange;
	TViewerOptions* FOptions;
	void CreateChessEffect();
	void __fastcall OptionsChange(TObject* ASender);
	void SetOptions(TViewerOptions* AOptions);
	void UpdateChessBitmap();
protected:
	virtual void DoSetOptions(TViewerOptions* AOptions);
	virtual void OptionsChanged();
	void ScrollBoxEraseBackground(TObject* ASender, const HDC ADC) override;
	HIDESBASE void Show(String ATitle, String ADescription);
	__property TBackgroundKind BackgroundKind = {read=FBackgroundKind, write=FBackgroundKind};
	__property TViewerOptions* Options = {read=FOptions, write=SetOptions};
	__property std::function<void()> OnOptionsChange = {read=FOnOptionsChange, write=FOnOptionsChange};
public:
	__fastcall TfrmBaseViewer(TComponent* Owner) override;
};

#endif
