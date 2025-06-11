#include "BinomialHeap.h"
#include <iostream>
#include <chrono>


void BinomialHeap::link(Node* y, Node* z)
{
	y->next = z->child; // ������������� ��������� next ���� y �� ������� �������� ���� z
	z->child = y; // ������ y �������� ����� z
	z->priority += 1; // ����������� ������� ������ z
}

Node* BinomialHeap::mergeTrees(Node* h1, Node* h2)
{

	if (!h1) return h2;
	if (!h2) return h1;

	if (h1->priority < h2->priority)
	{
		h1->next = h2; // ������������� h1 ��� ��������� ���� ��� h2
		return h1; // ���������� h1 ��� ������ ������������� ������
	}
	else
	{
		h2->next = h1; // ������������� h2 ��� ��������� ���� ��� h1
		return h2; // ���������� h2 ��� ������ ������������� ������
	};
}

void BinomialHeap::Enqueue(int key, int priority)
{
	Node* newNode = new Node(key, priority); // ������� ����� ���� � �������� ������ � �����������
	head = mergeTrees(head, newNode); // ���������� ����� ���� � ������� �����
}

Node* BinomialHeap::Dequeue()
{
	if (!head)
	{
		return nullptr; // ���� ���� �����, ���������� nullptr
	}

	Node* minNode = head; // �������������� minNode ��� ������ ����
	Node* prevMin = nullptr; // ��������� �� ���������� ���� minNode
	Node* curr = head; // ��������� ��� �������� �� ����
	Node* prev = nullptr; // ��������� �� ���������� ���� curr

	// ����� ���� � ���������� �����������
	while (curr)
	{
		if (curr->priority < minNode->priority)
		{
			minNode = curr; // ��������� minNode
			prevMin = prev; // ���������� ���������� ����
		}
		prev = curr; // ��������� ������� ���� ��� ����������
		curr = curr->next; // ��������� � ���������� ����
	}
	
	// �������� minNode �� ����
	if (prevMin)
	{
		prevMin->next = minNode->next; // ���� minNode �� ������, ��������� ���������
	}
	else
	{
		head = minNode->next; // ���� minNode - ������, ��������� ������
	}

	// ��������� �������� ����� minNode
	Node* child = minNode->child; // �������� �������� ����
	Node* temp = nullptr; // ��������� ��������� ��� �������������� �������� �����

	// �������������� �������� �����
	while (child)
	{
		Node* nextChild = child->next; // ��������� ��������� �������� ����
		child->next = temp; // ����������� ���������
		temp = child; // ��������� ��������� ���������
		child = nextChild; // ��������� � ���������� ��������� ����
	}

	// ���������� ���������� ���� � ���������������� ��������� ������
	head = mergeTrees(head, temp);
	return minNode; // ���������� ���� � ���������� �����������
}

int BinomialHeap::Peek()
{
	if (!head)
	{
		return std::numeric_limits<int>::min(); // ���� ���� �����, ���������� ����������� �������� int
	}
	Node* minNode = head; // �������������� minNode ��� ������ ����
	// �������� �� ���� ����� � ����
	while (minNode->next) {
		// ���� ��������� ���� ����� ������� ���������
		if (minNode->next->priority < minNode->priority)
		{
			minNode = minNode->next; // ��������� minNode
		}
	}
	return minNode->key; // ���������� ���� ���� � ���������� �����������
}

void BinomialHeap::DecreasePriority(int key, int newPriority)
{

}

void BinomialHeap::Merge(BinomialHeap& other)
{
	head = mergeTrees(head, other.head); // ���������� ������� ���� � ������
	other.head = nullptr; // �������� ������ ������ ����
}

void BinomialHeap::Print()
{
	Node* curr = head; // �������������� ��������� �� ������ ����
	// �������� �� ���� ����� � ����
	while (curr) {
		// �������� ���� � ���������
		std::cout << "Key: " << curr->key << ", Priority: " << curr->priority << std::endl;
		curr = curr->next; // ��������� � ���������� ����
	}
}

void performanceTest(int size) {
	BinomialHeap heap;
	auto start = std::chrono::high_resolution_clock::now();

	// ���������� ��������� � ������������ ����
	for (int i = 0; i < size; ++i) {
		heap.Enqueue(i, rand() % 100); // ��������� ���������
	}

	// �������� ��������� �� ������������ ����
	for (int i = 0; i < size; ++i) {
		heap.Dequeue();
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Razmer: " << size << ", Vremya: " << duration.count() << " sekundy" << std::endl;
}

int main() {
	srand(static_cast<unsigned int>(time(0))); // ������������� ���������� ��������� �����

	// ���������� ������ ������������������ ��� ��������� ��������
	for (int size = 1000; size <= 10000; size += 1000) {
		performanceTest(size);
	}

	return 0;
}


