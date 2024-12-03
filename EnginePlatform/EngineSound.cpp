#include "PreCompile.h"
#include "EngineSound.h"
#include <EngineBase/EngineString.h>
#include <EngineBase/EngineDebug.h>

std::map<std::string, UEngineSound*> UEngineSound::Sounds;
std::list<USoundPlayer> UEngineSound::Players;

// ���带 �����ϱ����� �ڵ�
FMOD::System* SoundSystem = nullptr;

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

class SoundInit
{
public:
	SoundInit()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MSGASSERT("FMOD �ý��� �̴ֿ� �����߽��ϴ�.");
			return;
		}

		// ���� ä�μ���
		// int maxchannels, ���ÿ� ����� ���� ����� �Ǵ°�?
		// FMOD_INITFLAGS flags, ���������� �ֳ��ε�
		// void* extradriverdata �������׿� ���� �����ͳ־��ٰ� �ֳ�.
		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MSGASSERT("FMOD �ý��� �̴ֿ� �����߽��ϴ�.");
			return;
		}
	}
};

SoundInit SoundInitObject;

void UEngineSound::AllSoundStop()
{
	std::list<USoundPlayer>::iterator StartIter = Players.begin();
	std::list<USoundPlayer>::iterator EndIter = Players.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		USoundPlayer& CurSoundPlayer = *StartIter;
		CurSoundPlayer.Stop();
	}
}

void UEngineSound::AllSoundOn()
{
	std::list<USoundPlayer>::iterator StartIter = Players.begin();
	std::list<USoundPlayer>::iterator EndIter = Players.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		USoundPlayer& CurSoundPlayer = *StartIter;
		CurSoundPlayer.On();
	}
}

void UEngineSound::AllSoundOff()
{
	std::list<USoundPlayer>::iterator StartIter = Players.begin();
	std::list<USoundPlayer>::iterator EndIter = Players.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		USoundPlayer& CurSoundPlayer = *StartIter;
		CurSoundPlayer.Off();
	}
}


void UEngineSound::Update()
{
	if (nullptr == SoundSystem)
	{
		return;
	}

	std::list<USoundPlayer>::iterator StartIter = Players.begin();
	std::list<USoundPlayer>::iterator EndIter = Players.end();

	for (; StartIter != EndIter; )
	{
		USoundPlayer& CurSoundPlayer = *StartIter;

		if (true == CurSoundPlayer.IsPlaying())
		{
			++StartIter;
			continue;
		}

		StartIter = Players.erase(StartIter);
		
	}

	if (FMOD_RESULT::FMOD_OK != SoundSystem->update())
	{
		MSGASSERT("FMOD �ý��� ������Ʈ�� �̻��� �����Ǿ����ϴ�.");
	}
}

// ������ ������ ���� ȣ��
void UEngineSound::Release()
{
	std::map<std::string, UEngineSound*>::iterator StartIter = Sounds.begin();
	std::map<std::string, UEngineSound*>::iterator EndIter = Sounds.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Sounds.clear();

	if (nullptr != SoundSystem)
	{
		SoundSystem->release();
		SoundSystem = nullptr;
	}
}

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
	
	
	if (nullptr != SoundHandle)
	{
		SoundHandle->release();
		SoundHandle = nullptr;
	}
}

void UEngineSound::Load(std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);
	std::string FileName = EnginePath.GetFileName();

	UEngineSound::Load(FileName.data(), _Path);
}

void UEngineSound::Load(std::string_view _Name, std::string_view _Path)
{
	// �̳༮�� UTF-8�� ��θ� �ٲ���� �Ҽ� �ִ�.
	std::string UpperString = UEngineString::ToUpper(_Name);

	UEngineSound* NewSound = new UEngineSound();

	if (false != UEngineSound::Sounds.contains(UpperString))
	{
		delete NewSound;
		MSGASSERT("�̹� �ε��� ���带 �� �ε��Ϸ��� �߽��ϴ�." + UpperString);
		return;
	}

	if (false == NewSound->ResLoad(_Path))
	{
		delete NewSound;
		MSGASSERT("���� �ε忡 �����߽��ϴ�" + UpperString);
		return;
	}

	UEngineSound::Sounds.insert({ UpperString, NewSound });
	// Load(FileName, Path);
}

UEngineSound* UEngineSound::Find(std::string_view _Name)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (false == Sounds.contains(UpperString))
	{
		return nullptr;
	}

	return Sounds[UpperString];
}

USoundPlayer UEngineSound::Play(std::string_view _Name)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	UEngineSound* FindSound = Find(_Name);

	if (nullptr == FindSound)
	{
		MSGASSERT("�ε����� ���� ���带 ����Ϸ��� �߽��ϴ�" + UpperString);
	}


	// �׳� �ܼ��� ����ϴ°� �ƴ϶�� ä���� ���;� �ӷ��̳� ��ġ ���� �ͽ� ����� �����Ҽ� �ִ�.
	FMOD::Channel* Ch = nullptr;

	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Ch);

	// �� ����� ���õ� ��� ���׿� ���� 
	// WINproc => 
	// Ch->setCallback();

	// 1�� ���
	Ch->setLoopCount(0);

	// ���� 1��
	Ch->setVolume(1.0f);

	USoundPlayer NewPlayer;
	NewPlayer.Control = Ch;
	NewPlayer.SoundHandle = FindSound->SoundHandle;

	Players.push_back(NewPlayer);

	return NewPlayer;
}


bool UEngineSound::ResLoad(std::string_view _Path)
{
	// �����ڵ�� �־
	// ��Ƽ����Ʈ�� �־ ����� �ȵɶ��� �ִ�.
	// �׷��� UTF�ø���� ���ڵ��ؼ� �־�����Ҷ��� �ִ�.
	// FMOD�� ����ϴ� �κ�
	// �غô��� �ȴ� UTF�ø���� �����൵ �ƴ�.
	SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (nullptr == SoundHandle)
	{
		MSGASSERT("���� �ε��� �����߽��ϴ�" + std::string(_Path));
		return false;
	}

	return true;
}