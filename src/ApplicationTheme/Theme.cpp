#include "Theme.h"

#include <QApplication>
#include <QFile>
#include <QIconEngine>
#include <QPainter>
#include <QRegularExpression>
#include <QSvgRenderer>

#include "Logger.h"

static void updateSvgColors(QByteArray& content, const QColor& color);

class IconEngine : public QIconEngine {
public:
    IconEngine(Theme* theme, const QString& name);

public:
    void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) override;
    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) override;
    QIconEngine* clone() const override;

private:
    Theme* m_theme;
    QString m_name;
};

Theme::Theme(QObject* parent)
    : QObject(parent) {
}

QIcon Theme::icon(const QString& name) {
    const auto resource = QString(":/icons/%1").arg(name);

    if (!m_iconContentMap.contains(name)) {
        Logger::info(this) << "caching icon content for:" << name;
        QFile file(resource);
        if (!file.open(QFile::ReadOnly)) {
            return QIcon();
        }

        auto content = file.readAll();
        updateSvgColors(content, qApp->palette().text().color());
        m_iconContentMap.insert(name, content);
    }
    else {
        Logger::info(this) << "load icon content form cache:" << name;
    }

    auto engine = new IconEngine(this, name);
    m_iconEngines.insert(engine);
    return QIcon(engine);
}

const QByteArray Theme::iconContent(const QString& name, QPalette::ColorRole role, QPalette::ColorGroup group) const {
    QByteArray content = m_iconContentMap.value(name);
    updateSvgColors(content, qApp->palette().color(group, role));
    return content;
}

void updateSvgColors(QByteArray& content, const QColor& color) {
    QRegularExpression pattern("fill=\"(#[0-9A-Fa-f]+)\"");
    auto result = pattern.match(content);
    while (result.hasMatch()) {
        const auto newColor = color.name().toUpper().toUtf8();
        const auto oldColor = result.captured(1).toUtf8();
        content.replace(oldColor, newColor);
        result = pattern.match(content, result.capturedEnd());
    }
}

IconEngine::IconEngine(Theme* theme, const QString& name)
    : QIconEngine()
    , m_theme(theme)
    , m_name(name) {
    Logger::info() << "[IconEngine] created:" << m_name;
}

void IconEngine::paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) {
    if (!m_theme) {
        return;
    }

    QPalette::ColorRole role = QPalette::Text;
    QPalette::ColorGroup group = QPalette::Normal;
    switch (mode) {
        case QIcon::Disabled:
            group = QPalette::Disabled;
            break;
        case QIcon::Active:
        case QIcon::Selected:
            role = QPalette::Highlight;
            group = QPalette::ColorGroup::Active;
            break;
        default:
            break;
    }

    QSvgRenderer renderer(m_theme->iconContent(m_name, role, group));
    renderer.render(painter, rect);
}

QPixmap IconEngine::pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) {
    QImage image(size, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));

    QPixmap pixmap = QPixmap::fromImage(image, Qt::NoFormatConversion);
    {
        QPainter painter(&pixmap);
        QRect rect(QPoint(0, 0), size);
        paint(&painter, rect, mode, state);
    }
    return pixmap;
}

QIconEngine* IconEngine::clone() const {
    return new IconEngine(*this);
}
