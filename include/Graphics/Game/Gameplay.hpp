/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gameplay.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:03:52 by laprieur          #+#    #+#             */
/*   Updated: 2024/08/13 16:04:32 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gomoku.hpp"

enum pageTextures {
	BACKWARDBUTTON,
	BACKWARDHOVEREDBUTTON,
	GRIDANDINDEX,
	VSPAGE,
	AIVERSUSPAGE
};

enum popUpTextures {
	FORBIDDENMOVE,
	MEGATRONVICTORY,
	PLAYER1VICTORY,
	PLAYER2VICTORY,
	MAINMENUBUTTON,
	MAINMENUHOVEREDBUTTON,
	PLAYAGAINBUTTON,
	PLAYAGAINHOVEREDBUTTON
};

enum Statistics {
	CAPTUREDSTONES,
	TOTALPLAYTIME,
	LASTMOVETIME
};

class Bitboard;

class Gameplay {
	private:
		float						_cellSize;
		sf::Font					_font;
		sf::Sprite					_firstPlayerAvatarSprite;
		sf::Sprite					_secondPlayerAvatarSprite;
		sf::Sprite					_gobanSprite;
		sf::Sprite					_backwardButtonSprite;
		sf::Sprite					_gridAndIndexSprite;
		sf::Sprite					_gamePageSprite;
		sf::Sprite					_firstPlayerStoneSprite;
		sf::Sprite					_secondPlayerStoneSprite;
		std::thread					_aiThread;
		std::atomic<int>			_currentPlayer{1};
		std::atomic<bool>			_isAIPlaying{true};
		std::atomic<bool>			_aiThreadRunning{false};
		std::atomic<bool>			_stopAITimer{false};
		std::vector<sf::Text>		_player1Stats;
		std::vector<sf::Text>		_player2Stats;
		std::vector<sf::Texture>	_pageTextures;
		std::vector<sf::Texture>	_popupTextures;
		std::vector<sf::Texture>	_stonesTextures;
		std::vector<sf::Texture>	_avatarsTextures;
		std::vector<sf::Texture>	_boardsTextures;
		// sf::Texture					_popupTexture;
		sf::Sprite					_popupSprite;
		sf::Sprite					_popupMainMenuButtonSprite;
		sf::Sprite					_popupPlayAgainButtonSprite;

	public:
		Gameplay();
		~Gameplay();

		void	init();
		void	display(const sf::Event& event, sf::RenderWindow& window, Bitboard& bitboard);
		void	returnButton(const sf::Event& event, const sf::RenderWindow& window);
		void	statistics(sf::RenderWindow& window);
		void	popUp(const sf::Event& event, sf::RenderWindow& window, Bitboard& bitboard);
		void	drawStones(sf::RenderWindow& window, const Bitboard& bitboard);
		void	defineStones();
		void	defineAvatars();
		void	defineBoard();
		void	mouseHover(sf::RenderWindow& window, Bitboard& bitboard, bool isAIPlaying);
		void	AITurn(Bitboard& bitboard);
};