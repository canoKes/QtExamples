#pragma once

#include <QHash>
#include <QIcon>
#include <QObject>
#include <QSet>

class IconEngine;

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
    explicit Theme(QObject* parent = nullptr);
    ~Theme() = default;

public:
    Mode mode() const;
    QIcon icon(const QString& name, const QColor& color = QColor());
    const QByteArray iconContent(const QString& name) const;

public slots:
    void setMode(Mode mode);
    void toggleMode();

private slots:
    void setColorScheme(Qt::ColorScheme colorScheme);

private:
    void updateIconEngines();

private:
    Mode m_mode;
    QSet<IconEngine*> m_iconEngines;
    QHash<QString, QByteArray> m_iconContentMap;
};
