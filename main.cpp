#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
const char kWindowTitle[] = "学籍番号";

enum EaseType {
	kNormal,
	kEase,
	kEaseOut,
	kEaseIn,
};

struct Vector2
{
	float x; 
	float y;
};

Vector2 Lerp(float t, const Vector2& a, const Vector2& b) {
	return { (1.0f - t) * a.x + t * b.x,(1.0f - t) * a.y + t * b.y };
}

float Ease(float t) {
	return -(cosf(M_PI * t) - 1.0f) / 2.0f;
}

float EaseOut(float t) {
	return 1.0f - cosf((t * (float)M_PI) / 2.0f);
}

float EaseIn(float t) {
	return sinf((t * (float)M_PI) / 2.0f);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	const int kBallNum = 4;
	Vector2 pos[kBallNum] = {};

	float t = 0.0f;
	float tspeed = 0.01f;

	Vector2 start[kBallNum] = {};
	Vector2 end[kBallNum] = {};

	for (int i = 0; i < kBallNum; i++) {
		pos[i] = { 0,0 };
		start[i] = { 50.0f, 144.0f + i * 144.0f };
		end[i] = { 1230.0f, 144.0f+ i * 144.0f };
	}



	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		t += tspeed;
		if (t >= 1.0f) {
			t = 0.0f;
		}

		pos[kNormal] = Lerp(t, start[kNormal], end[kNormal]);
		pos[kEase] = Lerp(Ease(t), start[kEase], end[kEase]);
		pos[kEaseOut] = Lerp(EaseOut(t), start[kEaseOut], end[kEaseOut]);
		pos[kEaseIn] = Lerp(EaseIn(t), start[kEaseIn], end[kEaseIn]);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (const auto& it : pos) {
			Novice::DrawEllipse((int)it.x, (int)it.y, 50, 50, 0.0f, RED, kFillModeSolid);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
