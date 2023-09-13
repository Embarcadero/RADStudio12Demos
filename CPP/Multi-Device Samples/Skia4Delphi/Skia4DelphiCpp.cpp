//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
#include <FMX.Skia.hpp>
//---------------------------------------------------------------------------
USEFORM("Source\Base\SampleFormBaseViewer.cpp", frmBaseViewer);
USEFORM("Source\Base\SampleFormBase.cpp", frmBase);
USEFORM("Source\SampleFormBasics.cpp", frmBasics);
USEFORM("Source\SampleFormControls.cpp", frmControls);
USEFORM("Source\SampleFormControlsTSkAnimatedImage.cpp", frmTSkAnimatedImage);
USEFORM("Source\SampleFormControlsTSkLabel.cpp", frmTSkLabel);
USEFORM("Source\SampleFormControlsTSkPaintBox.cpp", frmTSkPaintBox);
USEFORM("Source\SampleFormControlsTSkSVG.cpp", frmTSkSVG);
USEFORM("Source\SampleFormDocuments.cpp", frmDocuments);
USEFORM("Source\SampleFormFilter.cpp", frmFilter);
USEFORM("Source\SampleFormImage.cpp", frmImage);
USEFORM("Source\SampleFormMain.cpp", frmMain);
USEFORM("Source\SampleFormPathsAndEffects.cpp", frmPathsAndEffects);
USEFORM("Source\SampleFormRuntimeEffects.cpp", frmRuntimeEffects);
USEFORM("Source\SampleFormSplashScreen.cpp", frmSplashScreen);
USEFORM("Source\SampleFormText.cpp", frmText);
USEFORM("Source\SampleFormTransforms.cpp", frmTransforms);
USEFORM("Source\SampleFormUnicode.cpp", frmUnicode);
USEFORM("Source\Viewer\SampleFormViewerAnimatedPaintBox.cpp", frmAnimatedPaintBoxViewer);
USEFORM("Source\Viewer\SampleFormViewerComparisonImage.cpp", frmComparisonImageViewer);
USEFORM("Source\Viewer\SampleFormViewerControl.cpp", frmControlViewer);
USEFORM("Source\Viewer\SampleFormViewerPaintBox.cpp", frmPaintBoxViewer);
USEFORM("Source\Viewer\SampleFormViewerPDF.cpp", frmPDFViewer);
USEFORM("Source\Viewer\SampleFormViewerTImage.cpp", frmTImageViewer);
USEFORM("Source\Viewer\SampleFormViewerUnicodeBiDi.cpp", frmUnicodeBiDiViewer);
USEFORM("Source\Viewer\SampleFormViewerUnicodeGraphemes.cpp", frmUnicodeGraphemesViewer);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		GlobalUseMetal = true;
		GlobalUseSkiaRasterWhenAvailable = false;
		GlobalUseSkia = true;
		ReportMemoryLeaksOnShutdown = true;
		Application->Initialize();
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
