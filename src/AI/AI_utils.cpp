/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AI_utils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:29:01 by hsebille          #+#    #+#             */
/*   Updated: 2024/11/09 16:59:42 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AI/AI.hpp"

int partition(std::vector<std::pair<std::pair<int, int>, int>> &vec, int low, int high) {
	int mid = low + (high - low) / 2;

	if (vec[low].second > vec[mid].second) std::swap(vec[low], vec[mid]);
	if (vec[low].second > vec[high].second) std::swap(vec[low], vec[high]);
	if (vec[mid].second > vec[high].second) std::swap(vec[mid], vec[high]);

	std::swap(vec[low], vec[mid]);

	int pivot = vec[low].second;
	int i = low - 1, j = high + 1;

	while (true) {
		do {
			i++;
		} while (vec[i].second < pivot);

		do {
			j--;
		} while (vec[j].second > pivot);

		if (i >= j)
			return j;

		std::swap(vec[i], vec[j]);
	}
}

void AI::quicksort(std::vector<std::pair<std::pair<int, int>, int>> &vec, int low, int high) {
	if (low < high) {
		int pivot = partition(vec, low, high);

		quicksort(vec, low, pivot);
		quicksort(vec, pivot + 1, high);
	}
}

std::vector<std::pair<int, int>>	AI::sortMoves(const std::unordered_set<std::pair<int, int>, pair_hash> &possibleMoves, Bitboard &bitboard, bool maximizingPlayer) {
	std::vector<std::pair<std::pair<int, int>, int>>	movesToSort;
	std::vector<std::pair<int, int>>					sortedMoves;

	for (const auto& move : possibleMoves) {
		std::pair<std::pair<int, int>, int> moveAndValue;
		std::vector<std::pair<int, int>> removedStones = bitboard.placeStoneAI(move.first, move.second, maximizingPlayer ? 2 : 1, true);
		moveAndValue.second = heuristic(bitboard);
		for (const auto& stone : removedStones)
			bitboard.placeStoneAI(stone.first, stone.second, maximizingPlayer ? 1 : 2, false);
		bitboard.removeStone(move.first, move.second, maximizingPlayer ? 2 : 1);
		moveAndValue.first = move;
		movesToSort.push_back(moveAndValue);
	}
	
	quicksort(movesToSort, 0, movesToSort.size() - 1);

	if (maximizingPlayer) {
		for (size_t i = 0; i < movesToSort.size(); i++)
			sortedMoves.insert(sortedMoves.begin(), movesToSort[i].first);
	}
	if (!maximizingPlayer) {
		for (size_t i = 0; i < movesToSort.size(); i++)
			sortedMoves.push_back(movesToSort[i].first);
	}

	return sortedMoves;
}