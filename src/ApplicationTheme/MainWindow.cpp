#include "MainWindow.h"

#include "Application.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    ui.actionToggleThemeMode->setIcon(App->icon("wrench"));

    App->icon("wrench");

    connect(ui.actionToggleThemeMode, &QAction::triggered, App, &Application::toggleColorScheme);
    connect(ui.actionQuit, &QAction::triggered, App, &Application::quit);
}
