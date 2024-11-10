#pragma once

#include <QApplication>

#include "Theme.h"

class Application;
#if defined(App)
    #undef App
#endif
#define App (static_cast<Application*>(QCoreApplication::instance()))

class Application : public QApplication {
    Q_OBJECT

public:
    explicit Application(int& argc, char** argv);
    ~Application() = default;

public slots:
    void toggleThemeMode();

private:
    Theme m_theme;
};
