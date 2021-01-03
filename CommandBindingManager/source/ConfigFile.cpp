#include "ConfigFile.h"

ConfigFile::ConfigFile(const QString& configName)
	: QFile("ressources/configs/" + configName + ".txt"), _rawCommands({ })
{
	this->open(QFile::ReadWrite | QFile::Text);
}

ConfigFile::~ConfigFile()
{
	this->close();
}

void ConfigFile::Load()
{
	int idx, size;
	QString qline;
	QTextStream in(this);
	while (!in.atEnd())
	{
		qline = in.readLine();
		if (qline.indexOf("#") >= 0)
			qline = qline.left(idx);

		if ((idx = qline.indexOf("prefix=")) >= 0)
		{
			_prefix = qline.mid(7);
		}
		else
		{
			if ((idx = qline.indexOf("suffix=")) >= 0)
			{
				_suffix = qline.mid(7);
			}
			else
			{
				if ((idx = qline.indexOf("model=")) >= 0)
				{
					_models.append(qline.mid(idx + 6));
				}
				else
				{
					size = qline.size();
					idx = qline.indexOf(":");

					if (idx > 0 && size > idx + 1)
					{
						_rawCommands.append(Binding(qline.left(idx).toInt(), qline.mid(idx + 1)));
					}
				}
			}
		}
	}
}

ConfigFile ConfigFile::Import(const QString& configName)
{
	return ConfigFile(configName);
}

QStringList ConfigFile::List()
{
	QDir dir("ressources/configs");
	QStringList files = dir.entryList(QStringList() << ".txt", QDir::Files);
	foreach(QString file, files)
		file.remove(".txt");
	return files;
}

QStringList ConfigFile::models() const
{
	return _models;
}

QList<Binding> ConfigFile::commands() const
{
	return _rawCommands;
}

int ConfigFile::amount() const
{
	return _rawCommands.size();
}

QString ConfigFile::prefix() const
{
	return _prefix;
}

QString ConfigFile::suffix() const
{
	return _suffix;
}
