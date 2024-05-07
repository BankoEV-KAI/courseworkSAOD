#pragma once
#include "Team.h"
int CorrectInput();

class SportLeague {

private:

	struct Info
	{
		std::string name;
	} league;

	static const int maxCountTeam = 5;
	int currentCountTeams;

	int Head;
	int Tail;

	Team teamQueue[maxCountTeam];

public:

	SportLeague() {
		league.name = "";
		currentCountTeams = 0;
		Head = 0;
		Tail = 0;
	}

	SportLeague(std::string newName) {
		league.name = newName;
		currentCountTeams = 0;
		Head = 0;
		Tail = 0;
	}

	bool IsEmpty() {
		return currentCountTeams == 0;
	}

	bool IsFull() {
		return currentCountTeams == maxCountTeam;
	}

	bool EnQueue(Team newTeam)
	{
		if (!(IsFull())) {

			for (int i = 0; i < currentCountTeams; ++i) {
				if (teamQueue[i].GetTeamName() == newTeam.GetTeamName()) {
					std::cout << " оманда с таким именем уже существует в лиге!" << std::endl;
					return false; 
				}
			}

			teamQueue[Tail] = newTeam;
			Tail++;
			currentCountTeams++;
			Tail %= maxCountTeam;
			return true;
		}
		else {
			return false;
		}
	}

	std::string DeQueue() {
		if (!(IsEmpty())) {
			std::string name = teamQueue[Head].GetTeamName();
			Head++;
			currentCountTeams--;

			Head %= maxCountTeam;
			return name;
		}
		else {
			return "";
		}
	}

	int Search(std::string teamName) {
		if (IsEmpty())
			return -1;

		int temp = Head;
		for (int i = 0; i < currentCountTeams; i++)
		{
			if (teamQueue[temp].GetTeamName() == teamName) {
				return temp;
			}
			temp++;
			temp %= maxCountTeam;
		}

		return -1;
	}

	void printItems(int index) {
		teamQueue[index].Show();
	}

	std::string FullSearch(std::string surname) {
		if (IsEmpty())
			return "";

		for (int i = 0; i < currentCountTeams; i++)
		{
			int j = teamQueue[i].Search(surname);
			if (j != -1)
				return teamQueue[i].GetTeamName();
		}
		return "";
	}

	bool SearchInSubList(std::string teamName, std::string surname)
	{
		int i = Search(teamName);

		if (i == -1) //≈сли команда не найдена
			return false;

		int j = teamQueue[i].Search(surname);

		if (j == -1) //≈сли игрок не был найден
			return false;
		return true;
	}

	bool AddInSubList(std::string teamName, Player newPlayer)
	{
		int i = Search(teamName);

		if (i == -1) 
			return false;

		if (teamQueue[i].Add(newPlayer))
			return true;

		return false;
	}

	bool DeleteFromSubList(std::string teamName, std::string surname)
	{
		int i = Search(teamName);

		if (i == -1) 
			return false;

		if (teamQueue[i].Delete(surname))
			return true;

		return false;
	}

	void Show() {
		std::cout << "Ќазвание спортлиги: " << league.name;

		if (IsEmpty())
			std::cout << " ни одной команд не зарегестрировано. " << std::endl;
		else
		{
			std::cout << std::endl;
			int temp = Head;
			for (int i = 0; i < currentCountTeams; i++)
			{
				teamQueue[temp].Show();
				temp++;
				temp %= maxCountTeam;
			}
		}

		std::cout << std::endl;
	}

	void WriteInTXT(std::ofstream& out) {
		out << league.name << std::endl;
		for (int i = 0; i < currentCountTeams; i++)
		{
			teamQueue[i].WriteInTXT(out);
		}
	}

	void SetName(std::string newName) {
		league.name = newName;
	}

	std::string GetName() {
		return league.name;
	}
};