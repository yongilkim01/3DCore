#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

// 설명 :
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	void BeginPlay();

protected:

private:
	// 여기에다가 받아야 합니다.
	
	class AScore* Score;
};

