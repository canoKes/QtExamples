#include "Application.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv) {
}

void Application::toggleThemeMode() {
    m_theme.toggleMode();
}
