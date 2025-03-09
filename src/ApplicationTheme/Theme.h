#pragma once

#include <QHash>
#include <QIcon>
#include <QObject>
#include <QSet>

class IconEngine;

class Theme : public QObject {
    Q_OBJECT

public:
    explicit Theme(QObject* parent = nullptr);
    ~Theme() = default;

public:
    QIcon icon(const QString& name);
    const QByteArray iconContent(const QString& name) const;
    void update();

private slots:
    void updateIconEngines();

private:
    QSet<IconEngine*> m_iconEngines;
    QHash<QString, QByteArray> m_iconContentMap;
};
