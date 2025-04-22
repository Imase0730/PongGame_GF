#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// ----- �萔�錾 ----- //
	
	// ��ʂ̃T�C�Y
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	// �p�h���̑傫��
	const int PADDLE_WIDTH = 32;
	const int PADDLE_HEIGHT = 64;

	// �p�h���̏����ʒu
	const int PADDLE_START_X = 100;
	const int PADDLE_START_Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

	// �p�h���̈ړ��̑���
	const int PADDLE_SPEED = 8;

	// �{�[���̑傫��
	const int BALL_SIZE = 32;

	// �{�[���̏����ʒu
	const int BALL_X = SCREEN_WIDTH - BALL_SIZE;
	const int BALL_Y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

	// �{�[���̏������x
	const int BALL_SPEED_X = -5;
	const int BALL_SPEED_Y = 5;

	// ----- �ϐ��錾 ----- //
	int key;
	int paddleX;
	int paddleY;
	int ballX;
	int ballY;
	int ballVelocityX;
	int ballVelocityY;

	// ----- �ϐ��̏����� ----- //
	key = 0;
	paddleX = PADDLE_START_X;
	paddleY = PADDLE_START_Y;
	ballX = BALL_X;
	ballY = BALL_Y;
	ballVelocityX = BALL_SPEED_X;
	ballVelocityY = BALL_SPEED_Y;

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

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
			paddleY = paddleY - PADDLE_SPEED;
		}

		// ���������Ă����牺�ɐi��
		if (key & PAD_INPUT_DOWN)
		{
			paddleY = paddleY + PADDLE_SPEED;
		}

		// �p�h������ʊO�ɏo�Ȃ���Ɉʒu��␳����
		if (paddleY < 0)
		{
			paddleY = 0;
		}
		if (paddleY > SCREEN_HEIGHT - PADDLE_HEIGHT)
		{
			paddleY = SCREEN_HEIGHT - PADDLE_HEIGHT;
		}

		// �{�[���̈ړ�
		ballX += ballVelocityX;
		ballY += ballVelocityY;

		// �{�[������ʂ̉��ɐڐG������
		if (ballY >= SCREEN_HEIGHT - BALL_SIZE)
		{
			ballVelocityY = -ballVelocityY;
		}
		// �{�[������ʂ̏�ɐڐG������
		if (ballY <= 0)
		{
			ballVelocityY = -ballVelocityY;
		}
		// �{�[������ʂ̍��ɐڐG������
		if (ballX <= 0)
		{
			ballVelocityX = -ballVelocityX;
		}
		// �{�[������ʂ̉E�ɐڐG������
		if (ballX >= SCREEN_WIDTH - BALL_SIZE)
		{
			ballVelocityX = -ballVelocityX;
		}

		// ��ʂ�����������
		ClearDrawScreen();

		// ----- �Q�[���̕`�揈�� ----- //

		// �p�h���̕`��
		DrawBox(paddleX, paddleY, paddleX + PADDLE_WIDTH, paddleY + PADDLE_HEIGHT, GetColor(255, 255, 255), TRUE);

		// �{�[���̕`��
		DrawBox(ballX, ballY, ballX + BALL_SIZE, ballY + BALL_SIZE, GetColor(255, 255, 255), TRUE);

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}
