#pragma once
#include "SceneBase.h"
#include "ShotBase.h"
#include "enemy.h"
#include "Player.h"
#include "SceneTitle.h"
#include <vector>

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_textPosX = 0;
		m_textVecX = 0;
		m_isEnd = false;
		m_hPlayerGraohic = -1;
		m_hShotGraphic = -1;
		m_hEnemyGraphc = -1;
		m_EnemyNum = 0;
		
	}
	virtual ~SceneMain() {}


	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();

	// 弾の生成
	virtual bool createShotNormal(Vec2 pos);

	virtual bool isEnd() { return m_isEnd; }

	virtual bool isCol();

private:
	// テキスト表示位置変更
	int m_textPosX;
	int m_textVecX;

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraohic;
	int m_hShotGraphic;
	int m_hEnemyGraphc;

	int m_EnemyNum;

	bool m_isEnd;

	Enemy m_enemy;
	Player m_player;


	// ショット
	std::vector<ShotBase*> m_pShotVt;
};