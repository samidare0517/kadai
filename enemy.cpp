#include "DxLib.h"
#include "enemy.h"
#include "game.h"
#include <cmath>

namespace
{
	// �����蔼�a�̔��a
	constexpr float kColRadius = 16.0f;

	// �L�����N�^�[�̈ړ����x
	constexpr int kSpeedX = 8;
	constexpr int kSpeedY = 8;
}

Enemy::Enemy()
{
	

	sizeX = 0;
	sizeY = 0;

	// �摜�f�[�^
	m_handle = 0;		// �摜�̃n���h��

	// �ʒu
	m_pos;

	// �ړ���
	m_vec;


}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	// �������x��ݒ�
	m_vec.x = 3.0f;
	m_vec.y = 3.0f;

}

void Enemy::setPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Enemy::update()
{
	m_pos += m_vec;

	if (m_pos.x < 0.0f)
	{
		m_pos.x = 0.0f;
		m_vec.x *= -1.0f;
	}
	if (m_pos.x > Game::kScreenWindth - sizeX)
	{
		m_pos.x = static_cast<float>(Game::kScreenWindth - sizeX);
		m_vec.x *= -1.0f;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_vec.y *= -1.0f;
	}
	if (m_pos.y > Game::kScreenHeight - sizeY)
	{
		m_pos.y = static_cast<float>(Game::kScreenHeight - sizeY);
		m_vec.y *= -1.0f;
	}
}


void Enemy::draw()
{
	
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawCircle(static_cast<int>(getCenter().x), static_cast<int>(getCenter().y), static_cast<int>(getRadius()), GetColor(225, 225, 225), false);
}

// �����蔻��̔��a�擾
float Enemy::getRadius()const
{
	return kColRadius;
}

// �����蔻��̒��S�ʒu�擾
Vec2 Enemy::getCenter() const
{
	int sizeX = 0;
	int sizeY = 0;

	if (GetGraphSize(m_handle, &sizeX, &sizeY) == -1)
	{
		// �T�C�Y���擾�ł��Ȃ������ꍇ�͍��ʒu��n���Ă���
		return m_pos;
	}
	
	Vec2 result = m_pos;
	result.x += sizeX / 2;
	result.y += sizeY / 2;
	
	return result;
}

void Enemy::bound(Vec2 targetPos)
{
	// ���˕���
	Vec2 boundDir = m_pos - targetPos;

	// ���݂̑��x�Ɠ������x�ɂ���
	float speed = m_vec.length();

	// ���Ε����Ɍ��݂̑��x�ňړ�����悤�ɂ���
	m_vec = boundDir.normalize() * speed;
}
