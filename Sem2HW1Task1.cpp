//Бинарный поиск
//Реализуйте функцию бинарного поиска в отсортированном по возрастанию массиве.
//Если объект есть в массиве, функция должна вернуть его индекс, иначе — вернуть - 1.

#include <iostream>
#include <vector>

using namespace std;

int main() {

	int array_length;
	cin >> array_length;

	//классическая инициализация закомменчена, массив будет забиваться для демонстрации функцией

	vector<int> array_for_search;
	array_for_search.reserve(array_length);
	for (int _i = 0; _i != array_length; ++_i) {

		array_for_search.push_back(_i*2);
		cout << array_for_search[_i] << " ";

		//int _a;
		//cin >> _a;
		//array_for_search.push_back(_a);

	}
	cout << endl;

	int left = 0, right = array_length - 1;

	int search, answer = -1;
	cin >> search;

	while (left < right) {

		//
		cout << left << " " << right << endl;
		//
		int _new_edge = (right + left) / 2;

		if (array_for_search[_new_edge] == search) {

			left = right;
			answer = array_for_search[_new_edge];
			break;

		}
		if (array_for_search[_new_edge] < search)
			left = _new_edge;
		if (array_for_search[_new_edge] > search)
			right = _new_edge;
		
		if (left == right - 1)
			break;

	}

	cout << answer << endl;

}