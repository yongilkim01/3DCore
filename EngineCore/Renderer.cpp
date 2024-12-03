#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
}

void URenderer::Render(float _DeltaTime)
{

}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;

	Order = _Order;

	// PushRenderer ���� ���� ���� ������ ���Եȴ�.
	// �׷��� 2������ ���װ� ������.
	// �׷��� �̰� �ؼ� �ϴܤ� ���Ҵ�. 
	if (PrevOrder == Order)
	{
		return;
	}

	// �������� �ؾ��Ҷ��� ������ ���õǾ� ���� ���̹Ƿ�
	// ������ ���õǾ� �ִٸ� �ﰢ �ٲ��ش�.
	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != Level)
	{
		Level->ChangeRenderOrder(this, PrevOrder);
	}
}


void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// ��������Ʈ �������� 

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	Level->ChangeRenderOrder(this, this->GetOrder());

}
