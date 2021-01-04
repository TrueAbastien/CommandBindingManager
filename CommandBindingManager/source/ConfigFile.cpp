#include "ConfigFile.h"

ConfigFile::ConfigFile(const QString& configName)
	: QFile("ressources/configs/" + configName + ".txt"), _rawCommands({ })
{
	this->open(QFile::ReadWrite | QFile::Text);
	Load();
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
		if ((idx = qline.indexOf("#")) >= 0)
		{
			qline = qline.left(idx);
			qline.remove(QRegExp("(\\s+)(?!.+)"));
		}

		if ((idx = qline.indexOf("prefix=")) >= 0)
		{
			_prefix = qline.mid(7);
		}
		else if((idx = qline.indexOf("suffix=")) >= 0)
		{
			_suffix = qline.mid(7);
		}
		else if ((idx = qline.indexOf("model=")) >= 0)
		{
			_models.append(qline.mid(idx + 6));
		}
		else
		{
			size = qline.size();
			idx = qline.indexOf(":");

			if (idx > 0 && size > idx + 1)
			{
				QStringList
					keys = qline.left(idx).split(","),
					cmds = qline.mid(idx + 1).split(",");

				for (int idx = 0; idx < keys.size();)
				{
					if ((size = keys[idx].indexOf("-")) > 0)
					{
						int first = keys[idx].left(size).toInt(),
							last = keys[idx].mid(size + 1).toInt();
						for (int ii = first; ii <= last; ++ii)
							keys.append(QString::number(ii));
						keys.removeAt(idx);
					}
					else idx++;
				}
					
				foreach(QString cmd, cmds)
				{
					foreach(QString key, keys)
					{
						_rawCommands.append(Binding(key.toInt(), cmd));
					}
				}
			}
		}
	}
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
