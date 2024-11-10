#pragma once

#include <QMetaEnum>
#include <QObject>

class Settings : public QObject {
    Q_OBJECT

public:
    explicit Settings(QObject* parent = nullptr);
    ~Settings() = default;

public:
    QVariant load(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void store(const QString& key, const QVariant& value) const;

    template <typename EnumClass>
    QVariant load(EnumClass key, const QVariant& defaultValue = QVariant()) const;
    template <typename EnumClass>
    void store(EnumClass, const QVariant& value) const;
};

template <typename EnumClass>
inline QVariant Settings::load(EnumClass key, const QVariant& defaultValue) const {
    const auto meta = QMetaEnum::fromType<EnumClass>();
    const auto name = QString("%1/%2")
                          .arg(meta.name())
                          .arg(meta.valueToKey((int)key));
    return load(name, defaultValue);
}

template <typename EnumClass>
inline void Settings::store(EnumClass key, const QVariant& value) const {
    const auto meta = QMetaEnum::fromType<EnumClass>();
    const auto name = QString("%1/%2")
                          .arg(meta.name())
                          .arg(meta.valueToKey((int)key));
    store(name, value);
}
