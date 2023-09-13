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

#include "SampleFormViewerPDF.h"
#include "SampleFormDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void __fastcall TfrmDocuments::btnCreatePDFDrawingSVGClick(TObject* Sender)
{
	auto LSVGDOM = TSkSVGDOM::MakeFromFile(AssetsPath + "lion.svg");
	auto LSize = TSizeF(600, 600);
	LSVGDOM->SetContainerSize(LSize);

	auto LDocumentFileName = OutputPath + "document.pdf";
	TFileStream *LDocumentStream = new TFileStream(LDocumentFileName, fmCreate);
	try {
		auto LDocument = TSkDocument::MakePDF(LDocumentStream);
		try {
			auto LCanvas = LDocument->BeginPage(LSize.Width, LSize.Height);
			try {
				LSVGDOM->Render(LCanvas);
			} __finally {
				LDocument->EndPage();
			}
		} __finally {
			LDocument->Close();
		}
	} __finally {
		LDocumentStream->Free();
	}
	ChildForm<TfrmPDFViewer>()->Show("Creating PDF", "", LDocumentFileName);
}
//---------------------------------------------------------------------------

void __fastcall TfrmDocuments::btnCreateXPSDrawingSVGClick(TObject* Sender)
{
	auto LSVGDOM = TSkSVGDOM::MakeFromFile(AssetsPath + "lion.svg");
	auto LSize = TSizeF(600, 600);
	LSVGDOM->SetContainerSize(LSize);

	auto LDocumentFileName = OutputPath + "document.xps";
	TFileStream *LDocumentStream = new TFileStream(LDocumentFileName, fmCreate);
	try {
		auto LDocument = TSkDocument::MakeXPS(LDocumentStream);
		if (LDocument == nullptr) {
			ShowMessage("This OS doesn''t support XPS!");
			return;
		}
		try {
			auto LCanvas = LDocument->BeginPage(LSize.Width, LSize.Height);
			try {
				LSVGDOM->Render(LCanvas);
			} __finally {
				LDocument->EndPage();
			}
		} __finally {
			LDocument->Close();
		}
	} __finally {
		LDocumentStream->Free();
	}
	ShowMessage("Created XPS file!");
}
//---------------------------------------------------------------------------

