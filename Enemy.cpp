#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Enemy.h"
#include "player.h"

//struct ENEMY mEnemy[i];
struct ENEMY mEnemy[ENEMY_MAX];

static int mImageEnemy;

extern int HitBoxEnemy(PLAYER*, ENEMY*);	//当たり判定（四角）hpが減る

void Enemy_Initialize() {

	//mImageEnemy = LoadDivGraph("images/enemy1.png", 8, 2, 4, 70, 95, ene,TRUE);	//画像のロード
	LoadDivGraph("images/enemy1clear.png", 8, 2, 4, 70, 95, ene);
	LoadDivGraph("images/tomtom.png", 8, 2, 4, 70, 95, tom);

	// エネミーの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
		mEnemy[i].dashLeft = true;			//左に移動する判定
		mEnemy[i].dashRight = true;			//右に移動する判定
		//mEnemy[i].x = 800;
		mEnemy[i].y = 395;				//x,y座標
		mEnemy[i].move = 1.0f;				//移動係数
		mEnemy[i].oldchar = 0;			//前の画像を入れる
		mEnemy[i].xcount = 0;
		mEnemy[i].ycount = 0;		//横方向と縦方向のカウント数
		mEnemy[i].ix = 0;
		mEnemy[i].iy = 0;
		mEnemy[i].result = 0;		//添字用変数

		mEnemy[i].gekiha = false;
		mEnemy[i].y_temp;
		mEnemy[i].y_prev;
		mEnemy[i].angle = 0;
	}

}
void Enemy_Finalize() {
	DeleteGraph(mImageEnemy); //画像の解放
}
void Enemy_Update() {

	//エネミー処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {


			//テスト
			if (mEnemy[i].gekiha == true) {			//撃破フラグがtrueになったら

				mEnemy[i].angle = 1;	//敵を傾ける

				mEnemy[i].y_prev = mEnemy[i].y;				//prevに360を代入
				mEnemy[i].y_temp = mEnemy[i].y;					//tempに360を代入
				mEnemy[i].y = mEnemy[i].y + 15;				//yに340を代入

				mEnemy[i].y += 1;		//yに(y - y_prev) + 1を足す
				mEnemy[i].y_prev = mEnemy[i].y_temp;			//prevにtemp（360）を代入


				if (mEnemy[i].y == 370)				//yが360なら								//360
					mEnemy[i].gekiha = false;			//フラグをfalseにする

			}


			if (CheckHitKey(KEY_INPUT_Z) == 0) {//zキーを押していなければ
				if (HitBoxEnemy(&mPlayer, &mEnemy[i]) == TRUE && mPlayer.panchi == false) {
					mPlayer.hp -= 15;//ｈｐを減らす
					if (mx != 0) {
						mEnemy[i].flg = FALSE;
					}
				}
			}
			//移動
			if (mEnemy[i].x >= 765) {//エネミーの位置が左端なら
				mEnemy[i].dashLeft = true;//dashLeftをtrueにする
				mEnemy[i].dashRight = false;//dashRightをfalseにする
			}
			else if (mEnemy[i].x <= 35) {//エネミーの位置が左端なら
				mEnemy[i].dashRight = true;//dashRightをtrueにする
				mEnemy[i].dashLeft = false;//dashLeftをfalseにする
			}

			if (mEnemy[i].dashLeft == true) {//dashLeftがtrueなら
				mEnemy[i].x -= (int)2 * mEnemy[i].move;//左に移動する
			}
			if (mEnemy[i].dashRight == true) {//dashRightがtrueなら
				mEnemy[i].x += (int)2 * mEnemy[i].move;//右に移動する
			}
			if (mEnemy[i].dashLeft == true) {			//移動した際にモーションをつける
				if (mEnemy[i].xcount > 0)
					mEnemy[i].xcount = 0;
				--mEnemy[i].xcount;

			}
			if (mEnemy[i].dashRight == true) {		//移動した際にモーションをつける
				if (mEnemy[i].xcount < 0)
					mEnemy[i].xcount = 0;
				++mEnemy[i].xcount;

			}
			mEnemy[i].ix = abs(mEnemy[i].xcount) % 20 / 10;		//画像2枚パラパラ
			mEnemy[i].iy = abs(mEnemy[i].ycount) % 20 / 10;

			//
			if (mEnemy[i].xcount > 0) {
				mEnemy[i].ix += 0;
				mEnemy[i].result = mEnemy[i].ix;
				mEnemy[i].oldchar = mEnemy[i].ix;
				if (mEnemy[i].x >= 190 && mEnemy[i].x <= 400) {//エネミー左から来てxが190に入ると威嚇モーションにする
					mEnemy[i].ix += 4;	//威嚇画像
					mEnemy[i].result = mEnemy[i].ix;
					mEnemy[i].oldchar = mEnemy[i].ix;
				}
			}
			else if (mEnemy[i].xcount < 0) {
				mEnemy[i].ix += 2;
				mEnemy[i].result = mEnemy[i].ix;
				mEnemy[i].oldchar = mEnemy[i].ix;
				if (mEnemy[i].x >= 400 && mEnemy[i].x <= 610) {//エネミー右から来てxが610に入ると威嚇モーションにする
					mEnemy[i].ix += 4;	//威嚇画像
					mEnemy[i].result = mEnemy[i].ix;
					mEnemy[i].oldchar = mEnemy[i].ix;
				}
			}

			// 画面をはみ出したら消去
			if (mEnemy[i].x > 800 && mx != 0)
				mEnemy[i].flg = FALSE;
			/*if (mEnemy[i].y > 600) {
				mEnemy[i].flg = FALSE;
			}*/

		}
		//押されてなければカウントをゼロにする
		if (mEnemy[i].dashLeft != true && mEnemy[i].dashRight != true) {//動いていなければモーションを止める
			mEnemy[i].xcount = 0;
		}


	}

	// エネミーの生成
	/*or (int i = 0; i < ENEMY_MAX; i++) {
		if (GetRand(3) == 2) {
			if (0 % ENEMY_CREATE_TIME == 0) {
				CreateEnemy();
			}
		}
	}*/
	/*if (0 % ENEMY_CREATE_TIME == 0) {
		CreateEnemy();
	}*/
	if (GetRand(3) == 2) {
		if (mx == 0) {
			CreateEnemy();
		}
		if (mx == -300 || mx == -306 || mx == -309 ) {
			CreateEnemy();
		}
		if (mx == -400) {
			CreateEnemy();
		}
		if (mx == -600 || mx == -603 || mx == -606) {
			CreateEnemy();
		}
		if (mx == -801|| mx == -804 || mx == -807) {
			CreateEnemy();
		}
		if (mx == -1110 || mx == -1113 || mx == -1116) {
			CreateEnemy();
		}
		if (mx == -1470 || mx == -1473 || mx == -1476) {
			CreateEnemy();
		}
	}

}
void Enemy_Draw() {

	//エネミー処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == true) {
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.2, mEnemy[i].angle, ene[mEnemy[i].result], TRUE);	//angleつけた
		}
	}



	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == TRUE) {
			DrawFormatString(600, 80, 0xFFFFFF, "true");
		}
		else if (mEnemy[i].flg == FALSE) {
			DrawFormatString(600, 80, 0xFFFFFF, "false");
		}
	}
}



int CreateEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == FALSE) {
			mEnemy[i].flg = TRUE;
			mEnemy[i].type = GetRand(3);
			if (GetRand(2) == 1) {
			mEnemy[i].x = 800;
			}
			else {
				mEnemy[i].x = 0;
			}
			// 成功
			return TRUE;
		}

		mEnemy[i].flg = FALSE;
	}
	// 失敗
	return FALSE;
}

int HitBoxEnemy(PLAYER* p, ENEMY* e)//当たり判定（四角）hpが減る
{
	// x, y は中心座標とする
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
	// 矩形が重なっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}