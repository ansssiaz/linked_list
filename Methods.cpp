#include "Header.h"

binary_file::binary_file(int p) :fstream() {
    node current;
    current.str = NULL;
    current.length = 0;
    current.next = -1;
    number = 0;
    first = 8;
    parametr = p;
}

binary_file::~binary_file() {
    delete[] current.str;
    cout << "Вызов деструктора" << endl;
}

long count_lines(const char* in_text_file) {
    fstream in;
    in.open(in_text_file, ios::in);
    char buffer[50]; int count = 0;
    if (in.is_open()) {
        while (in >> buffer) {
            count = count + 1;
        }
    }
    else cout << "Ошибка открытия файла" << endl;
    in.close();
    return count;
}

void binary_file::add(char* line, const char* bin_file) {
    current.length = strlen(line);
    current.str = new char[current.length + 1];
    for (int i = 0; i < current.length; i++)
    {
        current.str[i] = line[i];
    }
    current.str[current.length] = '\0';
    if (number == 0) {       // если список пуст, добавляем первый элемент в список
        seekg(0, ios::beg);
        current.next = tellg();       //заголовок списка
        seekp(0, ios::beg);
        if (current.next == 0)
            first = 8;
        write((char*)&first, sizeof(first));
        current.next = -1;
        seekp(first, ios::beg);
        write((char*)&current.next, sizeof(current.next));
        write((char*)&current.length, sizeof(current.length));
        write(current.str, current.length);
    }
    else {
        long temp_next = 0;
        long last = 8;
        seekg(0, ios::beg);
        read((char*)&temp_next, sizeof(temp_next));
        seekg(temp_next, ios::beg);
        read((char*)&temp_next, sizeof(temp_next));
        while (temp_next != -1) {
            last = temp_next;
            seekg(temp_next, ios::beg);
            read((char*)&temp_next, sizeof(temp_next));
        }
        seekg(0, ios::end);
        current.next = tellg();
        seekp(last, ios::beg);
        write((char*)&current.next, sizeof(current.next));
        seekp(current.next, ios::beg);
        current.next = -1;
        write((char*)&current.next, sizeof(current.next));
        write((char*)&current.length, sizeof(current.length));
        write(current.str, current.length);
    }
    number = number + 1;
}

void binary_file::fill_from_file(const char* in_text_file, const char* bin_file) {
    fstream in;
    in.open(in_text_file, ios::in);
    if (parametr == 1) {
        this->open(bin_file, ios::out | ios::in | ios::binary| ios::trunc);
        parametr = 0;
    }
    else if (parametr == 0) {
        this->open(bin_file, ios::out | ios::in| ios::binary);
        seekg(0, ios::beg);
        read((char*)&first, sizeof(first));
        read((char*)&number, sizeof(number));
    }
    if (((in.is_open()) && (this->is_open()))) {
        long quantity = count_lines(in_text_file);
        char** line_array = new char* [quantity];
        for (int j = 0; j < quantity; j++) {
            line_array[j] = new char[50];
            in >> line_array[j];
        }
        for (int j = 0; j < quantity; j++) {
            this->add(line_array[j], bin_file);
        }
        seekp(4, ios::beg);
        write((char*)&number, sizeof(number));
        delete[] line_array;
    }
    else cout << "Ошибка открытия файла" << endl;
    in.close();
    this->close();
}

void binary_file::save_to_file(const char* out_text_file, const char* bin_file) {
    fstream out;
    out.open(out_text_file, ios::out | ios::trunc);
    if (parametr == 0) {
        this->open(bin_file, ios::in | ios::binary);
        seekg(4, ios::beg);
        read((char*)&number, sizeof(number));
    }
    if (((out.is_open()) && (this->is_open()))) {
        seekg(0, ios::beg);
        node* array_current = new node[number + 1];
        read((char*)&array_current[0].next, sizeof(current.next));//считываем из двоичного файла заголовок списка
        for (int j = 1; j <= number; j++) {
            seekg(array_current[j - 1].next, ios::beg);
            read((char*)&array_current[j].next, sizeof(current.next));
            read((char*)&array_current[j].length, sizeof(current.length));
            array_current[j].str = new char[array_current[j].length + 1];
            read(array_current[j].str, array_current[j].length);
            array_current[j].str[array_current[j].length] = '\0';
        } 
        out << "Количество элементов в списке: " << number << endl;
        out << "Заголовок списка: " << array_current[0].next << endl; 
        out << "-----------------------------------------------------------------------------------" << endl;
        out << "||     N      ||    Следующий элемент:      ||      Длина     ||    Строка        || " << endl;
        out << "-----------------------------------------------------------------------------------" << endl;
        for (int j = 1; j <= number; j++) {
            out << "      " << j << "                   " << array_current[j].next << "                       " << array_current[j].length << "             " << array_current[j].str << endl;
        }
        delete[] array_current;
    }
    else cout << "Ошибка открытия файла" << endl;
    out.close();
    this->close();
}

void binary_file::insert_on_position(char* line, int pos, const char* bin_file) {
    long prev = 0;
    long next_line = 0;
    if (parametr == 0) {
        this->open(bin_file, ios::in | ios::out | ios::binary);
        seekg(4, ios::beg);
        read((char*)&number, sizeof(number));
    }
    if (pos == number + 1)
    {
        add(line, bin_file);
        seekp(4, ios::beg);
        write((char*)&number, sizeof(number));
    }
    else {
        seekg(0, ios::beg);
        read((char*)&next_line, sizeof(next_line));
        for (int k = 0; k < pos - 1; k++) {
            if (pos == 2)
                prev = next_line;
            seekg(next_line, ios::beg);
            read((char*)&next_line, sizeof(next_line));
            if (k == pos - 3)
                prev = next_line;
        }
        current.next = next_line;
        seekp(0, ios::end);
        write((char*)&current.next, sizeof(current.next));
        current.length = strlen(line);
        write((char*)&current.length, sizeof(current.length));
        current.str = new char[current.length + 1];
        for (int i = 0; i < current.length; i++)
        {
            current.str[i] = line[i];
        }
        current.str[current.length] = '\0';
        write(current.str, current.length);
        seekg(-(current.length + 4 + 4), ios::cur);
        current.next = tellg();
        seekp(prev, ios::beg);
        write((char*)&current.next, sizeof(current.next));
        number = number + 1;
        seekp(4, ios::beg);
        write((char*)&number, sizeof(number));
    }
    this->close();
}

long binary_file::delete_line(int pos, const char* bin_file) {
    long prev = 0;
    if (parametr == 0) {
        this->open(bin_file, ios::in | ios::out | ios::binary);
        seekg(4, ios::beg);
        read((char*)&number, sizeof(number));
    }
    seekg(0, ios::beg);
    read((char*)&current.next, sizeof(current.next));               //считываем из двоичного файла заголовок списка
    for (int k = 0; k < pos; k++) {             //находим указатель на элемент под номером pos
        if (pos == 2) {
            prev = current.next;
            k++;
            seekg(current.next, ios::beg);
            read((char*)&current.next, sizeof(current.next));
        }
        seekg(current.next, ios::beg);
        read((char*)&current.next, sizeof(current.next));
        if (k == pos - 3)
            prev = current.next;                        //находим указатель на элемент под номером pos-1
    }
    if (pos == number)
        current.next = -1;
    seekp(prev, ios::beg);
    write((char*)&current.next, sizeof(current.next));
    number = number - 1;
    seekp(4, ios::beg);
    write((char*)&number, sizeof(number));
    this->close();
    return prev;
}

void binary_file::edit_line(char* line, int pos, const char* bin_file) {
    long prev;
    if (parametr == 0) {
        this->open(bin_file, ios::in | ios::out | ios::binary);
        seekg(4, ios::beg);
        read((char*)&number, sizeof(number));
        this->close();
    }
    prev = delete_line(pos, bin_file);//указатель на элемент перед редактируемым
    this->open(bin_file, ios::in | ios::out | ios::binary);
    seekg(prev, ios::beg);
    read((char*)&current.next, sizeof(current.next));//указатель на элемент после редактируемого
    seekp(0, ios::end);
    write((char*)&current.next, sizeof(current.next));//записываем указатель на редактируемый элемент
    current.length = strlen(line);
    write((char*)&current.length, sizeof(current.length));
    current.str = new char[current.length + 1];
    for (int i = 0; i < current.length; i++)
    {
        current.str[i] = line[i];
    }
    current.str[current.length] = '\0';
    write(current.str, current.length);
    seekg(-(current.length + 4 + 4), ios::cur);
    current.next = tellg();
    seekp(prev, ios::beg);
    write((char*)&current.next, sizeof(current.next));
    number = number + 1;
    seekp(4, ios::beg);
    write((char*)&number, sizeof(number));
    this->close();
}

void binary_file::show_list(const char* bin_file) {
    if (parametr == 0) {
        this->open(bin_file, ios::in | ios::binary);
        seekg(4, ios::beg);
        read((char*)&number, sizeof(number));
    }
    cout << "Количество элементов в списке: " << number << endl;
    if (this->is_open()) {
        seekg(0, ios::beg);
        node* array_current = new node[number + 1];
        read((char*)&array_current[0].next, sizeof(current.next));
        cout << "Заголовок списка: " << array_current[0].next << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << "||     N      ||    Следующий элемент:      ||      Длина     ||    Строка        || " << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        for (int j = 1; j <= number; j++) {
            seekg(array_current[j - 1].next, ios::beg);
            read((char*)&array_current[j].next, sizeof(current.next));
            read((char*)&array_current[j].length, sizeof(current.length));
            array_current[j].str = new char[array_current[j].length + 1];
            read(array_current[j].str, array_current[j].length);
            array_current[j].str[array_current[j].length] = '\0';
        }
        for (int j = 1; j <= number; j++) {
            cout << "      " << j << "                   " << array_current[j].next << "                       " << array_current[j].length << "                " << array_current[j].str << endl;
        }
        delete[] array_current;
    }
    else cout << "Ошибка открытия файла" << endl;
    this->close();
}

void binary_file::read_number(const char* bin_file) {
    if (parametr == 0) {
        this->open(bin_file, ios::in | ios::binary);
        seekg(4, ios::beg);
        read((char*)&number, sizeof(number));
        this->close();
    }
}