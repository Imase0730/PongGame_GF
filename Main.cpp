#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// ----- 定数宣言 ----- //
	
	// 画面のサイズ
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	// パドルの大きさ
	const int PADDLE_WIDTH = 32;
	const int PADDLE_HEIGHT = 64;

	// パドルの初期位置
	const int PADDLE_START_X = 100;
	const int PADDLE_START_Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

	// パドルの移動の速さ
	const int PADDLE_SPEED = 8;

	// ボールの大きさ
	const int BALL_SIZE = 32;

	// ボールの初期位置
	const int BALL_X = SCREEN_WIDTH - BALL_SIZE;
	const int BALL_Y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

	// ボールの初期速度
	const int BALL_SPEED_X = -5;
	const int BALL_SPEED_Y = 5;

	// ----- 変数宣言 ----- //
	int key;
	int paddleX;
	int paddleY;
	int ballX;
	int ballY;
	int ballVelocityX;
	int ballVelocityY;

	// ----- 変数の初期化 ----- //
	key = 0;
	paddleX = PADDLE_START_X;
	paddleY = PADDLE_START_Y;
	ballX = BALL_X;
	ballY = BALL_Y;
	ballVelocityX = BALL_SPEED_X;
	ballVelocityY = BALL_SPEED_Y;

	// 画面モードのセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// ウインドウのタイトルを変更する
	SetMainWindowText(L"Pong Game");

	// ウインドウモードへ変更
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ----- ゲームの更新処理 ----- //

		// キー入力取得
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// 上を押していたら上に進む
		if (key & PAD_INPUT_UP)
		{
			paddleY = paddleY - PADDLE_SPEED;
		}

		// 下を押していたら下に進む
		if (key & PAD_INPUT_DOWN)
		{
			paddleY = paddleY + PADDLE_SPEED;
		}

		// パドルが画面外に出ないよに位置を補正する
		if (paddleY < 0)
		{
			paddleY = 0;
		}
		if (paddleY > SCREEN_HEIGHT - PADDLE_HEIGHT)
		{
			paddleY = SCREEN_HEIGHT - PADDLE_HEIGHT;
		}

		// ボールの移動
		ballX += ballVelocityX;
		ballY += ballVelocityY;

		// ボールが画面の下に接触したら
		if (ballY >= SCREEN_HEIGHT - BALL_SIZE)
		{
			ballVelocityY = -ballVelocityY;
		}
		// ボールが画面の上に接触したら
		if (ballY <= 0)
		{
			ballVelocityY = -ballVelocityY;
		}
		// ボールが画面の左に接触したら
		if (ballX <= 0)
		{
			ballVelocityX = -ballVelocityX;
		}
		// ボールが画面の右に接触したら
		if (ballX >= SCREEN_WIDTH - BALL_SIZE)
		{
			ballVelocityX = -ballVelocityX;
		}

		// 画面を初期化する
		ClearDrawScreen();

		// ----- ゲームの描画処理 ----- //

		// パドルの描画
		DrawBox(paddleX, paddleY, paddleX + PADDLE_WIDTH, paddleY + PADDLE_HEIGHT, GetColor(255, 255, 255), TRUE);

		// ボールの描画
		DrawBox(ballX, ballY, ballX + BALL_SIZE, ballY + BALL_SIZE, GetColor(255, 255, 255), TRUE);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
