#include "Logger.h"

#include <QDateTime>
#include <QMetaEnum>

Logger::Logger(Type type, QObject* sender)
    : m_logger(qInfo().noquote()) {
    const auto date = QDateTime::currentDateTime().toUTC();
    const auto meta = QMetaEnum::fromType<Type>();
    const auto name = QString(meta.valueToKey((int)type)).at(0);
    const auto senderName = sender ? QString(" [%1]").arg(sender->metaObject()->className()) : QString();
    m_logger << QString("[%1] [%2]%3")
                    .arg(date.toString(Qt::DateFormat::ISODateWithMs))
                    .arg(name)
                    .arg(senderName);
}
Logger Logger::info(QObject* sender) {
    return Logger(Type::Info, sender);
}
Logger Logger::warning(QObject* sender) {
    return Logger(Type::Warning, sender);
}
Logger Logger::debug(QObject* sender) {
    return Logger(Type::Debug, sender);
}
