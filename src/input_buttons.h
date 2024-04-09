/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EP_INPUT_BUTTONS_H
#define EP_INPUT_BUTTONS_H

// Headers
#include <vector>
#include <array>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <algorithm>
#include <ostream>

#include <lcf/enum_tags.h>
#include "flat_map.h"
#include "keys.h"

struct Game_ConfigInput;

#if USE_SDL==1
#include "platform/sdl/axis.h"
#endif

/**
 * Input namespace.
 */
namespace Input {
	/** Input buttons list. */
	enum InputButton : uint8_t {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		DECISION,
		CANCEL,
		SHIFT,
		N0,
		N1,
		N2,
		N3,
		N4,
		N5,
		N6,
		N7,
		N8,
		N9,
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		PERIOD,
		DEBUG_MENU,
		DEBUG_THROUGH,
		DEBUG_SAVE,
		DEBUG_ABORT_EVENT,
		SETTINGS_MENU,
		TOGGLE_FPS,
		TAKE_SCREENSHOT,
		SHOW_LOG,
		RESET,
		PAGE_UP,
		PAGE_DOWN,
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_MIDDLE,
		SCROLL_UP,
		SCROLL_DOWN,
		FAST_FORWARD_A,
		FAST_FORWARD_B,
		TOGGLE_FULLSCREEN,
		TOGGLE_ZOOM,
		BUTTON_COUNT
	};

	constexpr auto kInputButtonNames = lcf::makeEnumTags<InputButton>(
		"UP",
		"DOWN",
		"LEFT",
		"RIGHT",
		"DECISION",
		"CANCEL",
		"SHIFT",
		"N0",
		"N1",
		"N2",
		"N3",
		"N4",
		"N5",
		"N6",
		"N7",
		"N8",
		"N9",
		"PLUS",
		"MINUS",
		"MULTIPLY",
		"DIVIDE",
		"PERIOD",
		"DEBUG_MENU",
		"DEBUG_THROUGH",
		"DEBUG_SAVE",
		"DEBUG_ABORT_EVENT",
		"SETTINGS_MENU",
		"TOGGLE_FPS",
		"TAKE_SCREENSHOT",
		"SHOW_LOG",
		"RESET",
		"PAGE_UP",
		"PAGE_DOWN",
		"MOUSE_LEFT",
		"MOUSE_RIGHT",
		"MOUSE_MIDDLE",
		"SCROLL_UP",
		"SCROLL_DOWN",
		"FAST_FORWARD_A",
		"FAST_FORWARD_B",
		"TOGGLE_FULLSCREEN",
		"TOGGLE_ZOOM",
		"BUTTON_COUNT");

	constexpr auto kInputButtonHelp = lcf::makeEnumTags<InputButton>(
		"方向键 上",
		"方向键 下",
		"方向键 左",
		"方向键 右",
		"确定(Enter)键",
		"取消(ESC)键",
		"Shift键",
		"数字0",
		"数字1",
		"数字2",
		"数字3",
		"数字4",
		"数字5",
		"数字6",
		"数字7",
		"数字8",
		"数字9",
		"加号+键",
		"减号-键",
		"乘号*键",
		"除号÷键",
		"Period键",
		"(调试模式)打开调试菜单",
		"(调试模式)穿墙",
		"(调试模式)打开存档菜单",
		"(调试模式)中止当前活动事件",
		"打开此设置菜单",
		"切换FPS显示",
		"截图",
		"在屏幕上显示控制台日志",
		"重置游戏到初始标题屏幕",
		"在菜单中上一页",
		"在菜单中下一页",
		"鼠标左键",
		"鼠标右键",
		"鼠标中键",
		"向上滚动键",
		"向下滚动键",
		"以x{}的速度运行游戏",
		"以x{}的速度运行游戏",
		"切换全屏模式",
		"切换窗口缩放级别",
		"按键总数");

	/**
	 * Return true if the given button is a system button.
	 * System buttons are refreshed on every physical frame
	 * and do not affect the game logic.
	 */
	constexpr bool IsSystemButton(InputButton b) {
		switch (b) {
			case TOGGLE_FPS:
			case TAKE_SCREENSHOT:
			case SHOW_LOG:
			case TOGGLE_ZOOM:
			case FAST_FORWARD_A:
			case FAST_FORWARD_B:
				return true;
			default:
				return false;
		}
	}

	/**
	 * Protected buttons are buttons where unmapping them makes the Player unusable.
	 * @return true when the button is protected
	 */
	constexpr bool IsProtectedButton(InputButton b) {
		switch (b) {
			case UP:
			case DOWN:
			case LEFT:
			case RIGHT:
			case DECISION:
			case CANCEL:
			case SETTINGS_MENU: // Not really critical but needs a way to enter it
				return true;
			default:
				return false;
		}
	}

	namespace Direction {
		enum InputDirection : uint8_t {
			NONE = 0,
			DOWNLEFT = 1,
			DOWN = 2,
			DOWNRIGHT = 3,
			LEFT = 4,
			CENTER = 5,
			RIGHT = 6,
			UPLEFT = 7,
			UP = 8,
			UPRIGHT = 9,
			NUM_DIRECTIONS = 10,
		};

		static constexpr auto kInputDirectionNames = lcf::makeEnumTags<InputDirection>(
			"NONE",
			"DOWNLEFT",
			"DOWN",
			"DOWNRIGHT",
			"LEFT",
			"CENTER",
			"RIGHT",
			"UPLEFT",
			"UP",
			"UPRIGHT",
			"NUM_DIRECTIONS");
	};

	using ButtonMappingArray = FlatUniqueMultiMap<InputButton,Keys::InputKey>;

	/** A mapping for a button to a input key */
	using ButtonMapping = ButtonMappingArray::pair_type;

	inline std::ostream& operator<<(std::ostream& os, ButtonMapping bm) {
		os << "{ " << kInputButtonNames.tag(bm.first) << ", " << Keys::kInputKeyNames.tag(bm.second) << " }";
		return os;
	}

	using DirectionMappingArray = FlatUniqueMultiMap<Direction::InputDirection, InputButton>;

	/** A mapping for a single direction to a button */
	using DirectionMapping = DirectionMappingArray::pair_type;

	inline std::ostream& operator<<(std::ostream& os, DirectionMapping dm) {
		os << "{ " << Direction::kInputDirectionNames.tag(dm.first) << ", " << kInputButtonNames.tag(dm.second) << " }";
		return os;
	}

	/** Provides platform-specific, human readable name for an input key */
	using KeyNamesArray = std::vector<std::pair<Keys::InputKey, std::string>>;

	/** Returns default button mappings */
	ButtonMappingArray GetDefaultButtonMappings();

	/** Returns platform-specific, human readable name for an input key */
	KeyNamesArray GetInputKeyNames();

	/** Used to declare which config options are available */
	void GetSupportedConfig(Game_ConfigInput& cfg);

#if USE_SDL==1
	SdlAxis GetSdlAxis();
#endif
}

#endif
