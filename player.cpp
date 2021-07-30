#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"

struct PLAYER mPlayer;

extern int HitBoxPlayer(PLAYER*, ENEMY*);	//�����蔻��i�l�p�j

int mx = 0;

//static int mImagePlayer;	//�摜�n���h���i�[�p�ϐ�
static int mImageCong;

//������
void Player_Initialize() {
	LoadDivGraph("images/thomas2clear.png", 21, 3, 7, 70, 95, gh);

	mImageCong = LoadGraph("images/congra.png");

	//�v���C���[�̏������ݒ�
	mPlayer.jflag = false;
	mPlayer.huse = false;//���Ⴊ�݂��Ă��邩�̃t���O
	mPlayer.panchi = false;
	mPlayer.stop = false;//�U�������Ƃ��ɕ������~�߂�t���O
	mPlayer.x = 400;//x���W
	mPlayer.y = 400;//y���W
	mPlayer.y_prev = 0;//���W
	mPlayer.y_temp = 0;//���W
	mPlayer.oldchar = 3;//�O�̉摜������(�E�����������������f���邽��)
	mPlayer.attack = 0;//���Ⴊ�ݍU��
	mPlayer.move = 1.0f;//�ړ��W��
	mPlayer.xcount = 0;//�������̃J�E���g��
	mPlayer.ycount = 0;//�c�����̃J�E���g��
	mPlayer.ix = 0;//�Y���p�ϐ�
	mPlayer.iy = 0;//�Y���p�ϐ�
	mPlayer.result = 0;//�Y���p�ϐ�
	mPlayer.hp = PLAYER_HP;
}

//�I������
void Player_Finalize() {
	//DeleteGraph(mImagePlayer);	//�摜�̉��
}

//�X�V
void Player_Update() {
	//LoadDivGraph("images/thomas2.png", 21, 3, 7, 70, 95, gh);
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		mPlayer.move = 1.0f;
	}
	else if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1) {
		mPlayer.move = 1.0f;
	}

	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (mPlayer.stop == false) {
			//mPlayer.x -= (int)4 * mPlayer.move;
			if (mx <= -3) {
				mx += 3;
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		if (mPlayer.stop == false) {
			//mPlayer.x += (int)4 * mPlayer.move;
			if (mx >= -2197) {
				mx -= 3;
			}
		}
	}

	DrawFormatString(500, 100, 0xFFFFFF, "%d", mx);

	//��ʈړ�����
	if (mPlayer.x + (PLAYER_WIDHT / 2) > 800)
		mPlayer.x = 800 - (PLAYER_WIDHT / 2);
	if (mPlayer.x < (49 / 2))
		mPlayer.x = (49 / 2);



	//�W�����v����
	if (mPlayer.jflag == true) {			//�W�����v�t���O��true�ɂȂ�����
		mPlayer.y_temp = mPlayer.y;					//temp��360����
		mPlayer.y += (mPlayer.y - mPlayer.y_prev) + 1;		//y��(y - y_prev) + 1�𑫂�
		mPlayer.y_prev = mPlayer.y_temp;			//prev��temp�i360�j����
		if (mPlayer.oldchar == 3 || mPlayer.oldchar == 4 || mPlayer.oldchar == 5) {//�E�����Ȃ�
			mPlayer.ix = 0;			//[0]�̉摜��\��(�W�����v�̉摜)
		}
		else {//�������Ȃ�
			mPlayer.ix = 1;			//[1]�̉摜��\��(�W�����v�̉摜)
		}
		mPlayer.result = mPlayer.ix;		//�摜��\��(�W�����v�̉摜)
		if (mPlayer.y == 400)				//y��360�Ȃ�
			mPlayer.jflag = false;			//�t���O��false�ɂ���
	}
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && mPlayer.jflag == false) {
		mPlayer.jflag = true;			//�W�����v�t���O��true�ɂ���
		mPlayer.y_prev = mPlayer.y;				//prev��360����
		mPlayer.y = mPlayer.y - 15;				//y��340����
	}

	//�p���`
	if (CheckHitKey(KEY_INPUT_Z) == 1 && mPlayer.panchi == false) {//Z�L�[����������

		mPlayer.panchi = true;			//panchi��true�ɂ���
		mPlayer.stop = true;


	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (HitBoxPlayer(&mPlayer, &mEnemy[i]) == TRUE) {
			mEnemy[i].gekiha = true;
			//mEnemy[i].flg = false;
		}


		if (mPlayer.panchi == true) {		//panchi��true�Ȃ�
			if (mPlayer.oldchar == 3 || mPlayer.oldchar == 4 || mPlayer.oldchar == 5) {
				mPlayer.ix = 15;//�E�����p���`
				mPlayer.result = mPlayer.ix;
			}
			else if (mPlayer.oldchar == 6 || mPlayer.oldchar == 7 || mPlayer.oldchar == 8) {
				mPlayer.ix = 16;//�������p���`
				mPlayer.result = mPlayer.ix;

			}
		}

	}
	if (CheckHitKey(KEY_INPUT_Z) != 1 && mPlayer.panchi == false) {//Z�L�[��������Ă��Ȃ����
		mPlayer.stop = false;
	}




	//���Ⴊ��
	if (CheckHitKey(KEY_INPUT_DOWN) == 1 && mPlayer.huse == false) {//�����L�[����������
		mPlayer.huse = true;			//huse��true�ɂ���

		if (mPlayer.huse == true) {		//huse��true�Ȃ�
			if (mPlayer.oldchar == 3 || mPlayer.oldchar == 4 || mPlayer.oldchar == 5) {
				mPlayer.ix = 13;//�E�������Ⴊ��
				mPlayer.result = mPlayer.ix;
				if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 1)//���Ⴊ�ݍU��
				{
					mPlayer.attack++;
					if (mPlayer.attack == 1) {//attack���P�Ȃ�

						timer++;									//�e�X�g
						if (timer < 100) {							//
							//ix += 1;								//
							//result = ix;							//
						}											//�e�X�g
						mPlayer.ix += 1;	//ix��+1����
						mPlayer.result = mPlayer.ix;//�U���摜�ɂ��肩��

						//�G��|���v���O����������

					}
				}
				else if (mPlayer.attack > 0)
				{
					mPlayer.attack = -1;
				}
				else {
					mPlayer.attack = 0;
				}
			}
			else  if (mPlayer.oldchar == 6 || mPlayer.oldchar == 7 || mPlayer.oldchar == 8) {
				mPlayer.ix = 10;//���������Ⴊ��
				mPlayer.result = mPlayer.ix;
				if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 1) {
					mPlayer.ix += 1;
					mPlayer.result = mPlayer.ix;
					//�G��|���v���O����������

				}
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {			//�ړ������ۂɃ��[�V����������
		if (mPlayer.stop == false) {//�X�g�b�v�t���O��false1�Ȃ�
			if (mPlayer.xcount > 0)
				mPlayer.xcount = 0;
			--mPlayer.xcount;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {		//�ړ������ۂɃ��[�V����������
		if (mPlayer.stop == false) {//�X�g�b�v�t���O��false1�Ȃ�
			if (mPlayer.xcount < 0)
				mPlayer.xcount = 0;
			++mPlayer.xcount;
		}
	}

	//
	mPlayer.ix = abs(mPlayer.xcount) % 30 / 10;
	mPlayer.iy = abs(mPlayer.ycount) % 30 / 10;

	//
	if (mPlayer.xcount > 0) {
		mPlayer.ix += 3;
		mPlayer.result = mPlayer.ix;
		mPlayer.oldchar = mPlayer.ix;
	}
	else if (mPlayer.xcount < 0) {
		mPlayer.ix += 6;
		mPlayer.result = mPlayer.ix;
		mPlayer.oldchar = mPlayer.ix;
	}

	//DrawGraph(mPlayer.x - (PLAYER_WIDHT / 2), mPlayer.y - (PLAYER_HEIGHT / 2), gh[mPlayer.result], TRUE);

	DrawRotaGraph(400, mPlayer.y, 1.2, 0, gh[mPlayer.result], TRUE);	//test

	//������ĂȂ���΃J�E���g���[���ɂ���
	if (CheckHitKey(KEY_INPUT_LEFT) != 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		mPlayer.xcount = 0;

		mPlayer.panchi = false;
		mPlayer.huse = false;
		if (mPlayer.panchi == false) {
			mPlayer.ix += 3;
			mPlayer.result = mPlayer.oldchar;
		}
		if (mPlayer.huse == false) {
			mPlayer.ix += 3;
			mPlayer.result = mPlayer.oldchar;
		}
	}
	if (mx == -2199) {
		GameClear();
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			SceneMgr_ChangeScene(eScene_End);	//
		}
	}
}

//�`��
void Player_Draw() {

}
void GameClear(void) {

	if (CheckHitKey(PAD_INPUT_2)) {
		SceneMgr_ChangeScene(eScene_Menu);
	}

	//DrawBox(150, 150, 490, 330, 0x009900, TRUE);
	//DrawBox(150, 150, 490, 330, 0x009900, FALSE);
	DrawGraph(400, 300, mImageCong, TRUE);

	SetFontSize(20);
	DrawString(220, 170, "�Q�[���N���A", 0xcc0000);
	SetFontSize(16);
	DrawFormatString(150, 450, 0xFFFFFF, "---- X�L�[�������ă^�C�g���֖߂� ----", 0xffffff, 0);
}
int HitBoxPlayer(PLAYER* p, ENEMY* e)
{
	// x, y �͒��S���W�Ƃ���
	int sx1 =
		p->x - (int)(
			40 * 0.45f);
	int sy1 =
		p->y - (int)(
			95 * 0.45f);
	int sx2 =
		p->x + (int)(
			40 * 0.45f);
	int sy2 =
		p->y + (int)(
			95 * 0.45f);
	int dx1 =
		e->x - (int)(
			40 * 0.4f);
	int dy1 =
		e->y - (int)(
			95 * 0.4f);
	int dx2 =
		e->x + (int)(
			40 * 0.4f);
	int dy2 =
		e->y + (int)(
			95 * 0.4f);
	// ��`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}