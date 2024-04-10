/*
 * This file is part of EasyRPG Player
 *
 * Copyright (c) EasyRPG Project. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "org_easyrpg_player_player_EasyRpgPlayerActivity.h"
#include "android.h"
#include "player.h"
#include "baseui.h"
#include "scene_settings.h"
#include "game_clock.h"

#ifdef __cplusplus
extern "C" {
#endif

// To prevent race conditions use EpAndroid::schedule for everything that is not just a variable read/write

JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_endGame
  (JNIEnv *, jclass)
{
	Player::exit_flag = true;
}

JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_setFastForwardMultiplier
  (JNIEnv *, jclass, jint ji)
{
	Player::speed_modifier_a = ji;
}

JNIEXPORT void JNICALL
Java_org_easyrpg_player_player_EasyRpgPlayerActivity_openSettings(JNIEnv *, jclass) {
	EpAndroid::schedule([]() {
		if (Scene::instance->type != Scene::Logo && !Scene::Find(Scene::Settings)) {
			Scene::Push(std::make_shared<Scene_Settings>());
		}
	});
}

//region 修改
JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_pauseGame
  (JNIEnv *, jclass)
{
	Player::Pause();
}

JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_resumeGame
  (JNIEnv *, jclass)
{
	Player::Resume();
}
JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_resetGame
  (JNIEnv *, jclass)
{
	Player::reset_flag = true;
}
JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_switchWalkThroughWalls
  (JNIEnv *, jclass, jboolean enabled)
{
	Player::through_flag_25 = enabled;
}
JNIEXPORT jboolean JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_getSwitchWalkThroughWalls
  (JNIEnv *, jclass)
{
	return Player::through_flag_25;
}
JNIEXPORT void JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_setGameSpeedFactor
  (JNIEnv *, jclass, jfloat speed)
{
	Game_Clock::SetGameSpeedFactor(speed);
}
JNIEXPORT jfloat JNICALL Java_org_easyrpg_player_player_EasyRpgPlayerActivity_getGameSpeedFactor
  (JNIEnv *, jclass)
{
	return Game_Clock::GetGameSpeedFactor();
}
//endregion
#ifdef __cplusplus
}
#endif
