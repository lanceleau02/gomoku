/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:51:50 by hsebille          #+#    #+#             */
/*   Updated: 2024/05/20 16:05:02 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

bool displayMenu = true;
bool displayGame = false;

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gomoku");
	MainMenu mainMenu(window.getSize().x, window.getSize().y);
	Gameplay gameplay(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			mainMenu.handleKeys(event, window);
		}   

		if (displayMenu == true) {
			window.clear(sf::Color::Black);
			mainMenu.display(window);
			window.display();
		}
		else if (displayGame == true) {
			gameplay.circleFollowMouse(window, event);
			window.display();
		}
	}
}
