#pragma once

#include <vector>

#include "Player.h"
#include "ShotBase.h"
#include "enemy.h"


class LoadScene
{
public:
	LoadScene();
	virtual ~LoadScene();

	// ������
	void init();


	// �I������
	void end();

	// ���t���[���̏���
	void update();

	// ���t���[���̕`��
	void draw();
	
	// �e�̐���
	bool createShotNormal(Vec2 pos);


private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraohic;
	int m_hShotGraphic;
	int m_hEnemyGraphc;

	// �v���C���[
	Player m_player;

	// �G�l�~�[
	Enemy m_enemy;

	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;


};