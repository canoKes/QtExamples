#include "Settings.h"

Settings::Settings(QObject* parent)
    : QObject(parent) {
}

QVariant Settings::load(const QString& key, const QVariant& defaultValue) const {
    return QVariant();
}

void Settings::store(const QString& key, const QVariant& value) const {
}
