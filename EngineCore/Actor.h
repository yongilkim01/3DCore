#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/TimeEvent.h>


#include "EngineSprite.h"

// ���� :
class AActor : public UObject
{
public:
	typedef AActor Super;

	friend class ULevel;

	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	// �� ��ü�� �������� ó�� Tick�� ������ ������ ����ȴ�.
	virtual void BeginPlay() {}

	// ��ŸŸ���̶� �����ΰ�?
	virtual void Tick(float _DeltaTime);

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	class ULevel* GetWorld()
	{
		return World;
	}

	void SetActorLocation(FVector _Location)
	{
		Transform.Location = _Location;
	}

	void AddActorLocation(FVector _Direction)
	{
		Transform.Location += _Direction;
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	FVector GetActorLocation()
	{
		return Transform.Location;
	}

	// ������Ʈ�� �����ڴ� ���� ������ ���Ͱ� �ؾ��Ѵ�.
	// �ٸ� Ŭ������ ����� �����ϸ� �ȵȴ�.
	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject()
	{
		ComponentType* NewComponent = new ComponentType();

		UActorComponent* ComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);
		// ���� �� ���� �����̾�.
		ComponentPtr->ParentActor = this;

		// �����ɶ� ���� �ʽ��ϴ�.
		// NewComponent->BeginPlay();
		// ����⸸ �ϰ� ���� ���� ���°� �Ȱ�.
		Components.push_back(NewComponent);

		// BeginPlay�� ����ȵ� ������Ʈ���� �� �ڷᱸ���� ��´�.
		ComponentList.push_back(NewComponent);
		return NewComponent;
	}


protected:
	UTimeEvent TimeEventer;

private:
	static void ComponentBeginPlay();

	static bool IsNewActorCreate;
	static std::list<class UActorComponent*> ComponentList;

	void ReleaseCheck(float _DeltaTime) override;
	void ReleaseTimeCheck(float _DeltaTime) override;

	class ULevel* World = nullptr;
	FTransform Transform;


	std::list<class UActorComponent*> Components;
};

