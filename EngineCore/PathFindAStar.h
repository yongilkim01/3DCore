#pragma once
#include <EngineBase/EngineMath.h>
#include <list>
#include <vector>

// ö���ϰ� Ÿ�ϸʿ� Ưȭ�� ��ã�⸦ ����ڽ��ϴ�.
// �밢���̵��� �ȴٰ� �Ǵ��ϰ� ����ڽ��ϴ�.
// 

class UPathFindNode
{
public:
	UPathFindNode* ParentNode;
	FIntPoint Point;
	float F = 0.0f; // G + H
	float G = 0.0f; // ���� �� ��ġ���� ������������ �Ÿ�
	float H = 0.0f; // ���� �� ��ġ���� ������������ �Ÿ�

	FVector GetPointToVector()
	{
		return { Point.X, Point.Y };
	}
};

class IPathFindData
{
public:
	// �Ϲ���
	// const FIntPoint& _Point ��ġ�� �̵��Ҽ� �ִ� �����̾�?
	virtual bool IsMove(const FIntPoint& _Point) = 0;
};

// ���� :
class UPathFindAStar
{
public:
	// constrcuter destructer
	UPathFindAStar();
	~UPathFindAStar();

	// delete Function
	UPathFindAStar(const UPathFindAStar& _Other) = delete;
	UPathFindAStar(UPathFindAStar&& _Other) noexcept = delete;
	UPathFindAStar& operator=(const UPathFindAStar& _Other) = delete;
	UPathFindAStar& operator=(UPathFindAStar&& _Other) noexcept = delete;

	std::list<FIntPoint> PathFind(const FIntPoint& _Start, const FIntPoint& _End);

	void SetData(IPathFindData* _PathFindData)
	{
		PathFindData = _PathFindData;
	}

protected:

private:
	IPathFindData* PathFindData = nullptr;

	std::vector<FIntPoint> WayDir;

	std::list<UPathFindNode*> OpenList;
	std::list<UPathFindNode*> CloseList;

	FIntPoint EndPoint;

	// Ǯ ����� ����ϰڽ��ϴ�.
	// �̸� ��â ���ܳ��� 
	// �Ѱ踦 �����ϰ� �� ����ų� ����ų� �������� �ʴ� ����Դϴ�.
	// �����̱� ������ �޸𸮰� �������� �ְ�.
	// ����� ���� ������ �̸� ��â ����� ���� ���̴�.
	std::vector<UPathFindNode> NodePool;
	int PoolCount = 0;

	void NodeClear()
	{
		OpenList.clear();
		CloseList.clear();
		PoolCount = 0;
	}

	bool FindOpenNode(FIntPoint _Point);
	bool FindCloseNode(FIntPoint _Point);

	UPathFindNode* GetNewNode(FIntPoint _Point, UPathFindNode* _ParentNode)
	{
		UPathFindNode* NewNode = &NodePool[PoolCount];
		NewNode->Point = _Point;
		NewNode->ParentNode = _ParentNode;

		FVector ThisPos = NewNode->GetPointToVector();

		if (nullptr != _ParentNode)
		{
			FVector ParentPos = _ParentNode->GetPointToVector();
			NewNode->G = _ParentNode->G + (ThisPos- ParentPos).Length();
		}

		FVector EndPos = { EndPoint.X, EndPoint.Y };
		NewNode->H = (EndPos - ThisPos).Length();
		NewNode->F = NewNode->H + NewNode->G;

		OpenList.push_back(NewNode);

		++PoolCount;
		return NewNode;
	}
};

