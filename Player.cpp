#include "DxLib.h"
#include "game.h"
#include "Player.h"
#include "LoadScene.h"

namespace
{
	// X方向、Y方向の最大速度
	constexpr float kSpeedMax = 8.0f;
	constexpr float kAcc = 0.4f;
}



Player::Player()
{
	m_handle = -1;

}
Player::~Player()
{


}

// プレイヤーの初期化
void Player::init()
{
	m_pos.x = 100.0f;
	m_pos.y = 100.0f;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

// 処理
void Player::update()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	
	// パッド移動処理
	
	if (padState & PAD_INPUT_UP)
	{
		m_vec.y -= kAcc;
	
		if (m_vec.y < -kSpeedMax)
		{
			m_vec.y = -kSpeedMax;
		}
	}
	else if (padState & PAD_INPUT_DOWN)
	{
		m_vec.y += kAcc;

		if (m_vec.y > kSpeedMax)
		{
			m_vec.y > kSpeedMax;
		}
	}
	else
	{
		m_vec.y *= 0.9f;
	}
	if (padState & PAD_INPUT_LEFT)
	{
		m_vec.x -= kAcc;

		if (m_vec.x > kSpeedMax)
		{
			m_vec.x = -kSpeedMax;
		}
	}
	else if (padState & PAD_INPUT_RIGHT)
	{
		m_vec.x += kAcc;
		
		if (m_vec.x > kSpeedMax)
		{
			m_vec.x = kSpeedMax;
		}
	}
	else
	{
		m_vec.x *= 0.9f;
	}
	m_pos += m_vec;

}

// 描画
void Player::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

