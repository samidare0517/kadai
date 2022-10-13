#pragma once

#include "Vec2.h"

class LoadScene;

class Player
{
public:
	Player();
	virtual ~Player();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	// �v���C���[�̏�����
	void init();

	// ScneneMain�N���X�̃|�C���^�ݒ�
	void setMain(LoadScene* pMain) { m_pMain = pMain; }
	
	// ����
	void update();

	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }


	// �����蔻��̔��a�擾
	virtual float getRadius() const;

	// �����蔻��̒��S�ʒu�擾
	virtual Vec2 getCenter() const;
private:

	int m_handle;
	
	// SceneMain�̃|�C���^
	LoadScene* m_pMain;
	
	// �\���ʒu
	Vec2 m_pos;

	// �ړ�
	Vec2 m_vec;

	// �V���b�g�̔��ˊԊu
	int m_shotInterval;
};
