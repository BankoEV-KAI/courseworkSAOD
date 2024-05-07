#pragma once
#include <string>

class Player {
private:

	struct Info {
		std::string surname;
		int number;
	} player;

public:

	Player() {
		player.surname = "noName";
		player.number = -1;
	}

	Player(std::string newSurname, int newNumber) {
		player.surname = newSurname;
		player.number = newNumber;
	}

	void SetSurname(std::string newSurname) {
		player.surname = newSurname;
	}

	void SetNumber(int newNumber) {
		player.number = newNumber;
	}

	std::string GetSurname() {
		return player.surname;
	}

	int GetNumber() {
		return player.number;
	}
};