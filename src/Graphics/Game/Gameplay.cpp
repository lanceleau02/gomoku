/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gameplay.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:50:06 by hsebille          #+#    #+#             */
/*   Updated: 2024/06/25 15:50:20 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

using namespace std;

Gameplay::Gameplay() {
	for (int i = 0; i < 19; i++) {
		int character = 'A' + i;
		for (int j = 1; j < 20; j++) {
			string position = string(1, character) + to_string(j);
			_playerPositions.insert(pair<string, int>(position, 0));
		}
	}
	
	_currentPlayer = 1;
    _gridPosition = sf::Vector2f(525, 48);
    _gridSize = 868;
    _cellSize = _gridSize / 19.0f;
	
	if (!_blackStoneTexture.loadFromFile("assets/images/game/stones/blackStoneTexture.png"))
		cerr << "Error while loading the blackStoneTexture file." << endl;
	if (!_whiteStoneTexture.loadFromFile("assets/images/game/stones/whiteStoneTexture.png"))
		cerr << "Error while loading the whiteStoneTexture file." << endl;
	if (!_coralStoneTexture.loadFromFile("assets/images/game/stones/coralStoneTexture.png"))
		cerr << "Error while loading the coralStoneTexture file." << endl;
	if (!_darkGreenStoneTexture.loadFromFile("assets/images/game/stones/darkGreenStoneTexture.png"))
		cerr << "Error while loading the darkGreenStoneTexture file." << endl;
	if (!_lightGreenStoneTexture.loadFromFile("assets/images/game/stones/lightGreenStoneTexture.png"))
		cerr << "Error while loading the lightGreenStoneTexture file." << endl;
	if (!_violetStoneTexture.loadFromFile("assets/images/game/stones/violetStoneTexture.png"))
		cerr << "Error while loading the violetStoneTexture file." << endl;
	if (!_yellowStoneTexture.loadFromFile("assets/images/game/stones/yellowStoneTexture.png"))
		cerr << "Error while loading the yellowStoneTexture file." << endl;
	if (!_fluoYellowStoneTexture.loadFromFile("assets/images/game/stones/fluoYellowStoneTexture.png"))
		cerr << "Error while loading the fluoYellowStoneTexture file." << endl;
	if (!_pinkStoneTexture.loadFromFile("assets/images/game/stones/pinkStoneTexture.png"))
		cerr << "Error while loading the pinkStoneTexture file." << endl;
	if (!_greenStoneTexture.loadFromFile("assets/images/game/stones/greenStoneTexture.png"))
		cerr << "Error while loading the greenStoneTexture file." << endl;
	if (!_indigoStoneTexture.loadFromFile("assets/images/game/stones/indigoStoneTexture.png"))
		cerr << "Error while loading the indigoStoneTexture file." << endl;
	if (!_orangeStoneTexture.loadFromFile("assets/images/game/stones/orangeStoneTexture.png"))
		cerr << "Error while loading the orangeStoneTexture file." << endl;
	if (!_redStoneTexture.loadFromFile("assets/images/game/stones/redStoneTexture.png"))
		cerr << "Error while loading the redStoneTexture file." << endl;
	if (!_salmonStoneTexture.loadFromFile("assets/images/game/stones/salmonStoneTexture.png"))
		cerr << "Error while loading the salmonStoneTexture file." << endl;
	if (!_turquoiseGreenStoneTexture.loadFromFile("assets/images/game/stones/turquoiseGreenStoneTexture.png"))
		cerr << "Error while loading the turquoiseGreenStoneTexture file." << endl;

	_firstPlayerStoneSprite.setTexture(_blackStoneTexture);
	_secondPlayerStoneSprite.setTexture(_whiteStoneTexture);
}

Gameplay::~Gameplay() {}

void	Gameplay::selectTextures() {
	if (stonesColors == BlackAndWhite) {
		_firstPlayerStoneSprite.setTexture(_blackStoneTexture);
		_secondPlayerStoneSprite.setTexture(_whiteStoneTexture);
	} else if (stonesColors == GreenAndRed) {
		_firstPlayerStoneSprite.setTexture(_greenStoneTexture);
		_secondPlayerStoneSprite.setTexture(_redStoneTexture);
	} else if (stonesColors == SalmonAndCoral) {
		_firstPlayerStoneSprite.setTexture(_salmonStoneTexture);
		_secondPlayerStoneSprite.setTexture(_coralStoneTexture);
	} else if (stonesColors == PinkAndFluoYellow) {
		_firstPlayerStoneSprite.setTexture(_pinkStoneTexture);
		_secondPlayerStoneSprite.setTexture(_fluoYellowStoneTexture);
	} else if (stonesColors == BlackAndYellow) {
		_firstPlayerStoneSprite.setTexture(_blackStoneTexture);
		_secondPlayerStoneSprite.setTexture(_yellowStoneTexture);
	} else if (stonesColors == OrangeAndViolet) {
		_firstPlayerStoneSprite.setTexture(_orangeStoneTexture);
		_secondPlayerStoneSprite.setTexture(_violetStoneTexture);
	} else if (stonesColors == DarkGreenAndLightGreen) {
		_firstPlayerStoneSprite.setTexture(_darkGreenStoneTexture);
		_secondPlayerStoneSprite.setTexture(_lightGreenStoneTexture);
	} else if (stonesColors == TurquoiseGreenAndIndigo) {
		_firstPlayerStoneSprite.setTexture(_turquoiseGreenStoneTexture);
		_secondPlayerStoneSprite.setTexture(_indigoStoneTexture);
	}
}

void	Gameplay::handleKeys(sf::Event& event, sf::RenderWindow& window) {
	(void)window;
	(void)event;

	if (gameState == GAME) {
		//mouseHover(window, event);
	}
}

void	Gameplay::mouseHover(sf::RenderWindow &window, Bitboard &bitboard, bool isAIPlaying) {
	// selectTextures();

	float cellSize = 48;
	std::pair <unsigned int, unsigned int>	startPoint = std::make_pair(527, 50);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);	
	if (mousePosition.x > 525 + 868 || mousePosition.y > 48 + 868)
		return ;
	
	float xIndex = std::round((mousePosition.x - startPoint.first) / cellSize);
	float yIndex = std::round((mousePosition.y - startPoint.second) / cellSize);

	sf::Vector2f nearestIntersection(startPoint.first + xIndex * cellSize, startPoint.second + yIndex * cellSize);
	_firstPlayerStoneSprite.setPosition(nearestIntersection.x - 13, nearestIntersection.y - 13);
	_secondPlayerStoneSprite.setPosition(nearestIntersection.x - 13, nearestIntersection.y - 13);

	sf::Vector2i stonePos(nearestIntersection.x, nearestIntersection.y);

	sf::Vector2f worldPos = window.mapPixelToCoords(stonePos);
		
	float relativeX = worldPos.x - startPoint.first;
    float relativeY = worldPos.y - startPoint.second;

	int col = static_cast<int>(relativeX / _cellSize);
    int row = static_cast<int>(relativeY / _cellSize);

	if (col >= 0 && col < 19 && row >= 0 && row < 19) {
		if (bitboard.getBit(col, row) != 0)
			return ;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (col >= 0 && col < 19 && row >= 0 && row < 19) {
			if ((_currentPlayer == 1 && bitboard.placeStone(col, row, _currentPlayer)) || (!isAIPlaying && bitboard.placeStone(col, row, _currentPlayer))) {
				if (_currentPlayer == 1)
					_currentPlayer = 2;
				else
					_currentPlayer = 1;
			}
		}
		sf::sleep(sf::milliseconds(100));
	}

	if (isAIPlaying && _currentPlayer == 2) {
		AI ai;
		ai.play(bitboard);
		_currentPlayer = 1;
	}

	if (_currentPlayer == 1)
		window.draw(_firstPlayerStoneSprite);
	else
		window.draw(_secondPlayerStoneSprite);
}
