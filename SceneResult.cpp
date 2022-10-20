#include "SceneResult.h"
#include "DxLib.h"
#include "Pad.h"

void SceneResult::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;

}

void SceneResult::end()
{

}

void SceneResult::update()
{

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_isEnd = true;
	}
}

void SceneResult::draw()
{
	// デバック用	
	DrawString(350, 300, "ゲームクリア", GetColor(255, 255, 255));
}