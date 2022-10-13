#pragma once
#include "Vec2.h"
#include "game.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void init();
	virtual void setHandle(int handle, int sizeX, int sizeY);
	virtual void setPos(float x, float y);
	virtual void update() = 0;		// 純粋仮想関数
	virtual void draw();

	// 当たり判定の半径取得
	virtual float getRadius() const;

	// 当たり判定の中心位置取得
	virtual Vec2 getCenter() const;
	
	// ほかの敵に当たった場ありの反射処理
	virtual void bound(Vec2 targetPos);

	
protected:

	int m_handle;	// 画像のハンドル
	int sizeX;
	int sizeY;

	// 位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_vec;

	// 左上座標
	Vec2 m_size;

	
};

// まっすぐ移動

class EnemyStraight : public Enemy
{
public:
	EnemyStraight();
	virtual ~EnemyStraight() {}

	virtual void init() override;
			void update() override;


};