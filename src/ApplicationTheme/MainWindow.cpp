#include "MainWindow.h"

#include "Application.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    ui.toggleColorSchemeAction->setIcon(App->icon("wrench"));
    connect(ui.toggleColorSchemeAction, &QAction::triggered, App, &Application::toggleColorScheme);
}
