#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// 変数の宣言
	int key;
	int x;
	int y;

	// 変数の初期化
	key = 0;
	x = 0;
	y = 0;

	// 画面モードのセット
	SetGraphMode(1280, 720, 32);

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
			y = y - 10;
		}

		// 下を押していたら下に進む
		if (key & PAD_INPUT_DOWN)
		{
			y = y + 10;
		}

		// 画面を初期化する
		ClearDrawScreen();

		// ----- ゲームの描画処理 ----- //

		// パドルの描画
		DrawBox(x, y, x + 32, y + 64, GetColor(255, 255, 255), TRUE);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
