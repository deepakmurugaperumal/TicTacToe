#pragma once

#include <string>


class TicTacToe
{

public:
	TicTacToe();
	void play();

private:
	const char space{ ' ' };
	const char stright{ '|' };
	const std::string downFour = "----";

	const std::string multiPlayeKeys[3]{ "M", "MULTIPLE", "2" };
	const std::string singlePlayeKeys[3]{ "S", "SINGLE", "1" };

	const std::string difficultyEasyKeys[3]{ "E", "EASY", "1" };
	const std::string difficultyMediumKeys[3]{ "M", "MEDIUM", "2" };
	const std::string difficultyHardKeys[3]{ "H", "HARD", "3" };
	const std::string allowedPlayKeys[9]{ "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	const enum GameSymbol {
		NOUGHT = 'O',
		CROSS = 'X'
	};

	const enum GameDiffiCulty {
		NONE,
		EASY,
		MEDIUM,
		HARD
	};

	const enum PlayerTurn {
		FIRST,
		SECOND
	};

	struct {
		PlayerTurn player;
	} WinnerDetail;

	PlayerTurn playerTurn{ PlayerTurn::FIRST };
	GameDiffiCulty gameDifficulty{};

	bool isPlayerTypeChoosed{ false };
	bool isGameDifficultyChoosed{ false };
	bool isMultiPlayer{ false };
	bool isGameFinished{ false };
	char spaces[9]{ space, space, space, space, space, space, space, space, space };

	bool markAsMultiplayer(std::string playerInput);
	bool markAsSinglePlayer(std::string playerInput);
	bool markGameDifficulty(std::string playerInput);
	void markPosition(int position);
	void findWinner();
	void announceWinner();

	void playerPlay();
	void botPlay();
	void choosePlayerType();
	void draw();
	void printInputChoosePlayerSamples();
	void printInputChooseDifficultySamples();
	void printDrawDetails();
	void chooseDifficulty();
	bool positionAvailable(int position);
	bool threeSame(char first, char second, char third);
	std::string getPlayerInput(std::string& playerInput);
	std::string getGameDifficultyName(GameDiffiCulty difficulty);
	std::string placeVal(int index);
	void screenClear();

	template<class C, typename T>
	bool contains(C&& c, T t);
};

