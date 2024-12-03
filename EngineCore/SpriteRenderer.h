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

// ���� :
class USpriteRenderer : public URenderer
{
	// �ְ� �� ����Ѵ�.
	// Ŭ������ ��ȭ�з��ؼ�
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

	// _AnimationName �̸��� �ִϸ��̼��� ������.
	// _SpriteName �� �̸��� ��������Ʈ��
	// _Indexs �������� �̳༮���� ����ؼ�   0     1      2     3     4     5 
	// _Frame �� �ð��� �����                 0.1    0.1    0.1   0.1  0.1   0.1
	// _Loop = true�� �ݺ� false�� ������ �����ӿ��� ����
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);

	// ���� Idle�ε� Idle �ٲٶ�� �ߴ�. 
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

	// �ִϸ��̼��� ����ǰ� �ִٸ�.
	// �� �ִϸ��̼��� ���� ������ üũ�ϰ� ������.
	bool IsCurAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}

	// 0 �������� 255�� ������
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
		// �������� ���� �ٸ� ������ ������ ����ɼ� �ִ�.
		// ���̷�Ʈ�� ���� ������ 0~1�� �������� �ϴ� �����̴�.
		// �׷��� ���̺귯���� ������ �������� ���̹Ƿ� �̰� ��������
		// �ٸ� �����ͷ� ��ȯ�ϴ� ���� �����Ҷ� 0~1������ �����ϱ� ������ 0~1������ ����Ѵ�.
		Alpha = static_cast<unsigned char>(_Value * 255.0f);
	}

protected:

private:
	int CurIndex = 0;
	bool IsCameraEffect = true;
	float CameraEffectScale = 1.0f;
	float CurAnimationSpeed = 1.0f;


	// ���̷�Ʈ�� ��� ������ 0~1.0f�� ǥ���Ѵ�.
	unsigned char Alpha = 255;

	FVector Pivot = FVector(0.5f, 0.5f);
	// FVector PivotRealScale = FVector::ZERO;

	class UEngineSprite* Sprite = nullptr;

	std::map<std::string, FrameAnimation> FrameAnimations;
	FrameAnimation* CurAnimation = nullptr;
};
