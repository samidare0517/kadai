#pragma once

#include <vector>

#include "Player.h"
#include "ShotBase.h"


class LoadScene
{
public:
	LoadScene();
	virtual ~LoadScene();

	// 初期化
	void init();


	// 終了処理
	void end();

	// 毎フレームの処理
	void update();

	// 毎フレームの描画
	void draw();
	
	// 弾の生成
	bool createShotNormal(Vec2 pos);


private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraohic;
	int m_hShotGraphic;

	// プレイヤー
	Player m_player;

	// ショット
	std::vector< ShotBase*> m_pShotVt;


};