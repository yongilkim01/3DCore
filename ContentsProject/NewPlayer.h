#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineSound.h>

enum class NewPlayerState
{
	Idle,
	Move,
	Dash,
	Attack,
	Jump,
};

// 설명 :
class ANewPlayer : public AActor
{
public:
	// constrcuter destructer
	ANewPlayer();
	~ANewPlayer();

	// delete Function
	ANewPlayer(const ANewPlayer& _Other) = delete;
	ANewPlayer(ANewPlayer&& _Other) noexcept = delete;
	ANewPlayer& operator=(const ANewPlayer& _Other) = delete;
	ANewPlayer& operator=(ANewPlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelChangeStart() override;

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Attack(float _DeltaTime);
	void Jump(float _DeltaTime);

	void SetColImage(std::string_view _ColImageName);

	void PlayerCameraCheck();
	void PlayerGroundCheck(FVector MovePos);

	void Gravity(float _DeltaTime);

	// 중력은 만드는 방법이 너무 많다.

	// 나랑 충돌한 액터를 준다.
	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

	void DirCheck();

protected:

private:
	// 물리에서 가장 많이 사용되는것이 addForce라는 개념이다.

	U2DCollision* CollisionComponent;
	float Speed = 500.0f;
	class UEngineWinImage* ColImage = nullptr;
	class USpriteRenderer* SpriteRenderer = nullptr;

	std::string DirString = "_Right";

	int IsGround = false;
	FVector GravityForce = FVector::ZERO;

	FVector JumpPower = FVector(0.0f, -500.0f);

	UFSMStateManager FSM;

	USoundPlayer BGMPlayer;

	UEngineWindow Window;
};

