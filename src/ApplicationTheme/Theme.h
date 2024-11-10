#pragma once

#include <QObject>

class Theme : public QObject {
    Q_OBJECT

public:
    enum class Mode {
        Light,
        Dark,
    };
    Q_ENUM(Mode)

signals:
    void modeChanged(Mode mode);

public:
    Theme(QObject* parent = nullptr);
    ~Theme() = default;

public:
    Mode mode() const;

public slots:
    void setMode(Mode mode);
    void toggleMode();

private slots:
    void setColorScheme(Qt::ColorScheme colorScheme);

private:
    Mode m_mode;
};
