#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class binary_file : public fstream
{
	typedef struct {
		char* str;		//строка
		int length;		//длина строки
		long next;		//файловый указатель
	} node;
	node current;
	int number;			//кол-во элементов
	long first;			//заголовок списка
	int parametr;		// параметр, определяет работа с новым списком или с существующим

public:
	binary_file(int p);
	~binary_file();

	long getNext() const { return current.next; }
	int getLength() const { return current.length; }
	char* getStr() const { return current.str; }
	int getNumber() const { return number; }
	int getParametr() const { return parametr; }

	void add(char* line, const char* bin_file);
	void fill_from_file(const char* in_text_file, const char* bin_file);
	void save_to_file(const char* out_text_file, const char* bin_file);
	void insert_on_position(char* line, int pos, const char* bin_file);
	long delete_line(int pos, const char* bin_file);
	void edit_line(char* line, int pos, const char* bin_file);
	void show_list(const char* bin_file);
	void read_number(const char* bin_file);
};

long count_lines(const char* in_text_file);