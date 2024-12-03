#include "PreCompile.h"
#include "ATileMap.h"

ATileMap::ATileMap()
{
}

ATileMap::~ATileMap()
{
}

// Ÿ���� 
void ATileMap::Create(std::string_view _Sprite, FIntPoint _Count, FVector _TileSize)
{
	SpriteName = _Sprite;
	TileSize = _TileSize;
	TileCount = _Count;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);;
	}

	// Ÿ�ϸ��� �ٽ� 0, 0�� �ΰ����� ���ؾ� �Ѵ�.
	// Ÿ�Ϸμ��� 0,0�� ����.
	// Ÿ���� ��ġ�� ����μ��� Ÿ�ϸ� * �ε����� �ȴ�.


}

FVector ATileMap::IndexToTileLocation(FIntPoint _Index)
{
	return FVector(_Index.X * TileSize.X, _Index.Y * TileSize.Y);
}

FIntPoint ATileMap::LocationToIndex(FVector _Location)
{
	FVector Location = _Location / TileSize;

	return FIntPoint(Location.iX(), Location.iY());
}

// ���콺 ��ġ�� �÷��̾� ��ġ�� ��������.
void ATileMap::SetTileLocation(FVector _Location, int _SpriteIndex)
{
	FVector TilePos = _Location - GetActorLocation();

	FIntPoint Point = LocationToIndex(TilePos);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTileIndex(Point, _SpriteIndex);
}

bool ATileMap::IsIndexOver(FIntPoint _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}

void ATileMap::SetTileIndex(FIntPoint _Index, int _SpriteIndex)
{
	SetTileIndex(_Index, {0,0}, TileSize, _SpriteIndex);
}

void ATileMap::SetTileIndex(FIntPoint _Index, FVector _Pivot, FVector _SpriteScale, int _SpriteIndex)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}

	// �̸� �� ������ �ʰ�
	// ���� 

	// SPriteRenderer�� ����.
	// �����ȸ�������ٴ� �̾߱�
	// �������� ��������Ʈ �������� �����.

	// �����ڿ��� �ۿ� ������ٸ�.
	// �������� �����ϴ°� ���Ѵٰ� ����.

	// �������ڸ��� Ÿ���� �� ��� ���°� �������� ����� �ִ�.
	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		// AllTiles[TileCount.Y][TileCount.X].SpriteRenderer;
		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}

	// ��������Ʈ�� ������ �����Ƿ�.
	// �� �̸����� �������ָ� �ȴ�.

	USpriteRenderer* FindSprite =  AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(SpriteName, _SpriteIndex);

	FVector TileLocation = IndexToTileLocation(_Index);
	FindSprite->SetComponentScale(_SpriteScale);
	// �Ʒ��ʿ� �������� �������� ���߿� �ȴ�.
	FindSprite->SetOrder(_Index.Y);

	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
	AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
	AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
	AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
}



Tile* ATileMap::GetTileRef(FVector _Location)
{
	FIntPoint Point = LocationToIndex(_Location);

	return GetTileRef(Point);
}

// Ÿ���� ���� ���� �̰ɷ� ���ͼ� ������Ű�� �ȴ�.
Tile* ATileMap::GetTileRef(FIntPoint _Index)
{
	if (true == IsIndexOver(_Index))
	{
		return nullptr;
	}

	return &AllTiles[_Index.Y][_Index.X];
}

void ATileMap::Serialize(UEngineSerializer& _Ser)
{
	// AllTiles

	// �����ϰ� �ʹ�.
	// : public ISerializObject ���
	// void Serialize(UEngineSerializer& _Ser)
	// void DeSerialize(UEngineSerializer & _Ser)
	// ����
	// �߿䵥���� �����ϴ� �ڵ� ���� ¥��

	_Ser << TileCount;
	_Ser << TileSize;
	_Ser << SpriteName;
	_Ser << AllTiles;
}

void ATileMap::DeSerialize(UEngineSerializer& _Ser)
{
	// ������ �ִ��� �� ���������� �ε��ؾ� �Ѵ�.
	// ����
	
	// ��ø��� ������� ������ �����̾�� �մϴ�.
	// ���� �ٲٸ� ����� �ȵǰų�
	_Ser >> TileCount;
	_Ser >> TileSize;
	_Ser >> SpriteName;

	std::vector<std::vector<Tile>> LoadTiles;
	_Ser >> LoadTiles;

	// �����͸� �о����������.
	Create(SpriteName, TileCount, TileSize);

	for (int y = 0; y < LoadTiles.size(); y++)
	{
		for (int x = 0; x < LoadTiles[y].size(); x++)
		{
			SetTileIndex({x, y}, LoadTiles[y][x].Pivot, LoadTiles[y][x].Scale, LoadTiles[y][x].SpriteIndex);
		}
	}

}

