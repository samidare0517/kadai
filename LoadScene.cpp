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

// 初期化
void LoadScene:: init()
{
	m_hPlayerGraohic = LoadGraph("data/player.png");

	m_player.setHandle(m_hPlayerGraohic);
	m_player.init();
	m_player.setMain(this);
}

// 終了処理
void LoadScene::end()
{
	DeleteGraph(m_hPlayerGraohic);
}

// 毎フレームの処理
void LoadScene::update()
{
	m_player.update();
}

// 毎フレームの描画
void LoadScene::draw()
{
	m_player.draw();
}


