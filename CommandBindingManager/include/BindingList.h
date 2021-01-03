#pragma once
#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QTableWidget>
#include <QtAlgorithms>
#include <QFileDialog>
#include "ConfigFile.h"

class BindingList : public QObject
{
	Q_OBJECT

public:
	BindingList(const QString& filePath = "");
	void LoadAt(const QString& filePath);
	void SaveAt(const QString& filePath);

	QString MakeSave(const QString& fileName);
	void LoadSave(const QString& fileName);
	void LoadConfig(const ConfigFile& file);

	int amount() const { return bindings.size(); }
	void Add(int key, QString cmd);
	void Edit(int index, int key, QString cmd);

	void Fill(QTableWidget* widget);
	void Reorder(QTableWidget* widget);

private:
	QList<Binding> bindings;

	bool __replace(QString& target, const QStringList& pool) const;
};