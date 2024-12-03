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

	// PushRenderer 에서 나는 랜더 구조에 편입된다.
	// 그런데 2번들어가는 버그가 보였다.
	// 그래서 이걸 해서 일단ㅌ 막았다. 
	if (PrevOrder == Order)
	{
		return;
	}

	// 동적으로 해야할때는 레벨이 세팅되어 있을 것이므로
	// 레벨이 세팅되어 있다면 즉각 바꿔준다.
	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != Level)
	{
		Level->ChangeRenderOrder(this, PrevOrder);
	}
}


void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// 스프라이트 랜더러가 

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	Level->ChangeRenderOrder(this, this->GetOrder());

}
