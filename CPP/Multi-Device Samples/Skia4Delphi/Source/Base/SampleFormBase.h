//---------------------------------------------------------------------------

// This software is Copyright (c) 2022 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

#ifndef SampleFormBaseH
#define SampleFormBaseH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Skia.hpp>
#include <FMX.Skia.hpp>
#include <vector>
//---------------------------------------------------------------------------

class TScrollBox : public Layouts::TScrollBox
{
protected:
	void __fastcall DoUpdateAniCalculations(TScrollCalculations* const AAniCalculations) override;
public:
	void __fastcall UpdateAniCalculations() { Layouts::TScrollBox::UpdateAniCalculations(); }
};

class TfrmBase : public TForm
{
	typedef TForm inherited;

__published:
	TRectangle *rctContent;
	TRectangle *rctHeader;
	TSkLabel *lblTitle;
	TSpeedButton *btnBack;
	TSkSvg *svgBackArrow;
	TRectangle *rctTip;
	TSkSvg *svgTipIcon;
	TLayout *lytTipContent;
	TSkLabel *lblTipDescription;
	::TScrollBox *sbxContent;
	TRectangle *rctGestureBar;
	TRectangle *rctNavigationBar;
	TRectangle *rctStatusBar;
	void __fastcall btnBackClick(TObject* Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyDown(TObject* Sender, WORD& Key, System::WideChar& KeyChar, TShiftState Shift);
	void __fastcall rctContentResized(TObject* Sender);
private:
	static std::vector<TfrmBase*> FCreatedFormsList;
	static std::vector<TfrmBase*> FShowingFormsList;
	static String GetAssetsPath();
	static String GetOutputPath();
private:
	bool FAllowScrollBoundsAnimation = true;
	void SetAllowScrollBoundsAnimation(const bool AValue);
protected:
	static void CloseForm(TfrmBase* AForm);
	virtual TAlphaColor FormBackgroundColor();
	static TAlphaColor FormBorderColor();
	static TfrmBase* GetCurrentForm();
	__property String AssetsPath = {read=GetAssetsPath};
	__property String OutputPath = {read=GetOutputPath};
protected:
	template<typename T> T* ChildForm() {
		assert(T::InheritsFrom(__classid(TfrmBase)));
		auto LSelfIndex = find(FCreatedFormsList.begin(), FCreatedFormsList.end(), this);
		if ((LSelfIndex != FCreatedFormsList.end()) && (LSelfIndex != --FCreatedFormsList.end()) && ((*next(LSelfIndex))->ClassType() == __classid(T))) {
			return dynamic_cast<T*>(*next(LSelfIndex));
		}
		T* Result = new T(Application);
		TfrmBase* FormBase = dynamic_cast<TfrmBase*>(Result);
		FormBase->rctContent->Align = TAlignLayout::Client;
		FormBase->btnBack->Visible = !FShowingFormsList.empty();
		FormBase->rctGestureBar->Height = rctGestureBar->Height;
		FCreatedFormsList.push_back(FormBase);
		return Result;
	}
	void __fastcall DoShow() override;
	virtual void DoSystemBarsInsetsChange();
	virtual bool HasBottomContent();
	void __fastcall PaintBackground() override;
	void ShowMessage(const String AMessage);
public:
	__fastcall TfrmBase(TComponent* Owner) override;
	HIDESBASE void Show();
	__property bool AllowScrollBoundsAnimation = {read=FAllowScrollBoundsAnimation, write=SetAllowScrollBoundsAnimation};
};

#endif
