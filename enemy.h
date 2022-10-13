#pragma once
#include "Vec2.h"
#include "game.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void init();
	virtual void setHandle(int handle, int sizeX, int sizeY);
	virtual void setPos(float x, float y);
	virtual void update() = 0;		// �������z�֐�
	virtual void draw();

	// �����蔻��̔��a�擾
	virtual float getRadius() const;

	// �����蔻��̒��S�ʒu�擾
	virtual Vec2 getCenter() const;
	
	// �ق��̓G�ɓ��������ꂠ��̔��ˏ���
	virtual void bound(Vec2 targetPos);

	
protected:

	int m_handle;	// �摜�̃n���h��
	int sizeX;
	int sizeY;

	// �ʒu
	Vec2 m_pos;

	// �ړ���
	Vec2 m_vec;

	// ������W
	Vec2 m_size;

	
};

// �܂������ړ�

class EnemyStraight : public Enemy
{
public:
	EnemyStraight();
	virtual ~EnemyStraight() {}

	virtual void init() override;
			void update() override;


};