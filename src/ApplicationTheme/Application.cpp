#include "Application.h"

#include <QPalette>
#include <QStyleHints>

#include "Logger.h"

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv) {
}

QIcon Application::icon(const QString& name) {
    return m_theme.icon(name);
}

Qt::ColorScheme Application::colorScheme() const {
    return styleHints()->colorScheme();
}

void Application::setColorScheme(Qt::ColorScheme scheme) {
    styleHints()->setColorScheme(scheme);
    Logger::info(this) << "changed color scheme:" << scheme;
    m_theme.update();
}

void Application::toggleColorScheme() {
    const auto scheme = colorScheme() == Qt::ColorScheme::Light ? Qt::ColorScheme::Dark : Qt::ColorScheme::Light;
    setColorScheme(scheme);
}
