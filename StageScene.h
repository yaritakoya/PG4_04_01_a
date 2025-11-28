#pragma once
#include "IScene.h"
#include <Novice.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

class StageScene : public IScene {

public:

	void Initialize() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	typedef struct Vector2 {
		float x;
		float y;
	}Vector2;

	typedef struct Player {
		Vector2 pos;
		Vector2 oldPos;
		Vector2 move;
		float speed;
		float radius;
		int shootCoolTime;
		int isAlive;
		float deathCount;
		float respawnTimer;
	} Player;

	typedef struct Bullet {
		Vector2 pos;
		float width;
		float height;
		float radius;
		float speed;
		int isShoot;
	} Bullet;

	typedef struct Attachment {
		Vector2 pos;
		Vector2 move;
		float speed;
		int backTimer;
		int shootCoolTime;
	} Attachment;

	typedef struct AttachmentBullet {
		Vector2 pos;
		float width;
		float height;
		float radius;
		float speed;
		int isShoot;
	} AttachmentBullet;

	typedef struct Enemy {
		Vector2 pos;
		Vector2 move;
		float width;
		float height;
		float radius;
		float speed;
		int respawnTimer;
		int isAlive;
		int shootCoolTime;
		float deathCount;
	} Enemy;

	typedef struct EnemyBullet {
		Vector2 pos;
		float width;
		float height;
		float radius;
		float speed;
		int isShoot;
	} EnemyBullet;

	typedef struct Boss {
		Vector2 pos;
		Vector2 move;
		float speed;
		float radius;
		int shootCoolTime;
		int shootCoolTimeRight;
		int shootCoolTimeLeft;
		int isAlive;
		float hp;
	} Boss;

	typedef struct BossBullet {
		Vector2 pos;
		float width;
		float height;
		float radius;
		float speed;
		int isShoot;
	} BossBullet;

	typedef struct Hp {
		Vector2 pos;
	}Hp;

	enum Scene {
		TITLE,
		GAMESCENE,
		ENDTITLE,
		COOLTIME,
		GAMECLAER
	};
	int scene = TITLE;
	
	//enemyBullet to player
	float EBtPX;
	float EBtPY;
	float EBtPdistance;
	//playerBullet to enemy
	float PBtEX;
	float PBtEY;
	float PBtEdistance;
	//attachmentBullet to enemy
	float ABtEX;
	float ABtEY;
	float ABtEdistance;
	//playerBullet to boss
	float PBtBX;
	float PBtBY;
	float PBtBdistance;
	//attachmentBullet to boss
	float ABtBX;
	float ABtBY;
	float ABtBdistance;
	//bossBullet to player
	float BBtPX;
	float BBtPY;
	float BBtPdistance;
	//bossBulletRight to player
	float BBRtPX;
	float BBRtPY;
	float BBRtPdistance;
	//bossBulletLeft to player
	float BBLtPX;
	float BBLtPY;
	float BBLtPdistance;
	
	//image handle
	int ziki = Novice::LoadTexture("./images/ziki.png");
	int teki = Novice::LoadTexture("./images/teki.png");
	int tekiDeath = Novice::LoadTexture("./images/tekideath.png");
	int bossHandle = Novice::LoadTexture("./images/boss.png");
	int tama = Novice::LoadTexture("./images/tama.png");
	int HP = Novice::LoadTexture("./images/HP.png");
	int graphAttachment = Novice::LoadTexture("./images/attachment.png");
	int attachmentTama = Novice::LoadTexture("./images/attachmentBullet.png");
	int background = Novice::LoadTexture("./images/background.png");
	int gameover = Novice::LoadTexture("./images/gameover.png");
	int gameclear = Novice::LoadTexture("./images/gameclear.png");
	int psts = Novice::LoadTexture("./images/PSTS.png");
	int pstt = Novice::LoadTexture("./images/PSTT.png");
	int gameTitle = Novice::LoadTexture("./images/gameTitle.png");

	Player player;
	Boss boss;
	Attachment attachment;
	Enemy enemy;
	Bullet bullet[32];
	EnemyBullet enemyBullet[32];
	AttachmentBullet attachmentBullet[32];
	BossBullet bossBullet[32];
	BossBullet bossBulletRight[32];
	BossBullet bossBulletLeft[32];
	Hp hp[3];
	float backgroundPosX;
	float lenght;
	int score;
	int bossCount;
	int backgroundTimer;
};