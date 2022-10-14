#include "DxLib.h"

#include "game.h"
#include "LoadScene.h"
#include "enemy.h"
#include "ShotBase.h"
#include "SceneManager.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[���̏�����
	SceneManager scene;
	scene.init();

	ShotBase shot;

	LoadScene player;
	player.init();

	int SizeX = 0;
	int SizeY = 0;

	int handle = LoadGraph("data/enemy.png");
	EnemyStraight enemyTbl[5];
	float posX = 80.0f;
	GetGraphSize(handle, &SizeX, &SizeY);

	for (auto& enemy : enemyTbl)
	{
		enemy.init();
		enemy.setHandle(handle, SizeX, SizeY);		// �\������摜�̎w��
		enemy.setPos(posX, 160.0f);		// �����ʒu
		posX += 80.0f;
	}


	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		scene.update();
		player.update();
		
		scene.draw();
		player.draw();

		// �L�����N�^�[�̈ړ�
		for (auto& enemy : enemyTbl)
		{
			enemy.update();
		}

		// �����蔻��

		// �o�E���h
		for (int i = 0; i < 5; i++)
		{
			for (int j = i + 1; j < 5; j++)
			{
				// enemyTbl[i]��enemyTbl[j]�̓����蔻����Ƃ�
				Vec2 dist = enemyTbl[i].getCenter() - enemyTbl[j].getCenter();
				float radiusAdd = enemyTbl[i].getRadius() + enemyTbl[j].getRadius();
				if (dist.length() < radiusAdd)
				{
					// ���������ꍇ�̏���
					enemyTbl[i].bound(enemyTbl[j].getCenter());
					enemyTbl[j].bound(enemyTbl[i].getCenter());
				}
			}
		}

		// �e�ƓG�̓����蔻��
		for (int i = 0; i < 5; i++)
		{

			Vec2 dist = shot.getCenter() - enemyTbl[i].getCenter();
			float radiusAdd = enemyTbl[i].getRadius() + shot.getRadius();
			if (dist.length() < radiusAdd)
			{
				// ���������ꍇ�̏���
				DrawFormatString(350, 350, GetColor(225, 0, 0), "�q�b�g�I");
				   
			}

		}


		// �摜�̕\��
		for (auto& enemy : enemyTbl)
		{
			enemy.draw();
		}


		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	scene.end();
	player.end();

	DeleteGraph(handle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}