#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ASoftRendererGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ASoftRendererGameMode();
	~ASoftRendererGameMode();

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:

};

