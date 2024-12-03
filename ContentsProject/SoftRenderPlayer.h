#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class SoftRenderPlayer : public AActor
{
public:
	// constrcuter destructer
	SoftRenderPlayer();
	~SoftRenderPlayer();

	// delete Function
	SoftRenderPlayer(const SoftRenderPlayer& _Other) = delete;
	SoftRenderPlayer(SoftRenderPlayer&& _Other) noexcept = delete;
	SoftRenderPlayer& operator=(const SoftRenderPlayer& _Other) = delete;
	SoftRenderPlayer& operator=(SoftRenderPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

