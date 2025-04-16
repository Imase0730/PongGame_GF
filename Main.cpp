#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// �ϐ��̐錾
	int key;
	int x;
	int y;

	// �ϐ��̏�����
	key = 0;
	x = 0;
	y = 0;

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

		// �L�[���͎擾
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// ��������Ă������ɐi��
		if (key & PAD_INPUT_UP)
		{
			y = y - 10;
		}

		// ���������Ă����牺�ɐi��
		if (key & PAD_INPUT_DOWN)
		{
			y = y + 10;
		}

		// ��ʂ�����������
		ClearDrawScreen();

		// ----- �Q�[���̕`�揈�� ----- //

		// �p�h���̕`��
		DrawBox(x, y, x + 32, y + 64, GetColor(255, 255, 255), TRUE);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
