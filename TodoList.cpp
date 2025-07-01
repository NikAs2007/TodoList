#include "header.h"

void TodoList::add_task() {
	Item item;
	print_text("������� �������� ������: ");
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //������� ������
	getline(cin, item.name);
	print_text("\n������� �������� ������: ");
	//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //������� ������
	getline(cin, item.text);
	list.push_back(item);
	thread th([&]() {save(); });
	//thread th(save); //� �� ������� ������ ��� ������
	th.detach();
	print_text("\n������ ���� ������� ��������� � ������\n");
}

void TodoList::show_all() {
	if (!list.empty()) print_text("������ ����� �����:\n");
	else print_text("� ��� ��� ������� �����\n");
	for (int i = 0; i < list.size(); i++) {
		print_text(to_string(i + 1) + "." + list[i].name + "\n");
	}
	print_text("\n");
}

void TodoList::asking() {
	print_text("\n��������� ��������:\n1.�������� ��� ������ [1]\n2.�������� ������ [2]\n3.������� ������ [3]\n4.��������� ������ [4]\n����� ��������: ");
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
		print_text("����� ������ �� ����������\n");
	}
}

void TodoList::close() {
	if (!save()) print_text("�� ������� ���������. ������ ���������.\n");
	else print_text("������ ���������, ��������� ��������� ������.\n");
}

void TodoList::choose_one() {
	if (list.empty()) {
		print_text("������ ����� ����.\n");
		return;
	}
	print_text("����� ������ ���������: ");
	string input;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //������� ������
	getline(cin, input);
	int chose = stoi(input);
	if (chose - 1 >= list.size()) {
		print_text("����� ������ �� ����������.\n");
		return;
	}
	else {
		print_text("�������� �������� ��� ������:\n1.�������� [1]\n2.������� [2]\n3.������ [3]\n������� �����: ");
		string in2;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //������� ������
		//getline(cin, in2); //��� ������
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
			print_text("����� �������.\n");
			return;
			break;
		default:
			print_text("�� ������� �������� �������. ����� �������.\n");
			return;
		}
	}
}

void TodoList::delete_one(int num) {
	list.erase(list.begin() + num - 1);
	thread th([&]() {save(); });
	//thread th(save); //� �� ������� ������ ��� ������
	th.detach();
	print_text("������ " + to_string(num) + " ���� ������� �������.\n");
}

void TodoList::show_one(int num) {
	print_text("\n" + list[num - 1].name + "\n" + list[num - 1].text + "\n\n", 0);
}

bool TodoList::save() {
	mtx.lock();
	fstream file;
	file.open("save.txt", fstream::out);
	if (!file.is_open()) {
		//print_text("�� ������� ���������.");
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
		print_text("�� ������� ���������� ������. � ����� � .exe ������ ����� ������ ���������� ���� save.txt (������ ��� �����������)!\n");
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
	//if (isOpen) save(); //������� �� ��������
	close();
}