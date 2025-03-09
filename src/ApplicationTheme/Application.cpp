#include "Application.h"

#include <QPalette>

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv) {
}

void Application::toggleThemeMode() {
    m_theme.toggleMode();
}

QIcon Application::icon(const QString& name, const QColor& color) {
    if (!color.isValid()) {
        return m_theme.icon(name, palette().color(QPalette::Text));
    }

    return m_theme.icon(name, color);
}
