#pragma once
#include <EngineBase/EngineMath.h>
#include "Renderer.h"

class FirstMesh
{
public:
	// �ﰢ��       ��
	std::vector<std::vector<FVector>> Vertexs;
	// std::vector<FVector> 1���� �迭�̾�� �Ѵ�.
};

// ������ ��ġ�� �̷��� ����... �ǹ� �����ϴ�
// 

// ���� :
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

	int Select;

	FirstMesh BoxMesh;


	// ũ����
	// ũ��
	FVector Scale = { 2, 2.5, 1.5 };
	// ����
	FVector Roation = { 0, 0, 0 };
	// �̵�
	FVector Position = { 300, 300 };
};

