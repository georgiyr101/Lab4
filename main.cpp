#include "Human.h"
#include "Teacher.h"
#include "CommissionMember.h"
#include "TeacherCommissionMember.h"
#include "C:\Users\Admin\source\repos\Lab4\Queue.h"
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <limits>


void clearConsole() {
    system("cls");
}

void pauseConsole() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    cin.get();
}

int getChoice(int max) 
{
    int choice;
    cout << "Ваш выбор: ";
    cin >> choice;
    while (choice < 0 || choice > max) {
        cout << "Неверный выбор, попробуйте еще раз: ";
        cin >> choice;
    }
    return choice;
}

void editObject(Queue<Human*>& queue) 
{
    if (queue.isEmpty()) {
        cout << "Очередь пуста." << endl;
        return;
    }
    Human* human = queue.getFront();
    human->editFields();
}

void addObject(Queue<Human*>& queue) 
{
    cout << "1. Teacher\n";
    cout << "2. CommissionMember\n";
    cout << "3. TeacherCommissionMember\n";
    int typeChoice = getChoice(3);
    Human* object = nullptr;
    if (typeChoice == 1) {
        Teacher* teacher = new Teacher();
        cin >> *teacher;
        object = teacher;
    }
    else if (typeChoice == 2) {
        CommissionMember* commissionMember = new CommissionMember();
        cin >> *commissionMember;
        object = commissionMember;
    }
    else {
        TeacherCommissionMember* teacherCommissionMember = new TeacherCommissionMember();
        cin >> *teacherCommissionMember;
        object = teacherCommissionMember;
    }

    if (object != nullptr) {
        queue.enqueue(object);
        cout << "Объект добавлен в очередь!" << endl;
    }
}

void deleteObject(Queue<Human*>& queue) 
{
    if (queue.isEmpty()) {
        cout << "Очередь пуста." << endl;
        return;
    }
    Human* human = queue.getFront();
    delete human;
    queue.dequeue();
    cout << "Объект удален из очереди." << endl;
}

void peekObject(Queue<Human*>& queue) 
{
    if (queue.isEmpty()) {
        cout << "Очередь пуста" << endl;
        return;
    }
    Human* human = queue.getFront();
    human->printHeader();
    human->printInfo();
}

void printQueue(Queue<Human*>& queue) 
{
    if (queue.isEmpty()) {
        cout << "Очередь пуста." << endl;
        return;
    }
    Queue<Human*> temp;

    while (!queue.isEmpty()) 
    {
        Human* human = queue.getFront();
        queue.dequeue();
        human->printHeader();
        human->printInfo();
        cout << "\n";
        temp.enqueue(human);
    }
    while (!temp.isEmpty()) 
    {
        Human* human = temp.getFront();
        temp.dequeue();
        queue.enqueue(human);
    }
}

void clearQueue(Queue<Human*>& queue) 
{
    while (!queue.isEmpty())
    {
        Human* human = queue.getFront();
        queue.dequeue();
        delete human;
    }
    cout << "Очередь очищена." << endl;
}

void searchInQueue(Queue<Human*>& queue) {
    if (queue.isEmpty()) 
    {
        cout << "Очередь пуста." << endl;
        return;
    }

    cout << "Выберите параметры для поиска:\n";
    cout << "1. Фамилия\n";
    cout << "2. Имя\n";
    cout << "3. Год рождения\n";
    cout << "4. Должность (Teacher)\n";
    cout << "5. Специальность (Teacher)\n";
    cout << "6. Название комиссии (CommissionMember)\n";
    cout << "0. Завершить выбор параметров\n";

    bool searchLastName = false, searchFirstName = false, searchBirthYear = false;
    bool searchPosition = false, searchSpecialty = false, searchCommissionName = false;

    String lastName, firstName, position, specialty, commissionName;
    int birthYear = 0;

    int paramChoice;
    while (true) {
        cout << "Выберите параметр (0 - завершить выбор): ";
        paramChoice = getChoice(6);

        if (paramChoice == 0) {break;}
        
        if (paramChoice == 1) 
        {
            searchLastName = true;
            cout << "Введите фамилию: ";
            cin.ignore(1000, '\n');
            cin >> lastName;
        }
        else if (paramChoice == 2) 
        {
            searchFirstName = true;
            cout << "Введите имя: ";
            cin.ignore(1000, '\n');
            cin >> firstName;
        }
        else if (paramChoice == 3) 
        {
            searchBirthYear = true;
            cout << "Введите год рождения: ";
            cin.ignore(1000, '\n');
            cin >> birthYear;
        }
        else if (paramChoice == 4) 
        {
            searchPosition = true;
            cout << "Введите должность: ";
            cin.ignore(1000, '\n');
            cin >> position;
        }
        else if (paramChoice == 5) 
        {
            searchSpecialty = true;
            cout << "Введите специальность: ";
            cin.ignore(1000, '\n');
            cin >> specialty;
        }
        else if (paramChoice == 6) 
        {
            searchCommissionName = true;
            cout << "Введите название комиссии: ";
            cin.ignore(1000, '\n');
            cin >> commissionName;
        }
    }

    if (!searchLastName && !searchFirstName && !searchBirthYear &&
        !searchPosition && !searchSpecialty && !searchCommissionName) 
    {
        cout << "Не выбран ни один параметр для поиска." << endl;
        return;
    }

    Queue<Human*> searchResults = queue.find([=](Human* h) 
        {
        bool match = true;

        if (searchLastName && h->getLastName() != lastName) match = false;
        if (searchFirstName && h->getFirstName() != firstName) match = false;
        if (searchBirthYear && h->getBirthYear() != birthYear) match = false;

        if (searchPosition || searchSpecialty) {
            Teacher* teacher = dynamic_cast<Teacher*>(h);
            if (!teacher) {
                match = false;
            }
            else {
                if (searchPosition && teacher->getPosition() != position) match = false;
                if (searchSpecialty && teacher->getSpecialty() != specialty) match = false;
            }
        }

        if (searchCommissionName) {
            CommissionMember* member = dynamic_cast<CommissionMember*>(h);
            if (!member) {
                match = false;
            }
            else {
                if (member->getCommissionName() != commissionName) match = false;
            }
        }

        return match;
        });

    if (searchResults.isEmpty()) {
        cout << "Результаты не найдены." << endl;
    }
    else {
        cout << "Найденные результаты:" << endl;
        printQueue(searchResults);
    }
}

void sortQueueByField(Queue<Human*>& queue) {
    if (queue.isEmpty()) 
    {
        cout << "Очередь пуста." << endl;
        return;
    }

    cout << "Выберите параметр для сортировки:\n";
    cout << "1. Фамилия\n";
    cout << "2. Имя\n";
    cout << "3. Год рождения\n";
    cout << "4. Должность (Teacher)\n";
    cout << "5. Специальность (Teacher)\n";
    cout << "6. Название комиссии (CommissionMember)\n";

    int choice = getChoice(6);
    if (choice == 1) 
    {
        queue.sort([](Human& a, Human& b) {return a.getLastName() < b.getLastName();});
        cout << "Очередь отсортирована по фамилии." << endl;
    }
    else if (choice == 2) 
    {
        queue.sort([](Human& a, Human& b) {return a.getFirstName() < b.getFirstName();});
        cout << "Очередь отсортирована по имени." << endl;
    }
    else if (choice == 3) 
    {
        queue.sort([](Human& a, Human& b) {return a.getBirthYear() < b.getBirthYear();});
        cout << "Очередь отсортирована по году рождения." << endl;
    }
    else if (choice == 4) 
    {
        queue.sort([](Human& a, Human& b) 
            {
            Teacher* teacherA = dynamic_cast<Teacher*>(&a);
            Teacher* teacherB = dynamic_cast<Teacher*>(&b);
            if (teacherA && teacherB) {return teacherA->getPosition() < teacherB->getPosition();}
            if (teacherA) return true;
            if (teacherB) return false;
            return false;
            });
        cout << "Очередь отсортирована по должности." << endl;
    }
    else if (choice == 5) 
    {
        queue.sort([](Human& a, Human& b) 
            {
            Teacher* teacherA = dynamic_cast<Teacher*>(&a);
            Teacher* teacherB = dynamic_cast<Teacher*>(&b);
            if (teacherA && teacherB) {return teacherA->getSpecialty() < teacherB->getSpecialty();}
            if (teacherA) return true;
            if (teacherB) return false;
            return false;
            });
        cout << "Очередь отсортирована по специальности." << endl;
    }
    else if (choice == 6) 
    {
        queue.sort([](Human& a, Human& b) 
            {
            CommissionMember* memberA = dynamic_cast<CommissionMember*>(&a);
            CommissionMember* memberB = dynamic_cast<CommissionMember*>(&b);

            if (memberA && memberB) {
                return memberA->getCommissionName() < memberB->getCommissionName();
            }
            if (memberA) return true;
            if (memberB) return false;
            return false;
            });
        cout << "Очередь отсортирована по названию комиссии." << endl;
    }
    else {return;}
    printQueue(queue);
}

int main() {
    setlocale(LC_ALL, "russian");
    Queue<Human*> myQueue;
    int choice;
    do {
        clearConsole();
        cout << "1. Добавить объект\n";
        cout << "2. Удалить объект\n";
        cout << "3. Изменить объект\n";
        cout << "4. Посмотреть объект\n";
        cout << "5. Вывести очередь\n";
        cout << "6. Поиск в очереди\n";
        cout << "7. Сортировка очереди\n";
        cout << "8. Очистить очередь\n";
        cout << "0. Выход\n";
        choice = getChoice(8);
        switch (choice) {
        case 1:
            addObject(myQueue);
            break;
        case 2:
            deleteObject(myQueue);
            break;
        case 3:
            editObject(myQueue);
            break;
        case 4:
            peekObject(myQueue);
            break;
        case 5:
            printQueue(myQueue);
            break;
        case 6:
            searchInQueue(myQueue);
            break;
        case 7:
            sortQueueByField(myQueue);
            break;
        case 8:
            clearQueue(myQueue);
            break; 
        case 0:
            break;
        }
        if (choice != 0) {
            pauseConsole();
        }
    } while (choice != 0);

    clearQueue(myQueue);

    cout << "Выход из программы..." << endl;

    return 0;
}


