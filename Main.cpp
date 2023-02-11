#include "Header.h"

void main() {
	system("cls");
	setlocale(LC_ALL, ".ACP");
	cout << "			Односвязный список строк в двоичном файле			" << endl;
	int p; char bin_file_name[50];
	cout << "Введите название двоичного файла. Пример: bin_file_name.bin" << endl;
	cout << "Название файла: ";
	cin >> bin_file_name;
	cout << "Выберите: 1 - создать новый список в файле " << bin_file_name << "    0 - продолжить работу с существующим списком в данном файле" << endl;
	cin >> p;
	while (true) {
		if (((p != 1) && (p != 0))) {
			cout << "Ошибка. Пожалуйста, выберите 1 либо 0." << endl;
			cin >> p;
		}
		else break;
	}
	binary_file list(p);
	list.read_number(bin_file_name);
	if (((p == 0) && (list.getNumber() == 0))) {
		cout << "Ошибка. Файл " << bin_file_name << " не содержит списка." << endl;
		return;
	}
	int act;
	while (true) {
		cout << "					МЕНЮ					" << endl;
		cout << "1. Заполнить список строками из текстового файла" << endl << "2. Добавить строку на определенную позицию" << endl << "3. Удалить строку определенной позиции" << endl << "4. Редактировать строку определенной позиции" << endl << "5. Сохранить список в текстовый файл" << endl << "6. Просмотреть список" << endl << "7. Завершить работу и выйти из программы" << endl;
		cout << "Выберите действие:	";
		cin >> act;
		cout << endl;
		switch (act) {
		case 1: {
			char file_name[50]; int flag;
			cout << "1. Заполнить список строками из текстового файла" << endl;
			cout << "Введите название текстового файла. Пример: in_file_name.txt" << endl;
			cout << "Название файла: ";
			cin >> file_name;
			list.fill_from_file(file_name, bin_file_name);
			if (list.getNumber() != 0)
				cout << "Список заполнен. Вы можете работать с ним через меню." << endl;
			break;
		}
		case 2: {
			int flag = 1, l, your_pos;
			cout << "2. Добавить строку на определенную позицию" << endl;
			if (list.getParametr() == 1) {
				cout << "Выполнение невозможно, список пуст. Для начала необходимо заполнить список." << endl;
				break;
			}
			else {
				while (flag == 1) {
					if (list.getParametr() == 1) {
						cout << "Выполнение невозможно, список пуст. Для начала необходимо заполнить список." << endl;
						break;
					}
					list.read_number(bin_file_name);
					cout << "Количество элементов в списке: " << list.getNumber() << endl;
					cout << "Введите длину строки:		";
					cin >> l;
					char* your_str = new char[l + 1];
					cout << "Введите строку:	";
					cin >> your_str;
					cout << "Введите позицию от 1 до " << list.getNumber() + 1 << ":	";
					cin >> your_pos;
					if (your_pos <= 0) {
						while (true) {
							cout << "Выполнение невозможно. Пожалуйста, выберите позицию от 1 до " << list.getNumber() + 1 << endl;
							cin >> your_pos;
							if (((your_pos >= 1) && (your_pos <= list.getNumber() + 1)))
								break;
						}
					}
					if (your_pos > list.getNumber() + 1) {
						cout << "Количество элементов в данном списке:  " << list.getNumber() << ". Вставка строки будет выполнена на " << list.getNumber() + 1 << " позицию." << endl;
						your_pos = list.getNumber() + 1;
					}

					list.insert_on_position(your_str, your_pos, bin_file_name);
					if (your_str != NULL)
						delete[] your_str;
					cout << "Элемент добавлен на " << your_pos << " позицию. Количество элементов в списке: " << list.getNumber() << ". Добавить еще элемент? Выберите : 1 - добавить новый элемент    0 - вернуться в меню" << endl;
					cin >> flag;
					while (true) {
						if (((flag != 1) && (flag != 0))) {
							cout << "Ошибка. Пожалуйста, выберите 1 либо 0." << endl;
							cin >> flag;
						}
						else break;
					}
				}
				break;
			}
		}
		case 3: {
			cout << "3. Удалить строку определенной позиции" << endl;
			int flag = 1; int pos;
			while (flag == 1) {
				if (list.getParametr() == 1) {
					cout << "Выполнение невозможно, список пуст. Для начала необходимо заполнить список." << endl;
					break;
				}
				list.read_number(bin_file_name);
				cout << "Количество элементов в списке: " << list.getNumber() << endl;
				cout << "Введите позицию удаляемой строки:		";
				cin >> pos;
				if (((pos <= 0) || (pos > list.getNumber()))) {
					while (true) {
						cout << "Выполнение невозможно. Пожалуйста, выберите позицию от 1 до " << list.getNumber() << endl;
						cin >> pos;
						if (((pos >= 1) && (pos <= list.getNumber())))
							break;
					}
				}
				list.delete_line(pos, bin_file_name);
				cout << "Элемент удален с " << pos << " позиции. Количество элементов в списке: " << list.getNumber() << ". Удалить еще? Выберите: 1 - удалить другой элемент    0 - вернуться в меню" << endl;
				cin >> flag;
				while (true) {
					if (((flag != 1) && (flag != 0))) {
						cout << "Ошибка. Пожалуйста, выберите 1 либо 0." << endl;
						cin >> flag;
					}
					else break;
				}
			}
			break;
		}
		case 4: {
			cout << "4. Редактировать строку определенной позиции" << endl;
			int flag = 1; int l, pos;
			while (flag == 1) {
				if (list.getParametr() == 1) {
					cout << "Выполнение невозможно, список пуст. Для начала необходимо заполнить список." << endl;
					break;
				}
				list.read_number(bin_file_name);
				cout << "Количество элементов в списке: " << list.getNumber() << endl;
				cout << "Введите позицию редактируемой строки от 1 до " << list.getNumber() << ":	";
				cin >> pos;
				if (((pos <= 0) || (pos > list.getNumber()))) {
					while (true) {
						cout << "Выполнение невозможно. Пожалуйста, выберите позицию от 1 до " << list.getNumber() << endl;
						cin >> pos;
						if (((pos >= 1) && (pos <= list.getNumber())))
							break;
					}
				}
				cout << "Введите длину новой строки:		";
				cin >> l;
				char* new_str = new char[l + 1];
				cout << "Введите новую строку:	";
				cin >> new_str;
				list.edit_line(new_str, pos, bin_file_name);
				cout << "Элемент на " << pos << " позиции отредактирован. Количество элементов в списке: " << list.getNumber() << ". Редактировать еще? Выберите: 1 - редактировать другой элемент    0 - вернуться в меню" << endl;
				cin >> flag;
				while (true) {
					if (((flag != 1) && (flag != 0))) {
						cout << "Ошибка. Пожалуйста, выберите 1 либо 0." << endl;
						cin >> flag;
					}
					else break;
				}
			}
			break;
		}
		case 5: {
			cout << "5. Сохранить список в текстовый файл" << endl;
			if (list.getParametr() == 1) {
				cout << "Выполнение невозможно, список пуст. Для начала необходимо заполнить список." << endl;
				break;
			}
			else {
				char out_file_name[50];
				cout << "Введите название файла, в который будет сохранен список. Пример: out_file_name.txt" << endl;
				cout << "Название файла: ";
				cin >> out_file_name;
				list.save_to_file(out_file_name, bin_file_name);
				cout << "Выполнено сохранение списка в файл " << out_file_name << endl;
				break;
			}
		}
		case 6: {
			cout << "6. Просмотреть список" << endl;
			if (list.getParametr() == 1) {
				cout << "Выполнение невозможно, список пуст. Для начала необходимо заполнить список." << endl;
				break;
			}
			else {
				list.show_list(bin_file_name);
				break;
			}
		}
		case 7: {
			cout << "7. Завершить работу и выйти из программы" << endl;
			return;
		}
		}
	}
}