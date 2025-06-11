#include "BinomialHeap.h"
#include <iostream>
#include <chrono>


void BinomialHeap::link(Node* y, Node* z)
{
	y->next = z->child; // Устанавливаем указатель next узла y на текущий дочерний узел z
	z->child = y; // Делаем y дочерним узлом z
	z->priority += 1; // Увеличиваем порядок дерева z
}

Node* BinomialHeap::mergeTrees(Node* h1, Node* h2)
{

	if (!h1) return h2;
	if (!h2) return h1;

	if (h1->priority < h2->priority)
	{
		h1->next = h2; // Устанавливаем h1 как следующий узел для h2
		return h1; // Возвращаем h1 как корень объединенного дерева
	}
	else
	{
		h2->next = h1; // Устанавливаем h2 как следующий узел для h1
		return h2; // Возвращаем h2 как корень объединенного дерева
	};
}

void BinomialHeap::Enqueue(int key, int priority)
{
	Node* newNode = new Node(key, priority); // Создаем новый узел с заданным ключом и приоритетом
	head = mergeTrees(head, newNode); // Объединяем новый узел с текущей кучей
}

Node* BinomialHeap::Dequeue()
{
	if (!head)
	{
		return nullptr; // Если куча пуста, возвращаем nullptr
	}

	Node* minNode = head; // Инициализируем minNode как голову кучи
	Node* prevMin = nullptr; // Указатель на предыдущий узел minNode
	Node* curr = head; // Указатель для итерации по куче
	Node* prev = nullptr; // Указатель на предыдущий узел curr

	// Поиск узла с наименьшим приоритетом
	while (curr)
	{
		if (curr->priority < minNode->priority)
		{
			minNode = curr; // Обновляем minNode
			prevMin = prev; // Запоминаем предыдущий узел
		}
		prev = curr; // Сохраняем текущий узел как предыдущий
		curr = curr->next; // Переходим к следующему узлу
	}
	
	// Удаление minNode из кучи
	if (prevMin)
	{
		prevMin->next = minNode->next; // Если minNode не голова, обновляем указатель
	}
	else
	{
		head = minNode->next; // Если minNode - голова, обновляем голову
	}

	// Обработка дочерних узлов minNode
	Node* child = minNode->child; // Получаем дочерние узлы
	Node* temp = nullptr; // Временный указатель для реверсирования дочерних узлов

	// Реверсирование дочерних узлов
	while (child)
	{
		Node* nextChild = child->next; // Сохраняем следующий дочерний узел
		child->next = temp; // Реверсируем указатель
		temp = child; // Обновляем временный указатель
		child = nextChild; // Переходим к следующему дочернему узлу
	}

	// Объединяем оставшиеся узлы с реверсированными дочерними узлами
	head = mergeTrees(head, temp);
	return minNode; // Возвращаем узел с наименьшим приоритетом
}

int BinomialHeap::Peek()
{
	if (!head)
	{
		return std::numeric_limits<int>::min(); // Если куча пуста, возвращаем минимальное значение int
	}
	Node* minNode = head; // Инициализируем minNode как голову кучи
	// Проходим по всем узлам в куче
	while (minNode->next) {
		// Если следующий узел имеет меньший приоритет
		if (minNode->next->priority < minNode->priority)
		{
			minNode = minNode->next; // Обновляем minNode
		}
	}
	return minNode->key; // Возвращаем ключ узла с наименьшим приоритетом
}

void BinomialHeap::DecreasePriority(int key, int newPriority)
{

}

void BinomialHeap::Merge(BinomialHeap& other)
{
	head = mergeTrees(head, other.head); // Объединяем текущую кучу с другой
	other.head = nullptr; // Обнуляем голову другой кучи
}

void BinomialHeap::Print()
{
	Node* curr = head; // Инициализируем указатель на голову кучи
	// Проходим по всем узлам в куче
	while (curr) {
		// Печатаем ключ и приоритет
		std::cout << "Key: " << curr->key << ", Priority: " << curr->priority << std::endl;
		curr = curr->next; // Переходим к следующему узлу
	}
}

void performanceTest(int size) {
	BinomialHeap heap;
	auto start = std::chrono::high_resolution_clock::now();

	// Добавление элементов в биномиальную кучу
	for (int i = 0; i < size; ++i) {
		heap.Enqueue(i, rand() % 100); // Приоритет случайный
	}

	// Удаление элементов из биномиальной кучи
	for (int i = 0; i < size; ++i) {
		heap.Dequeue();
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Razmer: " << size << ", Vremya: " << duration.count() << " sekundy" << std::endl;
}

int main() {
	srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

	// Проведение тестов производительности для различных размеров
	for (int size = 1000; size <= 10000; size += 1000) {
		performanceTest(size);
	}

	return 0;
}


