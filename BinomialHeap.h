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
    Node* head; // ��������� �� ������ (������ ����) ������������ ����

    void link(Node* y, Node* z); // ��������� ��� ������
    Node* mergeTrees(Node* h1, Node* h2); // ���������� ��� ������

public:
    BinomialHeap() : head(nullptr) {} // �����������, ���������������� ������������ ����
    void Enqueue(int key, int priority); // ��������� ������� � ����
    Node* Dequeue(); // ������� � ���������� ������� � ���������� �����������
    int Peek(); // ���������� ������� � ���������� ����������� ��� ��������
    void DecreasePriority(int key, int newPriority); // ��������� ��������� ��������
    void Merge(BinomialHeap& other); // ���������� ��� ������������ ����
    void Print(); // �������� ���������� ����
};