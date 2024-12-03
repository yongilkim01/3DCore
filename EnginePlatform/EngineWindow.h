#pragma once
// Os Header
#include <Windows.h>

// std Header
#include <map>
#include <string>
#include <functional>

// user header
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineMath.h>
#include "EngineWinImage.h"


// ���� �� ��

// ���� :
class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");

	inline FVector GetWindowSize() const
	{
		return WindowSize;
	}

	inline UEngineWinImage* GetWindowImage() const
	{
		return WindowImage;
	}

	inline UEngineWinImage* GetBackBuffer() const
	{
		return BackBufferImage;
	}

	// �Ƿ��� �������� ���� �����Ϸ��� ���Ѵ�.
	// �ڱ⸸ �ƴ°� ����ó�� ���ϰ�.

	inline void SetWindowTitle(std::string_view Text)
	{
		// WindowAPI�� ��Ģ �����ϰ� �ִ���.
		// ���δ� ������
		
		// �̷��� winapi�� std�� Ȥ�� �ʼ� ���̺귯�� �Լ����� 
		// �����Լ��� �ƴ϶� 
		// ����Ƽ�� �Լ���� �մϴ�.
		SetWindowTextA(WindowHandle, Text.data());
	}


	void SetWindowPosAndScale(FVector _Pos, FVector _Scale);

	FVector GetMousePos();


protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasss;

	// WinApi�� �⺻�������� �ٽ���
	// HDC�̴�. HDC�� windowâ�� �׸��� ���� ���� �ڵ��Դϴ�.
	// HDC�� �̹����̸鼭 �� �̹����� ���� ����
	// �� �������� 1���� Main HDC�� �����Ҽ� �ִ�.
	// ���� �̳༮�� BackBuffer��� �θ��ϴ�.

	// ������������ �������� �ȵǰų� ������ �ȵǴ� �ڵ尡 �ȴ�.
	// hwnd => ������ â 1��
	// �����쿡�� ������ �׸����� �Լ��� ��κ��� ù��° ���ڴ� hdc�ϰ��Դϴ�.

	// HDC�� �״�� ����Ҹ��� ����?

	// ����ۿ� �׸��� �� 1�� windowdc�� ����ٿ��ֱ� ������ �׸����̴�.
	// HDC BackBufferDC = nullptr;

	// ���⿡ �׷��߸� �����µ�.
	// HDC WindowMainDC = nullptr;

	FVector WindowSize;

	// HDC
	// �������� �ص� ������ ���� �� ��������.
	UEngineWinImage* BackBufferImage = nullptr;

	// HDC
	// ������ �̹����� ���εǾ���.
	UEngineWinImage* WindowImage = nullptr;

	HWND WindowHandle = nullptr;
};


