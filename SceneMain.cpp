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

	// �V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
}

void SceneMain::init()
{

	m_textPosX = 0;
	m_textVecX = 4;

	m_isEnd = false;

	// �摜�f�[�^
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
	// �摜�̊J��
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

	// enemy�o�E���h����
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			// enemy[i]��enemy[j]�̓����蔻����Ƃ�
			Vec2  dist = enemy[i].getCenter() - enemy[j].getCenter();
			float radiusAdd = enemy[i].getRadius() + enemy[j].getRadius();
			if (dist.length() < radiusAdd)
			{
				// ���������ꍇ�̏���
				enemy[i].bound(enemy[j].getCenter());
				enemy[j].bound(enemy[i].getCenter());
			}
		}
	}

	// enemy��player�̓����蔻��
	for (int i = 0; i < 5; i++)
	{
		// Player��flag (false = ����)
		bool isEnd = false;
		// enemy������ł����玀��enemy�\�����Ȃ�
		
	//	if (enemy->isDead())return false;

		Vec2  dist = m_player.getCenter() - enemy[i].getCenter();
		float radiusAdd = enemy[i].getRadius() + m_player.getRadius();
		if (dist.length() < radiusAdd)
		{
			// ���������ꍇ�̏���
			DrawFormatString(400, 0, GetColor(255, 0, 0), "�Ԃ����Ă��܂���!");
			
			// Player���G�ƐڐG�������_�ŃQ�[�����I������
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


		// enemy�ƒe�̓����蔻��
		for (int i = 0; i < 5; i++)
		{
			Vec2 dist = (*pShot).getCenter() - enemy[i].getCenter();
			float radiusAdd = enemy[i].getRadius() + (*pShot).getRadius();
			if (dist.length() < radiusAdd)
			{
				// shot��enemy�����������ꍇ�̎��S����
			
				DrawFormatString(200, 0, GetColor(225, 0, 0), "�q�b�g�I");
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

			// vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}

		it++;
	}

	
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = false;
	}
	DrawString(m_textPosX, 100, "�Q�[�����", GetColor(255, 255, 255));
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
	// ���ݑ��݂��Ă���ʂ̐���\��
	DrawFormatString(0, 0, GetColor(225, 225, 225), "�e�̐�:%d", m_pShotVt.size());
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