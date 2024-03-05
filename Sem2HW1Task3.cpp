//Имеется N предметов, каждый из которых имеет некоторую полезность p[i] и
//некоторый вес w[i].Максимальный вес, который выдерживает рюкзак, равен W.
//Требуется выбрать предметы, удовлетворяющие ограничению ∑𝑗∈𝐽
//𝑤[𝑗] ≤ 𝑊 и
//максимизирующие суммарную полезность.
//Предлагается решить задачу выше двумя способами.
//1. Жадным алгоритмом — в первую очередь брать предметы с максимальной
//удельной полезностью.Укажите асимптотику этого алгоритма.Всегда ли он
//выдаст правильный ответ, т.е.набор с максимальной полезностью ?
//2. Полным перебором : проверить все возможные варианты и выбрать из
//допустимых вариант с максимальным значением суммарной полезности.
//Укажите асимптотику этого алгоритма.

#include <random>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

void greed_alg(std::vector <int> ga_val, std::vector <int> ga_wei, int ga_lengh, int ga_size);
//(полезность каждой вещи, вес кажой вещи, количество вещей всего, размер рюкзака)
std::vector <int> full_search(std::vector <int> &fs_way, std::vector <int> fs_val, std::vector <int> fs_wei, int fs_lengh, int fs_size);
//(последовательность 0и1 отображающая взятые вещи, полезность каждой вещи, вес кажой вещи, количество вещей всего, размер рюкзака)

int main() {

	srand(std::time(0));

	std::vector <int> item_value;
	std::vector <int> item_weight;
	item_value.reserve(20);
	item_weight.reserve(20);

	int number_of_items = 20, backpack_size = 100;

	//создаю себе набор предметов и весов, можно и ввод сделать, но так быстрее и проще проверять
	for (int _i = 0; _i < 20; ++_i) {

		item_value.push_back(rand() % 50+1); //чтобы нолей не было
		item_weight.push_back(rand() % 40+1);

	}

	std::cout << "Values: ";
	for (int _i = 0; _i < 20; ++_i)
		std::cout << item_value[_i] << " ";

	std::cout << "\nWeights: ";
	for (int _i = 0; _i < 20; ++_i)
		std::cout << item_weight[_i] << " ";
	std::cout << std::endl << std::endl;

	//а вот отсюда начинается уже решение
	
	greed_alg(item_value, item_weight, number_of_items, backpack_size);

	std::vector <int> start1{ 1 };
	std::vector <int> start2{ 0 };
	std::vector <int> full_search_answer1(full_search(start1, item_value, item_weight, number_of_items, backpack_size));
	std::vector <int> full_search_answer2(full_search(start2, item_value, item_weight, number_of_items, backpack_size));

	if (full_search_answer1[number_of_items] > full_search_answer2[number_of_items]) {

		for (int _i = 0; _i != number_of_items; ++_i) {

			if (full_search_answer1[_i] != 0)
				std::cout << "(" << item_value[_i] << ", " << item_weight[_i] << ") ";

		}

		std::cout << "\nTotal value: " << full_search_answer1[number_of_items] << std::endl;

	}

	if (full_search_answer1[number_of_items] <= full_search_answer2[number_of_items]) {

		for (int _i = 0; _i != number_of_items; ++_i) {

			if (full_search_answer2[_i] != 0)
				std::cout << "(" << item_value[_i] << ", " << item_weight[_i] << ") ";

		}

		std::cout << "\nTotal value: " << full_search_answer2[number_of_items] << std::endl;

	}

}

std::vector <int> full_search(std::vector <int> &fs_way, std::vector <int> fs_val, std::vector <int> fs_wei, int fs_lengh, int fs_size) {

	std::vector <int> new_fs_way(fs_way);
	
	if (fs_way.size() < fs_lengh) {
		
		new_fs_way.push_back(1);
		std::vector <int> a1(full_search(new_fs_way, fs_val, fs_wei, fs_lengh, fs_size));
		new_fs_way.pop_back();

		new_fs_way.push_back(0);
		std::vector <int> a2(full_search(new_fs_way, fs_val, fs_wei, fs_lengh, fs_size));
		new_fs_way.pop_back();

		if (a1[fs_lengh] > a2[fs_lengh])
			return a1;
		else
			return a2;

	}
	else {

		int fs_answer = 0;
		for (int _i = 0; _i != fs_lengh; ++_i) {

			fs_size -= fs_wei[_i] * fs_way[_i];
			fs_answer += fs_val[_i] * fs_way[_i];

		}

		if (fs_size >= 0)
			new_fs_way.push_back(fs_answer);
		else
			new_fs_way.push_back(-1);
		
		return new_fs_way;

	}

}

void greed_alg(std::vector <int> ga_val, std::vector <int> ga_wei, int ga_lengh, int ga_size) {

	std::vector <float> spec_weight;
	spec_weight.reserve(20);

	for (int _i = 0; _i < ga_lengh; ++_i)
		spec_weight.push_back(ga_val[_i]*1.0 / ga_wei[_i]);

	int current_item_id = std::distance(spec_weight.begin(), std::max_element(spec_weight.begin(), spec_weight.end()));

	int value = 0;

	while (ga_size > 0) {

		if (spec_weight[current_item_id] == 0)
			break;
		
		if(ga_wei[current_item_id] <= ga_size){
		
			std::cout << std::setprecision(2) << "(" << ga_val[current_item_id] << ", " << ga_wei[current_item_id] << ", " << spec_weight[current_item_id] << ") ";
			ga_size -= ga_wei[current_item_id];
			value += ga_val[current_item_id];
		
		}

		spec_weight[current_item_id] = 0;
		current_item_id = std::distance(spec_weight.begin(), std::max_element(spec_weight.begin(), spec_weight.end()));

	}

	std::cout << "\nTotal value: " << value << std::endl;

}