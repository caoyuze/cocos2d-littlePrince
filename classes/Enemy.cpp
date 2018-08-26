#include "Enemy.h"
#include "CommonData.h"
#include "OverScene.h"

float Enemy::levelSpeed =  0;

Enemy::Enemy() {
    this->e_type = SMALL_ENEMY; 
    this->e_hp = HP_SMALL;
	this->e_step = SP_SMALL;
	this->e_score = SCORE_SMALL;
}

Enemy* Enemy::create(EnemyType type) {
    auto enemy = new Enemy();
    if( enemy && enemy->init(type) ) {
        enemy->autorelease();
        return enemy;
    }
    delete enemy;
    enemy = NULL;
    return NULL;
}

//���ݲ�ͬ�ĵл�������ͬ��ͼƬЧ��
bool Enemy::init(EnemyType type) {
    this->e_type = type;
    switch (type)
    {
    case  SMALL_ENEMY:
        this->e_hp = HP_SMALL;
        this->e_step = SP_SMALL;      
		this->e_score = SCORE_SMALL;
        cocos2d::Sprite::initWithSpriteFrameName("enemy1.png");
        break;
    case  MIDDLE_ENEMY:
        this->e_hp = HP_MIDDLE;
        this->e_step = SP_MIDDLE;
		this->e_score = SCORE_MIDDLE;
        cocos2d::Sprite::initWithSpriteFrameName("enemy2.png");
        break;
    case  BIG_ENEMY:
        this->e_hp = HP_BIG;
        this->e_step = SP_BIG;
		this->e_score = SCORE_BIG;
		cocos2d::Sprite::initWithSpriteFrameName("enemy3_n1.png");
		{
			auto animation = AnimationCacheInstance->getAnimation("Big Enemy Fly");
			this->runAction(cocos2d::Animate::create(animation));
			Audio->playEffect("big_spaceship_flay.mp3");
		}
        break;
    default:
        break;
    }
    return true;
}

//���Ч��
void Enemy::hit() { 
    auto animation = cocos2d::Animation::create();
    switch (this->e_type)
    {
    case MIDDLE_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Middle Enemy Hurt");
                break;
    case BIG_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Big Enemy Hurt");
            break;
    default:
            break;
    }
    auto animate = cocos2d::Animate::create(animation);
    this->runAction(animate);
}   

//�ݻ�Ч��
void Enemy::down() {
    auto animation = cocos2d::Animation::create();
    switch(this->e_type) {
    case SMALL_ENEMY:       
		animation=cocos2d::AnimationCache::getInstance()->getAnimation("Small Enemy Down");
		Audio->playEffect("enemy1_down.mp3");
        break;
    case MIDDLE_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Middle Enemy Down");
		Audio->playEffect("enemy2_down.mp3");
        break;
    case BIG_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Big Enemy Down");
		Audio->playEffect("enemy3_down.mp3");
        break;
    default:
        break;
    }
    auto animate = cocos2d::Animate::create(animation);
    auto callFuncN = cocos2d::CallFuncN::create([](Node* node) {
		node->removeFromParentAndCleanup(true);
    });

   this->runAction(cocos2d::Sequence::create(animate, callFuncN, NULL));
}

void Enemy::increeLevelSpeed(){
	if(Enemy::levelSpeed == 10)
	{
		return;
	}
	Enemy::levelSpeed += 0.4f;
}

void Enemy::clearLevelSpeed(){
	Enemy::levelSpeed = 0; 
}