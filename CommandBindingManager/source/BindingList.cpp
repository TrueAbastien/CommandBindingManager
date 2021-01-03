#include "BindingList.h"

BindingList::BindingList(const QString& filePath)
	: bindings({ })
{
	if (!filePath.isEmpty())
		LoadAt(filePath);
}

void BindingList::LoadAt(const QString& filePath)
{
	QFile file(filePath);
	file.open(QFile::ReadWrite | QFile::Text);

	QString qline;
	QTextStream in(&file);
	while (!in.atEnd())
	{
		qline = in.readLine();

		if (qline.indexOf("#") == 0)
			continue;
		else
		{
			int idx = qline.indexOf(":"),
				size = qline.size();
			if (idx > 0 && size > idx + 1)
			{
				bindings.append(BindingList::Binding(qline.left(idx).toInt(), qline.mid(idx + 1)));
			}
		}
	}

	file.close();
}

void BindingList::SaveAt(const QString& filePath)
{
	QFile file(filePath);
	file.open(QFile::ReadWrite | QFile::Text);

	file.resize(0);
	QTextStream out(&file);
	for (Binding bind : bindings)
		out << QString::number(bind.key) << ":" << bind.command << "\n";

	file.close();
}

void BindingList::LoadFrom(const QString& configName)
{
	QFile file("ressources/configs/" + configName + ".txt");
	file.open(QFile::ReadWrite | QFile::Text);

	int idx;
	QString qline, suffix = "", prefix = "";
	QTextStream in(&file);
	while (!in.atEnd())
	{
		qline = in.readLine();

		if (qline.indexOf("#") == 0)
			continue;
		else
		{
			if ((idx = qline.indexOf("prefix=")) >= 0)
			{
				prefix = qline.mid(7);
			}
			else
			{
				if ((idx = qline.indexOf("suffix=")) >= 0)
				{
					suffix = qline.mid(7);
				}
				else
				{
					int size = qline.size();
					idx = qline.indexOf(":");

					if (idx > 0 && size > idx + 1)
					{
						bindings.append(BindingList::Binding(qline.left(idx).toInt(), prefix + qline.mid(idx + 1) + suffix));
					}
				}
			}
			
		}
	}

	file.close();
}

void BindingList::Add(int key, QString cmd)
{
	for (auto& ele : bindings)
		if (ele.key == key)
			if (ele.command == cmd)
				return;

	bindings.append(BindingList::Binding(key, cmd));
}

void BindingList::Fill(QListWidget* widget)
{
	for (Binding binding : bindings)
		widget->addItem(QString((char)(binding.key)) + " -> " + binding.command);
}

void BindingList::Reorder(QListWidget* widget)
{
	qSort(bindings.begin(), bindings.end(), BindingList::Binding::isLess);

	widget->clear();
	Fill(widget);
}
