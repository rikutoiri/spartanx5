#include"Menu.h"
#include"SceneMgr.h"
#include"DxLib.h"
#include"Input.h"

#define PI 3.1415926535897932384626433832795f


static int MenuNumber = 0;  //���j���[�J�[�\���Ǘ��p�ϐ�

static int mImageHandle; //�摜�n���h���i�[�p�ϐ�
static int mImageGame;
static int mImageHelp;
static int mImageEnd;

static int mImageKnife;
//������
void Menu_Initialize() {
    //mImageHandle = LoadGraph("images/Scene_Menu.png"); //�摜�̃��[�h
    mImageGame = LoadGraph("images/game.png");
    mImageHelp = LoadGraph("images/help.png");
    mImageEnd = LoadGraph("images/end.png");

    mImageKnife = LoadGraph("images/knife1.png");
}
//�I������
void Menu_Finalize() {
    DeleteGraph(mImageHandle); //�摜�̉��
    DeleteGraph(mImageGame);
    DeleteGraph(mImageHelp);
    DeleteGraph(mImageEnd);

    DeleteGraph(mImageKnife);
}
//�X�V
void Menu_Update() {
    //���j���[�J�[�\���ړ�����
    if (iKeyFlg & PAD_INPUT_DOWN) {
        if (++MenuNumber > 2) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        if (--MenuNumber < 0) MenuNumber = 2;
    }

    if (CheckHitKey(KEY_INPUT_SPACE)) { //Z�L�[��������Ă�����
        switch (MenuNumber) {       //�V�[���ɂ���ď����𕪊�
        case 0:    //���݂̉�ʂ����j���[�Ȃ�
            SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Help); //�V�[�����Q�[����ʂɕύX
            break;
        case 2:
            SceneMgr_ChangeScene(eScene_End);	//
            break;
        }
    }

}
//�`��
void Menu_Draw() {
    DrawGraph(0, 0, mImageHandle, FALSE);
    DrawGraph(350, 330, mImageGame, TRUE);
    DrawGraph(350, 370, mImageHelp, TRUE);
    DrawGraph(350, 410, mImageEnd, TRUE);

    DrawRotaGraph(320, 345 + MenuNumber * 40, 0.7f, 0, mImageKnife, TRUE);
}