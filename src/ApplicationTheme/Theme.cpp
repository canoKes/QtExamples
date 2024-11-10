#include "Theme.h"

#include <QApplication>
#include <QFile>
#include <QIconEngine>
#include <QMetaEnum>
#include <QPainter>
#include <QRegularExpression>
#include <QStyleHints>
#include <QSvgRenderer>

#include "Application.h"
#include "Logger.h"

static void updateSvgColors(QByteArray& content, const QColor& color);

class IconEngine : public QIconEngine {
public:
    IconEngine(const QByteArray& content, const QColor& color = QColor());

public:
    void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) override;
    QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state) override;
    QIconEngine* clone() const override;

private:
    void update(const QColor& color);

private:
    QByteArray m_template;
    QByteArray m_content;
    QColor m_color;
};

Theme::Theme(QObject* parent)
    : QObject(parent)
    , m_mode(Mode::Light) {
    const auto styleHints = App->styleHints();
    connect(styleHints, &QStyleHints::colorSchemeChanged, this, &Theme::setColorScheme);
    setColorScheme(styleHints->colorScheme());
}

Theme::Mode Theme::mode() const {
    return m_mode;
}

QIcon Theme::icon(const QString& name, const QColor& color) const {
    const auto meta = QMetaEnum::fromType<Mode>();
    const auto modeName = meta.valueToKey((int)m_mode);
    const auto key = QString("%1_%2").arg(modeName, name);
    const auto resource = QString(":/icons/%1").arg(name);

    auto engine = m_iconEngineMap.value(key, nullptr);
    if (!engine) {
        QFile file(resource);
        if (!file.open(QFile::ReadOnly)) {
            return QIcon();
        }
        engine = new IconEngine(file.readAll(), color);
        m_iconEngineMap.insert(key, engine);
    }

    return QIcon(engine);
}

void Theme::setMode(Mode mode) {
    const auto scheme = mode == Mode::Dark
        ? Qt::ColorScheme::Dark
        : Qt::ColorScheme::Light;

    App->styleHints()->setColorScheme(scheme);
}

void Theme::toggleMode() {
    setMode(m_mode == Mode::Light ? Mode::Dark : Mode::Light);
}

void Theme::setColorScheme(Qt::ColorScheme colorScheme) {
    const auto mode = colorScheme == Qt::ColorScheme::Dark
        ? Theme::Mode::Dark
        : Theme::Mode::Light;

    if (m_mode == mode) {
        return;
    }

    m_mode = mode;

    Logger::info() << "theme mode changed:" << mode;
    emit modeChanged(m_mode);
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

IconEngine::IconEngine(const QByteArray& content, const QColor& color)
    : QIconEngine()
    , m_template(content)
    , m_color(color) {
    update(m_color);
}

void IconEngine::paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state) {
    QSvgRenderer renderer(m_content);
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

void IconEngine::update(const QColor& color) {
    m_content = m_template;
    updateSvgColors(m_content, m_color);
}