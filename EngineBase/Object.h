#pragma once
#include <string>

// ���� :
class UObject
{
public:
	// constrcuter destructer
	UObject();

	// Ȥ���� �ڽĵ��� �Ҹ��ڰ� ȣ�� �ȵǴ� ��츦 ����������
	// �����Լ� ���̺��� ���� ���̹Ƿ� �ظ��ϸ� �ڽ����� �Ҹ��ڰ� ȣ��ȵǴ� ���� ���� ���̴�.
	virtual ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	std::string GetName() const
	{
		return Name;
	}

	std::string_view GetNameView() const
	{
		return Name.c_str();
	}

	// �̸� �����Ҷ� ���� �ϰ� ������ �������̵���.
	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

	// bool IsActive()
	virtual bool IsActive()
	{
		return IsActiveValue && false == IsDestroyValue;
	}

	virtual bool IsDestroy()
	{
		return IsDestroyValue;
	}

	// �ٷ� �װ���?
	// _Time �ð��Ŀ� �׾��.
	void Destroy(float _Time = 0.0f)
	{
		DeathTime = _Time;

		if (0.0f < _Time)
		{
			IsDeathTimeCheck = true;
			return;
		}

		IsDestroyValue = true;
	}

	virtual void ReleaseTimeCheck(float _DeltaTime)
	{
		if (false == IsDeathTimeCheck)
		{
			return;
		}

		CurDeathTime += _DeltaTime;

		if (DeathTime <= CurDeathTime)
		{
			IsDestroyValue = true;
		}
	}

	virtual void ReleaseCheck(float _DeltaTime)
	{

	}

	// ��� ��� ����.
	// ���� �ܺο��� �ٸ� ��ü�� Ǯ����� �Ѵ�.
	void SetActive(bool _IsActive)
	{
		IsActiveValue = _IsActive;
	}

	void SetActiveSwitch()
	{
		IsActiveValue = !IsActiveValue;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

	void DebugOn()
	{
		IsDebugValue = true;
	}

	void DebugOff()
	{
		IsDebugValue = false;
	}

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

protected:

private:
	bool IsDestroyValue = false;
	bool IsActiveValue = true;

	bool IsDeathTimeCheck = false;
	float DeathTime = 0.0f;
	float CurDeathTime = 0.0f;

	std::string Name;

	bool IsDebugValue = false;

};

