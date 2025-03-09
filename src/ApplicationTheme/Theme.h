#pragma once

#include <QHash>
#include <QIcon>
#include <QObject>
#include <QPalette>
#include <QSet>

class IconEngine;

class Theme : public QObject {
    Q_OBJECT

public:
    explicit Theme(QObject* parent = nullptr);
    ~Theme() = default;

public:
    QIcon icon(const QString& name);
    const QByteArray iconContent(const QString& name, QPalette::ColorRole role = QPalette::Text, QPalette::ColorGroup group = QPalette::Normal) const;

private:
    QSet<IconEngine*> m_iconEngines;
    QHash<QString, QByteArray> m_iconContentMap;
};
