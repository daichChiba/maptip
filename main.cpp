#include <Novice.h>
#include"Vector2.h"
#define _USE_MATH_DEFINES
#include <math.h>


const char kWindowTitle[] = "LC1D_17_チバ_ダイチ";

const int mapY = 25;
const int mapX = 25;

const int blockSize = 32;


struct IntVector2 {
	int x;
	int y;
};


struct Corners {
	IntVector2 LeftTop;
	IntVector2 RightTop;
	IntVector2 LeftBottom;
	IntVector2 RightBottom;
};


struct Player {
	Vector2 pos;
	Vector2 verocity;
	Vector2 direction;
	float radius;
	int speed;
	Corners corners;
};

struct Map {
	int x;
	int y;
};




Corners PosUpDate(Vector2 pos, float radius, const int size, Vector2 velocity) {
	Corners returnCorners = { 0 };

	returnCorners.LeftTop.x = static_cast<int>(((pos.x - (radius * 0.5f)) + velocity.x) / static_cast<float>(size));
	returnCorners.LeftTop.y = static_cast<int>(((pos.y - (radius * 0.5f)) + velocity.y) / static_cast<float>(size));
	returnCorners.RightTop.x = static_cast<int>(((pos.x + (radius * 0.5f) + velocity.x) - 1) / static_cast<float>(size));
	returnCorners.RightTop.y = static_cast<int>(((pos.y - (radius * 0.5f)) + velocity.y) / static_cast<float>(size));
	returnCorners.LeftBottom.x = static_cast<int>(((pos.x - (radius * 0.5f) + velocity.x)) / static_cast<float>(size));
	returnCorners.LeftBottom.y = static_cast<int>(((pos.y + (radius * 0.5f) + velocity.y) - 1) / static_cast<float>(size));
	returnCorners.RightBottom.x = static_cast<int>(((pos.x + (radius * 0.5f) + velocity.x) - 1) / static_cast<float>(size));
	returnCorners.RightBottom.y = static_cast<int>(((pos.y + (radius * 0.5f) + velocity.y) - 1) / static_cast<float>(size));

	return returnCorners;
}



//当たっているかどうか
bool HitBox(int** map, Corners corners, char* keys) {

	if (keys[DIK_D]) {
		if (map[corners.RightTop.y][corners.RightTop.x] == 1 ||
			map[corners.RightBottom.y][corners.RightBottom.x] == 1) {
			return true;
		} else {
			return false;
		}
	}
	if (keys[DIK_A]) {
		if (map[corners.LeftTop.y][corners.LeftTop.x] == 1 ||
			map[corners.LeftBottom.y][corners.LeftBottom.x] == 1) {
			return true;
		} else {
			return false;
		}
	}
	if (keys[DIK_W]) {
		if (map[corners.RightTop.y][corners.RightTop.x] == 1 ||
			map[corners.LeftTop.y][corners.LeftTop.x] == 1) {
			return true;
		} else {
			return false;
		}
	}
	if (keys[DIK_S]) {
		if (map[corners.RightBottom.y][corners.RightBottom.x] == 1 ||
			map[corners.LeftBottom.y][corners.LeftBottom.x] == 1) {
			return true;
		} else {
			return false;
		}
	}
	//if (map[corners.LeftTop.y][corners.LeftTop.x] == 1 ||
	//	map[corners.RightTop.y][corners.RightTop.x] == 1 ||
	//	map[corners.LeftBottom.y][corners.LeftBottom.x] == 1 ||
	//	map[corners.RightBottom.y][corners.RightBottom.x] == 1){
	//	return true;
	//} else{
	//	return false;
	//}

	return false;
}


//マップチップのどこにいるかわかる関数
IntVector2 MapHitBox(Corners corners, int** Map, int returnMapA) {
	if (Map[corners.LeftTop.y][corners.LeftTop.x] == returnMapA) {
		return corners.LeftTop;
	}
	if (Map[corners.RightTop.y][corners.RightTop.x] == returnMapA) {
		return corners.RightTop;
	}
	if (Map[corners.LeftBottom.y][corners.LeftBottom.x] == returnMapA) {
		return corners.LeftBottom;
	}
	if (Map[corners.RightBottom.y][corners.RightBottom.x] == returnMapA) {
		return corners.RightBottom;
	}

	IntVector2 returnMapB = {};
	return returnMapB;
}



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 800, 864);
	Player player{
		Vector2(40.0f,40.0f),
		Vector2(0.0f,0.0f),
		Vector2(0.0f,0.0f),
		16.0f,//
		4,
		{}
	};

	//Map playerMap{
	//	1,1
	//};

	int map[mapY][mapX]{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int* pMap[mapY] = { 0 };
	for (int i = 0; i < mapY; i++) {
		pMap[i] = map[i];
	}
	int** ppMap = pMap;

	Vector2 leftTop = { 0 };
	Vector2 rightTop = { 0 };
	Vector2 leftBottom = { 0 };
	Vector2 rightBottom = { 0 };

	//仮移動した後の座標
	Vector2 tmpPos = {};

	IntVector2 hitMapKeep = {};



	int BlockGH = Novice::LoadTexture("./block.png");

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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



		//向きの初期化
		player.direction.x = 0.0f;
		player.direction.y = 0.0f;

		player.verocity.x = 0;
		player.verocity.y = 0;

		//向きを決める
		if (keys[DIK_D]) {
			player.direction.x += 1.0f;

			player.verocity.x = player.direction.x * float(player.speed);
			tmpPos = player.pos;
			tmpPos.x += player.verocity.x;


			//当たり判定を取るための四辺の変数を代入する
			player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
			//当たっているかどうか
			if (HitBox(ppMap, player.corners, keys)) {
				//hitMapKeep = MapHitBox(player.corners, ppMap, 1);
				hitMapKeep.x = static_cast<int>(floor(tmpPos.x));
				if (player.pos.x < static_cast<float>(hitMapKeep.x * blockSize + blockSize * 0.5f)) {
					while (true) {
						tmpPos.x -= 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.x = tmpPos.x;
							break;
						}
					}
				} else {
					while (true) {
						tmpPos.x += 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.x = tmpPos.x;
							break;
						}
					}
				}
			} else {
				player.pos.x = tmpPos.x;
			}

		}

		if (keys[DIK_A]) {
			player.direction.x -= 1.0f;

			player.verocity.x = player.direction.x * float(player.speed);
			tmpPos = player.pos;
			tmpPos.x += player.verocity.x;


			//当たり判定を取るための四辺の変数を代入する
			player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
			if (HitBox(ppMap, player.corners, keys)) {
				hitMapKeep = MapHitBox(player.corners, ppMap, 1);
				//hitMapKeep.x = static_cast<int>(floor(tmpPos.x));
				if (player.pos.x < static_cast<float>(hitMapKeep.x * blockSize + blockSize * 0.5f)) {
					while (true) {
						tmpPos.x -= 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.x = tmpPos.x;
							break;
						}
					}
				} else {
					while (true) {
						tmpPos.x += 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.x = tmpPos.x;
							break;
						}
					}
				}
			} else {
				player.pos.x = tmpPos.x;
			}
		}

		if (keys[DIK_W]) {
			player.direction.y -= 1.0f;
			player.verocity.y = player.direction.y * float(player.speed);
			tmpPos = player.pos;
			tmpPos.y += player.verocity.y;


			//当たり判定を取るための四辺の変数を代入する
			player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);

			if (HitBox(ppMap, player.corners, keys)) {
				hitMapKeep = MapHitBox(player.corners, ppMap, 1);
				//hitMapKeep.y = static_cast<int>(floor(tmpPos.y));
				if (player.pos.y < static_cast<float>(hitMapKeep.y * blockSize + blockSize * 0.5f)) {
					while (true) {
						tmpPos.y += 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.y = tmpPos.y;
							break;
						}
					}
				} else {
					while (true) {
						tmpPos.y -= 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.y = tmpPos.y;
							break;
						}
					}
				}
			} else {
				player.pos.y = tmpPos.y;
			}
		}

		if (keys[DIK_S]) {
			player.direction.y += 1.0f;
			player.verocity.y = player.direction.y * float(player.speed);
			tmpPos = player.pos;
			tmpPos.y += player.verocity.y;


			//当たり判定を取るための四辺の変数を代入する
			player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);

			if (HitBox(ppMap, player.corners, keys)) {
				hitMapKeep = MapHitBox(player.corners, ppMap, 1);
				//hitMapKeep.y = static_cast<int>(floor(tmpPos.y));
				if (player.pos.y < static_cast<float>(hitMapKeep.y * blockSize + blockSize * 0.5f)) {
					while (true) {
						tmpPos.y += 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.y = tmpPos.y;
							break;
						}
					}
				} else {
					while (true) {
						tmpPos.y -= 1;
						player.corners = PosUpDate(tmpPos, player.radius, blockSize, player.verocity);
						if (!HitBox(ppMap, player.corners, keys)) {
							player.pos.y = tmpPos.y;
							break;
						}
					}
				}
			} else {
				player.pos.y = tmpPos.y;
			}
		}

		////移動量の決定
		//player.verocity.x = player.direction.x * float(player.speed);
		//player.verocity.y = player.direction.y * float(player.speed);

		///*仮に移動させる
		//  playerの座標の代入をして
		//　仮に動いたｘの計算をする*/
		//tmpPos = player.pos;
		//tmpPos.x += player.verocity.x;

		////当たり判定を取るための四辺の変数を代入する
		//player.corners = PosUpDate(tmpPos, player.radius, blockSize);

		/*
		 仮に動かしたyの座標の値を小数点第一位を切り捨てて代入する。
		 //上向きだった場合
			 while(true){
				 当たった向きの+の方向に仮に動かしたyの座標の値を少しずつずらしていく
				 仮にずらした座標の四辺のマップチップの座標を更新する
					 if(当たっているかどうか調べて当たっていない場合){
						 playerを移動させる
						 breakする
					 }
			 }

		//下向きだった場合
			 while(true){
				 当たった向きの-の方向に仮に動かしたyの座標の値を少しずつずらしていく
				 仮にずらした座標の四辺のマップチップの座標を更新する
					 if(当たっているかどうか調べて当たっていない場合){
						 playerを移動させる
						 breakする
					 }
			 }
		*/

		//if (HitBox(ppMap, player.corners)) {
		//	hitMapKeep = MapHitBox(player.corners, ppMap, 1);
		//	hitMapKeep.x = static_cast<int>(floor(tmpPos.x));
		//	if (player.pos.x < static_cast<float>(hitMapKeep.x * blockSize + blockSize * 0.5f)) {
		//		while (true) {
		//			hitMapKeep.x -= 1;
		//			player.corners = PosUpDate(tmpPos, player.radius, blockSize);
		//			if (!HitBox(ppMap, player.corners)) {
		//				player.pos.x = tmpPos.x;
		//				break;
		//			}
		//		}
		//	} else {
		//		while (true) {
		//			hitMapKeep.x += 1;
		//			player.corners = PosUpDate(tmpPos, player.radius, blockSize);
		//			if (!HitBox(ppMap, player.corners)) {
		//				player.pos.x = tmpPos.x;
		//				break;
		//			}
		//		}
		//	}
		//}


		//if (HitBox(ppMap, player.corners)) {
		//	//当たった場所が左か右か調べてその場所の値を出す
		//	hitMapKeep = MapHitBox(player.corners, ppMap, 1);
		//	//当たった場所の壁の沿いに合わせてピッタリに返す
		//	if (player.pos.x < static_cast<float>(hitMapKeep.x * blockSize + blockSize * 0.5f)) {
		//		//右沿いだった場合左にピッタリに返す。
		//		player.pos.x = static_cast<float>(hitMapKeep.x * blockSize) - player.radius * 0.5f;
		//	} else {
		//		//左沿いだった場合右にピッタリに返す
		//		player.pos.x = static_cast<float>(hitMapKeep.x * blockSize) + blockSize + player.radius * 0.5f;
		//	}
		//} else {
		//	player.pos = tmpPos;
		//}



		//tmpPos.y += player.verocity.y;
		////当たり判定を取るための四辺の変数を代入する
		//player.corners = PosUpDate(tmpPos, player.radius, blockSize);

		//if (HitBox(ppMap, player.corners)) {
		//	hitMapKeep = MapHitBox(player.corners, ppMap, 1);
		//	hitMapKeep.y = static_cast<int>(floor(tmpPos.y));
		//	if (player.pos.y < static_cast<float>(hitMapKeep.y * blockSize + blockSize * 0.5f)) {
		//		while (true) {
		//			hitMapKeep.y += 1;
		//			player.corners = PosUpDate(tmpPos, player.radius, blockSize);
		//			if (!HitBox(ppMap, player.corners)) {
		//				player.pos.y = tmpPos.y;
		//				break;
		//			}
		//		}
		//	} else {
		//		while (true) {
		//			hitMapKeep.y -= 1;
		//			player.corners = PosUpDate(tmpPos, player.radius, blockSize);
		//			if (!HitBox(ppMap, player.corners)) {
		//				player.pos.y = tmpPos.y;
		//				break;
		//			}
		//		}
		//	}
		//}


		//if (HitBox(ppMap, player.corners)) {
		//	//当たった場所が左か右か調べてその場所の値を出す
		//	hitMapKeep = MapHitBox(player.corners, ppMap, 1);
		//	//当たった場所の壁の沿いに合わせてピッタリに返す
		//	if (player.pos.y < static_cast<float>(hitMapKeep.y * blockSize + blockSize * 0.5f)-1) {
		//		//右沿いだった場合左にピッタリに返す。
		//		player.pos.y = static_cast<float>(hitMapKeep.y * blockSize) - player.radius * 0.5f;
		//	} else {
		//		//左沿いだった場合右にピッタリに返す
		//		player.pos.y = static_cast<float>(hitMapKeep.y * blockSize) + blockSize + player.radius * 0.5f;
		//	}
		//} else {
		//	player.pos = tmpPos;
		//}




		//leftTop.x = ((tmpPos.x - (player.radius * 0.5f)) / blockSize);
		//leftTop.y = ((tmpPos.y - (player.radius * 0.5f)) / blockSize);
		//rightTop.x = ((tmpPos.x + (player.radius * 0.5f) - 1) / blockSize);
		//rightTop.y = ((tmpPos.y - (player.radius * 0.5f)) / blockSize);
		//leftBottom.x = ((tmpPos.x - (player.radius * 0.5f)) / blockSize);
		//leftBottom.y = ((tmpPos.y + (player.radius * 0.5f) - 1) / blockSize);
		//rightBottom.x = ((tmpPos.x + (player.radius * 0.5f) - 1) / blockSize);
		//rightBottom.y = ((tmpPos.y + (player.radius * 0.5f) - 1) / blockSize);

		//playerMap.x = int((player.pos.x - (player.size.x * 0.5f)) / blockSize.x);
		//playerMap.y = int((player.pos.y - (player.size.y * 0.5f)) / blockSize.y);





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(
			0, 0,
			800, 800,
			0.0f, BLACK, kFillModeSolid
		);

		Novice::DrawBox(
			(int)(player.pos.x - (player.radius * 0.5f)), (int)(player.pos.y - (player.radius * 0.5f)),
			(int)player.radius, (int)player.radius,
			0.0f,
			RED,
			kFillModeSolid
		);
		for (int X = 0; X < 25; X++) {
			for (int y = 0; y < 25; y++) {
				if (map[X][y] == 1) {
					Novice::DrawSprite(
						blockSize * y, blockSize * X,
						BlockGH,
						1.0f, 1.0f,
						0.0f, 0xFFFFFFFF);
				}


			}

		}
		Novice::ScreenPrintf(32, 800, "player.corners.LefeTop=[%d][%d]", player.corners.LeftTop.x, player.corners.LeftTop.y);
		Novice::ScreenPrintf(400, 800, "player.corners.RightTop=[%d][%d]", player.corners.RightTop.x, player.corners.RightTop.y);
		Novice::ScreenPrintf(32, 816, "player.corners.LeftBottom=[%d][%d]", player.corners.LeftBottom.x, player.corners.LeftBottom.y);
		Novice::ScreenPrintf(400, 816, "player.corners.RightBottom=[%d][%d]", player.corners.RightBottom.x, player.corners.RightBottom.y);
		Novice::ScreenPrintf(32, 832, "player.pos.x=%d", static_cast<int>(player.pos.x + player.verocity.x) / blockSize);
		Novice::ScreenPrintf(400, 832, "player.pos.y=%d", static_cast<int>(player.pos.y + player.verocity.y) / blockSize);



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
