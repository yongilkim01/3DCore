#pragma once
#include <EngineBase/EngineMath.h>
#include "Renderer.h"


// 액터의 위치와 이런건 전혀... 의미 없습니다
// 

// 설명 :
class USoftRenderer : public URenderer
{
public:
	// constrcuter destructer
	USoftRenderer();
	~USoftRenderer();

	// delete Function
	USoftRenderer(const USoftRenderer& _Other) = delete;
	USoftRenderer(USoftRenderer&& _Other) noexcept = delete;
	USoftRenderer& operator=(const USoftRenderer& _Other) = delete;
	USoftRenderer& operator=(USoftRenderer&& _Other) noexcept = delete;

protected:
	void BeginPlay();
	virtual void Render(float _Delta);

private:
	float Angle = 0.0f;
	float Speed = 0.0f;

	std::list<FTransform> SinG;

	std::list<FTransform> CosG;

};

