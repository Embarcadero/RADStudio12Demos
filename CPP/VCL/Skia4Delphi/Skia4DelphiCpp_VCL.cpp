//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <Vcl.Styles.hpp>
//---------------------------------------------------------------------------
USEFORM("Source\SampleFormMain.cpp", frmMain);
USEFORM("Source\Base\SampleFormBaseViewer.cpp", frmBaseViewer);
USEFORM("Source\Base\SampleFormBase.cpp", frmBase);
USEFORM("Source\Viewer\SampleFormViewerAnimatedPaintBox.cpp", frmAnimatedPaintBoxViewer);
USEFORM("Source\Viewer\SampleFormViewerControl.cpp", frmControlViewer);
USEFORM("Source\Viewer\SampleFormViewerPaintBox.cpp", frmPaintBoxViewer);
USEFORM("Source\Viewer\SampleFormViewerTImage.cpp", frmTImageViewer);
USEFORM("Source\Viewer\SampleFormViewerComparisonImage.cpp", frmComparisonImageViewer);
USEFORM("Source\Viewer\SampleFormViewerUnicodeBiDi.cpp", frmUnicodeBiDiViewer);
USEFORM("Source\Viewer\SampleFormViewerUnicodeGraphemes.cpp", frmUnicodeGraphemesViewer);
USEFORM("Source\SampleFormBasics.cpp", frmBasics);
USEFORM("Source\SampleFormControls.cpp", frmControls);
USEFORM("Source\SampleFormControlsTSkAnimatedImage.cpp", frmTSkAnimatedImage);
USEFORM("Source\SampleFormControlsTSkLabel.cpp", frmTSkLabel);
USEFORM("Source\SampleFormControlsTSkPaintBox.cpp", frmTSkPaintBox);
USEFORM("Source\SampleFormControlsTSkSVG.cpp", frmTSkSVG);
USEFORM("Source\SampleFormDocuments.cpp", frmDocuments);
USEFORM("Source\SampleFormFilter.cpp", frmFilter);
USEFORM("Source\SampleFormImage.cpp", frmImage);
USEFORM("Source\SampleFormPathsAndEffects.cpp", frmPathsAndEffects);
USEFORM("Source\SampleFormRuntimeEffects.cpp", frmRuntimeEffects);
USEFORM("Source\SampleFormSplashScreen.cpp", frmSplashScreen);
USEFORM("Source\SampleFormText.cpp", frmText);
USEFORM("Source\SampleFormTransforms.cpp", frmTransforms);
USEFORM("Source\SampleFormUnicode.cpp", frmUnicode);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        ReportMemoryLeaksOnShutdown = true;
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		if (FileExists("..\\..\\..\\Windows11.vsf"))
			TStyleManager::LoadFromFile("..\\..\\..\\Windows11.vsf");
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
