#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "player.h"
#include "Enemy.h"

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int mImageTime;	//
static int mImageHp;

//������
void Game_Initialize() {
	mImageHandle = LoadGraph("images/haikeigazo2.png"); //�摜�̃��[�h
	mImageTime = LoadGraph("images/time.png");
	mImageHp = LoadGraph("images/player.png");

	Player_Initialize();	//
	Enemy_Initialize();
}

//�I������
void Game_Finalize() {
	DeleteGraph(mImageHandle); //�摜�̉��
	DeleteGraph(mImageTime); //�摜�̉��
	DeleteGraph(mImageHp); //�摜�̉��

	Player_Finalize();	//�v���C���[�̊J��
	Enemy_Finalize();
}

//�X�V
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	DrawGraph(mx, 0, mImageHandle, FALSE);

	Player_Update();
	Enemy_Update();

}
//�`��
void Game_Draw() {
	Player_Draw();
	Enemy_Draw();

	DrawGraph(300, 30, mImageTime, TRUE);

	//�̗̓Q�[�W�̕\��
	//int X = 100; int Y = 430; int W = 100; int H = 20;
	DrawGraph(100, 30, mImageHp, TRUE);
	DrawBox(100, 70, 100 + (int)(mPlayer.hp * 100 / PLAYER_HP), 90, 0xff0000, TRUE);

}