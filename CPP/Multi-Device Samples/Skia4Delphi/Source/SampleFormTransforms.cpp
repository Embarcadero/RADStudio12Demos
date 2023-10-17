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

#include "SampleFormViewerPaintBox.h"
#include "SampleFormTransforms.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------

enum class TTaperCorner {LeftOrTop, RightOrBottom, Both};

static const TMatrix MatrixIdentity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
static const TMatrix3D Matrix3DIdentity = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

struct TSkMatrix
{
private:
	TMatrix FMatrix = MatrixIdentity;
	float GetValue(const int AIndex) { return FMatrix.M[AIndex / 3].V[AIndex % 3]; }
	void SetValue(const int AIndex, const float AValue) { FMatrix.M[AIndex / 3].V[AIndex % 3] = AValue; }
public:
	static TSkMatrix CreateFromMatrix3D(const TMatrix3D AMatrix3D);
	static TSkMatrix Identity() { return TSkMatrix(); }
    TMatrix ToTMatrix() { return FMatrix; }
	__property float Persp0 = {index=2, read=GetValue, write=SetValue};
	__property float Persp1 = {index=5, read=GetValue, write=SetValue};
	__property float Persp2 = {index=8, read=GetValue, write=SetValue};
	__property float ScaleX = {index=0, read=GetValue, write=SetValue};
	__property float ScaleY = {index=4, read=GetValue, write=SetValue};
	__property float SkewX  = {index=3, read=GetValue, write=SetValue};
	__property float SkewY  = {index=1, read=GetValue, write=SetValue};
	__property float TransX = {index=6, read=GetValue, write=SetValue};
	__property float TransY = {index=7, read=GetValue, write=SetValue};
	operator TMatrix&() { return FMatrix; }
	operator TMatrix() { return FMatrix; }
};

#pragma region " - Workaround RSP-36958"
// - ---------------------------------------------------------------------------
// - WORKAROUND
// - ---------------------------------------------------------------------------
// -
// - Description:
// -   This code is a workaround intended to fix a TMatrix3D to TMatrix
// -   conversion. The TMatrix3D.ToMatrix method results in some wrong values.
// -
// - Bug report:
// -   https://quality.embarcadero.com/browse/RSP-36958
// -
// - ---------------------------------------------------------------------------
#if __BCPLUSPLUS__ > 0x0770
	#warning Check if the issue has been fixed
#endif
// - ---------------------------------------------------------------------------
TSkMatrix TSkMatrix::CreateFromMatrix3D(const TMatrix3D AMatrix3D)
{
	TSkMatrix Result;
	Result.FMatrix.m11 = AMatrix3D.m11;
	Result.FMatrix.m21 = AMatrix3D.m21;
	Result.FMatrix.m31 = AMatrix3D.m41;
	Result.FMatrix.m12 = AMatrix3D.m12;
	Result.FMatrix.m22 = AMatrix3D.m22;
	Result.FMatrix.m32 = AMatrix3D.m42;
	Result.FMatrix.m13 = AMatrix3D.m14;
	Result.FMatrix.m23 = AMatrix3D.m24;
	Result.FMatrix.m33 = AMatrix3D.m44;
	return Result;
}
// - ---------------------------------------------------------------------------
#pragma end_region

TMatrix TaperTransform(const TSizeF& ASize, const TSide ATaperSide,
	const TTaperCorner ATaperCorner, const float ATaperFraction)
{
	TSkMatrix Result = TSkMatrix::Identity();
	switch(ATaperSide) {
		case TSide::Left:
			Result.ScaleX = ATaperFraction;
			Result.ScaleY = ATaperFraction;
			Result.Persp0 = (ATaperFraction - 1) / ASize.Width;

			switch(ATaperCorner) {
				case TTaperCorner::LeftOrTop:
					Result.SkewY = ASize.Height * Result.Persp0;
					Result.TransY = ASize.Height * (1 - ATaperFraction);
					break;
				case TTaperCorner::RightOrBottom: break;
				case TTaperCorner::Both:
					Result.SkewY = (ASize.Height / 2.f) * Result.Persp0;
					Result.TransY = ASize.Height * (1 - ATaperFraction) / 2.f;
					break;
			}
			break;
		case TSide::Top:
			Result.ScaleX = ATaperFraction;
			Result.ScaleY = ATaperFraction;
			Result.Persp1 = (ATaperFraction - 1) / ASize.Height;

			switch(ATaperCorner) {
				case TTaperCorner::LeftOrTop:
					Result.SkewX = ASize.Width * Result.Persp1;
					Result.TransX = ASize.Width * (1 - ATaperFraction);
					break;
				case TTaperCorner::RightOrBottom: break;
				case TTaperCorner::Both:
					Result.SkewX = (ASize.Width / 2.f) * Result.Persp1;
					Result.TransX = ASize.Width * (1 - ATaperFraction) / 2.f;
					break;
			}
			break;
		case TSide::Right:
			Result.ScaleX = 1.f / ATaperFraction;
			Result.Persp0 = (1 - ATaperFraction) / (ASize.Width * ATaperFraction);

			switch(ATaperCorner) {
				case TTaperCorner::LeftOrTop: Result.SkewY = ASize.Height * Result.Persp0; break;
				case TTaperCorner::RightOrBottom: break;
				case TTaperCorner::Both: Result.SkewY = (ASize.Height / 2.f) * Result.Persp0; break;
			}
			break;
		case TSide::Bottom:
			Result.ScaleY = 1.f / ATaperFraction;
			Result.Persp1 = (1 - ATaperFraction) / (ASize.Height * ATaperFraction);

			switch(ATaperCorner) {
				case TTaperCorner::LeftOrTop: Result.SkewX = ASize.Width * Result.Persp1; break;
				case TTaperCorner::RightOrBottom: break;
				case TTaperCorner::Both: Result.SkewX = (ASize.Width / 2) * Result.Persp1; break;
			}
			break;
	}
    return Result.ToTMatrix();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTransforms::btn3DRotationClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("X-Axis Rotation", 0, 360, 0);
	LOptions->AddFloat("Y-Axis Rotation", 0, 360, 45);
	LOptions->AddFloat("Z-Axis Rotation", 0, 360, 0);
	LOptions->AddFloat("Depth", 250, 2500, 650);

	ChildForm<TfrmPaintBoxViewer>()->Show("3D Rotation", "",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			static const float MarginProportion = 0.3;
            _di_ISkImage LImage;

			if (Sign(Cos(DegToRad(LOptions->Float["X-Axis Rotation"])) * Cos(DegToRad(LOptions->Float["Y-Axis Rotation"]))) == NegativeValue)
				LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "deck-card-back.webp");
			else
				LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "deck-card-front.webp");
            float LRatio;
			RectF(0, 0, LImage->Width, LImage->Height).FitInto(ADest, LRatio);
			LRatio = LRatio * (1 + MarginProportion);

			ACanvas->Save();
			try {
				TMatrix3D LMatrix3D = TMatrix3D::CreateRotationX(DegToRad(LOptions->Float["X-Axis Rotation"]))
					* TMatrix3D::CreateRotationY(DegToRad(LOptions->Float["Y-Axis Rotation"]))
					* TMatrix3D::CreateRotationZ(DegToRad(LOptions->Float["Z-Axis Rotation"]));
				TMatrix3D LPerspectiveMatrix3D = Matrix3DIdentity;
				LPerspectiveMatrix3D.m34 = -1.f / LOptions->Float["Depth"];
				TMatrix LMatrix = TMatrix::CreateTranslation(-ADest.CenterPoint().X, -ADest.CenterPoint().Y) * TMatrix::CreateScaling(1.f / LRatio, 1.f / LRatio);
				LMatrix = LMatrix * TSkMatrix::CreateFromMatrix3D(LMatrix3D * LPerspectiveMatrix3D);
				ACanvas->Concat(LMatrix * TMatrix::CreateTranslation(ADest.CenterPoint().X, ADest.CenterPoint().Y));

				ACanvas->DrawImage(LImage, ADest.CenterPoint().X - (LImage->Width / 2.f), ADest.CenterPoint().Y - (LImage->Height / 2.f),
					TSkSamplingOptions::High());
			} __finally {
				ACanvas->Restore();
			}
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

TMatrix ComputeMatrix(const TSizeF ASize, const TPointF ATopLeft,
	const TPointF ATopRight, const TPointF ABottomRight,
	const TPointF ABottomLeft)
{
	TMatrix S = TMatrix::CreateScaling(1.f / ASize.Width, 1.f / ASize.Height);

	// Affine transform
	TSkMatrix A = TSkMatrix::Identity();
	A.ScaleX = ATopRight.X - ATopLeft.X;
	A.SkewY = ATopRight.Y - ATopLeft.Y;
	A.SkewX = ABottomLeft.X - ATopLeft.X;
	A.ScaleY = ABottomLeft.Y - ATopLeft.Y;
	A.TransX = ATopLeft.X;
	A.TransY = ATopLeft.Y;

	// Non-Affine transform
	TPointF LPoint = ABottomRight * A.ToTMatrix().Inverse();
	TSkMatrix N = TSkMatrix::Identity();
	N.ScaleX = LPoint.X / (LPoint.X + LPoint.Y - 1);
	N.ScaleY = LPoint.Y / (LPoint.X + LPoint.Y - 1);
	N.Persp0 = N.ScaleX - 1;
	N.Persp1 = N.ScaleY - 1;

	// Multiply S * N * A
	TMatrix Result = MatrixIdentity;
	Result = Result * S;
	Result = Result * N;
	Result = Result * A;
	return Result;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTransforms::btnStrechedCornersClick(TObject* Sender)
{
	static const int CornerButtonSize = 20;
	static const int TouchExpansion = 5;

	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->Bool["IsFirstDraw"] = true;
	LOptions->Int["TouchCornerDraggingIndex"] = -1;

	// Mouse events
	ChildForm<TfrmPaintBoxViewer>()->OnMouseDown =
		[this, LOptions](const TPointF APoint, bool& AShouldRedraw) {
			auto LCorners = LOptions->GetValue<TCornersF>("TouchCorners");
			for (int i = 0; i < LCorners.Size(); i++) {
				if (LCorners[i].Distance(APoint) <= (CornerButtonSize / 2.f) + TouchExpansion) {
					AShouldRedraw = true;
					LOptions->Int["TouchCornerDraggingIndex"] = i;
					return;
				}
			}
			LOptions->Int["TouchCornerDraggingIndex"] = -1;
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseMove =
		[this, LOptions](const TPointF APoint, const bool AIsMouseDown, bool& AShouldRedraw) {
			if (LOptions->Int["TouchCornerDraggingIndex"] != -1) {
				TCornersF LCorners = LOptions->GetValue<TCornersF>("TouchCorners");
				LCorners[LOptions->Int["TouchCornerDraggingIndex"]] = APoint;
				LOptions->SetValue<TCornersF>("TouchCorners", LCorners);
				AShouldRedraw = true;
			}
		};
	ChildForm<TfrmPaintBoxViewer>()->OnMouseUp =
		[this, LOptions](const TPointF APoint, bool& AShouldRedraw) {
			AShouldRedraw = LOptions->Int["TouchCornerDraggingIndex"] != -1;
			LOptions->Int["TouchCornerDraggingIndex"] = -1;
		};

	// Draw method
	ChildForm<TfrmPaintBoxViewer>()->Show("Streched Corners", "Click and drag the corners",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			static const TAlphaColor CornerButtonColor[] = { 0x7F365FF4, 0x9FFF0000 };
			TCornersF LCorners;
			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "wolf.webp");
			auto LDest = ADest;
			LDest.Inflate(-50, -50);

			if (LOptions->Bool["IsFirstDraw"]) {
				LCorners = CornersF(LDest);
				// Changing the top-left corner initial value
				LCorners[0] = LCorners[0] + PointF(LDest.Width(), LDest.Height()) * 0.25;
				LOptions->SetValue<TCornersF>("TouchCorners", LCorners);
				LOptions->Bool["IsFirstDraw"] = false;
			} else
				LCorners = LOptions->GetValue<TCornersF>("TouchCorners");

			// Draw the image transformed
			ACanvas->Save();
			try {
				ACanvas->Concat(ComputeMatrix(LDest.Size, LCorners[0], LCorners[1], LCorners[2], LCorners[3]));
				ACanvas->Translate(-LDest.Left, -LDest.Top);
				ACanvas->DrawImageRect(LImage, LDest, TSkSamplingOptions::High());
			} __finally {
				ACanvas->Restore();
			}

			// Draw corner buttons
			auto LPaint = SkPaint();
			LPaint->AntiAlias = true;
			for (int i = 0; i < LCorners.Size(); i++) {
				LPaint->Color = CornerButtonColor[i == LOptions->Int["TouchCornerDraggingIndex"]];
				ACanvas->DrawCircle(LCorners[i], CornerButtonSize / 2.f, LPaint);
			}
		});
}
//---------------------------------------------------------------------------

void __fastcall TfrmTransforms::btnTaperTransformClick(TObject* Sender)
{
	TViewerOptions* LOptions = new TViewerOptions();
	LOptions->AddFloat("Fraction", 0.01, 1, 0.3);
	LOptions->AddEnum("Side", TSide::Right);
	LOptions->AddEnum("Corner", TTaperCorner::Both);

	ChildForm<TfrmPaintBoxViewer>()->Show("Taper Transform", "",
		[this, LOptions](ISkCanvas* const ACanvas, const TRectF& ADest) {
			auto LImage = TSkImage::MakeFromEncodedFile(AssetsPath + "prehistoric.webp");
			TRectF LDest = ADest;
			LDest.Inflate(-50, -50);

			ACanvas->Save();
			try {
				TMatrix LMatrix = TMatrix::CreateTranslation(-LDest.Left, -LDest.Top);
				LMatrix = LMatrix * TaperTransform(LDest.Size, TSide(LOptions->Int["Side"]), TTaperCorner(LOptions->Int["Corner"]), LOptions->Float["Fraction"]);
				LMatrix = LMatrix * TMatrix::CreateTranslation(LDest.Left, LDest.Top);
				ACanvas->Concat(LMatrix);
				ACanvas->DrawImageRect(LImage, LDest, TSkSamplingOptions::High());
			} __finally {
				ACanvas->Restore();
			}
		}, TBackgroundKind::Chess, LOptions);
}
//---------------------------------------------------------------------------

