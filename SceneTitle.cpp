#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

	m_menu.init();
	m_menu.addItem("�Q�[���X�^�[�g");


	m_menu.setPos(350, 300);

	m_menu.setupCursor();
}

void SceneTitle::end()
{
	m_menu.end();
}

void SceneTitle::update()
{
	m_menu.update();

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = true;
	}
}

void SceneTitle::draw()
{
	m_menu.draw();
	// �f�o�b�N�p	
//	DrawString(400, 100, "�^�C�g�����", GetColor(255, 255, 255));
}