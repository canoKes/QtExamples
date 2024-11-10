#include "Theme.h"

#include <QStyleHints>

#include "Application.h"
#include "Logger.h"

Theme::Theme(QObject* parent)
    : QObject(parent)
    , m_mode(Mode::Light) {
    const auto styleHints = App->styleHints();
    connect(styleHints, &QStyleHints::colorSchemeChanged, this, &Theme::setColorScheme);
    setColorScheme(styleHints->colorScheme());
}

Theme::Mode Theme::mode() const {
    return m_mode;
}

void Theme::setMode(Mode mode) {
    const auto scheme = mode == Mode::Dark
        ? Qt::ColorScheme::Dark
        : Qt::ColorScheme::Light;

    App->styleHints()->setColorScheme(scheme);
}

void Theme::toggleMode() {
    setMode(m_mode == Mode::Light ? Mode::Dark : Mode::Light);
}

void Theme::setColorScheme(Qt::ColorScheme colorScheme) {
    const auto mode = colorScheme == Qt::ColorScheme::Dark
        ? Theme::Mode::Dark
        : Theme::Mode::Light;

    if (m_mode == mode) {
        return;
    }

    m_mode = mode;

    Logger::info() << "theme mode changed:" << mode;
    emit modeChanged(m_mode);
}
