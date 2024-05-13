/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Goban.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:22:21 by laprieur          #+#    #+#             */
/*   Updated: 2024/05/13 15:46:56 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

Goban::Goban(sf::RenderWindow &window) : Graphics(window) {}

Goban::~Goban() {}

void	Goban::display(sf::RenderWindow &window) {
	// Display the grid
	for (int i = 0; i < 19; i++) {
		sf::Vertex verticalLine[] =
		{
			sf::Vertex(sf::Vector2f((_gridSize / 18) * i + _gridStartPoint.first, _gridStartPoint.second)),
			sf::Vertex(sf::Vector2f((_gridSize / 18) * i + _gridStartPoint.first, _gridStartPoint.second + _gridSize))
		};

		sf::Vertex horizontalLine[] =
		{
			sf::Vertex(sf::Vector2f(_gridStartPoint.first, (_gridSize / 18) * i + _gridStartPoint.second)),
			sf::Vertex(sf::Vector2f(_gridStartPoint.first + _gridSize, (_gridSize / 18) * i + _gridStartPoint.second))
		};

		window.draw(verticalLine, 2, sf::Lines);
		window.draw(horizontalLine, 2, sf::Lines);
	}

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/arial.ttf")) {
		return ;
	}

	for (int i = 1; i < 20; i++) {
		std::string number = std::to_string(i);
		std::string letter(1, '@' + i);
		sf::Text xIndex(letter, font, 15);
		sf::Text yIndex(number, font, 15);
		xIndex.setPosition((_windowWidth - _gridSize) / 2 + _cellSize * i - _cellSize - 7, _gridSize + 45);
		yIndex.setPosition((_windowWidth - _gridSize) / 2 - 40, _gridSize - _cellSize * i + _cellSize + 25);
		window.draw(xIndex);
		window.draw(yIndex);
	}
}
