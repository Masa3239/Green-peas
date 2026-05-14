#include "EnemyBoss.h"
#include "../../Chara/Collision.h"
#include "../../Utility/Transform.h"
#include "DxLib.h"
#include "../../Utility/MyRandom.h"
#include "../../Utility/Time.h"
#include "../Takagi/Player.h"
#include "../Kimura/Map/Map.h"
#include "BossBulletManager.h"
#include "../../System/SoundManager.h"

namespace {

	// 封印状態の画像のファイルパス
	const char* const kSealGraphPath = ".\\Resource\\Dino Rex\\columbus_egg.png";

	// 画像のサイズ
	constexpr float kGraphScale = 1.0f;

	// 画像のオフセットY
	constexpr int kGraphOffsetY = 40;

	// 円の当たり判定の半径
	constexpr float kCircleRadius = 50.0f * kGraphScale;
	
	// 近距離攻撃の当たり判定の大きさ
	constexpr Vector3 kCloseRangeCollisionSize = { 250.0f* kGraphScale, 100.0f* kGraphScale, 0.0f };

	// アニメーションのダメージ判定開始フレーム
	constexpr int kCloseRangeDamageStartFrame = 7;
	// アニメーションのダメージ判定終了フレーム
	constexpr int kCloseRangeDamageEndFrame = 11;

	// ボスの挙動で使うプレイヤーのオフセットの値
	constexpr float kPlayerOffsetPos = 200.0f;

	// ボスの最大体力
	constexpr int kMaxHp = 50000000;
	constexpr int kAngryHp = 10000;

	// ボスの攻撃力
	constexpr int kAttackPower = 25;

	// ランダムに行動を決める時のインターバル
	constexpr float kRandomInterval = 2.0f;

	// 弾を発射する時のインターバル
	constexpr float kShotInterval = 0.5f;

	// ボスのスピード
	constexpr float kSpeed = 500.0f;
	constexpr float kAngrySpeed = 3000.0f;

	// 封印解除に必要な鍵の数
	constexpr int kMaxKey = 4;

	// エフェクトを出す間隔
	constexpr float kEffectInterVal = 1.0f;

	// エフェクトのサイズ
	constexpr float kEffectScale = 5.0f * kGraphScale;

	constexpr float kMapRangeOffset = 60.0f;

}

EnemyBoss::EnemyBoss(ObjectManager* objManager, Vector3 position) :
	m_sealGraphHandle(-1),
	m_motionCounter(0),
	m_motionFrame(0),
	m_direction(-1),
	m_shotTimer(0.0f),
	m_isCloseTheAttack(false),
	m_isCloseTheAttackDamege(false),
	GameObject(objManager),
	m_collsion(GetTransform().position , kCircleRadius),
	m_closeRangeAttackCollision(GetTransform().position, kCloseRangeCollisionSize),
	m_maxHp(kMaxHp),
	m_currentHp(kMaxHp),
	m_attackPower(kAttackPower),
	m_getKey(0),
	m_sealRelease(false),
	m_status(BossAnimation::Idle),
	m_action(BossAction::Idle),
	m_getRandomTime(0.0f),
	m_targetPos(0.0f, 0.0f, 0.0f),
	m_pPlayer(nullptr),
	m_pMap(nullptr),
	m_pBossBulletMgr(nullptr),
	m_effectTimer(0.0f),
	m_effectCount(0),
	m_effectMotionCounter(0),
	m_effectMotionFrame(0),
	m_isEffect(false),
	m_effectPos(0.0f, 0.0f, 0.0f),
	m_isDead(false),
	m_speed(0),
	m_angrySpeed(1),
	m_isAngry(false),
	m_seBossFlag(false),
	m_isAttackHit(false),
	m_isPowerUp(false)
{

	m_pBossBulletMgr = std::make_unique<BossBulletManager>();

	for (int i = 0; i < static_cast<int>(BossAnimation::Max); i++) {

		for (int j = 0;j < kCharactorMotionNum; j++) {
			m_graphHandle[i][j] = -1;
		}
	}

	for (int i = 0; i < kEffectMotionNum; i++) {

		m_efffectGraphHandle[i] = -1;
	}
	GetTransform().Reset();
	GetTransform().position = position;
}

void EnemyBoss::Init()
{

	m_pBossBulletMgr->SetObjectManager(GetObjectManager());
	m_pBossBulletMgr->SetPlayer(m_pPlayer);
	m_pBossBulletMgr->Init();

	m_sealGraphHandle = LoadGraph(kSealGraphPath);
	
	// ボスのアイドルアニメーション
	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_idle.png",
		5, 5, 1, 128, 128, m_graphHandle[static_cast<int>(BossAnimation::Idle)]);

	// ボスが離れるアニメーション
	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_move.png",
		8, 8, 1, 384, 128, m_graphHandle[static_cast<int>(BossAnimation::LeaveMove)]);

	// ボスが近づくアニメーション
	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_attack_B_2_loop.png",
		5, 5, 1, 384, 128, m_graphHandle[static_cast<int>(BossAnimation::ApproachMove)]);

	// ボスの近距離攻撃のアニメーション
	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_attack_A.png",
		21, 21, 1, 384, 128, m_graphHandle[static_cast<int>(BossAnimation::CloseRangeAttack)]);

	// ボスの遠距離攻撃のアニメーション
	LoadDivGraph(".\\Resource\\Dino Rex\\dino_rex_ability_black.png",
		25, 25, 1, 384, 128, m_graphHandle[static_cast<int>(BossAnimation::LongRangeAttack)]);

	//ボスの爆発エフェクト
	LoadDivGraph(".\\Resource\\Explosion\\Fire_III_Flame_C_80x48.png",
		6, 6, 1, 80, 48, m_efffectGraphHandle);

}

void EnemyBoss::End()
{

	for (int i = 0; i < static_cast<int>(EnemyBoss::BossAnimation::Max); i++) {

		for (int j = 0; j < kCharactorMotionNum; j++) {

			// 画像の破棄
			DeleteGraph(m_graphHandle[i][j]);
		}
	}

	for (int i = 0; i < kEffectMotionNum; i++) {

		// 画像の破棄
		DeleteGraph(m_efffectGraphHandle[i]);
	}

	DeleteGraph(m_sealGraphHandle);
	m_pBossBulletMgr->End();
}

void EnemyBoss::Update()
{

	if (m_attackPower != m_attackPowerO) {
		m_attackPowerO = m_attackPower;
	}


	// ボスが画面の左側に出ないようする
	if (GetTransform().position.x < kMapRangeOffset) GetTransform().position.x = kMapRangeOffset;
	else
		// ボスが画面の右側に出ないようにする
		if (GetTransform().position.x > m_pMap->GetMapBlockNumX() * 40 - kMapRangeOffset) GetTransform().position.x = m_pMap->GetMapBlockNumX() * 40 - kMapRangeOffset;

	// ボスが画面の上側に出ないようにする
	if (GetTransform().position.y < kMapRangeOffset) GetTransform().position.y = kMapRangeOffset;
	else
		// ボスが画面の下側に出ないようにする
		if (GetTransform().position.y > m_pMap->GetMapBlockNumY() * 40 - kMapRangeOffset) GetTransform().position.y = m_pMap->GetMapBlockNumY() * 40 - kMapRangeOffset;

	// 当たり判定の更新
	m_collsion.SetPosition(GetTransform().position);

	// 封印状態ならこの先は呼ばない
	if (!m_sealRelease) return;

	// すでに倒されていたら呼ばない
	if (CheckDeadFlag()) return;

	if (m_seBossFlag) {

		SoundManager::GetInstance().StopBGM();
		SoundManager::GetInstance().PlayBGM(Sound::BGM::BGM1);
		// 封印解除SEを鳴らす
		SoundManager::GetInstance().PlaySe(Sound::SE::Boss1);
		m_seBossFlag = false;
	}

	m_pBossBulletMgr->Update();

	m_pBossBulletMgr->CheckHitCollision(m_pPlayer->GetCircle());
	
	m_closeRangeAttackCollision.SetPosition(GetTransform().position);

	// ボスの近距離攻撃とプレイヤーが当たっていたら
	if (CheckHitCloseRangeAttackCollison(m_pPlayer->GetCircle())) {


		if (!m_isAttackHit) {

			// プレイヤーのダメージ処理を呼ぶ
			m_pPlayer->Damage(m_attackPower);
		}
		m_isAttackHit = true;
	}

	// Idle状態なら
	if (m_status == BossAnimation::Idle) {

		// 時間を計測
		m_getRandomTime += Time::GetInstance().GetDeltaTime();
	}

	// 一定時間を超えたら
	if (m_getRandomTime >= kRandomInterval) {

		// ランダムで行動を決める
		GetRandomAction();
		m_getRandomTime = 0.0f;
	}

	Status();

	Action();

	AttackUp();
}

void EnemyBoss::Draw()
{

	m_pBossBulletMgr->Draw();

	// 封印状態なら
	if (!m_sealRelease) {
		// 封印状態の画像を描画
		DrawRotaGraph(GetTransform().position.x, GetTransform().position.y, kGraphScale * 0.5f, 0.0f, m_sealGraphHandle, TRUE);
	}
	// 封印が解除されたなら
	else
	{

		// 画像の描画
		DrawRotaGraph(GetTransform().position.x, GetTransform().position.y - kGraphOffsetY, kGraphScale, 0.0f,
			m_graphHandle[static_cast<int>(m_status)][m_motionFrame], TRUE, m_direction);

		// 円の当たり判定の描画
		m_collsion.DebugDraw();

		if (m_isCloseTheAttackDamege) {

			// 近距離攻撃の当たり判定の描画
			m_closeRangeAttackCollision.DebugDraw();
		}

		// 死んでいなければこの先は呼ばない
		if (!CheckDeadFlag()) return;
		
		Dead();
	}

}

bool EnemyBoss::SealReleaseFlag()
{

	// 封印解除されたらtrueを返す
	if (m_sealRelease) return true;

	// 鍵がとられる度に加算
	m_getKey++;

	// 指定された値より大きくなったら
	if (m_getKey >= kMaxKey) {

		// 封印解除されている(true)
		m_sealRelease = true;
	}

	// 結果を返す
	return m_sealRelease;
}

bool EnemyBoss::CheckHitCloseRangeAttackCollison(const Collision::Shape& other)
{

	// 攻撃中かつ、プレイヤーと当たっていればtrueを返す
	return  m_isCloseTheAttackDamege && m_isCloseTheAttack && m_closeRangeAttackCollision.CheckCollision(other);
}

bool EnemyBoss::Damage(const int damage)
{

	if (!m_sealRelease) {

		m_speed += kAngrySpeed;
		m_sealRelease = true;
	}
	m_currentHp -= damage;
	return true;
}

bool EnemyBoss::Damage(const int damage, int weapon, int index)
{

	// 封印宙に一定以上のダメージを受けたら
	if (!m_sealRelease && m_currentHp < kMaxHp - kAngryHp) {

		m_seBossFlag = true;
		m_sealRelease = true;
		m_isAngry = true;
		m_angrySpeed = 2;
		m_action = BossAction::CloseRangeAttack;
	}

	// 足りない分を追加
	CheckDamageFlagSize(weapon, index);

	// すでにその武器がダメージを与えていたら失敗
	if (m_damageFlag[weapon][index]) return false;

	m_damageFlag[weapon][index] = true;

	m_currentHp -= damage;

	SoundManager::GetInstance().PlaySe(Sound::SE::Damage4);

	return true;
}

bool EnemyBoss::ResetDamageFlag(int weapon, int index)
{

	if (index >= m_damageFlag[weapon].size()) return false;

	m_damageFlag[weapon][index] = false;

	return true;
}

void EnemyBoss::Action()
{

	switch (m_action)
	{
	case EnemyBoss::BossAction::Idle:
		break;
	case EnemyBoss::BossAction::CloseRangeAttack:

		// 攻撃モーション中なら処理を抜ける
		if (m_isCloseTheAttack)break;

		// プレイヤーの一定範囲内にいたら
		if (ApproachPlayer(m_pPlayer->GetTransform().position)) {

			// 近距離攻撃をする
			CloseRangeAttack();
		}
		break;
	case EnemyBoss::BossAction::LongRangeAttack:

		// 目標の位置に着いたら
		if (LeavePlayer(m_targetPos)) {
			// 目的地に着いたらプレイヤーの方向を向く
			m_direction = (m_pPlayer->GetTransform().position.x >= GetTransform().position.x) ? -1 : 1;
			// 遠距離攻撃をする
			LongRangeAttack();
		}
		break;
	default:
		break;
	}
}

void EnemyBoss::Status()
{

	// アニメーションを再生するまでのカウントをプラス
	m_motionCounter++;

	if (m_motionCounter % 5 == 0) {

		// アニメーションのフレームをプラス
		m_motionFrame++;

		// 近距離攻撃のダメージ判定のフラグの決める
		m_isCloseTheAttackDamege = (m_status == BossAnimation::CloseRangeAttack &&
			m_motionFrame >= kCloseRangeDamageStartFrame && m_motionFrame <= kCloseRangeDamageEndFrame) ? true : false;

		//アニメーションがなければ
		if (m_graphHandle[static_cast<int>(m_status)][m_motionFrame] == -1) {

			switch (m_status)
			{
			case EnemyBoss::BossAnimation::Idle:
			case EnemyBoss::BossAnimation::ApproachMove:
			case EnemyBoss::BossAnimation::LeaveMove:
				break;
			case EnemyBoss::BossAnimation::CloseRangeAttack:
				m_isAttackHit = false;
			case EnemyBoss::BossAnimation::LongRangeAttack:
				m_status = BossAnimation::Idle;
				m_action = BossAction::Idle;
				m_isCloseTheAttack = false;
				break;
			default:
				break;
			}

			// アニメーションのフレームをリセット
			m_motionFrame = 0;
		}

		// アニメーションを再生するまでのカウントをリセット
		m_motionCounter = 0;
	}
}

void EnemyBoss::GetRandomAction()
{


	// 次に選ぶ行動をランダムで取得
	BossAction nextAction = static_cast<BossAction>(MyRandom::Int(0, static_cast<int>(BossAction::Max) - 1));

	// 現在のステータスに入れる
	m_action = nextAction;


	// 範囲内になるまで繰り返す
	while (true) {

		m_targetPos = TargetPos(m_pPlayer->GetTransform().position);

		// 範囲内なら終了
		if (m_targetPos.x >= kMapRangeOffset &&
			m_targetPos.x <= m_pMap->GetMapBlockNumX() * 40 - kMapRangeOffset &&
			m_targetPos.y >= kMapRangeOffset &&
			m_targetPos.y <= m_pMap->GetMapBlockNumY() * 40 - kMapRangeOffset) {

			break;
		}
	}
}

bool EnemyBoss::ApproachPlayer(const Vector3& playerPos)
{

	

	// 方向ベクトル
	Vector3 direction = playerPos - GetTransform().position;

	// 距離チェック
	if (direction.GetSqLength() <= 3000.0f) return true;

	// アニメーションをApproachMoveにする
	m_status = BossAnimation::ApproachMove;

	// 正規化
	direction = direction.GetNormalize();

	// スピード
	m_speed = kSpeed * m_angrySpeed;

	// プレイヤーの位置に合わせてボスの向きを変える
	m_direction = (playerPos.x >= GetTransform().position.x) ? -1 : 1;

	// 移動
	GetTransform().position += direction * m_speed * Time::GetInstance().GetDeltaTime();

	return false;
}

bool EnemyBoss::LeavePlayer(const Vector3& playerPos)
{

	// 方向ベクトル
	Vector3 direction = playerPos - GetTransform().position;

	// 距離チェック
	if (direction.GetSqLength() <= 100.0f) return true;

	// アニメーションをLeaveMoveにする
	m_status = BossAnimation::LeaveMove;

	// 正規化
	direction = direction.GetNormalize();

	// スピード
	m_speed = kSpeed * m_angrySpeed;

	// プレイヤーの位置に合わせてボスの向きを変える
	m_direction = (playerPos.x >= GetTransform().position.x) ? -1 : 1;
	// 移動
	GetTransform().position += direction * m_speed * Time::GetInstance().GetDeltaTime();

	return false;
}

Vector3 EnemyBoss::TargetPos(const Vector3& playerPos)
{

	// プレイヤーから離した距離を用意
	float offsetX = kPlayerOffsetPos;
	float offsetY = kPlayerOffsetPos;

	// ランダムで+か-の値を決める
	int randomX = MyRandom::Int(0, 1) == 0 ? 1 : -1;
	int randomY = MyRandom::Int(0, 1) == 0 ? 1 : -1;

	Vector3 targetPos;

	// XとYの座標を計算する
	targetPos.x = playerPos.x + offsetX * randomX;
	targetPos.y = playerPos.y + offsetY * randomY;
	targetPos.z = playerPos.z;

	// 計算結果を返す
	return targetPos;
}

void EnemyBoss::CloseRangeAttack()
{

	// 攻撃していたらこの先は呼ばない
	if (m_isCloseTheAttack) return;

	// 攻撃するのでフラグをtrue
	m_isCloseTheAttack = true;

	// アニメーションをCloseRangeAttackにする
	m_status = BossAnimation::CloseRangeAttack;
}

void EnemyBoss::LongRangeAttack()
{
	
	// アニメーションをLongRangeAttackにする
	m_status = BossAnimation::LongRangeAttack;

	if (m_isAngry) {
		SoundManager::GetInstance().PlaySe(Sound::SE::BossBullet);
		// 弾を生成する
		m_pBossBulletMgr->Create(BossBulletBase::BulletType::Normal, GetTransform().position);
	}
	else {
		// 弾の発射感覚のタイマーを加算
		m_shotTimer += Time::GetInstance().GetDeltaTime();

		if (m_shotTimer >= kShotInterval) {

			SoundManager::GetInstance().PlaySe(Sound::SE::BossBullet);
			// 弾を生成する
			m_pBossBulletMgr->Create(BossBulletBase::BulletType::Normal, GetTransform().position);
			m_shotTimer = 0.0f;
		}
	}
}

bool EnemyBoss::CheckDeadFlag()
{
	return m_currentHp <= 0;
}

void EnemyBoss::Dead()
{

	// エフェクトタイマーを計測
	m_effectTimer += Time::GetInstance().GetDeltaTime();

	// アニメーションのカウンターをプラス
	m_effectMotionCounter++;

	// タイマーがインターバルの値以上になったら
	if (m_effectTimer >= kEffectInterVal) {

		if (m_effectCount >= 1) return;

		// エフェクトを描画する
		m_isEffect = true;

		// ランダムでエフェクトの座標を決める
		// m_effectPos = DeadEffect(GetTransform().position);

		// エフェクトを出した回数をプラス
		m_effectCount++;

		// タイマーをリセット
		m_effectTimer = 0.0f;
	};

	if (m_isEffect) {

		SoundManager::GetInstance().PlaySe(Sound::SE::Explosion);
		if (m_effectMotionCounter % 5 == 0) {

			// アニメーションのフレームをプラス
			m_effectMotionFrame++;

			// アニメーションのフレームになにもなかったら
			if (m_efffectGraphHandle[m_effectMotionFrame] == -1) {

				// リセット
				m_effectMotionFrame = 0;
				m_isEffect = false;
			}

			// 演出が終わったら
			if (!m_isEffect) {

				// 死んでいるのでtrue
				m_isDead = true;
				// 非表示
				SetState(State::Deactive);
			}

			m_effectMotionCounter = 0;
		}
		
		// 画像の描画
		DrawRotaGraph(GetTransform().position.x,
			GetTransform().position.y - kGraphOffsetY, kEffectScale, 0.0f,
			m_efffectGraphHandle[m_effectMotionFrame], TRUE);
	}

}

Vector3 EnemyBoss::DeadEffect(Vector3 position)
{

	// ランダムで座標を取得
	int randomX = MyRandom::Int(-40, 40);
	int randomY = MyRandom::Int(-40, 10);

	// エフェクトを出す座標
	Vector3 effectPos;

	effectPos.x = position.x + randomX;
	effectPos.y = position.y + randomY;
	effectPos.z = position.z;

	return effectPos;
}

void EnemyBoss::CheckDamageFlagSize(int weapon, int index)
{
	if (index < m_damageFlag[weapon].size()) return;

	for (int i = m_damageFlag[weapon].size() - 1;i < index; i++) {

		m_damageFlag[weapon].emplace_back(false);
	}
}

void EnemyBoss::AttackUp()
{

	if (m_currentHp > kMaxHp / 2) return;

	if (!m_isAttackHit) {
		m_isPowerUp = true;
		m_attackPower *= 2;
	}
}


