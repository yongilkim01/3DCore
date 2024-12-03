#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineSerializer.h>

// �׷����� �� �� �������� �Ұų�.
// �ټ��� �̹����� ���� �԰����� 
// �ƿ� UTileMapRenderer��� �� �����.
// Y������ �ʿ���� ����� �ϼ���. 
// UTileMapRenderer ����� �� ������ �ִ�.
// �ǰ��� ���ۺ��� �ϴ°� �ƴϰ� �ǰ��� �ٲٴ°ſ���.
// ���� ���� ������ �ϴ� ������������ �ƾ�.
// �׷� �ð� ������ �Ͻø� �˴ϴ�.
// 
// [][][][][][][][][][][]
// [][][][][][][][][][][]
// [][][][][][][][][][][]
// [][][][][][][][][][][]
// [][][][][][][][][][][]
// [][][][][][][][][][][]
// [][][][][][][][][][][]
// [][][][][][][][][][][]

// ������ �׳� �����ص� �ȴ�.
class Tile : public ISerializObject
{
public:
	// �̷� Ŭ������ �����Ҷ�
	// ���� ���δ� �� �����ؾ� �Ѵ�.
	// ���߿��� ������°� ��������?
	// �����Լ� ���̺�
	USpriteRenderer* SpriteRenderer;

	bool IsMove = true;
	int TileType = -1;
	// Ÿ���ϳ��ϳ��� �������� ũ�⸦ ������ �ִٸ�
	// �̰ɷ� ���� �Է����ּž� �մϴ�.
	FVector Scale;
	FVector Pivot;
	int SpriteIndex;

	// �����͸� ����ȭ(����)
	void Serialize(UEngineSerializer& _Ser)
	{
		std::string SpriteName;
		if (nullptr != SpriteRenderer)
		{
			SpriteName = SpriteRenderer->GetCurSpriteName();
		}
		_Ser << SpriteName;
		_Ser << IsMove;
		_Ser << TileType;
		_Ser << Scale;
		_Ser << Pivot;
		_Ser << SpriteIndex;
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{
		//std::string SpriteName;
		// _Ser >> SpriteName;

		// SpriteRenderer->SetSprite(SpriteName);

		std::string SpriteName;
		_Ser >> SpriteName;
		_Ser >> IsMove;
		_Ser >> TileType;
		_Ser >> Scale;
		_Ser >> Pivot;
		_Ser >> SpriteIndex;

	}

};

// ������� ���� ���� ���ϴ� ���.
// �÷��̾ ��� Ÿ�� ���� �����ϴ��� �˰� �;��.

// ���� :
class ATileMap : public AActor, public ISerializObject
{
public:
	// constrcuter destructer
	ATileMap();
	~ATileMap();

	// delete Function
	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	//             100, 100                  64 64 
	// Ÿ�� �̹����� sprite 1������ 
	void Create(std::string_view _Sprite, FIntPoint _Count, FVector _TileSize);

	// ���⿡��    �� �ε������ٰ�    �̽�������Ʈ 

	void SetTileLocation(FVector _Location, int _SpriteIndex);

	void SetTileIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileIndex(FIntPoint _Index, FVector _Pivot, FVector _SpriteScale, int _SpriteIndex);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector _Location);

	FVector IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector _Location);

	bool IsIndexOver(FIntPoint _Index);

	// �����͸� ����ȭ(����)
	void Serialize(UEngineSerializer& _Ser);

	// �����͸� ����(�Ҷ�)
	void DeSerialize(UEngineSerializer& _Ser);

protected:

private:
	// �޸𸮸� �Ƴ����� Map
	// Ÿ���� �������� �ʴٰ� Ÿ�� ���� �Ǿ���.
	
	// �ȾƳ����� Vector Vector
	// ������, ũ��, ��������, �ٹ�

	// �����ϴ� ����鸶�� ��������

	// �ΰ����� ȥ���ϰڽ��ϴ�.
	// ���ʹ� Ȯ���Ű������ SPriteRenderer�� ������ ���� �̴ϴ�.
	// ���� ������ �����.
	
	// ����ȭ ��� ȭ�鿡 ���̴� ũ�⸸ŭ�� �������� ���.
	// ������ �ȸ���� ������� ���ڽ��ϴ�.

	// �����̴ϱ� �׳� ���ܹ����°�.
	FIntPoint TileCount;
	std::string SpriteName;
	FVector TileSize;
	std::vector<std::vector<Tile>> AllTiles;
};


