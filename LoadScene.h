#pragma once

#include <vector>

#include "Player.h"



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

private:

	int m_hPlayerGraohic;

	
	// プレイヤー
	Player m_player;

};