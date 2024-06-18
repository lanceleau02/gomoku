/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Goban.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:23:35 by laprieur          #+#    #+#             */
/*   Updated: 2024/06/18 14:43:09 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gomoku.hpp"

class Goban : public Graphics {
	private:
		// Fonts
		sf::Font								_exo2BlackFont;
		sf::Font								_ex02BlackItalicFont;
		//Textures
		sf::Texture								_lanceAvatarTexture;
		sf::Texture								_tommyAvatarTexture;
		sf::Texture								_alexAvatarTexture;
		sf::Texture								_guntherAvatarTexture;
		sf::Texture								_hericAvatarTexture;
		sf::Texture								_laureAvatarTexture;
		sf::Texture								_returnArrowTexture;
		sf::Texture								_returnArrowHighlightTexture;
		sf::Texture								_gridTexture;
		sf::Texture 							_gobanAzureTexture;
		sf::Texture 							_gobanBlackTexture;
		sf::Texture 							_gobanGrayTexture;
		sf::Texture 							_gobanGreenTexture;
		sf::Texture 							_gobanOrangeTexture;
		sf::Texture 							_gobanPinkTexture;
		sf::Texture 							_gobanRedTexture;
		sf::Texture 							_gobanYellowTexture;
		// Sprites
		sf::Sprite								_firstPlayerAvatar;
		sf::Sprite								_secondPlayerAvatar;
		sf::Sprite								_goban;
		sf::Sprite								_returnArrow;
		sf::Sprite								_grid;
		// Text
		sf::Text								_backToMenu;
		sf::Text								_player1;
		sf::Text								_player2;
		sf::Text								_capturedStones;
		sf::Text								_capturedStones2;
		sf::Text								_totalTimer;
		sf::Text								_totalTimer2;
		sf::Text								_lastMoveTimer;
		sf::Text								_lastMoveTimer2;

	public:
		Goban(sf::RenderWindow &window);
		~Goban();

		void	display(sf::Event& event, sf::RenderWindow &window);
		void	gobanInit();
		void	drawPlayerPositions(sf::RenderWindow &window, std::map<std::string, int> playerPositions);
		void	returnButton(sf::Event &event, sf::RenderWindow &window);
};