#include "PreCompile.h"
#include "EduContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>
#include <EnginePlatform/EngineSound.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "TileMapGameMode.h"
#include "NewPlayer.h"
#include "SoftRendererGameMode.h"
#include "SoftRenderPlayer.h"


EduContentsCore::EduContentsCore()
{
}

EduContentsCore::~EduContentsCore()
{
}

// ������ ����ǰ� �� 1�� ����ȴ�.
void EduContentsCore::BeginPlay()
{

	std::vector<std::string> Texts = {
		"������",
		"�ڼ���",
		"���翵",
		"�����",
		"�̼�ȯ",
		"�ŵ���",
		"������",
		"����ȣ",
		"������",
		"��â��",
		"�ֿ���",
		"�̹���",
		"�輺��",
		"������",
		"������",
		"�����",
		"��â��",
		"����",
		"������"
	};

	UEngineRandom Random;

	for (int i = 0; i < 1000; i++)
	{
		int Left = Random.RandomInt(0, static_cast<int>(Texts.size()) - 1);
		int Right = Random.RandomInt(0, static_cast<int>(Texts.size()) - 1);

		std::string SwapValue = Texts[Left];
		Texts[Left] = Texts[Right];
		Texts[Right] = SwapValue;
	}

	int a = 0;

	// �̹����ε�
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UImageManager::GetInst().Load(FilePath);
		}
	}

	// ���� �ε�
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Sound");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}
	}


	// �Ϲ� �ؽ�ó�� �� �ε��Ǹ�
	// �ڸ��� �۾��� �Ʒ��� ���ִ°� ����.

	UImageManager::GetInst().CuttingSprite("Player_Right.png", {128, 128});
	UImageManager::GetInst().CuttingSprite("Text.bmp", { 16, 32 });

	//UEngineSprite* Sprite = UImageManager::GetInst().FindSprite("Player_Right.png");
	//UEngineWinImage* Image = UImageManager::GetInst().FindImage("Player_Right.png");
	//Sprite->ClearSpriteData();
	//Sprite->PushData(Image, { {0,0}, {350, 350} });

	{

		UEngineDirectory BombDir;
		BombDir.MoveParentToDirectory("Resources//Image");
		BombDir.Append("bomb");

		UImageManager::GetInst().LoadFolder(BombDir.GetPathToString());

	}

	{
		// Ÿ�ϼ� �ε�
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	



	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	// �̰� �� ȣ������� �մϴ�.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, {1280, 720});

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, ANewPlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	UEngineAPICore::GetCore()->CreateLevel<ASoftRendererGameMode, SoftRenderPlayer>("Soft");

	UEngineAPICore::GetCore()->OpenLevel("Soft");

}

void EduContentsCore::Tick()
{
	// ���� ���� �뵵�� ã�� ���ؼ� ������� �ʴ� �Լ��Դϴ�.
}