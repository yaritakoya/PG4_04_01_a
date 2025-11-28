#include "StageScene.h"
#include <Novice.h>

void StageScene::Initialize() {
	player = {
			0.0f,200.0f,
			0.0f,0.0f,
			0.0f,0.0f,
			6.0f,32.0f,10,true,0,60
	};

	boss = {
		1279.0f,300.0f,
		0.0f,0.0f,
		3.0f,128.0f,
		0,0,0,false,100.0f
	};

	attachment = {
		64.0f,64.0f,
		0.0f,0.0f,
		1.0f,60,0
	};

	enemy = {
		1000.0f,200.0f,
		0.0f,0.0f,
		0.0f,0.0f,32.0f,6.0f,1,true,false,60.0f
	};

	bullet[32];
	for (int i = 0; i < 32; i++) {
		bullet[i].pos.x = -128.0f;
		bullet[i].pos.y = -128.0f;
		bullet[i].width = 8.0f;
		bullet[i].height = 16.0f;
		bullet[i].radius = 16.0f;
		bullet[i].speed = 10.0f;
		bullet[i].isShoot = false;
	}

	enemyBullet[32];
	for (int i = 0; i < 32; i++) {
		enemyBullet[i].pos.x = -128.0f;
		enemyBullet[i].pos.y = -128.0f;
		enemyBullet[i].width = 8.0f;
		enemyBullet[i].height = 16.0f;
		enemyBullet[i].radius = 32.0f;
		enemyBullet[i].speed = 5.0f;
		enemyBullet[i].isShoot = false;
	}

	attachmentBullet[32];
	for (int i = 0; i < 32; i++) {
		attachmentBullet[i].pos.x = -128.0f;
		attachmentBullet[i].pos.y = -128.0f;
		attachmentBullet[i].width = 8.0f;
		attachmentBullet[i].height = 16.0f;
		attachmentBullet[i].radius = 16.0f;
		attachmentBullet[i].speed = 12.0f;
		attachmentBullet[i].isShoot = false;
	}

	bossBullet[32];
	for (int i = 0; i < 32; i++) {
		bossBullet[i].pos.x = -128.0f;
		bossBullet[i].pos.y = -128.0f;
		bossBullet[i].width = 8.0f;
		bossBullet[i].height = 16.0f;
		bossBullet[i].radius = 32.0f;
		bossBullet[i].speed = 4.0f;
		bossBullet[i].isShoot = false;
	}

	bossBulletRight[32];
	for (int i = 0; i < 32; i++) {
		bossBulletRight[i].pos.x = -128.0f;
		bossBulletRight[i].pos.y = -128.0f;
		bossBulletRight[i].width = 8.0f;
		bossBulletRight[i].height = 16.0f;
		bossBulletRight[i].radius = 16.0f;
		bossBulletRight[i].speed = 4.0f;
		bossBulletRight[i].isShoot = false;
	}

	bossBulletLeft[32];
	for (int i = 0; i < 32; i++) {
		bossBulletLeft[i].pos.x = -128.0f;
		bossBulletLeft[i].pos.y = -128.0f;
		bossBulletLeft[i].width = 8.0f;
		bossBulletLeft[i].height = 16.0f;
		bossBulletLeft[i].radius = 16.0f;
		bossBulletLeft[i].speed = 4.0f;
		bossBulletLeft[i].isShoot = false;
	}
	hp[3];
	for (int i = 0; i < 3; i++) {
		hp[i].pos.x = 50.0f;
		hp[i].pos.y = 30.0f;
	}
	backgroundPosX = 0.0f;
	lenght = 0.0f;
	score = 0;
	bossCount = 0;
	backgroundTimer = 30;
}

void StageScene::Update(char* keys, char* preKeys) {

	// スペースキーで次のシーン（クリア）へ
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		sceneNo = CLEAR;
	}

	///
	/// ↓更新処理ここから
	///
	
#pragma region AL1のゲームシーン処理

	if (scene == GAMESCENE) {

#pragma region 自機の移動
		player.move.x = 0.0f;
		player.move.y = 0.0f;
		if (keys[DIK_UP]) {
			player.move.y -= 1.0f;
			if (player.pos.y < 100) {
				player.move.y += 1.0f;
			}
		}
		if (keys[DIK_LEFT]) {
			player.move.x -= 1.0f;
			if (player.pos.x < 0) {
				player.move.x += 1.0f;
			}
		}
		if (keys[DIK_DOWN]) {
			player.move.y += 1.0f;
			if (player.pos.y > 720 - 128) {
				player.move.y -= 1.0f;
			}
		}
		if (keys[DIK_RIGHT]) {
			player.move.x += 1.0f;
			if (player.pos.x > 1280 / 2 - 128) {
				player.move.x -= 1.0f;
			}
		}
		lenght = sqrtf(player.move.x * player.move.x + player.move.y * player.move.y);
		if (lenght != 0.0f) {
			player.move.x /= lenght;
			player.move.y /= lenght;
		}
		player.pos.x += player.move.x * player.speed;
		player.pos.y += player.move.y * player.speed;
#pragma endregion

#pragma region 自機の弾の発射
		// 弾の発射処理
		if (keys[DIK_Z]) {

			// 発射間隔の調整用クールタイムの計算
			if (player.shootCoolTime > 0) {
				player.shootCoolTime--;
			} else {
				player.shootCoolTime = 30;
			}

			// i番目の弾が撃たれていなかったら発射する
			if (player.shootCoolTime <= 0) {
				for (int i = 0; i < 32; i++) {
					if (!bullet[i].isShoot) {
						bullet[i].isShoot = true;
						bullet[i].pos.x = player.pos.x;
						bullet[i].pos.y = player.pos.y;
						break;
					}
				}
			}
		}

		// 弾道計算
		for (int i = 0; i < 32; i++) {
			if (bullet[i].isShoot) {
				// 右方向に進ませる
				bullet[i].pos.x += bullet[i].speed;

				// 画面外に出たら発射フラグをFalseに変更する
				if (bullet[i].pos.x >= 1280 * 0.75f + player.pos.x) {
					bullet[i].isShoot = false;
					bullet[i].pos.x = 1280 + 64;
				}
			}
		}
#pragma endregion

#pragma region 自機の当たり判定
		for (int i = 0; i < 32; i++) {
			EBtPX = (player.pos.x + 64 - enemyBullet[i].pos.x);
			EBtPY = (player.pos.y - enemyBullet[i].pos.y);
			EBtPdistance = sqrtf(EBtPX * EBtPX + EBtPY * EBtPY);
			if (EBtPdistance < player.radius + enemyBullet[i].radius * 0.4f) {
				player.isAlive = 0;
				enemyBullet[i].pos.x = -128;
			}

			//bossBullet to player
			BBtPX = (bossBullet[i].pos.x - player.pos.x + 64);
			BBtPY = (bossBullet[i].pos.y - player.pos.y);
			BBtPdistance = sqrtf(BBtPX * BBtPX + BBtPY * BBtPY);
			if (BBtPdistance < player.radius + bossBullet[i].radius * 0.4f) {
				player.isAlive = false;
				bossBullet[i].pos.x = -128;
			}
			//bossBulletRight to player
			BBRtPX = (bossBulletRight[i].pos.x - player.pos.x + 64);
			BBRtPY = (bossBulletRight[i].pos.y - player.pos.y);
			BBRtPdistance = sqrtf(BBRtPX * BBRtPX + BBRtPY * BBRtPY);
			if (BBRtPdistance < player.radius + bossBulletRight[i].radius * 0.4f) {
				player.isAlive = false;
				bossBulletRight[i].pos.x = -128;
			}
			//bossBulletLeft to player
			BBLtPX = (bossBulletLeft[i].pos.x - player.pos.x + 64);
			BBLtPY = (bossBulletLeft[i].pos.y - player.pos.y);
			BBLtPdistance = sqrtf(BBLtPX * BBLtPX + BBLtPY * BBLtPY);
			if (BBLtPdistance < player.radius + bossBulletLeft[i].radius * 0.4f) {
				player.isAlive = false;
				bossBulletLeft[i].pos.x = -128;
			}
			if (player.isAlive == 0) {
				player.deathCount += 0.5f;
				player.respawnTimer -= 0.5f;
				if (player.respawnTimer == 0 && player.deathCount <= 120) {
					player.respawnTimer = 60;
					player.isAlive = true;
				}
			}
			if (player.deathCount >= 180) {
				backgroundTimer--;
			}
		}
#pragma endregion

#pragma region アタッチメントの発射
		if (keys[DIK_X] && preKeys[DIK_X] == 0 && player.pos.x + 64 >= player.pos.x + fabs(attachment.pos.x)) {
			attachment.pos.x += 300;
		}
		if (player.pos.x + 64 < player.pos.x + fabs(attachment.pos.x)) {
			attachment.pos.x -= 2;
		}
#pragma endregion

#pragma region アタッチメントの射撃
		// 発射間隔の調整用クールタイムの計算
		if (attachment.shootCoolTime > 0) {
			attachment.shootCoolTime--;
		} else {
			attachment.shootCoolTime = 20;
		}

		// i番目の弾が撃たれていなかったら発射する
		if (attachment.shootCoolTime <= 0) {
			for (int i = 0; i < 32; i++) {
				if (!attachmentBullet[i].isShoot) {
					attachmentBullet[i].isShoot = true;
					attachmentBullet[i].pos.x = player.pos.x + attachment.pos.x;
					attachmentBullet[i].pos.y = player.pos.y;
					break;
				}
			}
		}

		// 弾道計算
		for (int i = 0; i < 32; i++) {
			if (attachmentBullet[i].isShoot) {
				// 右方向に進ませる
				attachmentBullet[i].pos.x += attachmentBullet[i].speed;

				// 画面外に出たら発射フラグをFalseに変更する
				if (attachmentBullet[i].pos.x >= 1280 * 0.5f + attachment.pos.x + player.pos.x) {
					attachmentBullet[i].isShoot = false;
					attachmentBullet[i].pos.x = 1280 + 64;
				}
			}
		}
#pragma endregion

#pragma region 敵の移動
		unsigned int currentTime = static_cast<int>(time(nullptr));
		srand(currentTime);
		if (enemy.isAlive != 0) {
			enemy.pos.x -= player.speed * 0.2f;
			enemy.pos.y += enemy.speed;
		}
		if (enemy.isAlive == 0) {
			enemy.pos.y += 1;
		}
		if (enemy.pos.x <= 0 || enemy.isAlive == 0) {
			enemy.deathCount--;
			if (enemy.deathCount < 0) {
				enemy.pos.x = 1280;
				enemy.isAlive = true;
				enemy.deathCount = 60;
				for (int i = 0; i < 10; i++) {
					enemy.pos.y = rand() % 520 + 100.0f;
				}
			}
		}
		if (enemy.pos.y < 100 || enemy.pos.y > 720 - 96) {
			enemy.speed = -enemy.speed;
		}
		if (bossCount >= 10) {
			enemy.pos.y = -720;
			for (int i = 0; i < 32; i++) {
				enemyBullet[i].pos.y = -720;
			}
		}
#pragma endregion

#pragma region 敵の弾の発射
		// 弾の発射処理
		if (enemy.pos.x < 1280 && enemy.pos.y < 720 && enemy.pos.x > 0 && enemy.pos.y > 0 && enemy.isAlive != 0) {

			// 発射間隔の調整用クールタイムの計算
			if (enemy.shootCoolTime > 0) {
				enemy.shootCoolTime--;
			} else {
				enemy.shootCoolTime = 30;
			}

			// i番目の弾が撃たれていなかったら発射する
			if (enemy.shootCoolTime <= 0) {
				for (int i = 0; i < 32; i++) {
					if (!enemyBullet[i].isShoot) {
						enemyBullet[i].isShoot = true;
						enemyBullet[i].pos.x = enemy.pos.x;
						enemyBullet[i].pos.y = enemy.pos.y;
						break;
					}
				}
			}
		}

		// 弾道計算
		for (int i = 0; i < 32; i++) {
			if (enemyBullet[i].isShoot) {
				// 左方向に進ませる
				enemyBullet[i].pos.x -= enemyBullet[i].speed;

				// 画面外に出たら発射フラグをFalseに変更する
				if (enemyBullet[i].pos.x <= -128) {
					enemyBullet[i].isShoot = false;
				}
			}
		}
#pragma endregion

#pragma region 敵機の当たり判定
		if (enemy.pos.x < 1280 - 64)
		{
			//自機の弾に当たった時death
			for (int i = 0; i < 32; i++) {
				PBtEX = (enemy.pos.x - bullet[i].pos.x);
				PBtEY = (enemy.pos.y - bullet[i].pos.y);
				PBtEdistance = sqrtf(PBtEX * PBtEX + PBtEY * PBtEY);
				if (PBtEdistance < enemy.radius + bullet[i].radius) {
					enemy.isAlive = 0;
				}
			}
			//サブ機の弾に当たった時death
			for (int i = 0; i < 32; i++) {
				ABtEX = (enemy.pos.x - attachmentBullet[i].pos.x);
				ABtEY = (enemy.pos.y - attachmentBullet[i].pos.y);
				ABtEdistance = sqrtf(ABtEX * ABtEX + ABtEY * ABtEY);
				if (ABtEdistance < enemy.radius + attachmentBullet[i].radius) {
					enemy.isAlive = 0;
				}
			}
			if (enemy.deathCount == 0) {
				bossCount += 2;
				score += 1000;
			}
		}
#pragma endregion

#pragma region ボスの移動
		if (bossCount >= 10) {
			boss.isAlive = true;
			if (boss.pos.y <= 244 || boss.pos.y >= 720 - 214) {
				boss.speed = -boss.speed;
			}
			if (boss.pos.x >= 1280 - 350 && boss.isAlive != 0) {
				boss.pos.x--;
			}
			if (boss.pos.x <= 1280 - 350 && boss.isAlive != 0) {
				boss.pos.y += boss.speed;
			}

		}
#pragma endregion

#pragma region ボスの当たり判定
		if (boss.pos.x <= 1280 - 350 && boss.isAlive != 0) {
			for (int i = 0; i < 32; i++) {
				PBtBX = (bullet[i].pos.x - boss.pos.x - 128);
				PBtBY = (bullet[i].pos.y - boss.pos.y);
				PBtBdistance = sqrtf(PBtBX * PBtBX + PBtBY * PBtBY);
				if (PBtBdistance < bullet[i].radius + boss.radius) {
					boss.hp -= 1.0f;
					bullet[i].pos.x = 1280 + 128;
				}
				ABtBX = (attachmentBullet[i].pos.x - boss.pos.x - 128);
				ABtBY = (attachmentBullet[i].pos.y - boss.pos.y);
				ABtBdistance = sqrtf(ABtBX * ABtBX + ABtBY * ABtBY);
				if (ABtBdistance < attachmentBullet[i].radius * 0.6f + boss.radius) {
					boss.hp -= 1.5f;
					attachmentBullet[i].pos.x = 1280 + 128;
				}
				if (boss.hp > 0) {
					boss.isAlive = 1;
				}
				if (boss.hp < 0) {
					boss.isAlive = 0;
					scene = GAMECLAER;
				}
			}
		}
#pragma endregion

#pragma region ボスの射撃
		if (boss.pos.x <= 1280 - 350 && boss.isAlive != 0) {
			////正面発射
				// 発射間隔の調整用クールタイムの計算
			if (boss.shootCoolTime > 0) {
				boss.shootCoolTime--;
			} else {
				boss.shootCoolTime = 60;
			}

			// i番目の弾が撃たれていなかったら発射する
			if (boss.shootCoolTime <= 0) {
				for (int i = 0; i < 32; i++) {
					if (!bossBullet[i].isShoot) {
						bossBullet[i].isShoot = true;
						bossBullet[i].pos.x = boss.pos.x + 128;
						bossBullet[i].pos.y = boss.pos.y - 128;
						break;
					}
				}
			}

			// 弾道計算
			for (int i = 0; i < 32; i++) {
				if (bossBullet[i].isShoot) {
					// 左方向に進ませる
					bossBullet[i].pos.x -= bossBullet[i].speed;

					// 画面外に出たら発射フラグをFalseに変更する
					if (bossBullet[i].pos.x <= -128 || bossBullet[i].pos.y <= 100) {
						bossBullet[i].isShoot = false;
					}
				}
			}

			//右発射
				// 発射間隔の調整用クールタイムの計算
			if (boss.shootCoolTimeRight > 0) {
				boss.shootCoolTimeRight--;
			} else {
				boss.shootCoolTimeRight = 60;
			}

			// i番目の弾が撃たれていなかったら発射する
			if (boss.shootCoolTimeRight <= 0) {
				for (int i = 0; i < 32; i++) {
					if (!bossBulletRight[i].isShoot) {
						bossBulletRight[i].isShoot = true;
						bossBulletRight[i].pos.x = boss.pos.x + 128;
						bossBulletRight[i].pos.y = boss.pos.y - 128;
						break;
					}
				}
			}

			// 弾道計算
			for (int i = 0; i < 32; i++) {
				if (bossBulletRight[i].isShoot) {
					// 左方向に進ませる
					bossBulletRight[i].pos.x -= bossBulletRight[i].speed;
					bossBulletRight[i].pos.y -= bossBulletRight[i].speed / 4;

					// 画面外に出たら発射フラグをFalseに変更する
					if (bossBulletRight[i].pos.x <= -128 || bossBulletRight[i].pos.y <= 32) {
						bossBulletRight[i].isShoot = false;
					}
				}
			}

			//左発射
				// 発射間隔の調整用クールタイムの計算
			if (boss.shootCoolTimeLeft > 0) {
				boss.shootCoolTimeLeft--;
			} else {
				boss.shootCoolTimeLeft = 60;
			}

			// i番目の弾が撃たれていなかったら発射する
			if (boss.shootCoolTimeLeft <= 0) {
				for (int i = 0; i < 32; i++) {
					if (!bossBulletLeft[i].isShoot) {
						bossBulletLeft[i].isShoot = true;
						bossBulletLeft[i].pos.x = boss.pos.x + 128;
						bossBulletLeft[i].pos.y = boss.pos.y - 128;
						break;
					}
				}
			}

			// 弾道計算
			for (int i = 0; i < 32; i++) {
				if (bossBulletLeft[i].isShoot) {
					// 左方向に進ませる
					bossBulletLeft[i].pos.x -= bossBulletLeft[i].speed;
					bossBulletLeft[i].pos.y += bossBulletLeft[i].speed / 4;

					// 画面外に出たら発射フラグをFalseに変更する
					if (bossBulletLeft[i].pos.x <= -128 || bossBulletLeft[i].pos.y <= 100) {
						bossBulletLeft[i].isShoot = false;
					}
				}
			}
		}
#pragma endregion 

#pragma region 背景の移動
		backgroundPosX--;
		if (backgroundPosX < -1280) {
			backgroundPosX = 0.0f;
		}
#pragma endregion
	
}

#pragma region 位置のリセット
	if (scene == COOLTIME) {
		player.isAlive = true;
		player.pos.x = 10;
		player.pos.y = 200;
		player.deathCount = 0;
		enemy.pos.x = 1180;
		enemy.pos.y = rand() % 520 + 100.0f;
		enemy.deathCount = 60;
		boss.pos.x = 1279;
		boss.hp = 100.0f;
		score = 0;
		bossCount = 0;
		backgroundTimer = 30;
		for (int i = 0; i < 32; i++) {
			enemyBullet[i].pos.x = -64 * 2;
			bossBullet[i].pos.x = -128 * 3;
			bossBulletRight[i].pos.x = -128 * 3;
			bossBulletLeft[i].pos.x = -128 * 3;
		}
	}
#pragma endregion

#pragma region シーンの切り替え
	switch (scene)
	{
	case TITLE:
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			scene = GAMESCENE;
		}
		break;
	case GAMESCENE:
		if (backgroundTimer <= 0) {
			scene = ENDTITLE;
		}
		break;
	case ENDTITLE:
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			scene = COOLTIME;
		}
		break;
	case GAMECLAER:
		if (boss.hp < 0 && keys[DIK_SPACE]) {
			scene = COOLTIME;
		}
		break;
	case COOLTIME:
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			scene = TITLE;
		}

	}
#pragma endregion

#pragma endregion

	///
	/// ↑更新処理ここまで
	///

}

void StageScene::Draw() {

	Novice::ScreenPrintf(0, 0, "Curernt Scene : Stage");
	Novice::ScreenPrintf(0, 30, "Push Space : Next Scene");

	///
	/// ↓描画処理ここから
	///

#pragma region AL1の描画シーン処理

	switch (scene)
	{
	case TITLE:
		Novice::DrawSprite(0, 0, background, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(240, 260, gameTitle, 3.5f, 3.5f, 0.0f, 0xBAA9A9FF);
		Novice::DrawSprite(400, 500, psts, 2.0f, 2.0f, 0.0f, 0xFFFFFFFF);
		break;
	case GAMESCENE:
		//背景
		Novice::DrawSprite(static_cast<int> (backgroundPosX), 0, background, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawSprite(static_cast<int> (backgroundPosX) + 1280, 0, background, 1, 1, 0.0f, 0xFFFFFFFF);
		Novice::DrawLine(1280 / 2, 0, 1280 / 2, 720, 0xFF0000FF);
		//画面上メニューバー
		Novice::DrawBox(0, 0, 1280, 100, 0.0f, 0xEEBB99FF, kFillModeSolid);
		//HP
		Novice::DrawSprite(10, 10, HP, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		for (int i = 0; i < 3; i++) {
			Novice::DrawBox(static_cast<int>(hp[i].pos.x) * i + 10, 30, 40, 20, 0.0f, 0x00FF00FF, kFillModeSolid);
			if (player.deathCount >= 60) {
				Novice::DrawBox(static_cast<int>(hp[2].pos.x) * 2 + 10, 30, 40, 20, 0.0f, 0xFF0000FF, kFillModeSolid);
			}
			if (player.deathCount >= 120) {
				Novice::DrawBox(static_cast<int>(hp[1].pos.x) * 1 + 10, 30, 40, 20, 0.0f, 0xFF0000FF, kFillModeSolid);
			}
			if (player.deathCount >= 180) {
				Novice::DrawBox(static_cast<int>(hp[0].pos.x) * 0 + 10, 30, 40, 20, 0.0f, 0xFF0000FF, kFillModeSolid);
			}
		}
		//サブ機の弾
		for (int i = 0; i < 32; i++) {
			if (attachmentBullet[i].isShoot) {
				Novice::DrawSprite(
					static_cast<int>(attachmentBullet[i].pos.x + 64),
					static_cast<int>(attachmentBullet[i].pos.y + attachmentBullet[i].height * 3.0f),
					attachmentTama, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				/*Novice::DrawEllipse(
					static_cast<int>(attachmentBullet[i].pos.x + 64+16),static_cast<int>(attachmentBullet[i].pos.y + attachmentBullet[i].height * 3.0f+16),
					static_cast<int>(attachmentBullet[i].radius),static_cast<int>(attachmentBullet[i].radius),0.0f, 0xFFFFFFFF,kFillModeWireFrame);*/
			}
		}
		//サブ機
		Novice::DrawSprite(static_cast<int>(player.pos.x + attachment.pos.x * 1.75f), static_cast<int>(player.pos.y + attachment.pos.y * 0.5f),
			graphAttachment, 1, 1, 0.0f, 0xFFFFFFFF);
		//自機弾
		for (int i = 0; i < 32; i++) {
			if (bullet[i].isShoot) {
				Novice::DrawSprite(
					static_cast<int>(bullet[i].pos.x + 128),
					static_cast<int>(bullet[i].pos.y + bullet[i].height * 2.0f),
					tama, 0.6f, 0.6f, 0.0f, 0xFFFFFFFF);
			}
		}
		if (player.isAlive != 0) {
			//自機
			Novice::DrawSprite(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
				ziki, 1, 1, 0.0f, 0xFFFFFFFF);
			//当たり判定
			/*Novice::DrawEllipse(static_cast<int>(player.pos.x + 64), static_cast<int>(player.pos.y + 64),
				static_cast<int>(player.radius), static_cast<int>(player.radius), 0.0f, 0xFFFFFF32, kFillModeWireFrame);*/
		}
		//ザコ敵
		if (bossCount < 10) {
			//ザコ敵の弾
			for (int i = 0; i < 32; i++) {
				if (enemyBullet[i].isShoot) {
					Novice::DrawSprite(
						static_cast<int>(enemyBullet[i].pos.x),
						static_cast<int>(enemyBullet[i].pos.y + enemyBullet[i].height * 2.0f),
						tama, 0.4f, 0.4f, 0.0f, 0x00FFFFFF);
				}
			}
			//ザコ敵
			if (enemy.isAlive != 0) {
				Novice::DrawSprite(static_cast<int>(enemy.pos.x), static_cast<int>(enemy.pos.y),
					teki, 0.8f, 0.8f, 0.0f, 0xFFFFFFFF);
				//当たり判定
				/*Novice::DrawEllipse(static_cast<int>(enemy.pos.x + 64 * 0.8f), static_cast<int>(enemy.pos.y + 64 * 0.8f),
					static_cast<int>(enemy.radius * 0.8f), static_cast<int>(enemy.radius * 0.8f), 0.0f, 0xFFFFFF32, kFillModeWireFrame);*/
			}
			if (enemy.isAlive == 0) {
				Novice::DrawSprite(static_cast<int>(enemy.pos.x), static_cast<int>(enemy.pos.y),
					tekiDeath, 0.8f, 0.8f, 0.0f, 0xFFFFFFFF);
			}
		}

		//ボスの弾
		for (int i = 0; i < 32; i++) {
			if (bossBullet[i].isShoot) {
				//正面
				Novice::DrawSprite(
					static_cast<int>(bossBullet[i].pos.x + 128),
					static_cast<int>(bossBullet[i].pos.y + 64),
					tama, 0.4f, 0.4f, 0.0f, 0xFFFF00FF);
			}
			//斜め上
			if (bossBulletRight[i].isShoot) {
				Novice::DrawSprite(
					static_cast<int>(bossBulletRight[i].pos.x + 128),
					static_cast<int>(bossBulletRight[i].pos.y + 64),
					tama, 0.4f, 0.4f, 0.0f, 0xFFFF00FF);
			}
			//斜め下
			if (bossBulletLeft[i].isShoot) {
				Novice::DrawSprite(
					static_cast<int>(bossBulletLeft[i].pos.x + 128),
					static_cast<int>(bossBulletLeft[i].pos.y + 64),
					tama, 0.4f, 0.4f, 0.0f, 0xFFFF00FF);
			}
		}
		//ボス
		if (boss.isAlive != 0) {
			Novice::DrawSprite(static_cast<int>(boss.pos.x), static_cast<int>(boss.pos.y - 156), bossHandle, 3.0f, 3.0f, 0.0f, 0xFFFFFFFF);
		}
		//ボスのHP
		if (boss.pos.x <= 1280 - 350 && boss.isAlive != 0) {
			Novice::DrawBox(1000, 10, 100 * 2, 30, 0.0f, 0x00FF00FF, kFillModeSolid);
			Novice::DrawBox(1000, 10, static_cast<int>(-boss.hp + 100) * 2, 30, 0.0f, 0xFF0000FF, kFillModeSolid);
		}
		break;
	case ENDTITLE:
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
		Novice::DrawSprite(0, 0, gameover, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		break;
	case GAMECLAER:
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
		Novice::DrawSprite(0, 0, gameclear, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		break;
	case COOLTIME:
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
		Novice::DrawSprite(400, 300, pstt, 2.0f, 2.0f, 0.0f, 0xFFFFFFFF);
		break;

	}

#pragma endregion

	///
	/// ↑描画処理ここまで
	///
}
