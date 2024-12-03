#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include <EnginePlatform/EngineInput.h>


APlayMap::APlayMap()
{
	// �Ź� ������ ����� �ٲ��
	// �̰� ��ü�� ��� ������ �ƴմϴ�.
	//FVector WindowSize =  UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	//SetActorScale(WindowSize.Half());
	//SetActorLocation(WindowSize.Half());

	{
		{
			BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
			BackSpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
			BackSpriteRenderer->SetSprite("bg001.png");

			FVector MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
			BackSpriteRenderer->SetComponentLocation(MapScale.Half());
		}


		{
			ColSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
			ColSpriteRenderer->SetOrder(ERenderOrder::COLMAP);
			ColSpriteRenderer->SetSprite("bg001_Col.png");

			FVector MapScale = ColSpriteRenderer->SetSpriteScale(1.0f);
			ColSpriteRenderer->SetComponentLocation(MapScale.Half());
		}

	}

}

APlayMap::~APlayMap()
{
}



void APlayMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('Y'))
	{
		ColSpriteRenderer->SetActiveSwitch();
	}
}