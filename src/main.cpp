/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:28:37 by hsebille          #+#    #+#             */
/*   Updated: 2024/07/09 23:05:25 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

int				musicVolume		= 100;
AIMode			aiMode			= NOAIMODE;
Avatar			playerOneAvatar	= NOAVATAR;
Avatar			playerTwoAvatar	= NOAVATAR;
BoardColor		boardColor		= NOBOARD;
GameState		gameState		= MENU;
HelpMenuState	helpMenuState	= RULES;
MoveSuggestion	moveSuggestion	= ENABLED;
StonesColors	stonesColors	= NOSTONESCOLORS;

#include <chrono>

int main() {
	sf::RenderWindow	window(sf::VideoMode(1920, 1080), "Gomoku");
	sf::Texture			cursorTexture;
	sf::Sprite			cursorSprite;
	MainMenu			mainMenu;
	CustomMenu			customMenu;
	SettingsMenu		settingsMenu;
	HelpMenu			helpMenu;
	Music				music;
	Gameplay			gameplay;
	Goban				goban;
	Bitboard			bitboard;

	if (!cursorTexture.loadFromFile("assets/images/icons/cursor.png")) {
		std::cerr << "Error: could not load cursor texture" << std::endl;
		return 1;
	}
	
	cursorSprite.setTexture(cursorTexture);
	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			mainMenu.handleKeys(event, window);
			customMenu.handleKeys(event, window);
			settingsMenu.handleKeys(event, window);
			settingsMenu.handleVolume(event, window, music);
			helpMenu.handleKeys(event, window);
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
				window.close();
		}   
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		cursorSprite.setPosition(mousePos.x, mousePos.y);
		music.playMusic();
		switch (gameState) {
			case MENU:
				mainMenu.display(window);
				break;
			case GAME:
			case AIVERSUS:
				goban.display(event, window, bitboard);
				gameplay.mouseHover(window, bitboard, (gameState == GAME) ? false : true);
				break;
			case CUSTOM:
				customMenu.display(window);
				break;
			case SETTINGS:
				settingsMenu.display(window);
				break;
			case HELP:
				helpMenu.display(window);
				break;
			default:
				break;				
		}
		window.draw(cursorSprite);
		window.display();
	}
}
