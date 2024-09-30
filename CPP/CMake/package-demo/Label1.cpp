//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Label1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TLabel1 *)
{
	new TLabel1(NULL);
}
//---------------------------------------------------------------------------
__fastcall TLabel1::TLabel1(TComponent* Owner)
	: TLabel(Owner)
{
}
//---------------------------------------------------------------------------
namespace Label1
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TLabel1)};
		RegisterComponents(L"Samples", classes, 0);
	}
}
//---------------------------------------------------------------------------
