#pragma once
#include "Vec2.h"
#include "game.h"

class SceneMain;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void setHandle(int handle) { m_handle = handle; }
	void init();
	void setPos(float x, float y);
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	void update();
	void draw();
	void setDead() { m_isDead = true; }
	

	Vec2 getPos() const { return m_pos; }

	// �����蔻��̔��a�擾
	virtual float getRadius() const;

	// �����蔻��̒��S�ʒu�擾
	virtual Vec2 getCenter() const;
	
	// �ق��̓G�ɓ��������ꂠ��̔��ˏ���
	virtual void bound(Vec2 targetPos);
	
	bool isDead()const{return m_isDead;}


private:

	int m_handle;	// �摜�̃n���h��
	int sizeX;
	int sizeY;
	SceneMain* m_pMain;

	

	// �ʒu
	Vec2 m_pos;

	// �ړ���
	Vec2 m_vec;

	// ������W
	Vec2 m_size;

	bool m_isDead;

};
