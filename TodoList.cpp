#include "header.h"

void TodoList::add_task() {
	Item item;
	print_text("Введите название задачи: ");
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //очистка буфера
	getline(cin, item.name);
	print_text("\nВведите описание задачи: ");
	//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //очистка буфера
	getline(cin, item.text);
	list.push_back(item);
	thread th([&]() {save(); });
	//thread th(save); //я не понимаю почему так нельзя
	th.detach();
	print_text("\nЗадача была успешно добавлена в список\n");
}

void TodoList::show_all() {
	if (!list.empty()) print_text("Список ваших задач:\n");
	else print_text("У вас нет никаких задач\n");
	for (int i = 0; i < list.size(); i++) {
		print_text(to_string(i + 1) + "." + list[i].name + "\n");
	}
	print_text("\n");
}

void TodoList::asking() {
	print_text("\nВозможные действия:\n1.Показать все задачи [1]\n2.Добавить задачу [2]\n3.Выбрать задачу [3]\n4.Завершить работу [4]\nВыбор действия: ");
	int chose;
	cin >> chose;
	switch (chose) {
	case(1):
		show_all();
		break;
	case(2):
		add_task();
		break;
	case(3):
		choose_one();
		break;
	case(4):
		isOpen = false;
		break;
	default:
		print_text("Такой задачи не существует\n");
	}
}

void TodoList::close() {
	if (!save()) print_text("Не удалось сохранить. Работа завершена.\n");
	else print_text("Задачи сохранены, программа завершила работу.\n");
}

void TodoList::choose_one() {
	if (list.empty()) {
		print_text("Списко задач пуст.\n");
		return;
	}
	print_text("Какую задачу выбираете: ");
	string input;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //очистка буфера
	getline(cin, input);
	int chose = stoi(input);
	if (chose - 1 >= list.size()) {
		print_text("Такой задачи не существует.\n");
		return;
	}
	else {
		print_text("Выберите действие для задачи:\n1.Показать [1]\n2.Удалить [2]\n3.Отмена [3]\nВведите цифру: ");
		string in2;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //очистка буфера
		//getline(cin, in2); //тут ошибка
		cin >> in2;
		int move = stoi(in2);
		switch (move) {
		case(1):
			show_one(chose);
			break;
		case(2):
			delete_one(chose);
			break;
		case(3):
			print_text("Выбор отменен.\n");
			return;
			break;
		default:
			print_text("Вы выбрали неверную команду. Выбор отменен.\n");
			return;
		}
	}
}

void TodoList::delete_one(int num) {
	list.erase(list.begin() + num - 1);
	thread th([&]() {save(); });
	//thread th(save); //я не понимаю почему так нельзя
	th.detach();
	print_text("Задача " + to_string(num) + " была успешно удалена.\n");
}

void TodoList::show_one(int num) {
	print_text("\n" + list[num - 1].name + "\n" + list[num - 1].text + "\n\n", 0);
}

bool TodoList::save() {
	mtx.lock();
	fstream file;
	file.open("save.txt", fstream::out);
	if (!file.is_open()) {
		//print_text("Не удалось сохранить.");
		mtx.unlock();
		return false;
	}
	for (int i = 0; i < list.size(); i++) {
		file << list[i].name << "\n" << list[i].text << "\n";
	}
	file.close();
	mtx.unlock();
	return true;
}

TodoList::TodoList() {
	mtx.lock();
	fstream file;
	file.open("save.txt", fstream::in);
	if (!file.is_open()) {
		print_text("Не удалось подгрузить данные. В папке с .exe файлом также должен находиться файл save.txt (Пустой или наполненный)!\n");
		mtx.unlock();
		isOpen = false;
		return;
	}
	Item item;
	while (!file.eof()) {
		getline(file, item.name);
		getline(file, item.text);
		list.push_back(item);
	}
	list.pop_back();
	file.close();
	mtx.unlock();
}

TodoList::~TodoList() {
	//if (isOpen) save(); //кажется не работает
	close();
}