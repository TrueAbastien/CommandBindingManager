#pragma once
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include "Binding.h"

class ConfigFile : public QFile
{
public:
	ConfigFile(const QString& configName);
	virtual ~ConfigFile();
	void Load();

	static ConfigFile Import(const QString& configName);
	static QStringList List();

	QStringList models() const;
	QList<Binding> commands() const;
	int amount() const;
	QString prefix() const;
	QString suffix() const;

private:
	QList<Binding> _rawCommands;
	QStringList _models;
	QString _prefix, _suffix;
};