#pragma once
#include "../Lab3/Human.h"
#include "../Lab3/Teacher.h"
#include "../Lab3/CommissionMember.h"
#include "../Lab3/TeacherCommissionMember.h"
#include "../Lab4/Queue.cpp"
#include "../Lab4/Input.h"
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <limits>

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
void mainMenu(Queue<T*>& queue);

void run();
