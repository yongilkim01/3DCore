#pragma once

namespace UEngineDebug
{
	enum class EDebugPosType
	{
		Rect,
		Circle,
	};

	// MainWindow�� �ִ�.

	void SetIsDebug(bool _IsDebug);

	void SwitchIsDebug();

	void CoreOutPutString(std::string_view _Text);

	void CoreOutPutString(std::string_view _Text, FVector _Pos);

	void CoreDebugRender(FTransform _Trans, EDebugPosType _Type);

	// �и��ؾ� �ϰڳ׿�

	void PrintEngineDebugRender();
}