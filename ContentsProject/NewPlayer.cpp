#include "PreCompile.h"
#include "NewPlayer.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/2DCollision.h>
#include "PlayGameMode.h"
#include "Fade.h"
#include "ContentsEnum.h"

ANewPlayer::ANewPlayer()
{
	SetActorLocation({ 100, 100 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Player_Right.png");
		SpriteRenderer->SetComponentScale({ 300, 300 });
		SpriteRenderer->CreateAnimation("Run_Right", "Player_Right.png", 2, 4, 0.1f);
		SpriteRenderer->CreateAnimation("Idle_Right", "Player_Right.png", 0, 0, 0.1f);
		// SpriteRenderer->SetAlphafloat(0.5f);
		// SpriteRenderer->CreateAnimation("Test", "Player_Right.png", 0, 20, 0.1f, false);
	}

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 200, 0 });
		CollisionComponent->SetComponentScale({ 50, 50 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PlayerBody);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);


		// ������ ������ �̰ɷ� �ϴ°� ������.
		// �̰� ȣ���ؾ� �̺�Ʈ�� ���۵˴ϴ�.
		// ��� ȣ���ϰ� ������ ����
		// �ѹ��� ȣ���ϸ� �ȴ�.
		GetWorld()->CollisionGroupLink(ECollisionGroup::PlayerBody, ECollisionGroup::MonsterBody);

		// ���� ȣ��ȵ˴ϴ�.
		// � �׷�� � �׷��� �浹�ض�. �Լ��� �ٰŰ� �װ� ȣ������ ������ ���� 
		// �� �� �Լ��� ȣ���ϸ� ��� �ɴ� ������ ������ ����.
		
		CollisionComponent->SetCollisionEnter(std::bind(&ANewPlayer::CollisionEnter, this, std::placeholders::_1));
		CollisionComponent->SetCollisionStay(std::bind(&ANewPlayer::CollisionStay, this, std::placeholders::_1));
		CollisionComponent->SetCollisionEnd(std::bind(&ANewPlayer::CollisionEnd, this, std::placeholders::_1));

		// ó�� ������� �� 1���� ȣ��ȴ�.
		// ��� �浹üũ�� �Ұ̴ϴ�.
		// ��Ż => �̷� �͵��� �� �����غ��ž� �մϴ�.
		// CollisionComponent->SetCollisionEnter(��ų�);

		// ��� ��� ������ ȣ��Ǵ� �Լ�
		// CollisionComponent->SetCollisionStay(��ų�);

		// ��� ��� ������ ȣ��Ǵ� �Լ�
		// CollisionComponent->SetCollisionEnd(��ų�);
	}


	Window.Create("MyTest");

	DebugOn();
}

void ANewPlayer::CollisionEnter(AActor* _ColActor)
{
	int a = 0;
}

void ANewPlayer::CollisionStay(AActor* _ColActor)
{
	int a = 0;
}

void ANewPlayer::CollisionEnd(AActor* _ColActor)
{
	int  a = 0;
}

ANewPlayer::~ANewPlayer()
{
}

void ANewPlayer::BeginPlay()
{
	Super::BeginPlay();

	BGMPlayer = UEngineSound::Play("anipang_ingame_wav.wav");
	BGMPlayer = UEngineSound::Play("Grand_Prix.mp3");
	


	// ���� ī�޶� �Ǻ��� ��������� �Ѵ�.
	FVector Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

	GetWorld()->SetCameraToMainPawn(false);

	FSM.CreateState(NewPlayerState::Idle, std::bind(&ANewPlayer::Idle, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Idle" + DirString);
		}
	);

	FSM.CreateState(NewPlayerState::Move, std::bind(&ANewPlayer::Move, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run" + DirString);
		}
	);

	FSM.CreateState(NewPlayerState::Attack, std::bind(&ANewPlayer::Attack, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run" + DirString);
		}
	);

	FSM.CreateState(NewPlayerState::Jump, std::bind(&ANewPlayer::Jump, this, std::placeholders::_1),
		[this]()
		{
			SpriteRenderer->ChangeAnimation("Run" + DirString);
		}
	);


	FSM.ChangeState(NewPlayerState::Idle);

}

void ANewPlayer::PlayerCameraCheck()
{
	FVector WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPos(GetActorLocation() - WindowSize.Half());

	DebugOn();
}

void ANewPlayer::PlayerGroundCheck(FVector _MovePos)
{
	IsGround = false;

	if (nullptr != ColImage)
	{
		// �ȼ��浹���� ���� �߿��Ѱ� ���ʿ� ������ �ʴ°��̴�.
		FVector NextPos = GetActorLocation() + _MovePos;

		NextPos.X = floorf(NextPos.X);
		NextPos.Y = floorf(NextPos.Y);

		UColor Color = ColImage->GetColor(NextPos, UColor::WHITE);
		if (Color == UColor::WHITE)
		{
			IsGround = false;
		}
		else if (Color == UColor::BLACK)
		{
			IsGround = true;
			// ���� ������ ���������� �÷��ִ� ��ɵ� �Բ� ����ų� �ؾ��Ѵ�.
		}
	}
}

void ANewPlayer::Gravity(float _DeltaTime)
{
	if (false == IsGround)
	{
		// ������Ű�� 
		// ���⼭ ���
		AddActorLocation(GravityForce * _DeltaTime);
		GravityForce += FVector::DOWN * _DeltaTime * 500.0f;
	}
	else {
		GravityForce = FVector::ZERO;
	}

}

void ANewPlayer::DirCheck()
{

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		DirString = "_Right";
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		DirString = "_Left";
	}

}

void ANewPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::GetInst().IsDown(VK_F2))
	{
		UEngineDebug::SwitchIsDebug();
	}

	if (true == UEngineInput::GetInst().IsPress(VK_F7))
	{
		UEngineSound::AllSoundOn();
	}

	if (true == UEngineInput::GetInst().IsPress(VK_F3))
	{
		static float Volume = 1.0f;

		Volume -= _DeltaTime;

		// BGMPlayer.Stop();

		UEngineSound::AllSoundOff();

		// BGMPlayer.SetVolume(Volume);

		// static���. 
		//UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, ANewPlayer>("Play");
		//UEngineAPICore::GetCore()->OpenLevel("Play");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_F4))
	{
		Window.Open();

		// static���. 
		//UEngineAPICore::GetCore()->ResetLevel<APlayGameMode, ANewPlayer>("Play");
		//UEngineAPICore::GetCore()->OpenLevel("Play");
	}


	


	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	FTransform PlayerTransform = GetTransform();
	PlayerTransform.Location += FVector(20, 0) - GetWorld()->GetCameraPos();
	PlayerTransform.Scale = { 6,6 };
	UEngineDebug::CoreDebugRender(PlayerTransform, UEngineDebug::EDebugPosType::Circle);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
	}

	if (true == UEngineInput::GetInst().IsDown('U'))
	{
		AFade::MainFade->FadeIn();
	}

	if (true == UEngineInput::GetInst().IsDown('Y'))
	{
		AFade::MainFade->FadeOut();
	}


	DirCheck();
	FSM.Update(_DeltaTime);
}

void ANewPlayer::Idle(float _DeltaTime)
{
	// ������ ���
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDoubleClick('A', 0.2f))
	{

	}

	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		FSM.ChangeState(NewPlayerState::Jump);
		return;
		// AddActorLocation(FVector::UP * _DeltaTime * Speed);
	}


	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		FSM.ChangeState(NewPlayerState::Attack);
		return;
	}

	if (true == UEngineInput::GetInst().IsPress('A') ||
		true == UEngineInput::GetInst().IsPress('D'))
	{
		// ���¸� �ٲٴ� ������ �� �ٷ� �����ϴ°� ����.
		// ���������� ���¸� �ٲ�ٸ� �����ض�.
		FSM.ChangeState(NewPlayerState::Move);
		return;
	}
}

void ANewPlayer::Jump(float _DeltaTime)
{
	// ���� �߿��� �߷��� ����Ǿ� �Ѵ�.
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	//if (���� ���� ��Ҵٸ�)
	//{
	//	FSM.ChangeState*()
	//}
	AddActorLocation(JumpPower * _DeltaTime);


}

void ANewPlayer::Attack(float _DeltaTime)
{
	// AMonster* Monster;

	//FTransform MonsterTransform;// = Monster->GetRender()->GetActorTransfrom();
	//FTransform PlayerTransform; //= SpriteRenderer->GetActorTransform();

	//if (FTransform::RectToRect(MonsterTransform, PlayerTransform))
	//{
	//}

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::MonsterBody);
	if (nullptr != Result)
	{
		Result->Destroy();
	}
}


void ANewPlayer::Move(float _DeltaTime)
{
	// �Ϲ����� �̵��� �ϴ� ���� ���� ���� ����ֱ� ������
	PlayerCameraCheck();
	PlayerGroundCheck(GravityForce * _DeltaTime);
	Gravity(_DeltaTime);

	FVector Vector = FVector::ZERO;

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		Vector += FVector::RIGHT;
	}

	
	// DashTime += _DeltaTime;


	if (true == UEngineInput::GetInst().IsPress('A'))
	{


		Vector += FVector::LEFT;
		// AŰ�� ������.
	}


	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		FSM.ChangeState(NewPlayerState::Jump);
		return;
		// AddActorLocation(FVector::UP * _DeltaTime * Speed);
	}

	if (true == UEngineInput::GetInst().IsPress('F'))
	{
		FSM.ChangeState(NewPlayerState::Attack);
		return;
	}

	Vector.Normalize();

	// �� üũ�ϴ� �Լ�.
	// PlayerGroundCheck(Vector * _DeltaTime * Speed);

	// ���� �̹� �̵��� �ߴ�.
	AddActorLocation(Vector * _DeltaTime * Speed);


	// ���� ��� �ִ� ���� ��������� ��� �˰ų�????
	// 1. ������ ���� ����. ����� ���������� ĥ�Ѵ�.
	// 2. 


	while (true)
	{
		UColor Color = ColImage->GetColor(GetActorLocation(), UColor::WHITE);
		if (Color == UColor::BLACK)
		{
			// ���� ������ �ö󰥶����� while ��� �÷��ش�.
			AddActorLocation(FVector::UP);
		}
		else {
			break;
		}
	}


	if (false == UEngineInput::GetInst().IsPress('A') &&
		false == UEngineInput::GetInst().IsPress('D') &&
		false == UEngineInput::GetInst().IsPress('W') &&
		false == UEngineInput::GetInst().IsPress('S'))
	{
		FSM.ChangeState(NewPlayerState::Idle);
		return;
	}
	UEngineDebug::CoreOutPutString("IsGround : " + std::to_string(IsGround));
}

void ANewPlayer::SetColImage(std::string_view _ColImageName)
{
	ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}

void ANewPlayer::LevelChangeStart()
{
	int a = 0;
}