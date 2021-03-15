/*
Project: Map Implementation (Doubly Linked List)
Author: Rudy Orre
School: El Camino College
Professor: Russell Solomon
Date: 03-02-2020
*/

#ifndef MAP_CPP
#define MAP_CPP
#include "Map.h"
#include <iostream>
#include <iomanip>
using namespace std;

Map::Map()
{
	head = nullptr;
}

Map::Map(const Map& rhs)
{
	Node* current = rhs.head;

	do
	{
		insert(current->key, current->value);
		current = current->next;
	} while (current != rhs.head);
}

Map::~Map()
{
	if (head != nullptr)
	{
		Node* garbage = head;
		Node* current;

		do
		{
			current = garbage->next;
			delete garbage;
			garbage = current;

		} while (garbage != head);

		head = nullptr;
	}
}

const Map& Map::operator=(const Map& rhs)
{
	while (!empty()) // clears this Map if it contains anything
	{
		KeyType key;
		ValueType value;
		get(0, key, value);
		erase(key);
	}

	Node* current = rhs.head;

	do
	{
		insert(current->key, current->value);
		current = current->next;
	} while (current != rhs.head);

	return *this;
}

bool Map::empty() const
{
	if (head == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Map::size() const
{
	int count = 0;
	Node* current = head; 

	do
	{
		count++;
		current = current->next;
	} while (current != head);

	return count;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (contains(key))
	{
		return false;
	}

	Node* current = new Node(key, value);

	if (head == nullptr)
	{
		head = current;
		Node* tail = current;

		head->set(tail, tail);
		tail->set(head, head);
	}
	else
	{
		Node* tail = head->prev;
		tail->next = current;
		head->prev = current;
		current->set(head, tail);

		tail = current;
	}

	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	if (!contains(key))
	{
		return false;
	}

	Node* current = head;

	while (current->next != head)
	{
		if (current->key == key)
		{
			current->value = value;
			break;
		}
		current = current->next;
	}

	return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (contains(key))
	{
		update(key, value);
	}
	else
	{
		insert(key, value);
	}

	return true;
}

bool Map::erase(const KeyType& key)
{
	if (contains(key))
	{
		Node* current = head;

		do
		{
			if (current->key == key)
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;

				if (current == head)
				{
					head = current->next;

					if (current->next == current)
					{
						head = nullptr;
					}
				}
			}
			current = current->next;
		}
		while (head != nullptr && current != head);

		return true;
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	if (head == nullptr)
	{
		return false;
	}

	Node* current = head;

	if (current->key == key)
	{
		return true;
	}
	current = current->next;

	while (current != head)
	{
		if (current->key == key)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	if (!contains(key))
	{
		return false;
	}

	Node* current = head;

	do
	{
		if (current->key == key)
		{
			value = current->value;
		}
		current = current->next;
	}
	while (current != head);

	return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i >= size())
	{
		return false;
	}

	int index = 0;
	Node* current = head;

	for (index = 0; index < i; index++)
	{
		current = current->next;
	}

	key = current->key;
	value = current->value;

	return true;
}

void Map::swap(Map& other)
{
	Node* temp = head;
	head = other.head;
	other.head = temp;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
	bool ret = true;
	result = m1;

	for (int i = 0; i < m2.size(); i++)
	{
		KeyType key;
		ValueType value;
		m2.get(i, key, value);

		if (!result.contains(key))
		{
			result.insert(key, value);
		}
		else
		{
			ValueType resultValue;
			result.get(key, resultValue);

			if (resultValue != value)
			{
				ret = false;
				result.erase(key);
			}
		}
	}
	
	return ret;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	result = m1;

	for (int i = 0; i < m2.size(); i++)
	{
		KeyType key;
		ValueType value;
		m2.get(i, key, value);

		if (result.contains(key))
		{
			result.erase(key);
		}
	}
}

void print(const Map& m)
{
	cout << endl << left << setw(10) << "Key:" << left << setw(10) << "Value:" << endl << endl;

	for (int i = 0; i < m.size(); i++)
	{
		KeyType key;
		ValueType value;
		m.get(i, key, value);
		cout << left << fixed << setprecision(2) << setw(10) << key;
		cout << left << fixed << setprecision(2) << setw(10) << value << endl;
	}
}

int Convert_Key(string key)
{
	// nothing to hash
	return 0;
}

int Convert_Key(double key)
{
	// nothing to hash
	return 0;
}

#endif /*MAP_CPP*/