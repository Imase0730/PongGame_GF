#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1280, 720, 32);

	// �E�C���h�E�̃^�C�g����ύX����
	SetMainWindowText(L"Pong Game");

	// �E�C���h�E���[�h�֕ύX
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ----- �Q�[���̍X�V���� ----- //



		// ��ʂ�����������
		ClearDrawScreen();

		// ----- �Q�[���̕`�揈�� ----- //

		DrawBox(0, 0, 100, 200, GetColor(255, 255, 255), TRUE);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
