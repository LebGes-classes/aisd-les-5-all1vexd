#pragma once
#include <list>
#include <string>
#include <vector>

class Node
{
public:
    int key;
    int priority;
    Node* next;
    Node* child;

    Node(int k, int p) : key(k), priority(p), next(nullptr), child(nullptr) {}

};

class BinomialHeap
{
private:
    Node* head; // Указатель на голову (первый узел) биномиальной кучи

    void link(Node* y, Node* z); // связывает два дерева
    Node* mergeTrees(Node* h1, Node* h2); // объединяет два деерва

public:
    BinomialHeap() : head(nullptr) {} // Конструктор, инициализирующий биномиальную кучу
    void Enqueue(int key, int priority); // Добавляет элемент в кучу
    Node* Dequeue(); // Удаляет и возвращает элемент с наименьшим приоритетом
    int Peek(); // Возвращает элемент с наименьшим приоритетом без удаления
    void DecreasePriority(int key, int newPriority); // Уменьшает приоритет элемента
    void Merge(BinomialHeap& other); // Объединяет две биномиальные кучи
    void Print(); // Печатает содержимое кучи
};