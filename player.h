#pragma once

#define PI 3.1415926535897932384626433832795f

#define PLAYER_WIDHT 70
#define PLAYER_HEIGHT 95

const int PLAYER_HP = 100;

extern struct PLAYER mPlayer;

struct PLAYER {
	bool jflag;
	bool huse;//���Ⴊ�݂��Ă��邩�̃t���O
	bool panchi;
	bool stop;//�U�������Ƃ��ɕ������~�߂�t���O
	int x, y, y_prev, y_temp;//���W
	int oldchar;//�O�̉摜������(�E�����������������f���邽��)
	int attack;//���Ⴊ�ݍU��
	float move;//�ړ��W��
	int xcount, ycount;//�������Əc�����̃J�E���g��
	int ix, iy, result;//�Y���p�ϐ�
	int hp;
};

static int timer = 0;//�^�C�}�[
//�O���t�B�b�N�n���h���i�[�p�z��
static int gh[21];
//�L�[�擾�p�z��
static char key[256];

extern int mx;

extern void Player_Initialize();//
extern void Player_Finalize();
extern void Player_Update();	//
extern void Player_Draw();		//

void GameClear(void);
