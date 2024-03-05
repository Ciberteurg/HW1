//Определим последовательность натуральных чисел рекурсивно : следующее число
//равно сумме квадратов цифр текущего числа.Если последовательность придёт к 1, то
//начальное число последовательности называется счастливым.Например, 19 —
//счастливое число(последовательность 19 -> 82 -> 68 -> 100 -> 1), а число 2 — нет
//(последовательность 2 -> 4 -> 16 -> 37 -> 18 -> 65 -> 61 -> 37 -> ...).
//Напишите функцию, проверяющую, является ли переданное ей натуральное число
//счастливым.
#include <iostream>
#include <vector>
#include <algorithm>

int degrise(int d_number); //функция для создания суммы квадратов цифр
bool number_happines(int nh_number);

int main() {

	//bool ans = std::find(f.begin(), f.end(), 2) != f.end();
	//std::cout << std::boolalpha << ans;

	int isit_happy_number;
	std::cin >> isit_happy_number;
	std::cout << "\nI added a path of numbers for greater clarity. \n";

	std::cout << std::endl << std::endl << std::boolalpha << number_happines(isit_happy_number);

}

int degrise(int d_number) {

	int answer = 0;
	while (d_number > 0) {

		answer += (d_number % 10)*(d_number % 10);
		d_number = d_number / 10;

	}

	return answer;

}

bool number_happines(int nh_number) {

	std::vector <int> number_way {nh_number};
	std::cout << nh_number;

	while (true) {

		nh_number = degrise(nh_number);
		std::cout << " --> " << nh_number;

		if (nh_number == 1)
			return true;
		if (std::find(number_way.begin(), number_way.end(), nh_number) != number_way.end())
			return false;

		number_way.push_back(nh_number);

	}

}