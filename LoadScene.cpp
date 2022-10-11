#include "DxLib.h"
#include "LoadScene.h"
#include <cassert>

LoadScene::LoadScene()
{
	m_hPlayerGraohic = -1;

}

LoadScene::~LoadScene()
{

}

// ������
void LoadScene:: init()
{
	m_hPlayerGraohic = LoadGraph("data/player.png");

	m_player.setHandle(m_hPlayerGraohic);
	m_player.init();
	m_player.setMain(this);
}

// �I������
void LoadScene::end()
{
	DeleteGraph(m_hPlayerGraohic);
}

// ���t���[���̏���
void LoadScene::update()
{
	m_player.update();
}

// ���t���[���̕`��
void LoadScene::draw()
{
	m_player.draw();
}


