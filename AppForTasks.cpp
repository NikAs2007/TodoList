#include "header.h"

//Проблема с русским языком при записи/чтении!

int main()
{
    setlocale(LC_ALL, "Ru");
    TodoList todolist;

    while (todolist.isOpen) {
        todolist.asking();
    }
    //todolist.close();

    return 0;
}

void print_text(const string& s) {
    int i = 0;
    auto t1 = chrono::steady_clock::now();
    int dur;
    while (i < s.length()) {
        auto t2 = chrono::steady_clock::now();
        if (s[i] == ' ') {
            dur = 70;
        }
        else if (s[i] == '!' || s[i] == '.' || s[i] == '-' || s[i] == ',') {
            dur = 140;
        }
        else {
            dur = 25;
        }
        if (chrono::duration<float>(t2 - t1) >= chrono::milliseconds(dur)) {
            cout << s[i];
            i++;
            t1 = chrono::steady_clock::now();
        }
    }
}

void print_text(const string& s, int settings) {
    int i = 0, ent = 0;
    auto t1 = chrono::steady_clock::now();
    int dur;
    while (i < s.length()) {
        auto t2 = chrono::steady_clock::now();
        if (s[i] == ' ') {
            dur = 70;
        }
        else if (s[i] == '!' || s[i] == '.' || s[i] == '-' || s[i] == ',') {
            dur = 140;
        }
        else {
            dur = 25;
        }
        if (chrono::duration<float>(t2 - t1) >= chrono::milliseconds(dur)) {
            if (ent > 100 && s[i] == ' ') {
                cout << s[i];
                i++;
                ent++;
                cout << endl;
                ent = 0;
            }
            cout << s[i];
            i++;
            ent++;
            t1 = chrono::steady_clock::now();
        }
    }
}