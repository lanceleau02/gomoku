/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gomoku.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:37:22 by laprieur          #+#    #+#             */
/*   Updated: 2024/07/31 15:42:16 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <bitset>
#include <limits.h>
#include <unordered_set>
#include <atomic>
#include <thread>
#include <unordered_map>
#include <chrono>
#include <future>

struct PatternInfo {
	uint32_t	pattern;
	uint32_t	opponentPattern;
	int			patternSize;
	int			playerType;
	int			multiplier;
};

#include "MainMenu.hpp"
#include "Gameplay.hpp"
#include "CustomMenu.hpp"
#include "SettingsMenu.hpp"
#include "HelpMenu.hpp"
#include "Bitboard.hpp"
#include "AI.hpp"
#include "Music.hpp"

enum AIMode {
	IMPOSSIBLE,
	AGGRESSIVE,
	PASSIVE,
	DEFENSIVE,
	NOAIMODE
};

enum Avatar {
	TOMMY,
	LAURE,
	ALEX,
	HERIC,
	MOUSSE,
	GUNTHER,
	NOAVATAR
};

enum BoardColor {
	AZURE,
	YELLOW,
	RED,
	ORANGE,
	PINK,
	GREEN,
	GRAY,
	BLACK,
	NOBOARD
};

enum GameState {
	MENU,
	GAME,
	AIVERSUS,
	CUSTOM,
	HELP,
	SETTINGS,
	NONE
};

enum HelpMenuState {
	RULES,
	CAPTURES,
	DOUBLETHREE
};

enum MoveSuggestion {
	ENABLED,
	DISABLED
};

enum StonesColors {
	BLACK_WHITE,
	GREEN_RED,
	SALMON_CORAL,
	PINK_FLUOYELLOW,
	BLACK_YELLOW,
	ORANGE_VIOLET,
	DARKGREEN_LIGHTGREEN,
	TURQUOISEGREEN_INDIGO,
	NOSTONESCOLORS
};

extern int				musicVolume;
extern AIMode			aiMode;
extern Avatar			playerOneAvatar;
extern BoardColor		boardColor;
extern GameState		gameState;
extern HelpMenuState	helpMenuState;
extern MoveSuggestion	moveSuggestion;
extern StonesColors		stonesColors;

void	loadTextures(int nbTextures, const std::string pathStart, const std::string prefixes[], std::vector<sf::Texture>& textures);
void	setTextures(int nbTextures, const std::vector<sf::Texture>& textures, std::vector<sf::Sprite>& sprites);
void	setPosition(int nbSprites, std::vector<sf::Sprite>& sprites, int x, int y, int offset);
void	setPosition(sf::Sprite& sprite, int x, int y);