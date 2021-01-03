#include "Application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent), bindings(__cmdBindingPath)
{
    ui.setupUi(this);

    bindings.Fill(ui.DisplayWidget);
}

void Application::Cleanup(int errCode)
{
    bindings.SaveAt(__cmdBindingPath);
}
