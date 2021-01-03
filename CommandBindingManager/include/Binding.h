#pragma once
#include <QString>

class Binding
{
public:
	int key;
	QString command;

	Binding(int _key, QString _cmd)
		: key(_key), command(_cmd)
	{ }
	static bool isLess(const Binding& b1, const Binding& b2)
	{
		return b1.key < b2.key;
	}
};