#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>

// ���� :
class AScore : public AActor
{
public:
	// constrcuter destructer
	AScore();
	~AScore();

	// delete Function
	AScore(const AScore& _Other) = delete;
	AScore(AScore&& _Other) noexcept = delete;
	AScore& operator=(const AScore& _Other) = delete;
	AScore& operator=(AScore&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetValue(int _Score);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string TextSpriteName;
	FVector TextScale;
	std::vector<class USpriteRenderer*> Renders;
};

