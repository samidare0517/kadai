#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include <cassert>
#include "ShotNormal.h"
#include "enemy.h"
#include "SceneTitle.h"


namespace
{
	Enemy enemy[5];

	bool kCheck;

	// ショットの発射間隔
	constexpr int kShotInterval = 16;
}

void SceneMain::init()
{

	m_textPosX = 0;
	m_textVecX = 4;

	m_isEnd = false;

	// 画像データ
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
		m_enemy.setPos(posX, 160.0f);
		posX += 80.0f;
	}

	m_player.setMain(this);
	m_enemy.setMain(this);

}

void SceneMain::end()
{
	// 画像の開放
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

void SceneMain::update()
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
		// Playerのflag (false = 生存)
		bool isEnd = false;
		// enemyが死んでいたら死んだenemy表示しない
		
	//	if (enemy->isDead())return false;

		Vec2  dist = m_player.getCenter() - enemy[i].getCenter();
		float radiusAdd = enemy[i].getRadius() + m_player.getRadius();
		if (dist.length() < radiusAdd)
		{
			// 当たった場合の処理
			DrawFormatString(400, 0, GetColor(255, 0, 0), "ぶつかってしまった!");
			
			// Playerが敵と接触した時点でゲームを終了する
			isEnd = true;
			DxLib_End();

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
				// shotにenemyが当たった場合の死亡判定
			
				DrawFormatString(200, 0, GetColor(225, 0, 0), "ヒット！");
				kCheck = true;
			
			}
			else
			{
				kCheck = false;
			}
			if (isCol() == true)
			{
				enemy[i].setDead();
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

	
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = false;
	}
	DrawString(m_textPosX, 100, "ゲーム画面", GetColor(255, 255, 255));
}

void SceneMain::draw()
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

bool SceneMain::isCol()
{
	/*for (int i = 0; i < kCheck; i++)
	{
		if (enemy[i].isDead())
		{
			return true;
		}
	}*/

	if(kCheck == true)
	{
		return true;
	}
	else
	{
		return false;
	}


}



bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}