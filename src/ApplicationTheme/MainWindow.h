#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onThemeTriggered();

private:
    Ui::MainWindowClass ui;
};
