#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Application.h"

#include "BindingList.h"
#include <QStandardPaths>


class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = Q_NULLPTR);
    void Cleanup(int errCode);

    void EditBinding(int index, int key, QString command);
    void AddBinding(int key, QString command);

private:
    Ui::ApplicationClass ui;

    QString __cmdBindingPath =
        QStandardPaths::locate(QStandardPaths::StandardLocation::HomeLocation,
            "", QStandardPaths::LocateOption::LocateDirectory) + "AppData/Roaming/SCP Secret Laboratory/cmdbinding.txt";
    BindingList bindings;

    void LimitIndex();

private slots:
    //
};
