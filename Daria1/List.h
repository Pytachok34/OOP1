#pragma once
#include <iostream>
#include <fstream>

using TInfo = int;

struct NODE //Это структура элемента списка. У него есть числовое значение info и указатель на следующий элемент next.
{
	TInfo info;
	NODE* next;
	NODE(TInfo info, NODE* ptr = nullptr) :info(info), next(ptr) {}
	~NODE()
	{
		next = nullptr;
	}
};

using  ptrNODE = NODE*;

class LIST //сам класс. Здесь есть несколько лишних функций, но самые нужные функции в конце.
{
private:
	ptrNODE head, tail;
	size_t size;
	void add_by_pointer(ptrNODE& ptr, TInfo elem)
	{
		ptrNODE p = new NODE(elem, ptr);
		ptr = p;
	}
	void del_by_pointer(ptrNODE& ptr)
	{
		ptrNODE p = ptr;
		ptr = p->next;
		delete p;
	}
	bool empty();
	void clear(ptrNODE ptr);
	void add_to_head(TInfo elem);
	void add_to_tail(TInfo elem);
	void add_after(ptrNODE ptr, TInfo elem);
	void del_from_head();
	void del_after(ptrNODE ptr);
public:
	LIST()
	{
		head = new NODE(0);
		tail = head;
		size = 0;
	}
	LIST(const LIST& l);
	~LIST();
	ptrNODE get_head()
	{
		return head;
	}
	TInfo get_first()
	{
		return head->next->info;
	}
	TInfo get_size()
	{
		return size;
	}
	
	void create_by_stack(std::ifstream& file);
	void create_by_queue(std::ifstream& file);
	void create_by_order(std::ifstream& file);
	void print();
	ptrNODE operator[](int i); 
	LIST operator+(const LIST& l);
	LIST operator-(const LIST& l);
	LIST& operator=(const LIST& obj);
	friend std::ostream& operator<<(std::ostream& out, const LIST& l); //Это дружественная функция
};

