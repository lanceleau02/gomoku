/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gameplay.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:23:53 by laprieur          #+#    #+#             */
/*   Updated: 2024/05/14 14:14:41 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gomoku.hpp"

class Gameplay : public Graphics {
	private:
		std::map<std::string, int>				_playerPositions;
		std::map<int, int>						_catchedStones; // Key = player, value = number

	public:
		Gameplay(sf::RenderWindow &window);
		~Gameplay();

		void	circleFollowMouse(sf::RenderWindow &window, sf::Event &event);
		void	placeStone(std::string position, int player);
};
