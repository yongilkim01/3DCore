#include "PreCompile.h"
#include "SoftRenderer.h"
#include "EngineAPICore.h"

USoftRenderer::USoftRenderer()
{
}

USoftRenderer::~USoftRenderer()
{
}

void USoftRenderer::BeginPlay()
{
	URenderer::BeginPlay();

	// 라디안을 => 디그리(360분법)
	// 라디안각도의 개념
	// 6.28
}

void USoftRenderer::Render(float _Delta)
{
	URenderer::Render(_Delta);

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	HDC BackDC = BackBufferImage->GetDC();

	FTransform MainTrans = { {40, 40}, {300, 300} };

	{
		FVector LT = MainTrans.CenterLeftTop();
		FVector RB = MainTrans.CenterRightBottom();

		// Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB	.iY() );
	}

	// 11명

	FTransform SubTrans = { {40, 40}, {0, 0} };

	// 회전하는 벡터 1

	{
		//// 각도를 기반은 회전 회전 기본
		//// 0,0 벡터 + 300, 300을 한거야.
		//SubTrans.Location += MainTrans.Location;
		//Angle += _Delta;
		//FVector DirVector = FVector::AngleToVectorRad(Angle);
		//SubTrans.Location += DirVector * 100.0f;
		//FVector LT = SubTrans.CenterLeftTop();
		//FVector RB = SubTrans.CenterRightBottom();
		//Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
	}

	// 사인 그래프
	{
		//SinG.clear();

		//FVector StartPos = { 300, 300 };

		//for (size_t i = 0; i < 360; i++)
		//{
		//	float SinValue = cosf(static_cast<float>(i) * UEngineMath::D2R);
		//	FTransform ValueTrans = { { 30, 30 }, StartPos + FVector{ static_cast<float>(i * 2.0f),  SinValue * 100.0f } };
		//	SinG.push_back(ValueTrans);
		//}


		//// Ranged for
		//
		//// SinG.begin();
		//// SinG.end();

		//// 레인지드 for
		//// 절대로 삭제할때 쓰지마라.

		//for (FTransform& Trans : SinG)
		//{
		//	FVector LT = Trans.CenterLeftTop();
		//	FVector RB = Trans.CenterRightBottom();

		//	Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
		//}

	}


	{
		Angle += _Delta * 100.0f;

		FVector Point[10];

		for (int i = 0; i < 10; i++)
		{
			Point[i] = FVector::AngleToVectorDeg((Angle)+(90 + (i * 36))) * (i % 2 ? 100.0f : 50.0f);
		}

		POINT WindowPoint1[10];

		for (size_t i = 0; i < 10; i++)
		{
			//FVector DirVector = FVector::AngleToVectorDeg(Angle);
			Point[i] += {500, 300};
			//Point[i] += DirVector * 300.0f;
			WindowPoint1[i] = Point[i].ConvertWindowPOINT();
		}

		Polygon(BackDC, WindowPoint1, 10);
	}

	// 그냥 그대로 사각형을 그려보겠습니다.

}