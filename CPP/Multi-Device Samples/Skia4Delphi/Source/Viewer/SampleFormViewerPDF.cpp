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

#ifdef _Windows
	#include <Winapi.Windows.hpp>
	#include <Winapi.ShellAPI.hpp>
	#include <System.IOUtils.hpp>
#elif defined(__ANDROID__)
	#include <Androidapi.JNI.GraphicsContentViewText.hpp>
	#include <Androidapi.JNI.JavaTypes.hpp>
	#include <Androidapi.JNI.Support.hpp>
	#include <Androidapi.JNI.Net.hpp>
	#include <Androidapi.JNI.App.hpp>
	#include <Androidapi.Helpers.hpp>
#endif
#include "SampleFormViewerPDF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

void TfrmPDFViewer::Show(const String ATitle, const String ADescription,
	String AFileName)
{
#ifdef __ANDROID__
	_di_JFile LFile = TJFile::JavaClass->init(StringToJString(AFileName));
	_di_JIntent LIntent = TJIntent::JavaClass->init(TJIntent::JavaClass->ACTION_VIEW);
	LIntent->setDataAndType(TAndroidHelper::JFileToJURI(LFile), StringToJString("application/pdf"));
	LIntent->setFlags(TJIntent::JavaClass->FLAG_GRANT_READ_URI_PERMISSION);
	TAndroidHelper::Activity->startActivity(LIntent);
#else
	#ifdef _Windows
	AFileName = "file://" + StringReplace(Ioutils::TPath::GetFullPath(AFileName), "\\", "/", TReplaceFlags() << rfReplaceAll);
	ShellExecuteW(0, String("open").c_str(), AFileName.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
	#else
	AFileName = "file://" + StringReplace(AFileName, "\\", "/", TReplaceFlags() << rfReplaceAll);
	BackgroundKind = TBackgroundKind::Solid;
	wbrBrowser->Navigate(AFileName);
	inherited::Show(ATitle, ADescription);
	#endif
#endif
}

