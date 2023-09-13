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

#include "SampleFormViewerUnicodeGraphemes.h"
#include "SampleFormViewerUnicodeBiDi.h"
#include "SampleFormUnicode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void AddBiDiRegion(String& ABiDiRegionDescription, const String AText,
	const int AStartIndex, const int AEndIndex, const bool AIsRTL)
{
	String LRegionText = AText.SubString0(AStartIndex, AEndIndex - AStartIndex);
	ABiDiRegionDescription = ABiDiRegionDescription + sLineBreak +
		Format("  \"%s\"  - %s", ARRAYOFCONST((LRegionText, AIsRTL ? "Right-to-Left" : "Left-to-Right")));
}
//---------------------------------------------------------------------------

void __fastcall TfrmUnicode::btnBiDiIteratorClick(TObject* Sender)
{
	static const String Text = U"سلام دنیا! Hello Word!";
	String LBiDiRegionDescription = "";
	int LStartIndexValue = 0;
	int* LStartIndex = &LStartIndexValue;

	auto LUnicode = SkUnicode();
	LUnicode->ForEachBidiRegion(Text, TSkDirection::LeftToRight,
		[this, &LBiDiRegionDescription, &LStartIndex](const int AStart, const int AEnd, const unsigned char ALevel) {
			AddBiDiRegion(LBiDiRegionDescription, Text, *LStartIndex, AEnd, ALevel == 1);
			*LStartIndex = AEnd;
		});
	if (LStartIndexValue < Text.Length())
		AddBiDiRegion(LBiDiRegionDescription, Text, LStartIndexValue, Text.Length(), false);

	ChildForm<TfrmUnicodeBiDiViewer>()->Show("BiDi Regions Iterator",
		"Iterates over regions of text based on their direction.",
		Text, LBiDiRegionDescription);
}
//---------------------------------------------------------------------------

String StringHexadecimal(const String AText)
{
	String Result = "";
	for (Char LChar : AText) {
		if (!Result.IsEmpty())
			Result = Result + " ";
		Result = Result + "$" + IntToHex(int(LChar), 4);
	}
	return Result;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUnicode::btnGraphemeIteratorClick(TObject* Sender)
{
	static const String Text = U"Hi! ✋🏻🙏🏻🙋🏻‍♂️";
	String LGraphemesDescription = "";
	auto LUnicode = SkUnicode();
	for (String LGrapheme : LUnicode->GetBreaks(Text, TSkBreakType::Graphemes)) {
		LGraphemesDescription = LGraphemesDescription + sLineBreak +
			Format("  %s  - %d Char - %s", ARRAYOFCONST((LGrapheme, LGrapheme.Length(), StringHexadecimal(LGrapheme))));
	}
	ChildForm<TfrmUnicodeGraphemesViewer>()->Show("Graphemes Iterator", "Grapheme is the single displayed character (like one emoji, one letter).",
		Text, LGraphemesDescription);
}
//---------------------------------------------------------------------------

