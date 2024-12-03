#include "PreCompile.h"
#include "EngineCoreDebug.h"
#include <EnginePlatform/EngineWinDebug.h>
#include "EngineAPICore.h"

namespace UEngineDebug
{
	class DebugTextInfo
	{
	public:
		std::string Text;
		FVector Pos;
	};


	// ����
	std::vector<DebugTextInfo> DebugTexts;


// #ifdef _DEBUG
	FVector EngineTextPos = FVector::ZERO;
// #endif

#ifdef _DEBUG
	bool IsDebug = true;
#else
	bool IsDebug = false;
#endif

	void SetIsDebug(bool _IsDebug)
	{
		IsDebug = _IsDebug;
	}

	void SwitchIsDebug()
	{
		IsDebug = !IsDebug;
	}

	void CoreOutPutString(std::string_view _Text)
	{
		if (false == IsDebug)
		{
			return;
		}

// #ifdef _DEBUG
		// �ٷ� ������� �ʴ´�.
		DebugTexts.push_back({ _Text.data(), EngineTextPos});
		EngineTextPos.Y += 20;
// endif 
	}

	void CoreOutPutString(std::string_view _Text, FVector _Pos)
	{
		if (false == IsDebug)
		{
			return;
		}
// #ifdef _DEBUG
		DebugTexts.push_back({ _Text.data(), _Pos });
// #endif
	}

	class DebugRenderInfo
	{
	public:
		FTransform Trans;
		EDebugPosType Type;
	};


	std::vector<DebugRenderInfo> DebugPoses;

	void CoreDebugRender(FTransform _Trans, EDebugPosType _Type)
	{
		if (false == IsDebug)
		{
			return;
		}

		DebugPoses.push_back({ _Trans, _Type });
	}

	void PrintEngineDebugRender()
	{
		if (false == IsDebug)
		{
			return;
		}

		// void WinAPIOutPutString(UEngineWinImage * _Image, std::string_view _Text, FVector _Pos);
		UEngineWinImage* BackBuffer = UEngineAPICore::GetCore()->GetMainWindow().GetBackBuffer();

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			DebugTextInfo& Debug = DebugTexts[i];
			WinAPIOutPutString(BackBuffer, Debug.Text, Debug.Pos);
		}

		EngineTextPos = FVector::ZERO;
		DebugTexts.clear();

		for (size_t i = 0; i < DebugPoses.size(); i++)
		{

			EDebugPosType Type = DebugPoses[i].Type;

			FVector LT = DebugPoses[i].Trans.CenterLeftTop();
			FVector RB = DebugPoses[i].Trans.CenterRightBottom();
			switch (Type)
			{
			case UEngineDebug::EDebugPosType::Rect:
				Rectangle(BackBuffer->GetDC(), LT.iX(), LT.iY(), RB.iX(), RB.iY());
				break;
			case UEngineDebug::EDebugPosType::Circle:
				Ellipse(BackBuffer->GetDC(), LT.iX(), LT.iY(), RB.iX(), RB.iY());
				break;
			default:
				break;
			}
		}

		DebugPoses.clear();

	}


	void CoreDebugBox(FTransform _Trans)
	{

	}
}