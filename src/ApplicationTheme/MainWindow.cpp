#include "MainWindow.h"

#include "Application.h"
#include "Toast.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    ui.toggleThemeAction->setIcon(App->icon("wrench"));
    connect(ui.toggleThemeAction, &QAction::triggered, this, &MainWindow::onThemeTriggered);
}

void MainWindow::onThemeTriggered() {
    App->toggleColorScheme();
    auto toast = new Toast("Application Theme changed", this);
    toast->show();
}
