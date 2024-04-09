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

#ifndef EP_GAME_CONFIG_H
#define EP_GAME_CONFIG_H

/**
 * This class manages global engine configuration.
 * For game specific settings see Game_ConfigGame.
 *
 * @see Game_ConfigGame
 */

#include "config_param.h"
#include "filesystem.h"
#include "options.h"
#include "input_buttons.h"
#include "utils.h"

class CmdlineParser;

enum class ScalingMode {
	/** Nearest neighbour to fit screen */
	Nearest,
	/** Like NN but only scales to integers */
	Integer,
	/** Integer followed by Bilinear downscale to fit screen */
	Bilinear,
};

enum class GameResolution {
	/** 320x240 */
	Original,
	/** 416x240 */
	Widescreen,
	/** 560x240 */
	Ultrawide
};

enum class StartupLogos {
	None,
	Custom,
	All
};

struct Game_ConfigPlayer {
	StringConfigParam autobattle_algo{ "", "", "", "", "" };
	StringConfigParam enemyai_algo{ "", "", "", "", "" };
	BoolConfigParam settings_autosave{ "退出时保存设置", "退出时设置自动保存", "Player", "SettingsAutosave", false };
	BoolConfigParam settings_in_title{ "在起始标题显示设置", "在起始标题屏幕上显示设置菜单项", "Player", "SettingsInTitle", false };
	BoolConfigParam settings_in_menu{ "在菜单中显示设置", "在菜单屏幕上显示设置菜单项", "Player", "SettingsInMenu", false };
	EnumConfigParam<StartupLogos, 3> show_startup_logos{
		"启动标志", "启动时显示的标志", "Player", "StartupLogos", StartupLogos::Custom,
		Utils::MakeSvArray("无", "自定义", "全部"),
		Utils::MakeSvArray("none", "custom", "all"),
		Utils::MakeSvArray("不显示任何标志", "显示与游戏绑定的自定义标志", "显示所有标志，包括RPG Maker的标志")};

	void Hide();
};

struct Game_ConfigVideo {
	LockedConfigParam<std::string> renderer{ "渲染", "渲染引擎", "auto" };
	BoolConfigParam vsync{ "垂直同步", "垂直同步(建议：开启)", "Video", "Vsync", true };
	BoolConfigParam fullscreen{ "全屏", "切换全屏模式和窗口模式", "Video", "Fullscreen", true };
	BoolConfigParam show_fps{ "显示FPS", "切换帧率计数器的显示", "Video", "ShowFps", false };
	BoolConfigParam fps_render_window{ "在窗口中显示FPS", "在窗口模式下显示窗口内的FPS", "Video", "FpsRenderWindow", false };
	RangeConfigParam<int> fps_limit{ "帧限制器", "修改每秒帧数限制（建议：60）", "Video", "FpsLimit", DEFAULT_FPS, 0, 99999 };
	ConfigParam<int> window_zoom{ "Window Zoom", "Toggle the window zoom level", "Video", "WindowZoom", 2 };
	EnumConfigParam<ScalingMode, 3> scaling_mode{ "屏幕缩放", "输出画面的缩放方式", "Video", "ScalingMode", ScalingMode::Nearest,
		Utils::MakeSvArray("Nearest", "Integer", "Bilinear"),
		Utils::MakeSvArray("nearest", "integer", "bilinear"),
		Utils::MakeSvArray("缩放到屏幕大小(可能导致缩放瑕疵)", "缩放到游戏分辨率的倍数", "类似Nearest,但画面是模糊的以避免瑕疵")};
	BoolConfigParam stretch{ "拉伸", "拉伸到屏幕的宽度", "Video", "Stretch", false };
	BoolConfigParam touch_ui{ "Touch Ui", "Display the touch ui", "Video", "TouchUi", true };
	EnumConfigParam<GameResolution, 3> game_resolution{ "分辨率", "游戏分辨率,可能重启才能生效", "Video", "GameResolution", GameResolution::Original,
		Utils::MakeSvArray("原始(推荐)", "宽屏(实验)", "超宽(实验)"),
		Utils::MakeSvArray("original", "widescreen", "ultrawide"),
		Utils::MakeSvArray("默认分辨率(320x240, 4:3)", "可能导致故障(416x240, 16:9)", "可能导致故障(560x240, 21:9)")};

	// These are never shown and are used to restore the window to the previous position
	ConfigParam<int> window_x{ "", "", "Video", "WindowX", -1 };
	ConfigParam<int> window_y{ "", "", "Video", "WindowY", -1 };
	ConfigParam<int> window_width{ "", "", "Video", "WindowWidth", -1 };
	ConfigParam<int> window_height{ "", "", "Video", "WindowHeight", -1 };

	void Hide();
};

struct Game_ConfigAudio {
	RangeConfigParam<int> music_volume{ "背景音量", "背景音乐音量", "Audio", "MusicVolume", 100, 0, 100 };
	RangeConfigParam<int> sound_volume{ "音效音量", "音效音量", "Audio", "SoundVolume", 100, 0, 100 };

	void Hide();
};

struct Game_ConfigInput {
	RangeConfigParam<int> speed_modifier_a{ "游戏加速 A", "设置游戏加速A的速度", "Input", "SpeedModifierA", 3, 2, 100 };
	RangeConfigParam<int> speed_modifier_b{ "游戏加速 B", "设置游戏加速B的速度", "Input", "SpeedModifierB", 10, 2, 100 };
	BoolConfigParam gamepad_swap_analog{ "Gamepad:交换摇杆", "交换左右摇杆", "Input", "GamepadSwapAnalog", false };
	BoolConfigParam gamepad_swap_dpad_with_buttons{ "Gamepad:用按钮替换方向键", "用ABXY按钮替换方向键", "Input", "GamepadSwapDpad", false };
	BoolConfigParam gamepad_swap_ab_and_xy{ "Gamepad:替换AB和XY", "用X和Y替换A和B", "Input", "GamepadSwapAbxy", false };
	Input::ButtonMappingArray buttons;

	void Hide();
};

struct Game_Config {
	/** Gameplay subsystem options */
	Game_ConfigPlayer player;

	/** Video subsystem options */
	Game_ConfigVideo video;

	/** Audio subsystem options */
	Game_ConfigAudio audio;

	/** Input subsystem options */
	Game_ConfigInput input;

	/**
	 * Create an application config. This first determines the config file path if any,
	 * loads the config file, then loads command line arguments.
	 */
	static Game_Config Create(CmdlineParser& cp);

	/** @return config file path from command line args if found */
	static std::string GetConfigPath(CmdlineParser& cp);

	/**
	 * Returns the a filesystem view to the global config directory
	 */
	static FilesystemView GetGlobalConfigFilesystem();

	/**
	 * Returns a handle to the global config file for reading.
	 * The file is created if it does not exist.
	 *
	 * @return handle to the global file
	 */
	static Filesystem_Stream::InputStream GetGlobalConfigFileInput();

	/**
	 * Returns a handle to the global config file for writing.
	 * The file is created if it does not exist.
	 *
	 * @return handle to the global file
	 */
	static Filesystem_Stream::OutputStream GetGlobalConfigFileOutput();

	/**
	 * Load configuration values from a stream;
	 *
	 * @param is stream to read from.
	 * @post values of this are updated with values found in the stream.
	 */
	void LoadFromStream(Filesystem_Stream::InputStream& is);

	/**
	 * Load configuration values from a command line arguments.
	 *
	 * @param cp the command line parser to use.
	 * @post values of this are updated with values found in command line args.
	 */
	void LoadFromArgs(CmdlineParser& cp);

	/**
	 * Writes our configuration to the given stream.
	 *
	 * @param os stream to write to
	 */
	void WriteToStream(Filesystem_Stream::OutputStream& os) const;
};

#endif
