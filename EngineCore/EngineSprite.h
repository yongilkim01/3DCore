#pragma once
#include <EnginePlatform/EngineWinImage.h>
#include <vector>
#include <EngineBase/EngineDebug.h>

// ���� :
class UEngineSprite : public UObject
{
public:
	class USpriteData
	{
	public:
		// �� �̹�����
		UEngineWinImage* Image;
		// ���⼭���� xx ũ�����
		FTransform Transform;
		// �߶� ���ڴ�.
	};

	// constrcuter destructer
	UEngineSprite();
	~UEngineSprite();

	// delete Function
	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	void PushData(UEngineWinImage* Image, const FTransform& _Trans);

	USpriteData GetSpriteData(int _Index = 0)
	{
		if (_Index >= Data.size())
		{
			MSGASSERT("��������Ʈ�� �ε����� �����Ͽ� ����Ϸ��� �߽��ϴ�." + GetName());
		}

		return Data[_Index];
	}

	void ClearSpriteData()
	{
		Data.clear();
	}

protected:
	std::vector<USpriteData> Data;
};


