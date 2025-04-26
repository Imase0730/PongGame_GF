#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// ----- 定数宣言 ----- //
	
	// シーンの列挙子の定義
	enum class Scene
	{
		Title,
		GamePlay,
		GameOver,
	};

	// タイトルの文字列
	const wchar_t TITLE[] = L"Pong Game";

	// 画面のサイズ
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	// 文字のサイズ
	const int FONT_SIZE = 50;

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
	const int BALL_START_X = SCREEN_WIDTH - BALL_SIZE;
	const int BALL_START_Y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

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
	int score;
	Scene scene;

	// ----- 変数の初期化 ----- //
	key = 0;
	paddleX = PADDLE_START_X;
	paddleY = PADDLE_START_Y;
	ballX = BALL_START_X;
	ballY = BALL_START_Y;
	ballVelocityX = BALL_SPEED_X;
	ballVelocityY = BALL_SPEED_Y;
	score = 0;
	scene = Scene::Title;

	// 画面モードのセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// ウインドウのタイトルを変更する
	SetMainWindowText(TITLE);

	// ウインドウモードへ変更
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// 文字のサイズを変更する
	SetFontSize(FONT_SIZE);

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ----- ゲームの更新処理 ----- //

		// キー入力取得
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		///////////////////////////////////////////////////////////////////////////////////
		// タイトルだったら
		if (scene == Scene::Title)
		{
		}

		// ゲーム中だったら
		if (scene == Scene::GamePlay)
		{
		}

		// ゲームオーバーだったら
		if (scene == Scene::GameOver)
		{
		}
		///////////////////////////////////////////////////////////////////////////////////


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

		// パドルとボールの衝突判定
		if ( (ballVelocityX < 0)	// ボールが左方向へ移動しているなら
		  && ((paddleX <= ballX + BALL_SIZE) && (ballX <= paddleX + PADDLE_WIDTH))	// X軸の交差判定
		  && ((paddleY <= ballY + BALL_SIZE) && (ballY <= paddleY + PADDLE_HEIGHT))	// Y軸の交差判定
		   )
		{
			ballVelocityX = -ballVelocityX;
			// 得点を加算
			score++;
		}

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

		///////////////////////////////////////////////////////////////////////////////////
		// タイトルだったら
		if (scene == Scene::Title)
		{
			// タイトルの表示
			DrawFormatString(100, 100, GetColor(255, 255, 255), TITLE);
		}
		
		// ゲーム中だったら
		if (scene == Scene::GamePlay)
		{
		}

		// ゲームオーバーだったら
		if (scene == Scene::GameOver)
		{
		}
		///////////////////////////////////////////////////////////////////////////////////


		// パドルの描画
		DrawBox(paddleX, paddleY, paddleX + PADDLE_WIDTH, paddleY + PADDLE_HEIGHT, GetColor(255, 255, 255), TRUE);

		// ボールの描画
		DrawBox(ballX, ballY, ballX + BALL_SIZE, ballY + BALL_SIZE, GetColor(255, 255, 255), TRUE);

		// 得点の表示
		DrawFormatString(0, 0, GetColor(255, 255, 255), L"SCORE:%d", score);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
