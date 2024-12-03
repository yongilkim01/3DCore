#include "PreCompile.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "PlayMap.h"
#include "Monster.h"
#include "NewPlayer.h"
#include "Score.h"
#include "Fade.h"
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

// 언리얼에서는 MainPawn 주인공 무조건 지정하게 해요.
void APlayGameMode::BeginPlay()
{
	{
		ANewPlayer* Actor = GetWorld()->GetPawn<ANewPlayer>();
		Actor->SetColImage("bg001_Col.png");
	}

	{
		APlayMap* Actor = GetWorld()->SpawnActor<APlayMap>();
	}

	{
		AFade* Actor = GetWorld()->SpawnActor<AFade>();
		Actor->FadeOut();
	}

	{
		AMonster* Actor = GetWorld()->SpawnActor<AMonster>();
		Actor->SetActorLocation({335, 300});
		Actor->SetActive(false);
	}

	{
		AMonster* Actor = GetWorld()->SpawnActor<AMonster>();
		Actor->SetActorLocation({ 335, 500 });
		Actor->SetActive(false);
	}


	//{
	//	Score = GetWorld()->SpawnActor<AScore>();
	//	Score->SetActorLocation({300, 300});
	//	Score->SetTextSpriteName("Text.bmp");
	//	Score->SetOrder(ERenderOrder::UI);
	//	Score->SetTextScale({50, 100});
	//	Score->SetValue(45362784);
	//}
}
