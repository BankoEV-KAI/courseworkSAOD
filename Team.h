#pragma once
#include <iostream>
#include <fstream>

#include "Player.h"

class Team
{
private:

	struct Info {
		std::string teamName;
	} team;

	int currentCountPlayers;
	static const int maxCountPlayers = 5;

	Player listPlayers[maxCountPlayers];

public:

	Team() {
		team.teamName = "";
		currentCountPlayers = 0;
	}

	Team(std::string newName) {
		team.teamName = newName;
		currentCountPlayers = 0;
	}

	bool IsEmpty() {
		return currentCountPlayers == 0;
	}

	bool IsFull() {
		return currentCountPlayers == maxCountPlayers;
	}

	bool Add(Player newPlayer) {

		if (IsFull())
			return false;

		if (IsEmpty()) listPlayers[0] = newPlayer;
		else {
			int i;

			for (i = 0; i < currentCountPlayers; i++)
			{
				if (listPlayers[i].GetNumber() == newPlayer.GetNumber()) {
					std::cout << "����� � ����� ������� ��� ���������� � �������!" << std::endl;
					return false;
				}
				//�������������� �� ��������
				if (listPlayers[i].GetSurname() > newPlayer.GetSurname())
					break;
			}
			
			//�����
			for (int j = currentCountPlayers; j > i; j--)
				listPlayers[j] = listPlayers[j - 1];

			listPlayers[i] = newPlayer;
		}
		currentCountPlayers++;
		return true;
	}

	int Search(std::string surname) {
		if (IsEmpty())
			return -1;

		for (int i = 0; i < currentCountPlayers; i++)
		{
			if (listPlayers[i].GetSurname() == surname)
			{
				return i;
			}
		}

		return -1;
	}

	bool Delete(std::string surname) {

		if (IsEmpty())
			return false;

		int i = Search(surname);
		if (i == -1)
			return false;

		for (int j = i; j < currentCountPlayers; j++)
		{
			listPlayers[j] = listPlayers[j + 1];
		}
		currentCountPlayers--;
		return true;
	}

	void Show() {
		std::cout << "�������� �������: " << team.teamName << std::endl;

		if (IsEmpty())
			std::cout << "������� ���!" << std::endl;
		else
			for (int i = 0; i < currentCountPlayers; i++)
			{
				std::cout << "������� ������: " << listPlayers[i].GetSurname() << "; �����: " << listPlayers[i].GetNumber() << std::endl;
			}
	}

	void WriteInTXT(std::ofstream& out) {
		out << team.teamName;
		for (int i = 0; i < currentCountPlayers; i++)
		{
			out << "$" << listPlayers[i].GetSurname() << "$" << listPlayers[i].GetNumber();
		}
		out << std::endl;
	}

	void SetTeamName(std::string newName) {
		team.teamName = newName;
	}

	std::string GetTeamName() {
		return team.teamName;
	}
};