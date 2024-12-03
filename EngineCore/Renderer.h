#pragma once
#include "SceneComponent.h"

// 설명 :
class URenderer : public USceneComponent
{
public:
	friend class ULevel;

	// constrcuter destructer
	URenderer();
	~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	// int를 주는 함수들은 일반적으로 Enum으로 대체해서 넣고 싶을때가 많다.
// 그런데 그건 커텐츠 만드는 사람이 만드는 자신만의 enum일 것이기 때문에 
// 템플릿을 사용하여 어떤 enum이건 받게 만드는 방식을 선호한다.
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	int GetOrder()
	{
		return Order;
	}


protected:
	void BeginPlay() override;
	virtual void Render(float _DeltaTime);

private:
	int Order;
};

