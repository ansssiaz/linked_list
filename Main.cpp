#include "Header.h"

void main() {
	system("cls");
	setlocale(LC_ALL, ".ACP");
	cout << "			����������� ������ ����� � �������� �����			" << endl;
	int p; char bin_file_name[50];
	cout << "������� �������� ��������� �����. ������: bin_file_name.bin" << endl;
	cout << "�������� �����: ";
	cin >> bin_file_name;
	cout << "��������: 1 - ������� ����� ������ � ����� " << bin_file_name << "    0 - ���������� ������ � ������������ ������� � ������ �����" << endl;
	cin >> p;
	while (true) {
		if (((p != 1) && (p != 0))) {
			cout << "������. ����������, �������� 1 ���� 0." << endl;
			cin >> p;
		}
		else break;
	}
	binary_file list(p);
	list.read_number(bin_file_name);
	if (((p == 0) && (list.getNumber() == 0))) {
		cout << "������. ���� " << bin_file_name << " �� �������� ������." << endl;
		return;
	}
	int act;
	while (true) {
		cout << "					����					" << endl;
		cout << "1. ��������� ������ �������� �� ���������� �����" << endl << "2. �������� ������ �� ������������ �������" << endl << "3. ������� ������ ������������ �������" << endl << "4. ������������� ������ ������������ �������" << endl << "5. ��������� ������ � ��������� ����" << endl << "6. ����������� ������" << endl << "7. ��������� ������ � ����� �� ���������" << endl;
		cout << "�������� ��������:	";
		cin >> act;
		cout << endl;
		switch (act) {
		case 1: {
			char file_name[50]; int flag;
			cout << "1. ��������� ������ �������� �� ���������� �����" << endl;
			cout << "������� �������� ���������� �����. ������: in_file_name.txt" << endl;
			cout << "�������� �����: ";
			cin >> file_name;
			list.fill_from_file(file_name, bin_file_name);
			if (list.getNumber() != 0)
				cout << "������ ��������. �� ������ �������� � ��� ����� ����." << endl;
			break;
		}
		case 2: {
			int flag = 1, l, your_pos;
			cout << "2. �������� ������ �� ������������ �������" << endl;
			if (list.getParametr() == 1) {
				cout << "���������� ����������, ������ ����. ��� ������ ���������� ��������� ������." << endl;
				break;
			}
			else {
				while (flag == 1) {
					if (list.getParametr() == 1) {
						cout << "���������� ����������, ������ ����. ��� ������ ���������� ��������� ������." << endl;
						break;
					}
					list.read_number(bin_file_name);
					cout << "���������� ��������� � ������: " << list.getNumber() << endl;
					cout << "������� ����� ������:		";
					cin >> l;
					char* your_str = new char[l + 1];
					cout << "������� ������:	";
					cin >> your_str;
					cout << "������� ������� �� 1 �� " << list.getNumber() + 1 << ":	";
					cin >> your_pos;
					if (your_pos <= 0) {
						while (true) {
							cout << "���������� ����������. ����������, �������� ������� �� 1 �� " << list.getNumber() + 1 << endl;
							cin >> your_pos;
							if (((your_pos >= 1) && (your_pos <= list.getNumber() + 1)))
								break;
						}
					}
					if (your_pos > list.getNumber() + 1) {
						cout << "���������� ��������� � ������ ������:  " << list.getNumber() << ". ������� ������ ����� ��������� �� " << list.getNumber() + 1 << " �������." << endl;
						your_pos = list.getNumber() + 1;
					}

					list.insert_on_position(your_str, your_pos, bin_file_name);
					if (your_str != NULL)
						delete[] your_str;
					cout << "������� �������� �� " << your_pos << " �������. ���������� ��������� � ������: " << list.getNumber() << ". �������� ��� �������? �������� : 1 - �������� ����� �������    0 - ��������� � ����" << endl;
					cin >> flag;
					while (true) {
						if (((flag != 1) && (flag != 0))) {
							cout << "������. ����������, �������� 1 ���� 0." << endl;
							cin >> flag;
						}
						else break;
					}
				}
				break;
			}
		}
		case 3: {
			cout << "3. ������� ������ ������������ �������" << endl;
			int flag = 1; int pos;
			while (flag == 1) {
				if (list.getParametr() == 1) {
					cout << "���������� ����������, ������ ����. ��� ������ ���������� ��������� ������." << endl;
					break;
				}
				list.read_number(bin_file_name);
				cout << "���������� ��������� � ������: " << list.getNumber() << endl;
				cout << "������� ������� ��������� ������:		";
				cin >> pos;
				if (((pos <= 0) || (pos > list.getNumber()))) {
					while (true) {
						cout << "���������� ����������. ����������, �������� ������� �� 1 �� " << list.getNumber() << endl;
						cin >> pos;
						if (((pos >= 1) && (pos <= list.getNumber())))
							break;
					}
				}
				list.delete_line(pos, bin_file_name);
				cout << "������� ������ � " << pos << " �������. ���������� ��������� � ������: " << list.getNumber() << ". ������� ���? ��������: 1 - ������� ������ �������    0 - ��������� � ����" << endl;
				cin >> flag;
				while (true) {
					if (((flag != 1) && (flag != 0))) {
						cout << "������. ����������, �������� 1 ���� 0." << endl;
						cin >> flag;
					}
					else break;
				}
			}
			break;
		}
		case 4: {
			cout << "4. ������������� ������ ������������ �������" << endl;
			int flag = 1; int l, pos;
			while (flag == 1) {
				if (list.getParametr() == 1) {
					cout << "���������� ����������, ������ ����. ��� ������ ���������� ��������� ������." << endl;
					break;
				}
				list.read_number(bin_file_name);
				cout << "���������� ��������� � ������: " << list.getNumber() << endl;
				cout << "������� ������� ������������� ������ �� 1 �� " << list.getNumber() << ":	";
				cin >> pos;
				if (((pos <= 0) || (pos > list.getNumber()))) {
					while (true) {
						cout << "���������� ����������. ����������, �������� ������� �� 1 �� " << list.getNumber() << endl;
						cin >> pos;
						if (((pos >= 1) && (pos <= list.getNumber())))
							break;
					}
				}
				cout << "������� ����� ����� ������:		";
				cin >> l;
				char* new_str = new char[l + 1];
				cout << "������� ����� ������:	";
				cin >> new_str;
				list.edit_line(new_str, pos, bin_file_name);
				cout << "������� �� " << pos << " ������� ��������������. ���������� ��������� � ������: " << list.getNumber() << ". ������������� ���? ��������: 1 - ������������� ������ �������    0 - ��������� � ����" << endl;
				cin >> flag;
				while (true) {
					if (((flag != 1) && (flag != 0))) {
						cout << "������. ����������, �������� 1 ���� 0." << endl;
						cin >> flag;
					}
					else break;
				}
			}
			break;
		}
		case 5: {
			cout << "5. ��������� ������ � ��������� ����" << endl;
			if (list.getParametr() == 1) {
				cout << "���������� ����������, ������ ����. ��� ������ ���������� ��������� ������." << endl;
				break;
			}
			else {
				char out_file_name[50];
				cout << "������� �������� �����, � ������� ����� �������� ������. ������: out_file_name.txt" << endl;
				cout << "�������� �����: ";
				cin >> out_file_name;
				list.save_to_file(out_file_name, bin_file_name);
				cout << "��������� ���������� ������ � ���� " << out_file_name << endl;
				break;
			}
		}
		case 6: {
			cout << "6. ����������� ������" << endl;
			if (list.getParametr() == 1) {
				cout << "���������� ����������, ������ ����. ��� ������ ���������� ��������� ������." << endl;
				break;
			}
			else {
				list.show_list(bin_file_name);
				break;
			}
		}
		case 7: {
			cout << "7. ��������� ������ � ����� �� ���������" << endl;
			return;
		}
		}
	}
}