/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gameplay.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:46:26 by laprieur          #+#    #+#             */
/*   Updated: 2024/12/21 16:57:23 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphics/Game/Gameplay.hpp"

Gameplay::Gameplay() : _playerJustMoved(0), _isFirstMove(true), _didSuggestMove(false), _cellSize(868 / 19.0f), _player1Stats(3), _player2Stats(3) {
	init();
}

Gameplay::~Gameplay() {
	if (_aiThread.joinable())
		_aiThread.join();
}

void	Gameplay::moveSuggestion(sf::RenderWindow& window) {
	std::pair <unsigned int, unsigned int>	startPoint = std::make_pair(527, 50);
	sf::Vector2f nearestIntersection(startPoint.first + _suggestedMove.first * 48, startPoint.second + _suggestedMove.second * 48);
	if (_currentPlayer == 1) {
		sf::Color spriteColor = _firstPlayerMoveSuggestionSprite.getColor();
		_firstPlayerMoveSuggestionSprite.setColor(sf::Color(spriteColor.r, spriteColor.g, spriteColor.b, 150));
		_firstPlayerMoveSuggestionSprite.setPosition(nearestIntersection.x - 13, nearestIntersection.y - 13);
		window.draw(_firstPlayerMoveSuggestionSprite);
	} else if (_currentPlayer == 2) {
		sf::Color spriteColor = _secondPlayerMoveSuggestionSprite.getColor();
		_secondPlayerMoveSuggestionSprite.setColor(sf::Color(spriteColor.r, spriteColor.g, spriteColor.b, 150));
		_secondPlayerMoveSuggestionSprite.setPosition(nearestIntersection.x - 13, nearestIntersection.y - 13);
		window.draw(_secondPlayerMoveSuggestionSprite);
	}
}

void	Gameplay::mouseHover(sf::RenderWindow& window, Bitboard& bitboard) {
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
	
	if (_isFirstMove) {
		if (gameState == AIVERSUS)
			_currentPlayer = 2;
		else
			_currentPlayer = 1;
		setStatistics(_player1Stats, _font, 1);
		setStatistics(_player2Stats, _font, 2);
	}
	
	if (gameState == AIVERSUS && !bitboard.isGameOver() && _currentPlayer == 2 && !_aiThreadRunning) {
		_stopAITimer = false;
		_aiThreadRunning = true;
		aiPlaying = true;
		_aiThread = std::thread(&Gameplay::AITurn, this, std::ref(bitboard));
		if (_aiThread.joinable()) {
			_aiThread.join();
		}
	}
	
	if (!isStonePlaceable && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (col >= 0 && col < 19 && row >= 0 && row < 19) {
			PatternInfo pattern = {0b0110, 0b1001, 5, 1, 1};

			if (bitboard.findSinglePattern(pattern, col, row)) {
				std::cout << "Wallah il a trouvé le pattern." << std::endl;
			}

			if ((_currentPlayer == 1 && bitboard.placeStone(col, row, _currentPlayer))
			|| (gameState != AIVERSUS && bitboard.placeStone(col, row, _currentPlayer))) {
				if (_isFirstMove) {
					_isFirstMove = false;
					_moveStartTime = std::chrono::steady_clock::now();
					_lastMoveDuration = _moveStartTime - gameStartTime;
				} else {
					_moveEndTime = std::chrono::steady_clock::now();
					_lastMoveDuration = _moveEndTime - _moveStartTime;
					_moveStartTime = _moveEndTime;
				}
				isStonePlaceable = true;
				_playerJustMoved = _currentPlayer;
				_didSuggestMove = false;
				if (_playerJustMoved == 1)
					_player1TotalTime += _lastMoveDuration;
				else
					_player2TotalTime += _lastMoveDuration;
				_currentPlayer = (_currentPlayer == 1) ? 2 : 1;
			}
		}
	}

	if (moveSuggestionEnabled == true && gameState != AIVERSUS && _didSuggestMove == false) {
		_didSuggestMove = true;
		AI ai;
		_suggestedMove = ai.moveSuggestion(bitboard, _currentPlayer);
	}
	if (moveSuggestionEnabled == true && gameState != AIVERSUS && _didSuggestMove == true)
		moveSuggestion(window);
	if (_currentPlayer == 1)
		window.draw(_firstPlayerStoneSprite);
	else if (!_aiThreadRunning)
		window.draw(_secondPlayerStoneSprite);
}

void	Gameplay::AITurn(Bitboard& bitboard) {
	AI ai;
	ai.play(bitboard);
	if (_isFirstMove) {
		_isFirstMove = false;
		_moveStartTime = std::chrono::steady_clock::now();
		_lastMoveDuration = _moveStartTime - gameStartTime;
	} else {
		_moveEndTime = std::chrono::steady_clock::now();
		_lastMoveDuration = _moveEndTime - _moveStartTime;
		_moveStartTime = _moveEndTime;
	}
	_playerJustMoved = 2;
	if (_playerJustMoved == 1)
		_player1TotalTime += _lastMoveDuration;
	else
		_player2TotalTime += _lastMoveDuration;
	_currentPlayer = 1;
	aiPlaying = false;
	_aiThreadRunning = false;
}
