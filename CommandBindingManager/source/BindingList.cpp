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
	bindings.clear();

	int idx, size;
	QString qline;
	QTextStream in(&file);
	while (!in.atEnd())
	{
		qline = in.readLine();
		if ((idx = qline.indexOf("#")) >= 0)
			qline = qline.left(idx);

		idx = qline.indexOf(":");
		size = qline.size();
		if (idx > 0 && size > idx + 1)
		{
			bindings.append(Binding(qline.left(idx).toInt(), qline.mid(idx + 1)));
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

QString BindingList::MakeSave(const QString& fileName)
{
	SaveAt("ressources/saves/" + fileName + ".txt");
	return "ressources/saves/" + fileName + ".txt";
}

void BindingList::LoadSave(const QString& fileName)
{
	LoadAt("ressources/saves/" + fileName + ".txt");
}

void BindingList::LoadConfig(const ConfigFile& file)
{
	if (file.amount() <= 0)
		return;

	bindings.clear();
	Binding current = file.commands()[0];
	QString cmd = current.command, value;
	int idx, idx2, dist;

	QStringList models = { };
	//for (int ii = 0; ii < file.models().size();)
	//{
	//	if ((idx = cmd.indexOf("{")) >= 0)
	//	{
	//		if ((idx2 = cmd.indexOf("}")) >= 0)
	//		{
	//			if ((dist = idx - idx2) > 1)
	//			{
	//				int modelIndex = cmd.mid(idx + 1, dist - 1).toInt();
	//				value = (modelIndex == 0) ? QString::number(current.key)
	//					: (modelIndex > models.size() ? "" : models[modelIndex - 1]);

	//				cmd.remove(idx, dist + 1);
	//				continue;
	//			}
	//		}
	//	}
	//	//
	//}

	for (int ii = 0; ii < file.amount();)
	{
		if ((idx = cmd.indexOf("{")) >= 0)
		{
			if ((idx2 = cmd.indexOf("}")) >= 0)
			{
				if ((dist = idx - idx2) > 1)
				{
					int modelIndex = cmd.mid(idx + 1, dist - 1).toInt();
					value = (modelIndex == 0) ? QString::number(current.key)
						: (modelIndex > models.size() ? "" : models[modelIndex - 1]);
					
					cmd.remove(idx, dist + 1);
					continue;
				}
			}
		}
		bindings.append(Binding(current.key, cmd));

		if (++ii < file.amount())
		{
			current = file.commands()[ii];
			cmd = current.command;
		}
	}
}

void BindingList::Add(int key, QString cmd)
{
	for (auto& ele : bindings)
		if (ele.key == key)
			if (ele.command == cmd)
				return;

	bindings.append(Binding(key, cmd));
}

void BindingList::Edit(int index, int key, QString cmd)
{
	if (index >= 0 && index < amount())
	{
		bindings[index].key = key;
		bindings[index].command = cmd;
	}
}

void BindingList::Fill(QTableWidget* widget)
{
	for (Binding binding : bindings)
	{
		widget->insertRow(widget->rowCount());
		widget->setItem(widget->rowCount() - 1, 0, new QTableWidgetItem(QString((char)(binding.key))));
		widget->setItem(widget->rowCount() - 1, 1, new QTableWidgetItem(binding.command));
	}
}

void BindingList::Reorder(QTableWidget* widget)
{
	qSort(bindings.begin(), bindings.end(), Binding::isLess);

	widget->clear();
	Fill(widget);
}
