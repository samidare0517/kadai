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

	// �e�̐���
	virtual bool createShotNormal(Vec2 pos);

	virtual bool isEnd() { return m_isEnd; }

	virtual bool isCol();

private:
	// �e�L�X�g�\���ʒu�ύX
	int m_textPosX;
	int m_textVecX;

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraohic;
	int m_hShotGraphic;
	int m_hEnemyGraphc;

	int m_EnemyNum;

	bool m_isEnd;

	Enemy m_enemy;
	Player m_player;


	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
};