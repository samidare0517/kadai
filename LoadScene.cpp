#include "DxLib.h"
#include "LoadScene.h"
#include <cassert>

#include "ShotNormal.h"
#include "enemy.h"

namespace
{
	Enemy enemy[5];
	Player player;
	// ショットの発射間隔
	constexpr int kShotInterval = 16;
}

LoadScene::LoadScene()
{
	m_hPlayerGraohic = -1;
	m_hShotGraphic = -1;
	m_hEnemyGraphc = -1;

}

LoadScene::~LoadScene()
{

}

// 初期化
void LoadScene::init()
{
	m_hPlayerGraohic = LoadGraph("data/player.png");
	m_hShotGraphic = LoadGraph("data/shot.png");
	m_hEnemyGraphc = LoadGraph("data/enemy.png");

	m_player.setHandle(m_hPlayerGraohic);
	m_player.init();

	float posX = 80.0f;
	for (auto& m_enemy : enemy)
	{
		m_enemy.setHandle(m_hEnemyGraphc);
		m_enemy.init();
		m_enemy.setPos(posX,160.0f);
		posX += 80.0f;
	}

	m_player.setMain(this);
	m_enemy.setMain(this);
}

// 終了処理
void LoadScene::end()
{
	DeleteGraph(m_hPlayerGraohic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hEnemyGraphc);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
void LoadScene::update()
{
	
	m_player.update();

	for (auto& m_enemy : enemy)
	{
		m_enemy.update();
	}

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	
	// enemyバウンド判定
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			// enemy[i]とenemy[j]の当たり判定をとる
			Vec2  dist = enemy[i].getCenter() - enemy[j].getCenter();
			float radiusAdd = enemy[i].getRadius() + enemy[j].getRadius();
			if (dist.length() < radiusAdd)
			{
				// 当たった場合の処理
				enemy[i].bound(enemy[j].getCenter());
				enemy[j].bound(enemy[i].getCenter());
			}
		}
	}
	
	// enemyとplayerの当たり判定
	for (int i = 0; i < 5; i++)
	{
		Vec2  dist = m_player.getCenter() - enemy[i].getCenter();
		float radiusAdd = enemy[i].getRadius() + m_player.getRadius();
		if (dist.length() < radiusAdd)
		{
			// 当たった場合の処理
			DrawFormatString(400, 0, GetColor(255, 0, 0), "ぶつかってしまった!");

		}
	}
	DrawCircle(static_cast<int>(m_player.getCenter().x), static_cast<int>(m_player.getCenter().y), static_cast<int>(m_player.getRadius()), GetColor(225, 225, 0), false);



	while (it != m_pShotVt.end())
	{

		auto& pShot = (*it);

		assert(pShot);

		pShot->update();
		

		// enemyと弾の当たり判定
		for (int i = 0; i < 5; i++)
		{
			Vec2 dist = (*pShot).getCenter() - enemy[i].getCenter();
			float radiusAdd = enemy[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
			
				DrawFormatString(200, 0, GetColor(225, 0, 0), "ヒット！");
			}
		}
		DrawCircle(static_cast<int>((*pShot).getCenter().x), static_cast<int>((*pShot).getCenter().y), static_cast<int>((*pShot).getRadius()), GetColor(225, 225, 225), false);


		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			// vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}

		it++;
	}

}

// 毎フレームの描画
void LoadScene::draw()
{
	m_player.draw();
	
	for (auto& m_enemy : enemy)
	{
		m_enemy.draw();
	}


	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	// 現在存在している玉の数を表示
	DrawFormatString(0, 0, GetColor(225, 225, 225), "弾の数:%d", m_pShotVt.size());
}

bool LoadScene::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}
