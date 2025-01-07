/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AI.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:23:02 by hsebille          #+#    #+#             */
/*   Updated: 2025/01/07 17:40:48 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gomoku.hpp"

class Bitboard;

#define IMPOSSIBLE_AI_DEPTH 10
#define CHALLENGING_AI_DEPTH 6
#define EASY_AI_DEPTH 4
#define MOVE_SUGGESTION_DEPTH 2
#define MAX_TESTED_MOVES 6
#define NB_HEURISTIC_PATTERNS 46

struct Move {
	std::pair<int, int> position;
	int score;
};

class AI {
	private:
		static const int	BOARD_SIZE = 19;
		std::unordered_map<int, int>	_heuristicValuesOfBoards;
		
		int								_firstPlayerNbCaptures;
		int								_secondPlayerNbCaptures;

		int		heuristic(Bitboard &bitboard) __attribute__((hot));
		int		checkPatterns(Bitboard &bitboard, int player, int opponent);
		int		evaluateAlignments(Bitboard& bitboard);


		void	quicksort(std::vector<std::pair<std::pair<int, int>, int>> &vec, int low, int high);

		std::vector<std::pair<int, int>>	sortMoves(const std::unordered_set<std::pair<int, int>, pair_hash> &possibleMoves, Bitboard &bitboard, bool maximizingPlayer);
		Move								negamax(Bitboard &bitboard, int depth, bool aiTurn, int alpha, int beta) __attribute__((hot));

	public:
		AI();
		~AI();

        std::pair<int, int>	suggestMove(Bitboard &bitboard, int player);
		void				play(Bitboard &bitboard);
		void				crazyMode(Bitboard &bitboard);
};