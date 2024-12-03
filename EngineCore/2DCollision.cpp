#include "PreCompile.h"
#include "2DCollision.h"
#include <EngineCore/EngineCoreDebug.h>


U2DCollision::U2DCollision()
{
}

U2DCollision::~U2DCollision()
{
}

void U2DCollision::BeginPlay()
{
	Super::BeginPlay();

	// ��������Ʈ �������� 

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	if (0 > CollisionGroup)
	{
		MSGASSERT("�浹 �׷��� ������ �ɼ� �����ϴ�.");
		return;
	}

	Level->PushCollision(this);

	if (nullptr != Enter || nullptr != Stay || nullptr != End)
	{
		Level->PushCheckCollision(this);
	}
}

void U2DCollision::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	if (true == IsDebug() || true == GetActor()->IsDebug())
	{

		FTransform ActorTransform = GetActorTransform();
		FVector CameraPos = GetActor()->GetWorld()->GetCameraPos();

		
		if (true == IsCameraEffect)
		{
			ActorTransform.Location -= CameraPos;
		}

		switch (CollisionType)
		{
		case ECollisionType::Rect:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Rect);
			break;
		case ECollisionType::CirCle:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Circle);
			break;
		default:
			break;
		}
	}
}



bool U2DCollision::Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector _NextPos, unsigned int  _Limite)
{
	// ���� xxxx �׷��̶� �浹�ϴ°���.
	// ��� �浹ü�� �Ѱ��� ��Ƴ��°� Level
	U2DCollision* ThisCollision = this;

	if (false == ThisCollision->IsActive())
	{
		return false;
	}

	// ȣ���� �浹ü


	std::list<class U2DCollision*>& OtherCollisions = GetActor()->GetWorld()->Collisions[_OtherCollisionGroup];


	std::list<class U2DCollision*>::iterator StartIter = OtherCollisions.begin();
	std::list<class U2DCollision*>::iterator EndIter = OtherCollisions.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		U2DCollision* DestCollision = *StartIter;

		if (ThisCollision == DestCollision)
		{
			continue;
		}

		if (false == DestCollision->IsActive())
		{
			continue;
		}
		// 
		FTransform ThisTrans = ThisCollision->GetActorTransform();
		FTransform DestTrans = DestCollision->GetActorTransform();

		ThisTrans.Location += _NextPos;

		ECollisionType ThisType = ThisCollision->CollisionType;
		ECollisionType DestType = DestCollision->CollisionType;

		bool Result = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

		// �浹 true
		if (true == Result)
		{
			_Result.push_back(DestCollision->GetActor());
			--_Limite;

			if (0 == _Limite)
			{
				return 0 != _Result.size();
			}
		}
	}

	return 0 != _Result.size();
}



// �̺�Ʈ ���
void U2DCollision::SetCollisionEnter(std::function<void(AActor*)> _Function)
{
	Enter = _Function;

	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != GetActor()->GetWorld())
	{
		Level->PushCheckCollision(this);
	}
}

void U2DCollision::SetCollisionStay(std::function<void(AActor*)> _Function)
{
	Stay = _Function;

	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != GetActor()->GetWorld())
	{
		Level->PushCheckCollision(this);
	}

}

void U2DCollision::SetCollisionEnd(std::function<void(AActor*)> _Function)
{
	End = _Function;

	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != GetActor()->GetWorld())
	{
		Level->PushCheckCollision(this);
	}

}

void U2DCollision::CollisionSetRelease()
{
	std::set<U2DCollision*>::iterator StartIter = CollisionCheckSet.begin();
	std::set<U2DCollision*>::iterator EndIter = CollisionCheckSet.end();

	for (; StartIter != EndIter; )
	{
		U2DCollision* ColCollison = *StartIter;

		if (nullptr == ColCollison)
		{
			++StartIter;
			continue;
		}

		if (false == ColCollison->IsActive() || true == ColCollison->IsDestroy())
		{
			if (nullptr != End)
			{
				End(ColCollison->GetActor());
			}
			StartIter = CollisionCheckSet.erase(StartIter);
			continue;
		}

		++StartIter;
	}
}

// ���� �̺�Ʈ�ڵ�ϱ� �̻��� ������ ���ʿ䰡 ����.
// ������������ �����ϴ����� ����� �Ѵ�.
void U2DCollision::CollisionEventCheck(class U2DCollision* _Other)
{
	// ���� �浹
	// �ߵ���
	// �浹 ��
	U2DCollision* ThisCollision = this;
	U2DCollision* DestCollision = _Other;
	// 
	FTransform ThisTrans = ThisCollision->GetActorTransform();
	FTransform DestTrans = DestCollision->GetActorTransform();

	ECollisionType ThisType = ThisCollision->GetCollisionType();
	ECollisionType DestType = DestCollision->GetCollisionType();

	bool Result = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

	// �浹 true
	if (true == Result)
	{
		if (false == CollisionCheckSet.contains(DestCollision))
		{
			if (nullptr != Enter)
			{
				Enter(DestCollision->GetActor());
			}

			CollisionCheckSet.insert(DestCollision);
		}
		else 
		{
			if (nullptr != Stay)
			{
				Stay(DestCollision->GetActor());
			}
		}
	}
	else 
	{
		// �浹 ���ߴ�.
		// �浹�� ���ߴµ� ������ �浹�� ����� ������ �־.
		if (true == CollisionCheckSet.contains(DestCollision))
		{
			if (nullptr != End)
			{
				End(DestCollision->GetActor());
			}

			CollisionCheckSet.erase(DestCollision);
		}
	}
}