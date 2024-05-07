#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "SportLeague.h"

SportLeague league;

int CorrectInput() {
	int answer;
	while (!(std::cin >> answer) || (std::cin.peek() != '\n') || (answer < 0))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Ошибка: введено некорректное число. " << std::endl <<
			"Повторите: " << std::endl;
	}
	return answer;
}

void Dialog() {
	int answer = -1;
	while (answer != 0)
	{
		std::cout << "Введите одно из предложенных чисел: " << std::endl <<
			"1 - Создать новую спортлигу (команды не будут сохранены)." << std::endl <<
			"2 - Переименовать лигу (с сохраенением команд)." << std::endl <<
			"3 - Добавить команду в очередь." << std::endl <<
			"4 - Удалить команду из очереди." << std::endl <<
			"5 - Добавить игрока в список." << std::endl <<
			"6 - Удалить игрока из списка." << std::endl <<
			"7 - Найти команду." << std::endl <<
			"8 - Найти игрока в выбранной команде." << std::endl <<
			"9 - Найти игрока по всей лиге." << std::endl <<
			"10 - Вывести состояние структуры в консоль." << std::endl <<
			"11 - Загрузить структуру из файла." << std::endl <<
			"12 - Сохранить структуру в файл." << std::endl <<
			"0 - Завершить работу." << std::endl;
		answer = CorrectInput();
		system("cls");
		switch (answer)
		{
		case 1:
		{
			std::string name;
			std::cout << "Название спортивной логи: " << std::endl;
			std::cin.ignore();
			getline(std::cin, name);
			league = SportLeague(name);
			std::cout << "Сопртлига успешно добавлена!" << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "Новое название лиги: " << std::endl;
			std::string name;
			std::cin.ignore();
			getline(std::cin, name);

			league.SetName(name);

			std::cout << "Спортлига переименована!" << std::endl;
			break;
		}
		case 3:
		{
			league.Show();

			std::cout << "Название команды: " << std::endl;
			std::string name;
			std::cin.ignore();
			getline(std::cin, name);

			if (league.EnQueue(Team(name)))
				std::cout << "Команда успешно добавлена!" << std::endl;
			else
				std::cout << "Ошибка добавления!" << std::endl;

			break;
		}
		case 4:
		{
			league.Show();

			std::string name = league.DeQueue();
			if (name != "") {
				std::cout << "Команда " << name << " удалена!" << std::endl;
				std::cout << std::endl;
				league.Show();
			}
			else
				std::cout << "Ошибка удаления. Команда не найдена." << std::endl;

			break;
		}
		case 5:
		{
			league.Show();

			std::string name;
			std::string surname;
			int number;

			std::cout << "Введите наименование команды: " << std::endl;
			std::cin.ignore();
			getline(std::cin, name);

			if (league.Search(name) == -1) {
				std::cout << "Команды с таким названием не зарегистировано!" << std::endl;
				break;
			}

			std::cout << "Фамилия игрока:" << std::endl;
			getline(std::cin, surname);

			std::cout << "Номер игрока: " << std::endl;
			number = CorrectInput();

			//TODO: переименовать метод добавления?

			if (league.AddInSubList(name, Player(surname, number)))
				std::cout << "Успешно! " << std::endl;
			else
				std::cout << "Ошибка добавления." << std::endl;

			break;
		}
		case 6:
		{
			league.Show();
			std::string name, surname;

			std::cout << "Введите название команды: " << std::endl;
			std::cin.ignore();
			getline(std::cin, name);

			if (league.Search(name) == -1) {
				std::cout << "Команды с таким названием не зарегистировано!" << std::endl;
				break;
			}

			std::cout << "Фамилия игрока:" << std::endl;
			getline(std::cin, surname);

			//TODO: дать более понятное наименование Делит фром саб лист == удалить игрока?
			if (league.DeleteFromSubList(name, surname))
				std::cout << "Успешно!" << std::endl;
			else
				std::cout << "Ошибка удаления. Игрок не найден." << std::endl;

			break;
		}
		case 7:
		{
			league.Show();
			std::string name;
			std::cout << "Введите название искомой команды: " << std::endl;
			std::cin.ignore();
			getline(std::cin, name);

			int resultSearch = league.Search(name);
			if (resultSearch != -1) {
				std::cout << "Команда найдена!" << std::endl;
				league.printItems(resultSearch);
			}
			else
				std::cout << "Команда не найдена." << std::endl;

			break;
		}
		case 8:
		{
			league.Show();
			std::string name, surname;

			std::cout << "Введите название команды: " << std::endl;
			std::cin.ignore();
			getline(std::cin, name);

			if (league.Search(name) == -1) {
				std::cout << "Команды с таким названием не зарегистировано!" << std::endl;
				break;
			}

			std::cout << "Фамилия искомого игрока:" << std::endl;
			getline(std::cin, surname);

			//TODO: возвращать номер игрока?
			if (league.SearchInSubList(name, surname))
				std::cout << "Игрок найден!" << std::endl;
			else
				std::cout << "Игрок не найден!" << std::endl;

			break;
		}
		case 9:
		{
			league.Show();
			std::string surname;

			std::cout << "Фамилия искомого игрока:" << std::endl;
			std::cin.ignore();
			getline(std::cin, surname);

			//TODO: номер игрока?
			std::string name = league.FullSearch(surname);
			if (name != "")
				std::cout << "Игрок найден!" << std::endl
				<< "Он представляет команду: " << name << std::endl;
			else
				std::cout << "Игрок не найден!" << std::endl;

			break;
		}
		case 10:
		{
			league.Show();
			break;
		}
		case 11:
		{
			std::ifstream in;
			in.open("save.txt");
			bool successful = true;

			if (!in.is_open())
			{
				std::cout << "Ошибка чтения файла." << std::endl;
				successful = false;
				break;
			}
			else
			{
				//TODO: проверить названия полей

				char line[1000];
				char* parts;

				in.getline(line, 1000);
				std::string name = line;

				league = SportLeague(line);

				while (!in.eof()) {

					in.getline(line, 1000);

					parts = strtok(line, "$");

					if (parts == NULL)
						continue;

					std::string name = parts;

					if (!league.EnQueue(Team(name)))
					{
						std::cout << "Ошибка: массив переполнен." << std::endl;
						successful = false;
						break;
					}

					parts = strtok(NULL, "$");

					if (parts == NULL)
						continue;

					while (parts != NULL) {

						std::string surname = parts;
						parts = strtok(NULL, "$");

						if (parts == NULL)
						{
							std::cout << "Ошибка: не хватает данных." << std::endl;
							successful = false;
							break;
						}

						int salary = atoi(parts);

						std::string str = parts;

						for (int i = 0; i < str.length(); i++)
						{
							if (str[i] < '0' || str[i] > '9')
							{
								std::cout << "Ошибка: некорректный тип данных." << std::endl;
								successful = false;
								break;
							}
						}

						parts = strtok(NULL, "$");

						if (!league.AddInSubList(name, Player(surname, salary)))
						{
							std::cout << "Ошибка: массив переполнен." << std::endl;
							successful = false;
							break;
						}
					}
					if (!successful)
						break;
				}
			}
			in.close();
			if (successful)
				std::cout << "Данные успешно загружены!" << std::endl;
			else
			{
				league = SportLeague();
				std::cout << "Нарушение структуры записи файла." << std::endl;
			}

			break;
		}
		case 12:
		{
			std::ofstream out;
			out.open("save.txt");

			if (!out.is_open())
			{
				std::cout << "Ошибка чтения файла." << std::endl;
			}
			else
			{
				league.WriteInTXT(out);

				out.close();
				std::cout << "Данные успешно выгружены!" << std::endl;
			}
			break;
		}
		case 0:
			std::cout << "Удачи!" << std::endl;
			break;

		default:
			std::cout << "Ошибка: выбранного вами пункта не существует." << std::endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Работу выполнила: Банько. Е. В., гр 4211" << std::endl
		<< "Вариант: 32.25" << std::endl
		<< "32. Статическая очередь статических упорядоченных списков" << std::endl
		<< "25. Спортлига (название) – композиция команд (названия)" << std::endl
		<< "    команда – композиция игроков(фамилия, номер)" << std::endl << std::endl;
	system("pause");
	system("cls");
	Dialog();
	return 0;
}

