#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

	m_menu.init();
	m_menu.addItem("ゲームスタート");


	m_menu.setPos(64, 64);

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
}