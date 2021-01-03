#pragma once
#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QListWidget>
#include <QTextStream>
#include <QtAlgorithms>

class BindingList : public QObject
{
	Q_OBJECT

public:
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

public:
	BindingList(const QString& filePath = "");
	void LoadAt(const QString& filePath);
	void SaveAt(const QString& filePath);
	void LoadFrom(const QString& configName);

	int amount() const { return bindings.size(); }
	void Add(int key, QString cmd);

	void Fill(QListWidget* widget);
	void Reorder(QListWidget* widget);

private:
	QList<Binding> bindings;
};