#include "MainWindow.h"

#include "Application.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    ui.actionToggleThemeMode->setIcon(App->icon("wrench", QColor(Qt::yellow)));

    connect(ui.actionToggleThemeMode, &QAction::triggered, App, &Application::toggleThemeMode);
    connect(ui.actionQuit, &QAction::triggered, App, &Application::quit);
}
