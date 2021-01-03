#include "Application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent), bindings(__cmdBindingPath)
{
    ui.setupUi(this);

    // Bindings Loading
    bindings.Fill(ui.DisplayWidget);
    LimitIndex();
}

void Application::Cleanup(int errCode)
{
    bindings.SaveAt(__cmdBindingPath);
}

void Application::EditBinding(int index, int key, QString command)
{
    bindings.Edit(index, key, command);
}

void Application::AddBinding(int key, QString command)
{
    bindings.Add(key, command);
    LimitIndex();
}

void Application::LimitIndex()
{
    int max = bindings.amount() - 1;
    ui.IndexerEdit->setMaximum(max > 0 ? max : 0);
}
