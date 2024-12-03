#pragma once
#include "ActorComponent.h"

// ���� :
class USceneComponent : public UActorComponent
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	FTransform GetTransform()
	{
		return Transform;
	}

	// ���͸� ���������� Ʈ������ 
	FTransform GetActorTransform();

	FVector GetComponentScale()
	{
		return Transform.Scale;
	}

	FVector GetComponentLocation()
	{
		return Transform.Location;
	}


	// ���� ��ġ ������� ������ �Ұ��̴�.
	void SetComponentLocation(FVector _Location)
	{
		Transform.Location = _Location;
	}

	void SetComponentScale(FVector _Scale)
	{
		Transform.Scale = _Scale;
	}

protected:

private:
	FTransform Transform;
};

