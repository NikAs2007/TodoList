#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <limits> //для std::numeric_limits
using namespace std;

void print_text(const string& s);
void print_text(const string& s, int settings);

struct Item {
	string name = "";
	string text = "";
};

class TodoList {
	vector<Item> list;
	mutex mtx;

	void show_all();
	void show_one(int num);
	void delete_one(int num);
	void add_task();
	void choose_one();
	bool save();
	void close();
public:
	bool isOpen = true;

	TodoList();
	~TodoList();
	void asking();
};

#endif