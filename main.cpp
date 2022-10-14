#include "DxLib.h"

#include "game.h"
#include "LoadScene.h"
#include "enemy.h"
#include "ShotBase.h"
#include "SceneManager.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// 最初のシーンの初期化
	SceneManager scene;
	scene.init();

	ShotBase shot;

	LoadScene player;
	player.init();

	int SizeX = 0;
	int SizeY = 0;

	int handle = LoadGraph("data/enemy.png");
	EnemyStraight enemyTbl[5];
	float posX = 80.0f;
	GetGraphSize(handle, &SizeX, &SizeY);

	for (auto& enemy : enemyTbl)
	{
		enemy.init();
		enemy.setHandle(handle, SizeX, SizeY);		// 表示する画像の指定
		enemy.setPos(posX, 160.0f);		// 初期位置
		posX += 80.0f;
	}


	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		scene.update();
		player.update();
		
		scene.draw();
		player.draw();

		// キャラクターの移動
		for (auto& enemy : enemyTbl)
		{
			enemy.update();
		}

		// 当たり判定

		// バウンド
		for (int i = 0; i < 5; i++)
		{
			for (int j = i + 1; j < 5; j++)
			{
				// enemyTbl[i]とenemyTbl[j]の当たり判定をとる
				Vec2 dist = enemyTbl[i].getCenter() - enemyTbl[j].getCenter();
				float radiusAdd = enemyTbl[i].getRadius() + enemyTbl[j].getRadius();
				if (dist.length() < radiusAdd)
				{
					// あたった場合の処理
					enemyTbl[i].bound(enemyTbl[j].getCenter());
					enemyTbl[j].bound(enemyTbl[i].getCenter());
				}
			}
		}

		// 弾と敵の当たり判定
		for (int i = 0; i < 5; i++)
		{

			Vec2 dist = shot.getCenter() - enemyTbl[i].getCenter();
			float radiusAdd = enemyTbl[i].getRadius() + shot.getRadius();
			if (dist.length() < radiusAdd)
			{
				// あたった場合の処理
				DrawFormatString(350, 350, GetColor(225, 0, 0), "ヒット！");
				   
			}

		}


		// 画像の表示
		for (auto& enemy : enemyTbl)
		{
			enemy.draw();
		}


		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	scene.end();
	player.end();

	DeleteGraph(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}