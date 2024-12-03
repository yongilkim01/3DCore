#pragma once
#include "SceneComponent.h"

// ���� :
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

	// int�� �ִ� �Լ����� �Ϲ������� Enum���� ��ü�ؼ� �ְ� �������� ����.
// �׷��� �װ� Ŀ���� ����� ����� ����� �ڽŸ��� enum�� ���̱� ������ 
// ���ø��� ����Ͽ� � enum�̰� �ް� ����� ����� ��ȣ�Ѵ�.
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

