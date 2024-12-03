#pragma once
#include "SceneComponent.h"
#include "Renderer.h"
#include "EngineSprite.h"
#include <EngineBase/EngineDelegate.h>
#include <map>
#include <EngineBase/EngineMath.h>

enum class PivotType
{
	Center,
	Left,
	Bot,
	Top,
	LeftTop,
};

// 설명 :
class USpriteRenderer : public URenderer
{
	// 애가 다 담당한다.
	// 클래스를 심화분류해서
public:
	class FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		std::map<int, EngineDelegate> Events;

		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0.0f;
		bool Loop = true;
		bool IsEnd = false;

		void Reset()
		{
			CurIndex = 0;
			CurTime = 0;
			ResultIndex = 0;
			IsEnd = false;
		}
	};


public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void Render(float _DeltaTime);
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;


	int GetCurIndex()
	{
		return CurIndex;
	}

	int GetFrameIndex()
	{
		return CurAnimation->CurIndex;
	}

	FVector SetSpriteScale(float _Ratio = 1.0f, int _CurIndex = 0);


	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time = 0.1f, bool _Loop = true);

	// _AnimationName 이름의 애니메이션을 만들어라.
	// _SpriteName 이 이름의 스프라이트로
	// _Indexs 프레임은 이녀석들을 사용해서   0     1      2     3     4     5 
	// _Frame 이 시간을 드려서                 0.1    0.1    0.1   0.1  0.1   0.1
	// _Loop = true면 반복 false면 마지막 프레임에서 정지
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);

	// 내가 Idle인데 Idle 바꾸라고 했다. 
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);

	void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);

	std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	void SetCameraEffect(bool _Value)
	{
		IsCameraEffect = _Value;
	}

	void SetPivotValue(FVector _Value);

	void SetPivotType(PivotType _Type);

	void SetCameraEffectScale(float _Effect);
	void SetSprite(std::string_view _Name, int _CurIndex = 0);

	// 애니메이션이 실행되고 있다면.
	// 그 애니메이션이 끝난 순간을 체크하고 싶은것.
	bool IsCurAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	// 0 완전투명 255면 불투명
	void SetAlphaChar(unsigned char _Value)
	{
		Alpha = _Value;
	}
	void SetAnimationSpeed(float _Speed)
	{
		CurAnimationSpeed = _Speed;
	}

	void ResetAnimationSpeed()
	{
		CurAnimationSpeed = 1.0f;
	}

	void SetAlphafloat(float _Value)
	{
		_Value = UEngineMath::Clamp(_Value, 0.0f, 1.0f);
		// 언제든지 쉽게 다른 차원의 값으로 변경될수 있다.
		// 다이렉트가 색깔 단위를 0~1을 기준으로 하는 이유이다.
		// 그래픽 라이브러리는 색깔을 데이터일 뿐이므로 이걸 언제든지
		// 다른 데이터로 변환하는 일을 수행할때 0~1단위가 유리하기 때문에 0~1단위를 사용한다.
		Alpha = static_cast<unsigned char>(_Value * 255.0f);
	}

protected:

private:
	int CurIndex = 0;
	bool IsCameraEffect = true;
	float CameraEffectScale = 1.0f;
	float CurAnimationSpeed = 1.0f;


	// 다이렉트는 모든 색상을 0~1.0f로 표현한다.
	unsigned char Alpha = 255;

	FVector Pivot = FVector(0.5f, 0.5f);
	// FVector PivotRealScale = FVector::ZERO;

	class UEngineSprite* Sprite = nullptr;

	std::map<std::string, FrameAnimation> FrameAnimations;
	FrameAnimation* CurAnimation = nullptr;
};

