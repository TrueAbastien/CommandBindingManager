#include "Application.h"

Application::Application(QWidget *parent)
    : QMainWindow(parent), bindings(__cmdBindingPath)
{
    ui.setupUi(this);

    // Bindings Loading
    bindings.Fill(ui.DisplayWidget);
    LimitIndex();

    // Load & Save Connection
    UpdateConfigList();
    UpdateCommandList();
    connect(ui.LoadConfigBtn, &QPushButton::pressed, this, &Application::LoadConfig);
    connect(ui.ChangeSaveBtn, &QPushButton::pressed, this, &Application::LoadSave);

    // Edit & Add Connection
    //
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

void Application::UpdateConfigList()
{
    ui.ConfigCB->clear();
    ui.ConfigCB->addItems(ConfigFile::List());
}

void Application::UpdateCommandList()
{
    ui.CommandCB->clear();
    ui.CommandCB->addItems(bindings.commandList());
}

void Application::LoadConfig()
{
    bindings.LoadConfig(ConfigFile(ui.ConfigCB->currentText()));
    bindings.Fill(ui.DisplayWidget);
    UpdateCommandList();
}

void Application::LoadSave()
{
    QString savePath = QFileDialog::getSaveFileName(this, tr("Save File"), "ressources/saves", tr("Text File (*.txt)"));
    if (!savePath.isEmpty())
    {
        bindings.SaveAt(savePath);

        QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "ressources/saves", tr("Text File (*.txt)"));
        if (!filePath.isEmpty())
        {
            bindings.LoadAt(filePath);

            bindings.Fill(ui.DisplayWidget);
            UpdateCommandList();
        }
    }
    
}
