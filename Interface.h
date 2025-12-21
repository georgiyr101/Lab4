#pragma once
#include "../Lab3/Human.h"
#include "../Lab3/Teacher.h"
#include "../Lab3/CommissionMember.h"
#include "../Lab3/TeacherCommissionMember.h"
#include "../Lab4/Queue.cpp"
#include "../Lab4/Input.h"
#include "../Lab4/STLContainer.h"
#include "../Lab4/Algorithms.h"
#include "../Lab4/Exp_contr.h"
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <limits>
#include <map>

void clearConsole();

void pauseConsole();

int getChoice(int max);

template<typename T>
void addObject(Queue<T*>& queue);

template<typename T>
void deleteObject(Queue<T*>& queue);

template<typename T>
void editObject(Queue<T*>& queue);

template<typename T>
void peekObject(Queue<T*>& queue);

template<typename T>
void printQueue(Queue<T*>& queue);

template<typename T>
void clearQueue(Queue<T*>& queue);

struct SearchCriteria;

SearchCriteria inputSearchCriteria();

template<typename T>
bool matchesCriteria(T* obj, const SearchCriteria& criteria);

template<typename T>
void searchInQueue(Queue<T*>& queue);

template<typename T>
void sortQueueByField(Queue<T*>& queue);

template<typename T>
void saveToFile(Queue<T*>& queue);

template<typename T>
void loadFromFile(Queue<T*>& queue);

template<typename T>
void mainMenu(Queue<T*>& queue);

// STL Container functions
template<typename T>
void addToSTLContainer(STLContainer<T>& container);

template<typename T>
void viewFromSTLContainer(STLContainer<T>& container);

template<typename T>
void deleteFromSTLContainer(STLContainer<T>& container);

template<typename T>
void printSTLContainer(STLContainer<T>& container);

template<typename T>
void setIteratorToBegin(STLContainer<T>& container);

template<typename T>
void setIteratorToEnd(STLContainer<T>& container);

template<typename T>
void searchInSTLContainer(STLContainer<T>& container);

template<typename T>
void sortSTLContainer(STLContainer<T>& container);

template<typename T>
void saveSTLContainerToFile(STLContainer<T>& container);

template<typename T>
void loadSTLContainerFromFile(STLContainer<T>& container);

template<typename T>
void stlMenu(STLContainer<T>& container);

void run();
