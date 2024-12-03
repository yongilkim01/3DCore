#include "PreCompile.h"
#include "SoftRenderPlayer.h"
#include <EngineCore/SoftRenderer.h>

SoftRenderPlayer::SoftRenderPlayer()
{
	USoftRenderer* Renderer = CreateDefaultSubObject<USoftRenderer>();
}

SoftRenderPlayer::~SoftRenderPlayer()
{
}

void SoftRenderPlayer::BeginPlay()
{
	Super::BeginPlay();
}
void SoftRenderPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
