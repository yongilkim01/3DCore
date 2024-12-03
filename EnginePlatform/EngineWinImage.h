#pragma once
#include <Windows.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/Object.h>

// �̳༮�� �̹��� ������ ����� �̴ϴ�.
// �̳༮�� �翬�� �ε嵵 �˴ϴ�.

// ���� : API �̹� ������ ������ �ٽ� Ŭ����
//       ���� Ŭ���� winapi���� �츮���� �������� ������ �Լ����� �����ϴµ�
//       �ٽ� �ڷ����� HDC�� ���� ���α׷��� ���忡�� �̰� �����ϰų� ��ġ��
//       private���� ���� �ʹ�.
//       UEngineWinImage => ���ο� Has a�� HDC
//       ImageDC �� ��������� ���� HDC�� �ǹ̰� ����.
class UEngineWinImage : public UObject
{
public:
	// constrcuter destructer
	UEngineWinImage();
	~UEngineWinImage();

	// delete Function
	UEngineWinImage(const UEngineWinImage& _Other) = delete;
	UEngineWinImage(UEngineWinImage&& _Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& _Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& _Other) noexcept = delete;

	// void Load(std::string_view _Path);
	HDC GetDC()
	{
		return ImageDC;
	}
	
	// �̹� ������� DC�� ���ؼ� �̹����� ����� Ÿ��
	void Create(HDC _DC)
	{
		ImageDC = _DC;
	}

	void Create(UEngineWinImage* _TargetImage, FVector _Scale);

	// bit���� ũ�� �����Ƶ˴ϴ�. 
	void CopyToBit(UEngineWinImage* _TargetImage, 
		const FTransform& _Trans);

	// Ʈ���� ���� ���� ����Ѵ�.
	// �������ܵ� �ǰ� �̹��� �Ϻκи� ó���ϴ� �͵� �ȴ�.
	// �̹����� ��� �κ��� �׸��� ��Ȯ�ϰ� ǥ���ϱ� ���ؼ�
	// Ʈ���� ���� �ϳ��� �ʿ��մϴ�.
	void CopyToTrans(UEngineWinImage* _TargetImage, 
		const FTransform& _RenderTrans, 
		const FTransform& _LTImageTrans,
		UColor _Color = UColor(255, 0, 255, 0));

	void CopyToAlpha(UEngineWinImage* _TargetImage,
		const FTransform& _RenderTrans,
		const FTransform& _LTImageTrans,
		unsigned char _Alpha);


	void Load(UEngineWinImage* _TargetImage, std::string_view _Path);

	// �̹��� ũ�⸦ ����
	FVector GetImageScale() const
	{
		return { Info.bmWidth, Info.bmHeight };
	}

	UColor GetColor(FVector _Point, UColor _DefaultColor = UColor::WHITE)
	{
		return GetColor(_Point.ConvertToPoint(), _DefaultColor);
	}

	UColor GetColor(FIntPoint _Point, UColor _DefaultColor);

protected:

private:
	// BMP �̹��� ���� �� ��ü����
	// FVector Size;
	HDC ImageDC = nullptr;
	HBITMAP hBitMap = nullptr;

	// �̹��� ���� ������
	BITMAP Info;
};

