#include "PreCompile.h"
#include "SoftRenderer.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineInput.h>

USoftRenderer::USoftRenderer()
{

	BoxMesh.Vertexs.resize(12);

	for (size_t i = 0; i < BoxMesh.Vertexs.size(); i++)
	{
		BoxMesh.Vertexs[i].resize(3);
	}

	// ���ý����̽� ���� ��ǥ���� �θ��ϴ�.
	// ������ �����Ϸ��� 0,0 �� ���ĸ� ������ ���� �Ѵ�.
	BoxMesh.Vertexs[0].resize(3);
	BoxMesh.Vertexs[1].resize(3);

	// �Ʒ��� ����
	// BoxMesh.Vertexs[0][0] = FVector(-0.5, );

	// �ո� �����
	BoxMesh.Vertexs[0][0] = FVector(-0.5f, 0.5f, -0.5f);
	BoxMesh.Vertexs[0][1] = FVector(0.5f, 0.5f, -0.5f);
	BoxMesh.Vertexs[0][2] = FVector(-0.5f, -0.5f, -0.5f);
	BoxMesh.Vertexs[1][0] = FVector(0.5f, 0.5f, -0.5f);
	BoxMesh.Vertexs[1][1] = FVector(0.5f, -0.5f, -0.5f);
	BoxMesh.Vertexs[1][2] = FVector(-0.5f, -0.5f, -0.5f);

	// �޸�
	BoxMesh.Vertexs[2][0] = BoxMesh.Vertexs[0][0].RotationXDegReturn(180);
	BoxMesh.Vertexs[2][1] = BoxMesh.Vertexs[0][1].RotationXDegReturn(180);
	BoxMesh.Vertexs[2][2] = BoxMesh.Vertexs[0][2].RotationXDegReturn(180);
	BoxMesh.Vertexs[3][0] = BoxMesh.Vertexs[1][0].RotationXDegReturn(180);
	BoxMesh.Vertexs[3][1] = BoxMesh.Vertexs[1][1].RotationXDegReturn(180);
	BoxMesh.Vertexs[3][2] = BoxMesh.Vertexs[1][2].RotationXDegReturn(180);

	// ���ʸ�
	BoxMesh.Vertexs[4][0] = BoxMesh.Vertexs[0][0].RotationYDegReturn(90);
	BoxMesh.Vertexs[4][1] = BoxMesh.Vertexs[0][1].RotationYDegReturn(90);
	BoxMesh.Vertexs[4][2] = BoxMesh.Vertexs[0][2].RotationYDegReturn(90);
	BoxMesh.Vertexs[5][0] = BoxMesh.Vertexs[1][0].RotationYDegReturn(90);
	BoxMesh.Vertexs[5][1] = BoxMesh.Vertexs[1][1].RotationYDegReturn(90);
	BoxMesh.Vertexs[5][2] = BoxMesh.Vertexs[1][2].RotationYDegReturn(90);

	// ������
	BoxMesh.Vertexs[6][0] = BoxMesh.Vertexs[0][0].RotationYDegReturn(-90);
	BoxMesh.Vertexs[6][1] = BoxMesh.Vertexs[0][1].RotationYDegReturn(-90);
	BoxMesh.Vertexs[6][2] = BoxMesh.Vertexs[0][2].RotationYDegReturn(-90);
	BoxMesh.Vertexs[7][0] = BoxMesh.Vertexs[1][0].RotationYDegReturn(-90);
	BoxMesh.Vertexs[7][1] = BoxMesh.Vertexs[1][1].RotationYDegReturn(-90);
	BoxMesh.Vertexs[7][2] = BoxMesh.Vertexs[1][2].RotationYDegReturn(-90);

	// ����
	BoxMesh.Vertexs[8][0] = BoxMesh.Vertexs[0][0].RotationXDegReturn(-90);
	BoxMesh.Vertexs[8][1] = BoxMesh.Vertexs[0][1].RotationXDegReturn(-90);
	BoxMesh.Vertexs[8][2] = BoxMesh.Vertexs[0][2].RotationXDegReturn(-90);
	BoxMesh.Vertexs[9][0] = BoxMesh.Vertexs[1][0].RotationXDegReturn(-90);
	BoxMesh.Vertexs[9][1] = BoxMesh.Vertexs[1][1].RotationXDegReturn(-90);
	BoxMesh.Vertexs[9][2] = BoxMesh.Vertexs[1][2].RotationXDegReturn(-90);

	// ����
	BoxMesh.Vertexs[10][0] = BoxMesh.Vertexs[0][0].RotationXDegReturn(90);
	BoxMesh.Vertexs[10][1] = BoxMesh.Vertexs[0][1].RotationXDegReturn(90);
	BoxMesh.Vertexs[10][2] = BoxMesh.Vertexs[0][2].RotationXDegReturn(90);
	BoxMesh.Vertexs[11][0] = BoxMesh.Vertexs[1][0].RotationXDegReturn(90);
	BoxMesh.Vertexs[11][1] = BoxMesh.Vertexs[1][1].RotationXDegReturn(90);
	BoxMesh.Vertexs[11][2] = BoxMesh.Vertexs[1][2].RotationXDegReturn(90);

}

USoftRenderer::~USoftRenderer()
{
}

void USoftRenderer::BeginPlay()
{
	URenderer::BeginPlay();

	// BoxMesh.Vertexs.resize(12);

	// ������ => ��׸�(360�й�)
	// ���Ȱ����� ����
	// 6.28
}

void USoftRenderer::Render(float _Delta)
{
	URenderer::Render(_Delta);

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	HDC BackDC = BackBufferImage->GetDC();

	FTransform MainTrans = { {40, 40}, {300, 300} };


	// 11��
	FTransform SubTrans = { {40, 40}, {0, 0} };

	// ȸ���ϴ� ���� 1

	for (size_t i = 0; i < 4; i++)
	{
		if (true == UEngineInput::GetInst().IsDown('1' + i))
		{
			Select = i + 1;
			break;
		}
	}

	switch (Select)
	{
	case 0:
	{
		// ���庯ȯ


		// ������ �Ž��� ī�Ǹ� �����.
		// ���� �����̽���� �θ��� �ڽŸ��� ������ �����ߴ�.
		FirstMesh Copy = BoxMesh;

		// ���� ��ȯ�� ������ �ֽ��ϴ�.
		// ũ���̰���
		// ũ�� ���� �̵� ���� �θ�

		// ũ��
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex].X = Copy.Vertexs[Tri][Vertex].X * 100.0f * Scale.X;
				Copy.Vertexs[Tri][Vertex].Y = Copy.Vertexs[Tri][Vertex].Y * 100.0f * Scale.Y;
				Copy.Vertexs[Tri][Vertex].Z = Copy.Vertexs[Tri][Vertex].Z * 100.0f * Scale.Z;
			}
		}

		// ����
		//Roation.X += _Delta * 360;
		//Roation.Y = 30;
		Roation.Y += _Delta * 60;

		// ���� ��ȯ�� �ؼ� ���� ���Ӽ��迡�� ���̰� ����� ���̴�.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex].RotationXDeg(Roation.X);
				Copy.Vertexs[Tri][Vertex].RotationYDeg(Roation.Y);
				Copy.Vertexs[Tri][Vertex].RotationZDeg(Roation.Z);
			}
		}


		// �̵�
		// ���� ��ȯ�� �ؼ� ���� ���Ӽ��迡�� ���̰� ����� ���̴�.
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				Copy.Vertexs[Tri][Vertex] += Position;
			}
		}

		// 2���� 3����
		for (size_t Tri = 0; Tri < Copy.Vertexs.size(); Tri++)
		{
			POINT WindowPoint[3];

			for (size_t Vertex = 0; Vertex < Copy.Vertexs[Tri].size(); Vertex++)
			{
				WindowPoint[Vertex] = Copy.Vertexs[Tri][Vertex].ConvertWindowPOINT();
			}

			Polygon(BackDC, WindowPoint, Copy.Vertexs[Tri].size());
		}

		break;
	}
	case 1:
#pragma region RotVector
	{
		SubTrans.Location += MainTrans.Location;
		Angle += _Delta;
		FVector DirVector = FVector::AngleToVectorRad(Angle);
		SubTrans.Location += DirVector * 100.0f;
		FVector LT = SubTrans.CenterLeftTop();
		FVector RB = SubTrans.CenterRightBottom();
		Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
	}
#pragma endregion

	break;
	case 2:
#pragma region Sin

	{
		SinG.clear();

		FVector StartPos = { 300, 300 };

		for (size_t i = 0; i < 360; i++)
		{
			float SinValue = cosf(static_cast<float>(i) * UEngineMath::D2R);
			FTransform ValueTrans = { { 30, 30 }, StartPos + FVector{ static_cast<float>(i * 2.0f),  SinValue * 100.0f } };
			SinG.push_back(ValueTrans);
		}


		// Ranged for

		// SinG.begin();
		// SinG.end();

		// �������� for
		// ����� �����Ҷ� ��������.

		for (FTransform& Trans : SinG)
		{
			FVector LT = Trans.CenterLeftTop();
			FVector RB = Trans.CenterRightBottom();

			Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
		}

	}
#pragma endregion
	break;
	case 3:
#pragma region Rotfigure
	{
		// ���� ȸ����Ű�°� �������.
		const int PointCount = 10;

		FVector Point[PointCount];
		FVector Pos = { 200, 200 };

		Angle += _Delta * 100;

		float StartAngle = 90.0f;
		float interAngle = static_cast<float>(360) / static_cast<float>(PointCount);
		float Len = 100.0f;


		for (size_t i = 0; i < PointCount; i++)
		{
			if ((i % 2) == 0)
			{
				Len = 100.0f;
			}
			else {
				Len = 40.0f;
			}

			Point[i] = FVector::AngleToVectorDeg(StartAngle + interAngle * i + Angle) * Len;


		}

		POINT WindowPoint[PointCount];

		for (size_t i = 0; i < PointCount; i++)
		{
			Point[i] += Pos;
			WindowPoint[i] = Point[i].ConvertWindowPOINT();
		}

		Polygon(BackDC, WindowPoint, PointCount);
	}
#pragma endregion
	break;
	case 4:
#pragma region RotVector
	{
		{
			static FVector SubRotPivot = FVector(200, 50);
			SubRotPivot.RotationZDeg(_Delta * 360.0f);

			{
				FVector LT = MainTrans.CenterLeftTop();
				FVector RB = MainTrans.CenterRightBottom();
				Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
			}

			{
				SubTrans.Location += SubRotPivot;
				FVector LT = SubTrans.CenterLeftTop();
				FVector RB = SubTrans.CenterRightBottom();
				Rectangle(BackDC, LT.iX(), LT.iY(), RB.iX(), RB.iY());
			}
		}
	}
#pragma endregion
	default:
		break;
	}
	// ���� �׷���



	// �׳� �״�� �簢���� �׷����ڽ��ϴ�.

}