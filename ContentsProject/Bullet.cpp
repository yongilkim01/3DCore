#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}

void ABullet::Tick(float _DeltaTime)
{
	AddActorLocation(FVector::RIGHT * _DeltaTime * 300.0f);
}