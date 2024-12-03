#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>


#include <EnginePlatform/EngineInput.h>
#include "Bullet.h"
#include <EngineCore/2DCollision.h>
#include "ContentsEnum.h"

void AMonster::TestTimeEvent()
{
	UEngineDebug::OutPutString("Test");

	// TimeEventer.PushEvent(1.0f, std::bind(&AMonster::TestTimeEvent, this));


	//AMonster* NewActor = GetWorld()->SpawnActor<AMonster>();
	//NewActor->SetActorLocation(GetActorLocation() + FVector{ 100, 0 });
}

AMonster::AMonster()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Player_Right.png");
		SpriteRenderer->SetComponentScale({ 300, 300 });
		SpriteRenderer->CreateAnimation("Run_Right", "Player_Right.png", 2, 4, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Right.png", 0, 0, 0.1f);
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}

	{
		U2DCollision* CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 50, 50 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::MonsterBody);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);

		DebugOn();
	}

	// TimeEventer.PushEvent(1.0f, std::bind(&AMonster::TestTimeEvent, this), true);
}


AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}