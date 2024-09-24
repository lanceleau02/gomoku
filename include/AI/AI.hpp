/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AI.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:01:02 by hsebille          #+#    #+#             */
/*   Updated: 2024/09/24 13:48:57 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "gomoku.hpp"
	
class Bitboard;

enum NodeType { EXACT, LOWERBOUND, UPPERBOUND };

struct TTEntry {
    uint64_t key;    // Clé unique pour la position
    int value;       // Valeur de l'évaluation
    int depth;       // Profondeur à laquelle cette évaluation a été faite
    NodeType type;   // Type de nœud (exact, limite inférieure, limite supérieure)
};

class AI {
	private:
		std::unordered_map<uint64_t, TTEntry>	_transpositionTable;
		static const int						BOARD_SIZE = 19;
		
		uint64_t								_zobristTable[BOARD_SIZE][BOARD_SIZE][2];
		int										_centerScores[BOARD_SIZE][BOARD_SIZE];

	public:
		AI();
		~AI();
		
		int													minimax(Bitboard &bitboard, int depth, bool maximizingPlayer, int alpha, int beta) __attribute__((hot));
		int													heuristic(Bitboard &bitboard, int depth) __attribute__((hot));
		
		int													countStones(Bitboard &bitboard);
		int													checkPatterns(Bitboard &bitboard, int player, int opponent);

		void												play(Bitboard &bitboard);
		
		std::pair<int, int>									findBestMove(Bitboard& bitboard);
		std::vector<std::pair<int, int>>					sortMoves(const std::unordered_set<std::pair<int, int>, pair_hash> &possibleMoves, Bitboard &bitboard, bool maximizingPlayer);
		void												quicksort(std::vector<std::pair<std::pair<int, int>, int>> &vec, int low, int high);
};