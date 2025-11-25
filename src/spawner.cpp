#include "spawner.h"
#include "enemy.h"
#include "core/scene.h"
#include "world/effect.h"

void Spawner::update(float dt)
{
    if (!player_ || !player_->getActive())
        return;
    timer_ += dt;
    if (timer_ >= interval_)
    {
        timer_ = 0;
        game_.playSound("assets/sound/silly-ghost-sound-242342.mp3");
        for (int i = 0; i < num_; ++i)
            spawnEnemy();
    }
}

void Spawner::spawnEnemy()
{
    auto pos = game_.randomVec2(game_.getCurrentScene()->getCameraPos(), game_.getCurrentScene()->getCameraPos() + game_.getScreenSize());
    Enemy *enemy = Enemy::addEnemyChild(nullptr, pos, player_);
    Effect::addEffectChild(game_.getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
}
