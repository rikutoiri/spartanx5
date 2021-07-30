#pragma once

#define PI 3.1415926535897932384626433832795f

const int ENEMY_MAX = 6;			//�G�̍ő吔
const int ENEMY_IMAGE_MAX = 4;
const int ENEMY_CREATE_TIME = 200;

//extern struct ENEMY mEnemy;
extern struct ENEMY mEnemy[ENEMY_MAX];

struct ENEMY {
	bool dashLeft;			//���Ɉړ����锻��
	bool dashRight;			//�E�Ɉړ����锻��
	int x,y;				//x,y���W
	float move;				//�ړ��W��
	int oldchar;			//�O�̉摜������
	int xcount,ycount;		//�������Əc�����̃J�E���g��
	int ix,iy,result;		//�Y���p�ϐ�

	bool gekiha;				//�e�X�g�G�̌��j����
	int y_temp, y_prev;		//�e�X�g�G�̌��j��������
	int angle;

	int img;	//�e�X�g2
	int type;	//�e�X�g2
	bool flg;	//�e�X�g�Q
};

//�G�l�~�[�̐���
extern int CreateEnemy();//�e�X�g�Q

//�G�l�~�[
static int ene[8];
static int tom[8];

extern void Enemy_Initialize();
extern void Enemy_Finalize();
extern void Enemy_Update();
extern void Enemy_Draw();