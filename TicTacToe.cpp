#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>

#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	choosePlayerType();
}

void TicTacToe::play()
{
	if (!this->isPlayerTypeChoosed) this->choosePlayerType();
	if (!this->isMultiPlayer) this->chooseDifficulty();

	do {
		this->playerPlay();
	} while (!isGameFinished);

	std::cout << "Game Over";
}

void TicTacToe::playerPlay()
{
	std::string playerInput;
	bool validKey = false;
	this->draw();
	while (!validKey && !this->isGameFinished) {
		this->getPlayerInput(playerInput);
		if (this->contains(this->allowedPlayKeys, playerInput)) {
			int position = std::stoi(playerInput) - 1;
			if (!this->positionAvailable(position)) {
				std::cout << playerInput << " Posistion already occupied." << std::endl;
				continue;
			}
			validKey = true;
			this->markPosition(position);
			if (!this->isMultiPlayer && !this->isGameFinished) this->botPlay();
		}
		else {
			std::cout << "Please Enter Values Between 1 to 9" << std::endl;
		}
	}
	this->draw();
}

void TicTacToe::botPlay()
{
	while (true) {
		srand((unsigned)time(NULL));
		int position = (1 + std::rand() % 9) - 1;
		if (this->positionAvailable(position)) {
			this->markPosition(position);
			break;
		}
	}
}

void TicTacToe::chooseDifficulty()
{
	std::cout << "Please choose game difficulty by entering below values" << std::endl;
	this->printInputChooseDifficultySamples();
	std::string playerInput;
	while (!this->isGameDifficultyChoosed) {
		this->getPlayerInput(playerInput);
		if (this->markGameDifficulty(playerInput) == false) {
			std::cout << "Please enter valid input" << std::endl;
			this->printInputChooseDifficultySamples();
		}
		else {
			this->isGameDifficultyChoosed = true;
		}
	}
}

bool TicTacToe::positionAvailable(int position)
{
	return this->spaces[position] == this->space;
}

bool TicTacToe::threeSame(char first, char second, char third)
{
	char arr[3] = { first, second, third };
	if (this->contains(arr, this->space)) {
		return false;
	}
	return first == second && second == third && third == first;
}

void TicTacToe::choosePlayerType()
{
	std::cout << "Please choose multi player or single player by entering below values" << std::endl;
	this->printInputChoosePlayerSamples();
	std::string playerInput;
	while (!this->isPlayerTypeChoosed) {
		this->getPlayerInput(playerInput);
		if (markAsMultiplayer(playerInput) == false && markAsSinglePlayer(playerInput) == false) {
			std::cout << "Please enter valid input" << std::endl;
			this->printInputChoosePlayerSamples();
		}
		else {
			this->isPlayerTypeChoosed = true;
		}
	}
}

void TicTacToe::draw()
{
	this->printDrawDetails();
	for (int i = 0; i < 3; i++) {
		for (int j = i; j < (i + 3); j++) {
			std::cout << placeVal(i + i + j);
			if (j == 2 + i) break;
			std::cout << this->stright;
		}
		std::cout << std::endl;
		if (i == 2) break;
		std::cout << this->downFour << this->stright << this->downFour << this->stright << this->downFour << std::endl;
	}

	if (this->isMultiPlayer && !this->isGameFinished) {
		std::string playerTurnText = this->playerTurn == PlayerTurn::FIRST ? "First Player Turn" : "Second Player Turn";
		std::cout << std::endl << playerTurnText << std::endl;
	}
}

std::string TicTacToe::placeVal(int index)
{
	std::string fiveSpaces = "    ";
	if (this->spaces[index] == this->space) return fiveSpaces;

	std::string val = "  ";
	return val + this->spaces[index] + val.substr(0, 1);
}

void TicTacToe::screenClear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

bool TicTacToe::markAsMultiplayer(std::string playerInput)
{
	if (!this->contains(this->multiPlayeKeys, playerInput)) return false;

	this->isMultiPlayer = true;
	this->gameDifficulty = GameDiffiCulty::NONE;
	this->isGameDifficultyChoosed = true;
	std::cout << "You have choosen multiplayer game." << std::endl << std::endl << std::endl;
	return true;
}

bool TicTacToe::markAsSinglePlayer(std::string playerInput)
{
	if (!this->contains(this->singlePlayeKeys, playerInput)) return false;

	this->isMultiPlayer = false;
	std::cout << "You have choosen single player game and bot will play opposite possition." << std::endl << std::endl << std::endl;
	return true;
}

bool TicTacToe::markGameDifficulty(std::string playerInput)
{
	if (this->contains(this->difficultyEasyKeys, playerInput)) {
		this->gameDifficulty = GameDiffiCulty::EASY;
		std::cout << "You have choosen easy game." << std::endl << std::endl << std::endl;
		return true;
	}

	if (this->contains(this->difficultyMediumKeys, playerInput)) {
		this->gameDifficulty = GameDiffiCulty::MEDIUM;
		std::cout << "You have choosen medium game." << std::endl << std::endl << std::endl;
		return true;
	}

	if (this->contains(this->difficultyHardKeys, playerInput)) {
		this->gameDifficulty = GameDiffiCulty::HARD;
		std::cout << "You have choosen hard game." << std::endl << std::endl << std::endl;
		return true;
	}

	return false;
}

void TicTacToe::markPosition(int position)
{
	this->spaces[position] = this->playerTurn == PlayerTurn::FIRST ? GameSymbol::CROSS : GameSymbol::NOUGHT;
	this->playerTurn = this->playerTurn == PlayerTurn::FIRST ? PlayerTurn::SECOND : PlayerTurn::FIRST;
	this->findWinner();
}

void TicTacToe::findWinner()
{
	for (int i = 0; i < 3; i++) {
		if (this->threeSame(this->spaces[i * 3], this->spaces[(i * 3) + 1], this->spaces[(i * 3) + 2])) {
			std::cout << i << " row ";
			this->isGameFinished = true;
		}

		if (this->threeSame(this->spaces[i * 1], this->spaces[i + 3], this->spaces[i + 6])) {
			std::cout << i << " column ";
			this->isGameFinished = true;
		}

		if (i > 1) continue;
		int last = i == 0 ? 8 : 6;
		if (this->threeSame(this->spaces[i * 2], this->spaces[4], this->spaces[last])) {
			std::cout << " First Cross ";
			this->isGameFinished = true;
		}
	}

	if (this->threeSame(this->spaces[2], this->spaces[4], this->spaces[6])) {
		std::cout << " First row ";
	}
}

void TicTacToe::announceWinner()
{
	if (this->isGameFinished) {

	}
}

void TicTacToe::printInputChoosePlayerSamples()
{
	std::cout << "For Single player enter S or 1 Or Single or Enter" << std::endl;
	std::cout << "For Multi player enter M or 2 Or Multiple" << std::endl;
}

void TicTacToe::printInputChooseDifficultySamples()
{
	std::cout << "For Easy Difficulty enter E or 1 Or Easy" << std::endl;
	std::cout << "For Medium Difficulty enter M or 2 Or Medium" << std::endl;
	std::cout << "For Hard Difficulty enter H or 3 Or Hard" << std::endl;
}

void TicTacToe::printDrawDetails()
{
	std::cout << "\x1B[2J\x1B[H";
	this->screenClear();
	std::cout << "Game Type : " << (this->isMultiPlayer ? "Multi Player" : "Single Player") << std::endl << std::endl;
	if (!this->isMultiPlayer) {
		std::cout << "Game Difficulty : " << this->getGameDifficultyName(this->gameDifficulty) << std::endl << std::endl;
	}
}

std::string TicTacToe::getPlayerInput(std::string& playerInput)
{
	std::getline(std::cin, playerInput);
	std::transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);
	return playerInput;
}

std::string TicTacToe::getGameDifficultyName(GameDiffiCulty difficulty)
{
	switch (difficulty)
	{
	case TicTacToe::NONE:
		return "None";
	case TicTacToe::EASY:
		return "Easy";
	case TicTacToe::MEDIUM:
		return "Medium";
	case TicTacToe::HARD:
		return "Hard";
	default:
		return "None";
	}
}


template<class C, typename T>
inline bool TicTacToe::contains(C&& c, T t)
{
	return std::find(std::begin(c), std::end(c), t) != std::end(c);
}
