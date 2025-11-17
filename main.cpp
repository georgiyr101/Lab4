#include "Human.h"
#include "Teacher.h"
#include "CommissionMember.h"
#include "TeacherCommissionMember.h"
#include "C:\Users\Admin\source\repos\Lab4\Queue.h"
#include <iostream>
#include <iomanip>
#include <locale.h>


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
    if (queue.isEmpty()) {
        cout << "Очередь пуста." << endl;
        return;
    }
    cout << "1. Поиск по фамилии\n";
    cout << "2. Поиск по имени\n";
    cout << "3. Поиск по году рождения\n";
    cout << "4. Поиск по всем параметрам\n";
    int choice = getChoice(4);
    String searchString;
    int searchYear = 0;
    Teacher* searchObj = new Teacher("","",0,"","");
    if (choice == 1) {
        cout << "Введите фамилию для поиска: ";
        cin.ignore(1000, '\n');
        cin >> searchString;
        searchObj->setLastName(searchString);
        Human::setSearchParams(LAST_NAME);
    }
    else if (choice == 2) {
        cout << "Введите имя для поиска: ";
        cin.ignore(1000, '\n');
        cin >> searchString;
        searchObj->setFirstName(searchString);
        Human::setSearchParams(FIRST_NAME);
    }
    else if (choice == 3) {
        cout << "Введите год рождения для поиска: ";
        cin.ignore(1000, '\n');
        cin >> searchYear;
        searchObj->setBirthYear(searchYear);
        Human::setSearchParams(BIRTH_YEAR);
    }
    else if (choice == 4) {
        cout << "Введите фамилию для поиска: ";
        cin.ignore(1000, '\n');
        cin >> searchString;
        searchObj->setLastName(searchString);
        cout << "Введите имя для поиска: ";
        cin >> searchString;
        searchObj->setFirstName(searchString);
        cout << "Введите год рождения для поиска: ";
        cin >> searchYear;
        searchObj->setBirthYear(searchYear);
        Human::setSearchParams(ALL_PARAMS);
    }

    Queue<Human*> searchResults = queue.find(searchObj);
    //
    delete searchObj;
    if (searchResults.isEmpty()) {
        cout << "Совпадений нет." << endl;
    }
    else {
        cout << "Результаты поиска:" << endl;
        printQueue(searchResults);
    }
}

void sortQueueByField(Queue<Human*>& queue) {
    if (queue.isEmpty()) {
        cout << "Очередь пуста." << endl;
        return;
    }
    cout << "1. Сортировка по фамилии\n";
    cout << "2. Сортировка по имени\n";
    cout << "3. Сортировка по году рождения\n";
    int choice = getChoice(4);
    if (choice == 1) {
        Human::setSearchParams(LAST_NAME);
    }
    else if (choice == 2) {
        Human::setSearchParams(FIRST_NAME);
    }
    else if (choice == 3) {Human::setSearchParams(BIRTH_YEAR);}
    else {
        cout << "Неверный выбор." << endl;
        return;
    }
    queue.sort();
    Human::setSearchParams(LAST_NAME);
    cout << "Очередь отсортирована." << endl;
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


