#include "MainWindow.h"

#include "Application.h"
#include "Toast.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    ui.actionToggleThemeMode->setIcon(App->icon("wrench"));

    connect(ui.actionToggleThemeMode, &QAction::triggered, this, &MainWindow::onThemeTriggered);
    connect(ui.actionQuit, &QAction::triggered, App, &Application::quit);
}

void MainWindow::onThemeTriggered() {
    App->toggleThemeMode();
    auto toast = new Toast("Application Theme changed", this);
    toast->show();
}
