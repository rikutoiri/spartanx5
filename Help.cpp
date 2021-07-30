#include "Help.h"
#include "SceneMgr.h"
#include "Dxlib.h"
#include "Input.h"

static int mImageHandle;	//�摜�n���h���i�[�p�ϐ�

//������
void Help_Initialize() {
    mImageHandle = LoadGraph("images/.png");  //�w�i�摜

}

//�I������
void Help_Finalize() {
    DeleteGraph(mImageHandle);//�摜�̉��

}

//�X�V
void Help_Update() {
    if (CheckHitKey(KEY_INPUT_ESCAPE)) { //Esc�L�[��������Ă�����
        SceneMgr_ChangeScene(eScene_Menu); //�V�[�����Q�[����ʂɕύX
    }
}

//�`��
void Help_Draw() {
    DrawGraph(0, 0, mImageHandle, FALSE);

    SetFontSize(30);
    DrawString(20, 20, "�w���v���", 0xffffff, 0);

    SetFontSize(20);
    DrawString(20, 340, "", 0xffffff, 0);
    DrawString(20, 360, "", 0xffffff, 0);
    DrawString(20, 380, "", 0xffffff, 0);
    DrawString(20, 400, "", 0xffffff, 0);

    DrawString(150, 450, "---- X�L�[�������ă^�C�g���֖߂� ----", 0xffffff, 0);
}