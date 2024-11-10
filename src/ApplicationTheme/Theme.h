#pragma once

#include <QHash>
#include <QIcon>
#include <QObject>

class IconEngine;

class Theme : public QObject {
    Q_OBJECT

public:
    enum class Mode {
        Light,
        Dark,
    };
    Q_ENUM(Mode)

    enum class Role {
        ImageColor
    };
    Q_ENUM(Role)

signals:
    void modeChanged(Mode mode);

public:
    Theme(QObject* parent = nullptr);
    ~Theme() = default;

public:
    Mode mode() const;
    QIcon icon(const QString& name, const QColor& color = QColor()) const;

public slots:
    void setMode(Mode mode);
    void toggleMode();

private slots:
    void setColorScheme(Qt::ColorScheme colorScheme);

private:
    mutable QHash<QString, IconEngine*> m_iconEngineMap;
    Mode m_mode;
};
