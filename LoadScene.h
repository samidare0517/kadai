#pragma once

#include <vector>

#include "Player.h"



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

private:

	int m_hPlayerGraohic;

	
	// �v���C���[
	Player m_player;

};