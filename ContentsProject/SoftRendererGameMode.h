#pragma once
#include <EngineCore/GameMode.h>

// ���� :
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

