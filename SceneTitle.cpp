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
	m_menu.addItem("�I�v�V����");
	m_menu.addItem("�Q�[���I��");

	m_menu.setPos(64, 64);

	m_menu.setupCursor();
}

void SceneTitle::end()
{
	m_menu.end();
}

void SceneTitle::update()
{
	// �����̈ړ�
	m_textPosY += m_textVecY;
	if (m_textPosY < 0)
	{
		m_textPosY = 0;
		m_textVecY = 4;
	}
	if (m_textPosY > 200)
	{
		m_textPosY = 200;
		m_textVecY = -4;
	}

	m_menu.update();

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isEnd = true;
	}
}

void SceneTitle::draw()
{
	m_menu.draw();
}