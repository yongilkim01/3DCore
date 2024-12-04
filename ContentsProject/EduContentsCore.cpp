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

// 엔진이 실행되고 단 1번 실행된다.
void EduContentsCore::BeginPlay()
{

	std::vector<std::string> Texts = {
		"문병무",
		"박석원",
		"이재영",
		"김용일",
		"이수환",
		"신동민",
		"류성민",
		"김지호",
		"서은정",
		"김창수",
		"최예나",
		"이민하",
		"김성훈",
		"강민정",
		"전혜주",
		"장시혁",
		"이창준",
		"김경민",
		"이현정"
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

	// 이미지로드
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

	// 사운드 로드
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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


	// 일반 텍스처가 다 로딩되면
	// 자르는 작업을 아래서 해주는게 좋다.

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
		// 타일셋 로드
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Image");
		Dir.Append("TileMap//TileSet");

		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

	}


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("EduWindow");

	// 이거 꼭 호출해줘야 합니다.
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, {1280, 720});

	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, ANewPlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapGameMode, AActor>("Tile");

	UEngineAPICore::GetCore()->CreateLevel<ASoftRendererGameMode, SoftRenderPlayer>("Soft");

	UEngineAPICore::GetCore()->OpenLevel("Soft");

}

void EduContentsCore::Tick()
{
	// 지금 전혀 용도를 찾지 못해서 사용하지 않는 함수입니다.
}