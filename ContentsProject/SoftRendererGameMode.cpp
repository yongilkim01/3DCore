#include "PreCompile.h"
#include "SoftRendererGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "TitleLogo.h"

ASoftRendererGameMode::ASoftRendererGameMode()
{
}

ASoftRendererGameMode::~ASoftRendererGameMode()
{
}


// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void ASoftRendererGameMode::BeginPlay()
{
	Super::BeginPlay();
}


void ASoftRendererGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}