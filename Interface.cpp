#include "Interface.h"
#include "Input.h"
#include "FileTxt.h"
#include "FileBin.h"
#include "FileTxt.cpp"
#include "FileBin.cpp"
#include "Exp_file.h"
#include <windows.h>
#include <functional>
#include <vector>
#include <algorithm>

void clearConsole() {
    system("cls");
}

void pauseConsole() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

int getChoice(int max)
{
    int choice;
    choice = inputNumber(cin, 0, max, "Select option: ");
    return choice;
}

template<typename T>
void addObject(Queue<T*>& queue)
{
    T* object = new T();
    cin >> *object;
    queue.enqueue(object);
    cout << "Object added to queue!" << endl;
}

template<typename T>
void deleteObject(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Queue is empty." << endl;
        return;
    }
    T* obj = queue.getFront();
    delete obj;
    queue.dequeue();
    cout << "Object removed from queue." << endl;
}

template<typename T>
void editObject(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Queue is empty." << endl;
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
        cout << "Queue is empty" << endl;
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
        cout << "Queue is empty." << endl;
        return;
    }
    T* firstObj = queue.getFront();
    if (firstObj)
    {
        cout << "List of objects:" << endl;
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
    cout << "Queue cleared." << endl;
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

    cout << "Select search parameter:\n";
    cout << "1. Last Name\n";
    cout << "2. First Name\n";
    cout << "3. Birth Year\n";
    cout << "4. Position (Teacher)\n";
    cout << "5. Specialty (Teacher)\n";
    cout << "6. Commission Name (CommissionMember)\n";
    cout << "0. Exit\n";

    while (true) {
        cout << "Select parameter (0 - exit): ";
        paramChoice = getChoice(6);
        if (paramChoice == 0) break;
        switch (paramChoice) {
        case 1:
            criteria.searchLastName = true;
            criteria.lastName = inputName(std::cin, "Enter last name (Latin letters, space or hyphen): ");
            break;
        case 2:
            criteria.searchFirstName = true;
            criteria.firstName = inputName(std::cin, "Enter first name (Latin letters, space or hyphen): ");
            break;
        case 3:
            criteria.searchBirthYear = true;
            criteria.birthYear = inputNumber(std::cin, 1925, 2007, "Enter birth year: ");
            break;
        case 4:
            criteria.searchPosition = true;
            criteria.position = inputString(std::cin, "Enter position (Latin letters, space or hyphen): ");
            break;
        case 5:
            criteria.searchSpecialty = true;
            criteria.specialty = inputString(std::cin, "Enter specialty (Latin letters, space or hyphen): ");
            break;
        case 6:
            criteria.searchCommissionName = true;
            criteria.commissionName = inputString(std::cin, "Enter commission name (Latin letters, space or hyphen): ");
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
        cout << "Queue is empty." << endl;
        return;
    }
    SearchCriteria criteria = inputSearchCriteria();

    auto predicate = [&criteria](T* obj) {return matchesCriteria(obj, criteria); };
    Queue<T*> searchResults = queue.find(predicate);
    if (searchResults.isEmpty()) { cout << "Nothing found." << endl; }
    else
    {
        cout << "Found objects:" << endl;
        printQueue(searchResults);
    }
}

template<typename T>
void sortQueueByField(Queue<T*>& queue) {
    if (queue.isEmpty())
    {
        cout << "Queue is empty." << endl;
        return;
    }

    cout << "Select sort parameter:\n";
    cout << "1. Last Name \n";
    cout << "2. First Name \n";
    cout << "3. Birth Year \n";
    cout << "4. Position (Teacher)\n";
    cout << "5. Specialty (Teacher)\n";
    cout << "6. Commission Name (CommissionMember)\n";

    int choice = getChoice(6);

    switch (choice)
    {
    case 1:
        queue.sort([](T* a, T* b) {return a->getLastName() < b->getLastName(); });
        cout << "Objects sorted by last name." << endl;
        break;
    case 2:
        queue.sort([](T* a, T* b) {return a->getFirstName() < b->getFirstName(); });
        cout << "Objects sorted by first name." << endl;
        break;
    case 3:
        queue.sort([](T* a, T* b) {return a->getBirthYear() < b->getBirthYear(); });
        cout << "Objects sorted by birth year." << endl;
        break;
    case 4:
        queue.sort([](T* a, T* b)
            {
                Teacher* teacherA = dynamic_cast<Teacher*>(a);
                Teacher* teacherB = dynamic_cast<Teacher*>(b);
                if (teacherA && teacherB) { return teacherA->getPosition() < teacherB->getPosition(); }
            });
        cout << "Objects sorted by position." << endl;
        break;
    case 5:
        queue.sort([](T* a, T* b)
            {
                Teacher* teacherA = dynamic_cast<Teacher*>(a);
                Teacher* teacherB = dynamic_cast<Teacher*>(b);
                if (teacherA && teacherB) { return teacherA->getSpecialty() < teacherB->getSpecialty(); }
            });
        cout << "Objects sorted by specialty." << endl;
        break;

    case 6:
        queue.sort([](T* a, T* b)
            {
                CommissionMember* memberA = dynamic_cast<CommissionMember*>(a);
                CommissionMember* memberB = dynamic_cast<CommissionMember*>(b);
                if (memberA && memberB) { return memberA->getCommissionName() < memberB->getCommissionName(); }
            });
        cout << "Objects sorted by commission name." << endl;
        break;
    }
    cout << "\nSorted objects:\n";
    printQueue(queue);
}

template<typename T>
void saveToFile(Queue<T*>& queue)
{
    if (queue.isEmpty())
    {
        cout << "Queue is empty. No objects to save." << endl;
        return;
    }

    cout << "Select file type for saving:\n";
    cout << "1. Text file\n";
    cout << "2. Binary file\n";
    int fileTypeChoice = getChoice(2);

    string filename;
    cout << "Enter filename: ";
    cin.ignore(1000, '\n');
    getline(cin, filename);

    try {
        if (fileTypeChoice == 1)
        {
            FileTxt<T> fileTxt(filename);
            Queue<T*> temp;
            while (!queue.isEmpty())
            {
                T* obj = queue.getFront();
                queue.dequeue();
                fileTxt.save(*obj);
                temp.enqueue(obj);
            }
            while (!temp.isEmpty())
            {
                T* obj = temp.getFront();
                temp.dequeue();
                queue.enqueue(obj);
            }
            cout << "Objects saved to text file " << filename << endl;
        }
        else
        {
            FileBin<T> fileBin(filename);
            Queue<T*> temp;
            while (!queue.isEmpty())
            {
                T* obj = queue.getFront();
                queue.dequeue();
                fileBin.save(*obj);
                temp.enqueue(obj);
            }
            while (!temp.isEmpty())
            {
                T* obj = temp.getFront();
                temp.dequeue();
                queue.enqueue(obj);
            }
            cout << "Objects saved to binary file " << filename << endl;
        }
    }
    catch (const FileException& e)
    {
        cout << "Error saving file: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error saving file." << endl;
    }
}

template<typename T>
void loadFromFile(Queue<T*>& queue)
{
    cout << "Select file type for loading:\n";
    cout << "1. Text file\n";
    cout << "2. Binary file\n";
    int fileTypeChoice = getChoice(2);

    string filename;
    cout << "Enter filename: ";
    cin.ignore(1000, '\n');
    getline(cin, filename);

    try {
        if (fileTypeChoice == 1)
        {
            FileTxt<T> fileTxt(filename);
            Queue<T*> loadedQueue = fileTxt.read();
            if (loadedQueue.isEmpty())
            {
                cout << "File is empty. No objects to load." << endl;
                return;
            }
            while (!loadedQueue.isEmpty())
            {
                T* obj = loadedQueue.getFront();
                loadedQueue.dequeue();
                queue.enqueue(obj);
            }
            cout << "Objects loaded from text file " << filename << endl;
        }
        else
        {
            FileBin<T> fileBin(filename);
            Queue<T*> loadedQueue = fileBin.read();
            if (loadedQueue.isEmpty())
            {
                cout << "File is empty. No objects to load." << endl;
                return;
            }
            while (!loadedQueue.isEmpty())
            {
                T* obj = loadedQueue.getFront();
                loadedQueue.dequeue();
                queue.enqueue(obj);
            }
            cout << "Objects loaded from binary file " << filename << endl;
        }
    }
    catch (const FileException& e)
    {
        cout << "Error loading file: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error loading file." << endl;
    }
}

template<typename T>
void mainMenu(Queue<T*>& queue)
{
    int choice;
    do {
        clearConsole();
        cout << " Main Menu\n";
        cout << "1. Add object\n";
        cout << "2. Delete object\n";
        cout << "3. Edit object\n";
        cout << "4. View object\n";
        cout << "5. Print all objects\n";
        cout << "6. Clear queue\n";
        cout << "7. Search object\n";
        cout << "8. Sort objects\n";
        cout << "9. Save to file\n";
        cout << "10. Load from file\n";
        cout << "0. Exit\n";

        choice = getChoice(10);

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
        case 9:
            saveToFile(queue);
            break;
        case 10:
            loadFromFile(queue);
            break;
        case 0:
            clearQueue(queue);
            cout << "Exiting program..." << endl;
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
        cout << "Main Menu \n";
        cout << "1. Teacher\n";
        cout << "2. CommissionMember\n";
        cout << "3. TeacherCommissionMember\n";
        cout << "4. Work with STL\n";
        cout << "0. Exit\n";

        mainChoice = getChoice(4);

        if (mainChoice != 0)
        {
            clearConsole();
            cout << " CREATING NEW QUEUE \n";

            switch (mainChoice) {
            case 1:
            {
                Queue<Teacher*> teacherQueue;
                cout << "Creating new Teacher queue\n";
                pauseConsole();
                mainMenu(teacherQueue);
                break;
            }
            case 2:
            {
                Queue<CommissionMember*> commissionQueue;
                cout << "Creating new CommissionMember queue\n";
                pauseConsole();
                mainMenu(commissionQueue);
                break;
            }
            case 3:
            {
                Queue<TeacherCommissionMember*> teacherCommissionQueue;
                cout << "Creating new TeacherCommissionMember queue\n";
                pauseConsole();
                mainMenu(teacherCommissionQueue);
                break;
            }
            case 4:
            {
                clearConsole();
                cout << " STL Container Selection \n";
                cout << "1. Teacher\n";
                cout << "2. CommissionMember\n";
                cout << "3. TeacherCommissionMember\n";
                cout << "0. Back\n";

                int stlChoice = getChoice(3);
                if (stlChoice != 0)
                {
                    clearConsole();
                    cout << " Creating new STL container \n";

                    switch (stlChoice) {
                    case 1:
                    {
                        STLContainer<Teacher> teacherContainer;
                        cout << "Creating new Teacher STL container\n";
                        pauseConsole();
                        stlMenu(teacherContainer);
                        break;
                    }
                    case 2:
                    {
                        STLContainer<CommissionMember> commissionContainer;
                        cout << "Creating new CommissionMember STL container\n";
                        pauseConsole();
                        stlMenu(commissionContainer);
                        break;
                    }
                    case 3:
                    {
                        STLContainer<TeacherCommissionMember> teacherCommissionContainer;
                        cout << "Creating new TeacherCommissionMember STL container\n";
                        pauseConsole();
                        stlMenu(teacherCommissionContainer);
                        break;
                    }
                    }
                }
                break;
            }
            }
        }

    } while (mainChoice != 0);

    cout << "\nExiting program..." << endl;
    pauseConsole();
}

// STL Container functions implementation
template<typename T>
void addToSTLContainer(STLContainer<T>& container)
{
    try {
        T* object = new T();
        cin >> *object;
        int id = container.add(object);
        cout << "Object added to STL container with ID: " << id << endl;
    }
    catch (const ContainerException& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error adding object to container." << endl;
    }
}

template<typename T>
void viewFromSTLContainer(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    cout << "Enter ID to view: ";
    int id;
    cin >> id;

    try {
        T* obj = container.view(id);
        obj->printHeader();
        obj->printInfo();
    }
    catch (const ContainerException& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error viewing object from container." << endl;
    }
}

template<typename T>
void deleteFromSTLContainer(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    cout << "Enter ID to delete: ";
    int id;
    cin >> id;

    try {
        container.remove(id);
        cout << "Object with ID " << id << " deleted." << endl;
    }
    catch (const ContainerException& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error deleting object from container." << endl;
    }
}

template<typename T>
void printSTLContainer(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    try {
        T* firstObj = nullptr;
        typename STLContainer<T>::Iterator it = container.begin();
        if (it != container.end())
        {
            firstObj = (*it).second;
            if (firstObj)
            {
                cout << "List of objects in STL container:" << endl;
                firstObj->printHeader();
            }
        }

        for (typename STLContainer<T>::Iterator it = container.begin(); it != container.end(); ++it)
        {
            if ((*it).second)
            {
                (*it).second->printInfo();
                cout << "\n";
            }
        }
    }
    catch (const ContainerException& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error printing container." << endl;
    }
}

template<typename T>
void setIteratorToBegin(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    try {
        typename STLContainer<T>::Iterator it = container.begin();
        
        cout << "Iterator set to beginning." << endl;
        if (it != container.end())
        {
            cout << "Current element ID: " << (*it).first << endl;
            if ((*it).second)
            {
                (*it).second->printHeader();
                (*it).second->printInfo();
            }
        }
    }
    catch (const ContainerException& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error setting iterator to beginning." << endl;
    }
}

template<typename T>
void setIteratorToEnd(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    typename STLContainer<T>::Iterator it = container.end();
    --it; // Move to last element
    
    cout << "Iterator set to end." << endl;
    cout << "Last element ID: " << (*it).first << endl;
    if ((*it).second)
    {
        (*it).second->printHeader();
        (*it).second->printInfo();
    }
}

template<typename T>
void searchInSTLContainer(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    SearchCriteria criteria = inputSearchCriteria();

    typename STLContainer<T>::Iterator beginIt = container.begin();
    typename STLContainer<T>::Iterator endIt = container.end();

    // Create predicate for search
    auto predicate = [&criteria](const pair<const int, T*>& p) {
        return matchesCriteria(p.second, criteria);
    };

    // Use Algorithms::find to search
    typename STLContainer<T>::Iterator foundIt = Algorithms::find(beginIt, endIt, predicate);

    if (foundIt != endIt)
    {
        cout << "Found object with ID: " << (*foundIt).first << endl;
        (*foundIt).second->printHeader();
        (*foundIt).second->printInfo();
    }
    else
    {
        cout << "No objects found matching criteria." << endl;
    }
}

template<typename T>
void sortSTLContainer(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty." << endl;
        return;
    }

    cout << "Select sort parameter:\n";
    cout << "1. Last Name\n";
    cout << "2. First Name\n";
    cout << "3. Birth Year\n";
    cout << "4. Position (Teacher)\n";
    cout << "5. Specialty (Teacher)\n";
    cout << "6. Commission Name (CommissionMember)\n";

    int choice = getChoice(6);

    typename STLContainer<T>::Iterator beginIt = container.begin();
    typename STLContainer<T>::Iterator endIt = container.end();

    // Note: map is already sorted by key, so we'll create a sorted view
    // For actual sorting by value, we'd need to use a different approach
    vector<pair<int, T*>> sortedPairs;
    for (typename STLContainer<T>::Iterator it = beginIt; it != endIt; ++it)
    {
        sortedPairs.push_back(make_pair((*it).first, (*it).second));
    }

    // Define comparison function based on choice
    function<bool(const pair<int, T*>&, const pair<int, T*>&)> comp;
    
    switch (choice)
    {
    case 1:
        comp = [](const pair<int, T*>& a, const pair<int, T*>& b) {
            return a.second->getLastName() < b.second->getLastName();
        };
        break;
    case 2:
        comp = [](const pair<int, T*>& a, const pair<int, T*>& b) {
            return a.second->getFirstName() < b.second->getFirstName();
        };
        break;
    case 3:
        comp = [](const pair<int, T*>& a, const pair<int, T*>& b) {
            return a.second->getBirthYear() < b.second->getBirthYear();
        };
        break;
    case 4:
        comp = [](const pair<int, T*>& a, const pair<int, T*>& b) {
            Teacher* teacherA = dynamic_cast<Teacher*>(a.second);
            Teacher* teacherB = dynamic_cast<Teacher*>(b.second);
            if (teacherA && teacherB) return teacherA->getPosition() < teacherB->getPosition();
            return false;
        };
        break;
    case 5:
        comp = [](const pair<int, T*>& a, const pair<int, T*>& b) {
            Teacher* teacherA = dynamic_cast<Teacher*>(a.second);
            Teacher* teacherB = dynamic_cast<Teacher*>(b.second);
            if (teacherA && teacherB) return teacherA->getSpecialty() < teacherB->getSpecialty();
            return false;
        };
        break;
    case 6:
        comp = [](const pair<int, T*>& a, const pair<int, T*>& b) {
            CommissionMember* memberA = dynamic_cast<CommissionMember*>(a.second);
            CommissionMember* memberB = dynamic_cast<CommissionMember*>(b.second);
            if (memberA && memberB) return memberA->getCommissionName() < memberB->getCommissionName();
            return false;
        };
        break;
    }

    std::sort(sortedPairs.begin(), sortedPairs.end(), comp);

    cout << "\nSorted objects:\n";
    T* firstObj = sortedPairs.empty() ? nullptr : sortedPairs[0].second;
    if (firstObj)
    {
        firstObj->printHeader();
    }
    for (const auto& pair : sortedPairs)
    {
        if (pair.second)
        {
            pair.second->printInfo();
            cout << "\n";
        }
    }
}

template<typename T>
void saveSTLContainerToFile(STLContainer<T>& container)
{
    if (container.isEmpty())
    {
        cout << "Container is empty. No objects to save." << endl;
        return;
    }

    cout << "Select file type for saving:\n";
    cout << "1. Text file\n";
    cout << "2. Binary file\n";
    int fileTypeChoice = getChoice(2);

    string filename;
    cout << "Enter filename: ";
    cin.ignore(1000, '\n');
    getline(cin, filename);

    try {
        if (fileTypeChoice == 1)
        {
            FileTxt<T> fileTxt(filename);
            fileTxt.saveSTLContainer(container);
            cout << "Objects saved to text file " << filename << endl;
        }
        else
        {
            FileBin<T> fileBin(filename);
            fileBin.saveSTLContainer(container);
            cout << "Objects saved to binary file " << filename << endl;
        }
    }
    catch (const FileException& e)
    {
        cout << "Error saving file: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error saving file." << endl;
    }
}

template<typename T>
void loadSTLContainerFromFile(STLContainer<T>& container)
{
    if (!container.isEmpty())
    {
        cout << "Warning: Container is not empty. Loading will add to existing objects." << endl;
        cout << "Do you want to clear container first? (1 - Yes, 0 - No): ";
        int clearChoice = getChoice(1);
        if (clearChoice == 1)
        {
            container.clear();
        }
    }

    cout << "Select file type for loading:\n";
    cout << "1. Text file\n";
    cout << "2. Binary file\n";
    int fileTypeChoice = getChoice(2);

    string filename;
    cout << "Enter filename: ";
    cin.ignore(1000, '\n');
    getline(cin, filename);

    try {
        if (fileTypeChoice == 1)
        {
            FileTxt<T> fileTxt(filename);
            fileTxt.loadSTLContainer(container);
            cout << "Objects loaded from text file " << filename << endl;
        }
        else
        {
            FileBin<T> fileBin(filename);
            fileBin.loadSTLContainer(container);
            cout << "Objects loaded from binary file " << filename << endl;
        }
    }
    catch (const FileException& e)
    {
        cout << "Error loading file: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Error loading file." << endl;
    }
}

template<typename T>
void stlMenu(STLContainer<T>& container)
{
    int choice;
    do {
        clearConsole();
        cout << " STL Container Menu\n";
        cout << "1. Add object\n";
        cout << "2. View object\n";
        cout << "3. Delete object\n";
        cout << "4. Print all objects\n";
        cout << "5. Set iterator to beginning\n";
        cout << "6. Set iterator to end\n";
        cout << "7. Search object\n";
        cout << "8. Sort objects\n";
        cout << "9. Save to file\n";
        cout << "10. Load from file\n";
        cout << "0. Exit\n";

        choice = getChoice(10);

        switch (choice)
        {
        case 1:
            addToSTLContainer(container);
            break;
        case 2:
            viewFromSTLContainer(container);
            break;
        case 3:
            deleteFromSTLContainer(container);
            break;
        case 4:
            printSTLContainer(container);
            break;
        case 5:
            setIteratorToBegin(container);
            break;
        case 6:
            setIteratorToEnd(container);
            break;
        case 7:
            searchInSTLContainer(container);
            break;
        case 8:
            sortSTLContainer(container);
            break;
        case 9:
            saveSTLContainerToFile(container);
            break;
        case 10:
            loadSTLContainerFromFile(container);
            break;
        case 0:
            container.clear();
            cout << "Exiting STL menu..." << endl;
            break;
        }

        if (choice != 0 && choice != 3) { pauseConsole(); }
    } while (choice != 0);
}
