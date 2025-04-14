// �L�[���͊�{
#include "DxLib.h"

int PlayerX, PlayerY;
int PlayerGraph;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int Key;

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(640, 480, 16);

	// �E�C���h�E���[�h�֕ύX
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;				// �G���[���N�����璼���ɏI��
	}

	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// �O���t�B�b�N�̃��[�h
	PlayerGraph = LoadGraph(L"Player.bmp");

	// �L�����N�^�[�̏����ʒu���Z�b�g
	PlayerX = 0;
	PlayerY = 0;

	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �L�[���͎擾
		Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// ��������Ă������ɐi��
		if (Key & PAD_INPUT_UP) PlayerY -= 3;

		// ���������Ă����牺�ɐi��
		if (Key & PAD_INPUT_DOWN) PlayerY += 3;

		// �E�������Ă�����E�ɐi��
		if (Key & PAD_INPUT_RIGHT) PlayerX += 3;

		// ���������Ă����獶�ɐi��
		if (Key & PAD_INPUT_LEFT) PlayerX -= 3;

		// ��ʂ�����������
		ClearDrawScreen();

		// �v���C���[��`�悷��
		DrawGraph(PlayerX, PlayerY, PlayerGraph, TRUE);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
