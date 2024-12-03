#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "Renderer.h"
#include "2DCollision.h"

#include "EngineCoreDebug.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	{
		// BeginPlayList �ѹ��� ü���� ���� ���ʹ� 
		// ���͵��� �� ��� �÷��� ����Ʈ�� �� �ִ�.

		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			delete CurActor;
		}
	}



	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		if (nullptr != CurActor)
		{
			delete *StartIter;
		}
	}
}

void ULevel::BeginPlayCheck()
{
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->BeginPlay();
			AllActors.push_back(CurActor);
		}

		BeginPlayList.clear();

		AActor::ComponentBeginPlay();
	}


}

// ���� CurLevel ������
void ULevel::LevelChangeStart()
{
	BeginPlayCheck();

	{
		{
			std::list<AActor*>::iterator StartIter = AllActors.begin();
			std::list<AActor*>::iterator EndIter = AllActors.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				AActor* CurActor = *StartIter;

				// �̰� �����ֵ� ȣ��˴ϴ�.
				CurActor->LevelChangeStart();
			}
		}

		{
			std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
			std::list<AActor*>::iterator EndIter = BeginPlayList.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				AActor* CurActor = *StartIter;

				// �̰� �����ֵ� ȣ��˴ϴ�.
				CurActor->LevelChangeStart();
			}
		}
	}

}

// �� ���� ���ο� ������ �ٲ�ž�.
void ULevel::LevelChangeEnd()
{
	{
		{
			std::list<AActor*>::iterator StartIter = AllActors.begin();
			std::list<AActor*>::iterator EndIter = AllActors.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				AActor* CurActor = *StartIter;

				CurActor->LevelChangeEnd();
			}
		}

		{
			std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
			std::list<AActor*>::iterator EndIter = BeginPlayList.end();

			for (; StartIter != EndIter; ++StartIter)
			{
				AActor* CurActor = *StartIter;

				// �̰� �����ֵ� ȣ��˴ϴ�.
				CurActor->LevelChangeEnd();
			}
		}
	}

}

void ULevel::Tick(float _DeltaTime)
{
	BeginPlayCheck();

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			if (false == CurActor->IsActive())
			{
				continue;
			}

			CurActor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	ScreenClear();

	// ���� ���� �������� ��ü�� URenderer �ٲ����.
	// ���͸� ������� �������� �����°� �� ������ �̴ϴ�.

	// ���Ͱ� SpriteRenderer�� �����
	// Level�� �� ��������Ʈ �������� �˾ƾ� �Ѵ�.

	if (true == IsCameraToMainPawn)
	{
		// CameraPivot = FVector(-1280, -720) * 0.5f;
		CameraPos = MainPawn->GetTransform().Location + CameraPivot;
	}


	std::map<int, std::list<class URenderer*>>::iterator StartOrderIter = Renderers.begin();
	std::map<int, std::list<class URenderer*>>::iterator EndOrderIter = Renderers.end();

	for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
	{
		std::list<class URenderer*>& RendererList = StartOrderIter->second;

		std::list<class URenderer*>::iterator RenderStartIter = RendererList.begin();
		std::list<class URenderer*>::iterator RenderEndIter = RendererList.end();

		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			if (false == (*RenderStartIter)->IsActive())
			{
				continue;
			}

			(*RenderStartIter)->Render(_DeltaTime);
		}

	}

	UEngineDebug::PrintEngineDebugRender();

	DoubleBuffering();
}

void ULevel::Collision(float _DeltaTime)
{
	for (size_t i = 0; i < CollisionLink.size(); i++)
	{
		CollisionLinkData Data = CollisionLink[i];

		int Left = Data.Left;
		int Right = Data.Right;
		
		// �̺�Ʈ�� �浹üũ�ϴ� �׷�
		std::list<class U2DCollision*>& LeftList = CheckCollisions[Left];

		// �� ����� �̺�Ʈ �׷��� �ƴϾ �ǹǷ� �׳� �ݸ��� �������� �����´�.
		std::list<class U2DCollision*>& RightList = Collisions[Right];

		std::list<class U2DCollision*>::iterator StartLeftIter = LeftList.begin();
		std::list<class U2DCollision*>::iterator EndLeftIter = LeftList.end();

		std::list<class U2DCollision*>::iterator EndRightIter = RightList.end();

		for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
		{
		 	U2DCollision* LeftCollision = *StartLeftIter;

			if (false == LeftCollision->IsActive())
			{
				continue;
			}

			// LeftCollision->CollisionSetRelease();

			std::list<class U2DCollision*>::iterator StartRightIter = RightList.begin();

			for (; StartRightIter != EndRightIter; ++StartRightIter)
			{
				U2DCollision* RightCollision = *StartRightIter;
				if (LeftCollision == RightCollision)
				{
					continue;
				}

				if (false == RightCollision->IsActive())
				{
					continue;
				}

				LeftCollision->CollisionEventCheck(RightCollision);
			}
		}
	}

	// �浹���� �����ֵ��� �ѹ� üũ���ִ� �뵵
	for (size_t i = 0; i < CollisionLink.size(); i++)
	{
		CollisionLinkData Data = CollisionLink[i];
		int Left = Data.Left;
		int Right = Data.Right;
		// �̺�Ʈ�� �浹üũ�ϴ� �׷�
		std::list<class U2DCollision*>& LeftList = CheckCollisions[Left];
		std::list<class U2DCollision*>::iterator StartLeftIter = LeftList.begin();
		std::list<class U2DCollision*>::iterator EndLeftIter = LeftList.end();
		for (; StartLeftIter != EndLeftIter; ++StartLeftIter)
		{
			U2DCollision* LeftCollision = *StartLeftIter;

			if (false == LeftCollision->IsActive())
			{
				continue;
			}

			LeftCollision->CollisionSetRelease();
		}
	}
}

// ���� �̺�Ʈ�ڵ�ϱ� �̻��� ������ ���ʿ䰡 ����.
// ������������ �����ϴ����� ����� �Ѵ�.


void ULevel::Release(float _DeltaTime)
{
	// ������ ������ ���ܺ��� ������ �մϴ�.
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;
		CurActor->ReleaseTimeCheck(_DeltaTime);
	}

	// �浹ü ����
	{
		std::map<int, std::list<class U2DCollision*>>::iterator StartOrderIter = Collisions.begin();
		std::map<int, std::list<class U2DCollision*>>::iterator EndOrderIter = Collisions.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class U2DCollision*>& CollisionList = StartOrderIter->second;

			std::list<class U2DCollision*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<class U2DCollision*>::iterator CollisionEndIter = CollisionList.end();

			// �𸮾��� �߰��� �����Ҽ� ����.
			for (; CollisionStartIter != CollisionEndIter; )
			{
				if (false == (*CollisionStartIter)->IsDestroy())
				{
					++CollisionStartIter;
					continue;
				}

				// �������� ���� �ʿ䰡 �����ϴ�.
				// (*RenderStartIter) ���� ���� ������ ��������.
				// ������Ʈ�� �޸𸮸� �����Ҽ� ������ ������ ���͸� ������ �ִ�.
				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}

	// �̺�Ʈ �浹ü ����
	{
		std::map<int, std::list<class U2DCollision*>>::iterator StartOrderIter = CheckCollisions.begin();
		std::map<int, std::list<class U2DCollision*>>::iterator EndOrderIter = CheckCollisions.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class U2DCollision*>& CollisionList = StartOrderIter->second;

			std::list<class U2DCollision*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<class U2DCollision*>::iterator CollisionEndIter = CollisionList.end();

			// �𸮾��� �߰��� �����Ҽ� ����.
			for (; CollisionStartIter != CollisionEndIter; )
			{
				if (false == (*CollisionStartIter)->IsDestroy())
				{
					++CollisionStartIter;
					continue;
				}

				// �������� ���� �ʿ䰡 �����ϴ�.
				// (*RenderStartIter) ���� ���� ������ ��������.
				// ������Ʈ�� �޸𸮸� �����Ҽ� ������ ������ ���͸� ������ �ִ�.
				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}

	// ������ ����
	{
		std::map<int, std::list<class URenderer*>>::iterator StartOrderIter = Renderers.begin();
		std::map<int, std::list<class URenderer*>>::iterator EndOrderIter = Renderers.end();

		for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
		{
			std::list<class URenderer*>& RendererList = StartOrderIter->second;

			std::list<class URenderer*>::iterator RenderStartIter = RendererList.begin();
			std::list<class URenderer*>::iterator RenderEndIter = RendererList.end();

			// �𸮾��� �߰��� �����Ҽ� ����.
			for (; RenderStartIter != RenderEndIter; )
			{
				if (false == (*RenderStartIter)->IsDestroy())
				{
					++RenderStartIter;
					continue;
				}

				// �������� ���� �ʿ䰡 �����ϴ�.
				// (*RenderStartIter) ���� ���� ������ ��������.
				// ������Ʈ�� �޸𸮸� �����Ҽ� ������ ������ ���͸� ������ �ִ�.
				RenderStartIter = RendererList.erase(RenderStartIter);
			}
		}
	}

	// ���� ����
	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; )
		{
			AActor* CurActor = *StartIter;


			if (false == CurActor->IsDestroy())
			{
				CurActor->ReleaseCheck(_DeltaTime);
				++StartIter;
				continue;
			}

			// ������ ������ ���������� ������ ������ ���ʹ� ��¥ ���� �ش�.
			delete CurActor;
			StartIter = AllActors.erase(StartIter);
		}
	}
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -1, -1, Size.iX() + 2, Size.iY() + 2);
}

void ULevel::DoubleBuffering()
{
	// ������ �������� ������.
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	FTransform Trans;
	Trans.Location = MainWindow.GetWindowSize().Half();
	Trans.Scale = MainWindow.GetWindowSize();

	// �̹��� ���� ����ۿ� �� �׷����� ���̴�.
	BackBufferImage->CopyToBit(WindowImage, Trans);

}

void ULevel::PushRenderer(class URenderer* _Renderer)
{
	int Order = _Renderer->GetOrder();

	Renderers[Order].push_back(_Renderer);
}

void ULevel::PushCollision(U2DCollision* _Collision)
{
	int Order = _Collision->GetGroup();
	Collisions[Order].push_back(_Collision);
}

std::vector<CollisionLinkData> ULevel::CollisionLink;

void ULevel::PushCheckCollision(class U2DCollision* _Collision)
{
	int Order = _Collision->GetGroup();
	CheckCollisions[Order].push_back(_Collision);
}

void ULevel::ChangeRenderOrder(class URenderer* _Renderer, int _PrevOrder)
{
	//std::vector<int> Value;
	// ���ʹ� �����갡 ����.
	//Value.remove

	// 0���� ����־��� ���̴�.
	// ���� ���� �Լ��� �ƴմϴ�.
	Renderers[_PrevOrder].remove(_Renderer);

	Renderers[_Renderer->GetOrder()].push_back(_Renderer);


}