/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gomoku.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:37:22 by laprieur          #+#    #+#             */
/*   Updated: 2024/07/04 20:14:27 by laprieur         ###   ########.fr       */
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

#include "MainMenu.hpp"
#include "Gameplay.hpp"
#include "Goban.hpp"
#include "CustomMenu.hpp"
#include "SettingsMenu.hpp"
#include "HelpMenu.hpp"
#include "Bitboard.hpp"
#include "AI.hpp"

typedef enum {
	MENU,
	GAME,
	VS_IA,
	CUSTOM,
	HELP,
	SETTINGS,
} GameState;

typedef enum {
	AZURE,
	YELLOW,
	RED,
	ORANGE,
	PINK,
	GREEN,
	GRAY,
	BLACK,
	NOBOARD,
} BoardColor;

typedef enum {
	TOMMY,
	LAURE,
	ALEX,
	HERIC,
	MOUSSE,
	GUNTHER,
	NOAVATAR,
} Avatar;

typedef enum {
	BlackAndWhite,
	GreenAndRed,
	SalmonAndCoral,
	PinkAndFluoYellow,
	BlackAndYellow,
	OrangeAndViolet,
	DarkGreenAndLightGreen,
	TurquoiseGreenAndIndigo,
	NOSTONECOLOR,
} StonesColors;

typedef enum {
	ENABLED,
	DISABLED,
} MoveSuggestion;

typedef enum {
	NOAIMODE,
	IMPOSSIBLE,
	AGGRESSIVE,
	PASSIVE,
	DEFENSIVE,
} AIMode;

typedef enum {
	RULES,
	CAPTURES,
	DOUBLETHREE,
} HelpMenuState;

extern int				musicVolume;
extern sf::Sound		sound;
extern GameState		gameState;
extern BoardColor		boardColor;
extern Avatar			playerOneAvatar;
extern Avatar			playerTwoAvatar;
extern StonesColors		stonesColors;
extern MoveSuggestion	moveSuggestion;
extern AIMode			aiMode;
extern HelpMenuState	helpMenuState;