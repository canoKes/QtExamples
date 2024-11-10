#include "Application.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv) {
}

void Application::toggleThemeMode() {
    m_theme.toggleMode();
}

QIcon Application::icon(const QString& name, const QColor& color) {
    return m_theme.icon(name, color);
}
