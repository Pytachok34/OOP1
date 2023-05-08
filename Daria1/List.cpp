#include "List.h"
#include <functional>

LIST::LIST(const LIST& obj)
{
	head = new NODE(0);
	tail = head;
	size = obj.size;
	ptrNODE p = head, p2 = obj.head->next;
	while (p2)
	{
		add_after(p, p2->info);
		p = p->next, p2 = p2->next;
	}
}

LIST::~LIST()
{
	while (!empty())
	{
		del_from_head();
	}

	delete head;
}

bool LIST::empty()
{
	return !head->next;
}

void LIST::add_to_head(TInfo elem)
{
	add_by_pointer(head->next, elem);
	if (head == tail)
		tail = tail->next;
	++size;
}

void LIST::add_to_tail(TInfo elem)
{
	add_by_pointer(tail->next, elem);
	tail = tail->next;
}

void LIST::add_after(ptrNODE ptr, TInfo elem)
{
	if (ptr)
	{
		add_by_pointer(ptr->next, elem);
		if (ptr == tail)
			tail = tail->next;
	}
}

void LIST::del_from_head()
{
	if (head->next)
	{
		del_by_pointer(head->next);
		if (!head->next)
			tail = head;
		--size;
	}
}

void LIST::del_after(ptrNODE ptr)
{
	if (ptr && ptr->next)
	{
		if (ptr->next == tail)
			tail = ptr;
		del_by_pointer(ptr->next);
		if (empty())
			tail = head;
		--size;
	}
}
void LIST::clear(ptrNODE ptr)
{
	while (!empty())
		del_from_head();
}

void LIST::create_by_stack(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_head(elem);
}

void LIST::create_by_queue(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_tail(elem);
}

void LIST::create_by_order(std::ifstream& file)
{
	TInfo elem;
	ptrNODE p = nullptr;
	auto find_place = [this](TInfo elem) ->ptrNODE
	{
		ptrNODE result = head;
		while (result->next && result->next->info < elem)
			result = result->next;
		return result;
	};
	while (file >> elem)
	{
		p = find_place(elem);
		add_after(p, elem);
	}
}

void LIST::print()
{
	ptrNODE p = head->next;
	if (empty())
		std::cout << "no elem\n";
	while (p)
	{
		std::cout << p->info << ' ';
		p = p->next;
	}
}

ptrNODE LIST::operator[](int index)
{
	ptrNODE tmp=head->next;
	int i = 0;
	while (i < index && tmp)
	{
		tmp = tmp->next;
		++i;
	}
	return tmp;
}

LIST LIST::operator+(const LIST& l)
{
	LIST tmp = l;
	ptrNODE p1 = head->next, p2 = tmp.get_head()->next;
	while (p1 && p2)
	{
		p2->info += p1->info;
		p1 = p1->next, p2 = p2->next;
	}
	if(p1)
		while (p1)
		{
			tmp.add_to_tail(p1->info);
			p1 = p1->next;
		}
	
	return tmp;
}
LIST LIST::operator-(const LIST& l)
{
	LIST tmp = *this;
	ptrNODE p1 = tmp.head->next, p2 = l.head->next;
	while (p1 && p2)
	{
		p1->info =p1->info- p2->info;
		p1 = p1->next, p2 = p2->next;
	}
	if (p2)
		while (p2)
		{
			tmp.add_to_tail(-p2->info);
			p2 = p2->next;
		}

	return tmp;
}

LIST& LIST::operator=(const LIST& obj)
{
	if (this == &obj)
		return *this;
	else
	{
		while (!empty())
		{
			del_from_head();
		}
		size = obj.size;
		ptrNODE p = head, p2 = obj.head->next;
		while (p2)
		{
			add_after(p, p2->info);
			p = p->next,p2=p2->next;
		}
		return *this;
	}
}

std::ostream& operator<<(std::ostream& out, const LIST& l)
{
	ptrNODE p = l.head->next;
	while (p)
	{
		out << p->info << ' ';
		p = p->next;
	}
	out << '\n';
	return out;
}
