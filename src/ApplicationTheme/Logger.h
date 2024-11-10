#pragma once

#include <QDebug>
#include <QObject>

class Logger {
    Q_GADGET

public:
    enum class Type {
        Info,
        Warning,
        Debug,
    };
    Q_ENUM(Type)

private:
    explicit Logger(Type type, QObject* sender = nullptr);

public:
    ~Logger() = default;

public:
    static Logger info(QObject* sender = nullptr);
    static Logger warning(QObject* sender = nullptr);
    static Logger debug(QObject* sender = nullptr);

public:
    template <typename T>
    Logger& operator<<(const T& message);

private:
    QDebug m_logger;
};

template <typename T>
inline Logger& Logger::operator<<(const T& message) {
    m_logger << message;
    return *this;
}
