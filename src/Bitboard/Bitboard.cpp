/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bitboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:46:19 by laprieur          #+#    #+#             */
/*   Updated: 2025/01/07 13:24:50 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bitboard/Bitboard.hpp"

Bitboard::Bitboard() {
	clear();
}

Bitboard::~Bitboard() {}

bool	Bitboard::placeStone(int x, int y, int player) {
	uint32_t	mask = uint32_t(1) << x;

	if (!isLegalMove(x, y, player))
		return (false);

	(player == 1) ? _firstPlayerBoardLines[y] |= mask : _secondPlayerBoardLines[y] |= mask;

	update(x, y, player, true);
	
	std::vector<std::pair<int, int>> onverraplustard;

	int captures = makeCapture(x, y, player, onverraplustard);
	(player == 1) ? playersCaptures[0] += captures : playersCaptures[1] += captures;

	if (fiveInARow() || (playersCaptures[0] >= 5 || playersCaptures[1] >= 5)) {
		gameEndTime = std::chrono::steady_clock::now();
		if (player == 1)
			endGameState = P1VICTORY;
		else if (player == 2 && gameState != AIVERSUS)
			endGameState = P2VICTORY;
		else
			endGameState = AIVICTORY;
	} else if (draw()) {
		endGameState = SEEGAMESTATE;
	}
	return (true);
}

std::vector<std::pair<int, int>>	Bitboard::placeStoneAI(int x, int y, int player, bool mode) {
	uint32_t							mask = uint32_t(1) << x;
	std::vector<std::pair<int, int>>	removedStones;

	(player == 1) ? _firstPlayerBoardLines[y] |= mask : _secondPlayerBoardLines[y] |= mask;
	update(x, y, player, true);
	
	if (mode)
		makeCapture(x, y, player, removedStones);
	
	return removedStones;
}

void	Bitboard::removeStone(int x, int y, int player) {
	uint32_t mask = uint32_t(1) << x;

	if (getBit(x, y)) {
		if (player == 1) {
			_firstPlayerBoardLines[y] &= ~mask;
			update(x, y, 1, false);
		} else {
			_secondPlayerBoardLines[y] &= ~mask;
			update(x, y, 2, false);
		}
	}
}
