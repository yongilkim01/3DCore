#pragma once
#include "SceneComponent.h"
#include <set>

// �Ž� �浹. 


// ���� :
class U2DCollision : public USceneComponent
{
public:
	friend class ULevel;

	// constrcuter destructer
	U2DCollision();
	~U2DCollision();

	// delete Function
	U2DCollision(const U2DCollision& _Other) = delete;
	U2DCollision(U2DCollision&& _Other) noexcept = delete;
	U2DCollision& operator=(const U2DCollision& _Other) = delete;
	U2DCollision& operator=(U2DCollision&& _Other) noexcept = delete;

	void BeginPlay() override;

	void ComponentTick(float _DeltaTime) override;

	template<typename EnumType>
	EnumType GetGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}

	int GetGroup()
	{
		return CollisionGroup;
	}

	// �浹ü���� �浹�׷��� ���������ִ°� �ǹ̰� ����.
	// �߰��� �浹 �׷��� �ٲ��� �Ǹ� �̾߱� ��Ź.
	template<typename EnumType>
	void SetCollisionGroup(EnumType _CollisionGroup)
	{
		SetCollisionGroup(static_cast<int>(_CollisionGroup));
	}

	void SetCollisionGroup(int _CollisionGroup)
	{
		CollisionGroup = _CollisionGroup;
	}

	template<typename EnumType>
	AActor* CollisionOnce(EnumType _OtherCollisionGroup, FVector _NextPos = FVector::ZERO)
	{
		// ��밡 100���̴�. 100�� 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(_OtherCollisionGroup), Result, _NextPos, 1);

		if (true == Result.empty())
		{
			return nullptr;
		}

		return Result[0];
	}

	template<typename EnumType>
	std::vector<AActor*> CollisionAll(EnumType _OtherCollisionGroup, FVector _NextDir)
	{
		// ��밡 100���̴�. 100�� 
		std::vector<AActor*> Result;
		Collision(static_cast<int>(_OtherCollisionGroup), Result, _NextDir, -1);

		return Result;
	}

	bool Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector _NextDir, unsigned int  _Limite);

	void SetCollisionType(ECollisionType _CollisionType)
	{
		CollisionType = _CollisionType;
	}

	ECollisionType GetCollisionType()
	{
		return CollisionType;
	}

	void SetCameraEffect(bool _IsCameraEffect)
	{
		IsCameraEffect = _IsCameraEffect;
	}

	//                                        �浹�� ���
	void SetCollisionEnter(std::function<void(AActor*)> _Function);
	void SetCollisionStay(std::function<void(AActor*)> _Function);
	void SetCollisionEnd(std::function<void(AActor*)> _Function);

protected:

private:
	void CollisionSetRelease();

	void CollisionEventCheck(class U2DCollision* _Other);

	// �浹ü�� ������ �ణ �ǹ̰� �ٸ���.
	// -1 �浹 �׷��� ���������� �ʾҴ�
	// -1 �� ����ϸ� �ȵȴ�.
	// ����� �ȴ�.
	ECollisionType CollisionType = ECollisionType::CirCle;
	int CollisionGroup = -1;

	// value���� ���Դϴ�.
	std::set<U2DCollision*> CollisionCheckSet;

	bool IsCameraEffect = true;

	std::function<void(AActor*)> Enter;
	std::function<void(AActor*)> Stay;
	std::function<void(AActor*)> End;
};

// �����е��� ������ �ϴ� ���
// enum class ContentsCollision
// {
//     PlayerBody,
//     PlayerAttack,
//	   MonsterBody,
//     MonsterAttack,
// }

// ��κ��� �浹 �Լ����� �̿� ���� �����ִ� �Լ��� �����ϰų� 
// ���������� GUI�� ������ ��� �մϴ�.
// void SetCollisionGroupCheck(ContentsCollision::PlayerBody, ContentsCollision::MonsterAttack);
