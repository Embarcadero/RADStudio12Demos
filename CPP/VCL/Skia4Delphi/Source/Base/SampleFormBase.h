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
#pragma option push
#pragma option -w-
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------

class TScrollBox : public Forms::TScrollBox
{
	typedef Forms::TScrollBox inherited;

private:
	BEGIN_MESSAGE_MAP {
		MESSAGE_HANDLER(WM_ERASEBKGND, TWMEraseBkgnd, WMEraseBkgnd)
		MESSAGE_HANDLER(WM_HSCROLL, TWMHScroll, WMHScroll)
		MESSAGE_HANDLER(WM_VSCROLL, TWMVScroll, WMVScroll)
	} END_MESSAGE_MAP(inherited)

	void __fastcall WMEraseBkgnd(TWMEraseBkgnd& AMessage);
	void __fastcall WMHScroll(TWMHScroll& AMessage);
	void __fastcall WMVScroll(TWMVScroll& AMessage);
};

class TfrmBase : public TForm
{
	typedef TForm inherited;
	friend class ::TScrollBox;

__published:
	TPanel *pnlTitle;
	TSkLabel *lblTitle;
	TPanel *pnlTitleLine;
	::TScrollBox *sbxContent;
	TSkSvg *svgBackArrow;
	TPanel *pnlContent;
	TPanel *pnlTip;
	TSkSvg *svgTipIcon;
	TPanel *pnlTipLine;
	TPanel *pnlTipContent;
	TSkLabel *lblTipDescription;
	TPanel *pnlBack;
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
	void __fastcall FormMouseWheel(TObject* Sender, TShiftState Shift, int WheelDelta, TPoint& MousePos, bool& Handled);
	void __fastcall pnlBackClick(TObject* Sender);
	void __fastcall pnlContentResize(TObject* Sender);
private:
	static std::vector<TfrmBase*> FCreatedFormsList;
	static std::vector<TfrmBase*> FShowingFormsList;
	static String GetAssetsPath();
	static String GetOutputPath();
	void __fastcall CMBiDiModeChanged(TMessage& AMessage);

	BEGIN_MESSAGE_MAP {
		MESSAGE_HANDLER(CM_BIDIMODECHANGED, TMessage, CMBiDiModeChanged)
	} END_MESSAGE_MAP(inherited)
protected:
	static void CloseForm(TfrmBase* AForm);
	virtual TColor FormBackgroundColor();
	static TColor FormBorderColor();
	static TfrmBase* GetCurrentForm();
	__property String AssetsPath = {read=GetAssetsPath};
	__property String OutputPath = {read=GetOutputPath};
protected:
	void BeginUpdate();
	template<typename T> T* ChildForm() {
		assert(T::InheritsFrom(__classid(TfrmBase)));
		auto LSelfIndex = find(FCreatedFormsList.begin(), FCreatedFormsList.end(), this);
		if ((LSelfIndex != FCreatedFormsList.end()) && (LSelfIndex != --FCreatedFormsList.end()) && ((*next(LSelfIndex))->ClassType() == __classid(T))) {
			return dynamic_cast<T*>(*next(LSelfIndex));
		}
		T* Result = new T(Application);
		TfrmBase* FormBase = dynamic_cast<TfrmBase*>(Result);
		FormBase->pnlContent->Align = alClient;
		FormBase->pnlBack->Visible = !FShowingFormsList.empty();
		FCreatedFormsList.push_back(FormBase);
		return Result;
	}
	DYNAMIC void __fastcall DoShow();
	void EndUpdate();
	virtual void ScrollBoxChanged(TObject* ASender);
	virtual void ScrollBoxEraseBackground(TObject* ASender, const HDC ADC);
	void ShowMessage(const String AMessage);
public:
	__fastcall TfrmBase(TComponent* Owner) override;
	HIDESBASE void Show();
	int __fastcall ShowModal() override;
};

#pragma option pop
#endif
