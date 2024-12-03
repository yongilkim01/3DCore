#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "ImageManager.h"

#include "EngineAPICore.h"
#include <EngineBase/EngineString.h>

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

// SpriteRenderer : public URenderer
// MeshRenderer : public URenderer
// StaticMeshRenderer : public URenderer
void USpriteRenderer::Render(float _DeltaTime)
{
	// 업데이트

	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트가 세팅되지 않은 액터를 랜더링을 할수 없습니다.");
		return;
	}
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	FTransform Trans = GetActorTransform();

	ULevel* Level = GetActor()->GetWorld();

	if (true == IsCameraEffect)
	{
		Trans.Location = Trans.Location - (Level->CameraPos * CameraEffectScale);
	}

	// 100, 100 랜더링 한다고 치겠습니다.
	
	// 0.5f, 0.5f PivotRealScale = 0, 0이 나와야 한다.;


	// Trans.Scale;
	// 100, 100 
	
	// 0.5f, 0.5f 일때 
	// 0, 0
	// 0.0f, 0.5f 일때 
	// -50, 0.0f

	
	// 이미지 크기에 기반한 어떤 값이 될수밖에 없다.
	FVector PivotRealScale;

	//                 소수점 버림
	PivotRealScale.X = std::floorf((0.5f - Pivot.X) * Trans.Scale.X);
	PivotRealScale.Y = std::floorf((0.5f - Pivot.Y) * Trans.Scale.Y);

	Trans.Location += PivotRealScale;


	if (Alpha == 255)
	{
		CurData.Image->CopyToTrans(BackBufferImage, Trans, CurData.Transform);
	}
	else
	{
		CurData.Image->CopyToAlpha(BackBufferImage, Trans, CurData.Transform, Alpha);
	}
}

void USpriteRenderer::BeginPlay()
{
	// 부모 클래스의 함수를 호출하는걸 깜빡하면 안된다.
	// 습관되면 가장 언리얼 학습에서 걸림돌이 되는 습관이 된다.
	URenderer::BeginPlay();
}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	// 애니메이션 진행시키는 코드를 ComponentTick으로 옮겼다. 
	if (nullptr != CurAnimation)
	{
		CurAnimation->IsEnd = false;
		std::vector<int>& Indexs = CurAnimation->FrameIndex;
		std::vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;


		CurAnimation->CurTime += _DeltaTime * CurAnimationSpeed;

		float CurFrameTime = Times[CurAnimation->CurIndex];

		//                           0.1 0.1 0.1
		if (CurAnimation->CurTime > CurFrameTime)
		{

			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurIndex))
			{
				CurAnimation->Events[CurIndex]();
			}

			// 애니메이션 앤드
			if (CurAnimation->CurIndex >= Indexs.size())
			{
				CurAnimation->IsEnd = true;
			}
			else {
				CurAnimation->IsEnd = false;
			}


			if (CurAnimation->CurIndex >= Indexs.size())
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurIndex = 0;

					if (CurAnimation->Events.contains(CurIndex))
					{
						CurAnimation->Events[CurIndex]();
					}
				}
				else
				{
					CurAnimation->IsEnd = true;
					--CurAnimation->CurIndex;
				}
			}

		}


		//         2 3 4           0
		CurIndex = Indexs[CurAnimation->CurIndex];
		// ++CurAnimation->CurIndex;
	}

}

void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex /*= 0*/)
{
	// 싱글톤에 대해서 설명할때
	// 값을 편하게 공유하기 위해서 사용하는 거라고 하면 틀렸다.
	// 객체를 단 1개 만드는 패턴이라는 것을 잊지 마시고

	// 액터가 만들어졌을때는 로드가 끝난 상황이어야 한다.
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}

FVector USpriteRenderer::SetSpriteScale(float _Ratio /*= 1.0f*/, int _CurIndex /*= 0*/)
{
	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트를 세팅하지 않고 스프라이트 크기로 랜더러 크기를 조정할수 없습니다.");
		return FVector::ZERO;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_CurIndex);

	FVector Scale = CurData.Transform.Scale * _Ratio;

	SetComponentScale(CurData.Transform.Scale * _Ratio);

	return Scale;
}


void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time /*= 0.1f*/, bool _Loop /*= true*/)
{
	int Inter = 0;

	std::vector<int> Indexs;
	std::vector<float> Times;

	if (_Start < _End)
	{
		Inter = (_End - _Start) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexs.push_back(_Start);
			Times.push_back(Time);
			++_Start;
		}

	}
	else
	{
		Inter = (_Start - _End) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexs.push_back(_End);
			Times.push_back(Time);
			++_End;
		}
	}


	CreateAnimation(_AnimationName, _SpriteName, Indexs, Times, _Loop);
}


void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop /*= true*/)
{
	std::vector<float> Times;

	for (size_t i = 0; i < _Indexs.size(); i++)
	{
		Times.push_back(_Frame);
	}

	CreateAnimation(_AnimationName, _SpriteName, _Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
	{
		MSGASSERT(UpperName + "을 만들다 에러가 났습니다 프레임과 타임의 카운트가 서로 다릅니다");
		return;
	}

	if (FrameAnimations.contains(UpperName))
	{
		return;
	}

	UEngineSprite* FindSprite = UImageManager::GetInst().FindSprite(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 애니메이션 생서에 사용하려고 했습니다" + std::string(UpperName));
		return;
	}

	FrameAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite;
	NewAnimation.FrameIndex = _Indexs;
	NewAnimation.FrameTime = _Frame;
	NewAnimation.Loop = _Loop;
	NewAnimation.Reset();

	FrameAnimations.insert({ UpperName ,NewAnimation });

}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 애니메이션으로 변경하려고 했습니다. = " + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && false == _Force)
	{
		return;
	}

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();
	CurIndex = CurAnimation->FrameIndex[CurAnimation->CurIndex];

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
	{
		CurAnimation->Events[CurAnimation->CurIndex]();
	}

	Sprite = CurAnimation->Sprite;
}


void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 애니메이션으로 변경하려고 했습니다. = " + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	bool Check = false;

	for (size_t i = 0; i < ChangeAnimation->FrameIndex.size(); i++)
	{
		if (_Frame == ChangeAnimation->FrameIndex[i])
		{
			Check = true;
			break;
		}
	}

	if (false == Check)
	{
		MSGASSERT("존재하지 않는 프레임에 이벤트를 생성하려고 했습니다" + std::string(_AnimationName));
		return;
	}

	ChangeAnimation->Events[_Frame] += _Function;

}

void USpriteRenderer::SetCameraEffectScale(float _Effect)
{
	CameraEffectScale = _Effect;
}

// 여러분들이 애니메이션을 하거나
void USpriteRenderer::SetPivotType(PivotType _Type)
{
	if (PivotType::Center == _Type)
	{
		Pivot = FVector::ZERO;
		return;
	}

	if (nullptr == Sprite)
	{
		MSGASSERT("이미지를 기반으로한 피봇설정은 스프라이트가 세팅되지 않은 상태에서는 호출할수 없습니다");
		return;
	}

	// UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	switch (_Type)
	{
	case PivotType::Center:
		Pivot.X = 0.5f;
		Pivot.Y = 0.5f;
		break;
	case PivotType::Bot:
		Pivot.X = 0.5f;
		Pivot.Y = 1.0f;
		break;
	case PivotType::Top:
		Pivot.X = 0.5f;
		Pivot.Y = 0.0f;
		break;
	case PivotType::LeftTop:
		Pivot.X = 0.0f;
		Pivot.Y = 0.0f;
		break;
	default:
		break;
	}
}


void USpriteRenderer::SetPivotValue(FVector _Value)
{
	Pivot = _Value;
}