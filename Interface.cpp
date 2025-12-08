#include "Interface.h"

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
    choice = inputNumber(cin, 0, max);
    return choice;
}

template<typename T>
void addObject(Queue<T*>& queue)
{
    T* object = new T();
    cin >> *object;
    queue.enqueue(object);
    cout << "Объект добавлен в очередь!" << endl;
}

template<typename T>
void deleteObject(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Очередь пуста." << endl;
        return;
    }
    T* obj = queue.getFront();
    delete obj;
    queue.dequeue();
    cout << "Объект удален из очереди." << endl;
}

template<typename T>
void editObject(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Очередь пуста." << endl;
        return;
    }
    T* obj = queue.getFront();
    obj->editFields();
}

template<typename T>
void peekObject(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Очередь пуста" << endl;
        return;
    }
    T* obj = queue.getFront();
    obj->printHeader();
    obj->printInfo();
}

template<typename T>
void printQueue(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Очередь пуста." << endl;
        return;
    }
    T* firstObj = queue.getFront();
    if (firstObj)
    {
        cout << "Содержимое очереди:" << endl;
        firstObj->printHeader();
    }
    Queue<T*> temp;
    while (!queue.isEmpty())
    {
        T* obj = queue.getFront();
        queue.dequeue();
        obj->printInfo();
        cout << "\n";
        temp.enqueue(obj);
    }
    while (!temp.isEmpty())
    {
        T* obj = temp.getFront();
        temp.dequeue();
        queue.enqueue(obj);
    }
}

template<typename T>
void clearQueue(Queue<T*>& queue)
{
    while (!queue.isEmpty())
    {
        T* obj = queue.getFront();
        queue.dequeue();
        delete obj;
    }
    cout << "Очередь очищена." << endl;
}

struct SearchCriteria
{
    bool searchLastName = false, searchFirstName = false, searchBirthYear = false;
    bool searchPosition = false, searchSpecialty = false, searchCommissionName = false;
    string lastName, firstName, position, specialty, commissionName;
    int birthYear = 0;
};

SearchCriteria inputSearchCriteria()
{
    SearchCriteria criteria;
    int paramChoice;

    cout << "Выберите параметры для поиска:\n";
    cout << "1. Фамилия\n";
    cout << "2. Имя\n";
    cout << "3. Год рождения\n";
    cout << "4. Должность (Teacher)\n";
    cout << "5. Специальность (Teacher)\n";
    cout << "6. Название комиссии (CommissionMember)\n";
    cout << "0. Завершить выбор параметров\n";

    while (true) {
        cout << "Выберите параметр (0 - завершить выбор): ";
        paramChoice = getChoice(6);
        if (paramChoice == 0) break;
        switch (paramChoice) {
        case 1:
            criteria.searchLastName = true;
            cout << "Введите фамилию (только латиница, пробел или дефис): ";
            criteria.lastName = inputString();
            break;
        case 2:
            criteria.searchFirstName = true;
            cout << "Введите имя (только латиница, пробел или дефис): ";
            criteria.firstName = inputString();
            break;
        case 3:
            criteria.searchBirthYear = true;
            cout << "Введите год рождения: ";
            criteria.birthYear = inputNumber(cin, 1900, 2025);
            break;
        case 4:
            criteria.searchPosition = true;
            cout << "Введите должность (только латиница, пробел или дефис): ";
            criteria.position = inputString();
            break;
        case 5:
            criteria.searchSpecialty = true;
            cout << "Введите специальность (только латиница, пробел или дефис): ";
            criteria.specialty = inputString();
            break;
        case 6:
            criteria.searchCommissionName = true;
            cout << "Введите название комиссии (только латиница, пробел или дефис): ";
            criteria.commissionName = inputString();
            break;
        }
    }
    return criteria;
}

template<typename T>
bool matchesCriteria(T* obj, const SearchCriteria& criteria)
{
    if (criteria.searchLastName && obj->getLastName() != criteria.lastName)
        return false;
    if (criteria.searchFirstName && obj->getFirstName() != criteria.firstName)
        return false;
    if (criteria.searchBirthYear && obj->getBirthYear() != criteria.birthYear)
        return false;

    if (criteria.searchPosition || criteria.searchSpecialty)
    {
        Teacher* teacher = dynamic_cast<Teacher*>(obj);
        if (!teacher) return false;
        if (criteria.searchPosition && teacher->getPosition() != criteria.position)
            return false;
        if (criteria.searchSpecialty && teacher->getSpecialty() != criteria.specialty)
            return false;
    }

    if (criteria.searchCommissionName)
    {
        CommissionMember* member = dynamic_cast<CommissionMember*>(obj);
        if (!member) return false;
        if (member->getCommissionName() != criteria.commissionName)
            return false;
    }

    return true;
}

template<typename T>
void searchInQueue(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Очередь пуста." << endl;
        return;
    }
    SearchCriteria criteria = inputSearchCriteria();

    auto predicate = [&criteria](T* obj) {return matchesCriteria(obj, criteria); };
    Queue<T*> searchResults = queue.find(predicate);
    if (searchResults.isEmpty()) { cout << "Результаты не найдены." << endl; }
    else
    {
        cout << "Найденные результаты:" << endl;
        printQueue(searchResults);
    }
}

template<typename T>
void sortQueueByField(Queue<T*>& queue) {
    if (queue.isEmpty())
    {
        cout << "Очередь пуста." << endl;
        return;
    }

    cout << "Выберите параметр для сортировки:\n";
    cout << "1. Фамилия \n";
    cout << "2. Имя \n";
    cout << "3. Год рождения \n";
    cout << "4. Должность (Teacher)\n";
    cout << "5. Специальность (Teacher)\n";
    cout << "6. Название комиссии (CommissionMember)\n";

    int choice = getChoice(6);

    switch (choice)
    {
    case 1:
        queue.sort([](T* a, T* b) {return a->getLastName() < b->getLastName(); });
        cout << "Очередь отсортирована по фамилии." << endl;
        break;
    case 2:
        queue.sort([](T* a, T* b) {return a->getFirstName() < b->getFirstName(); });
        cout << "Очередь отсортирована по имени." << endl;
        break;
    case 3:
        queue.sort([](T* a, T* b) {return a->getBirthYear() < b->getBirthYear(); });
        cout << "Очередь отсортирована по году рождения." << endl;
        break;
    case 4:
        queue.sort([](T* a, T* b)
            {
                Teacher* teacherA = dynamic_cast<Teacher*>(a);
                Teacher* teacherB = dynamic_cast<Teacher*>(b);
                if (teacherA && teacherB) { return teacherA->getPosition() < teacherB->getPosition(); }
            });
        cout << "Очередь отсортирована по должности." << endl;
        break;
    case 5:
        queue.sort([](T* a, T* b)
            {
                Teacher* teacherA = dynamic_cast<Teacher*>(a);
                Teacher* teacherB = dynamic_cast<Teacher*>(b);
                if (teacherA && teacherB) { return teacherA->getSpecialty() < teacherB->getSpecialty(); }
            });
        cout << "Очередь отсортирована по специальности." << endl;
        break;

    case 6:
        queue.sort([](T* a, T* b)
            {
                CommissionMember* memberA = dynamic_cast<CommissionMember*>(a);
                CommissionMember* memberB = dynamic_cast<CommissionMember*>(b);
                if (memberA && memberB) { return memberA->getCommissionName() < memberB->getCommissionName(); }
            });
        cout << "Очередь отсортирована по названию комиссии." << endl;
        break;
    }
    cout << "\nОТСОРТИРОВАННАЯ ОЧЕРЕДЬ\n";
    printQueue(queue);
}

template<typename T>
void mainMenu(Queue<T*>& queue)
{
    int choice;
    do {
        clearConsole();
        cout << " МЕНЮ\n";
        cout << "1. Добавить объект\n";
        cout << "2. Удалить объект\n";
        cout << "3. Изменить объект (первый в очереди)\n";
        cout << "4. Посмотреть первый объект\n";
        cout << "5. Вывести всю очередь\n";
        cout << "6. Очистить очередь\n";
        cout << "7. Поиск в очереди\n";
        cout << "8. Сортировка очереди\n";
        cout << "0. Выйти в главное меню\n";

        choice = getChoice(8);

        switch (choice)
        {
        case 1:
            addObject(queue);
            break;
        case 2:
            deleteObject(queue);
            break;
        case 3:
            editObject(queue);
            break;
        case 4:
            peekObject(queue);
            break;
        case 5:
            printQueue(queue);
            break;
        case 6:
            clearQueue(queue);
            break;
        case 7:
            searchInQueue(queue);
            break;
        case 8:
            sortQueueByField(queue);
            break;
        case 0:
            clearQueue(queue);
            cout << "Возврат в главное меню..." << endl;
            break;
        }

        if (choice != 0 && choice != 6) { pauseConsole(); }
    } while (choice != 0);
}

void run()
{
    int mainChoice;

    do {
        clearConsole();
        cout << " ГЛАВНОЕ МЕНЮ \n";
        cout << "1. Работа с Teacher\n";
        cout << "2. Работа с CommissionMember\n";
        cout << "3. Работа с TeacherCommissionMember\n";
        cout << "0. Выход из программы\n";

        mainChoice = getChoice(3);

        if (mainChoice != 0)
        {
            clearConsole();
            cout << " СОЗДАНИЕ НОВОЙ ОЧЕРЕДИ \n";

            switch (mainChoice) {
            case 1:
            {
                Queue<Teacher*> teacherQueue;
                cout << "Создана очередь объектов типа Teacher\n";
                pauseConsole();
                mainMenu(teacherQueue);
                break;
            }
            case 2:
            {
                Queue<CommissionMember*> commissionQueue;
                cout << "Создана очередь объектов типа CommissionMember\n";
                pauseConsole();
                mainMenu(commissionQueue);
                break;
            }
            case 3:
            {
                Queue<TeacherCommissionMember*> teacherCommissionQueue;
                cout << "Создана очередь объектов типа TeacherCommissionMember\n";
                pauseConsole();
                mainMenu(teacherCommissionQueue);
                break;
            }
            }
        }

    } while (mainChoice != 0);

    cout << "\nВыход из программы..." << endl;
    pauseConsole();
}
