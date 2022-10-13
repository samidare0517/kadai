#include "DxLib.h"
#include "LoadScene.h"
#include <cassert>

#include "ShotNormal.h"

namespace
{
	// �V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
}

LoadScene::LoadScene()
{
	m_hPlayerGraohic = -1;
	m_hShotGraphic = -1;
}

LoadScene::~LoadScene()
{

}

// ������
void LoadScene:: init()
{
	m_hPlayerGraohic = LoadGraph("data/player.png");
	m_hShotGraphic = LoadGraph("data/shot.png");

	m_player.setHandle(m_hPlayerGraohic);
	m_player.init();
	m_player.setMain(this);
}

// �I������
void LoadScene::end()
{
	DeleteGraph(m_hPlayerGraohic);
	DeleteGraph(m_hShotGraphic);
	
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// ���t���[���̏���
void LoadScene::update()
{
	
	m_player.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		assert(pShot);

		pShot->update();

		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			// vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}

		it++;
	}
}

// ���t���[���̕`��
void LoadScene::draw()
{
	m_player.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}

	// ���ݑ��݂��Ă���ʂ̐���\��
	DrawFormatString(0, 0, GetColor(225, 225, 225), "�e�̐�:%d", m_pShotVt.size());
}

bool LoadScene::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}
