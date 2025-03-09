#include "Toast.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QScreen>

#include "Logger.h"

Toast::Toast(const QString& message, QWidget* parent)
    : Toast(message, 3, parent) {
}

Toast::Toast(const QString& message, int durationSeconds, QWidget* parent)
    : QFrame(parent)
    , m_defaultPalette(qApp->palette()) {
    Logger::debug(this) << "created" << this;

    setAttribute(Qt::WA_DeleteOnClose);
    setAutoFillBackground(true);
    setFrameShape(QFrame::NoFrame);
    setFrameShadow(QFrame::Plain);

    m_defaultPalette.setColor(QPalette::Window, m_defaultPalette.color(QPalette::Midlight));
    setPalette(m_defaultPalette);

    if (parent) {
        setWindowFlags(Qt::FramelessWindowHint);
        parent->installEventFilter(this);
    }
    else {
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    }

    auto label = new QLabel(message);
    auto layout = new QHBoxLayout;
    layout->addWidget(label);
    setLayout(layout);

    m_timer.setInterval(qMin(durationSeconds * 1000, 3000));
    connect(&m_timer, &QTimer::timeout, this, &Toast::close);
}

Toast::~Toast() {
    Logger::debug(this) << "deleted" << this;
}

bool Toast::eventFilter(QObject* watched, QEvent* event) {
    if (watched == parent()) {
        const auto type = event->type();
        switch (type) {
            case QEvent::Resize:
                updatePosition();
                return true;
                break;
            default:
                break;
        }
    }

    return QFrame::eventFilter(watched, event);
}

void Toast::enterEvent(QEnterEvent* event) {
    QPalette palette = m_defaultPalette;
    palette.setColor(QPalette::ColorRole::Window, palette.color(QPalette::Highlight));
    palette.setColor(QPalette::ColorRole::WindowText, palette.color(QPalette::HighlightedText));
    setPalette(palette);
}

void Toast::leaveEvent(QEvent* event) {
    setPalette(m_defaultPalette);
}

void Toast::mousePressEvent(QMouseEvent* event) {
    const auto button = event->button();
    switch (button) {
        case Qt::LeftButton:
            emit clicked();
            break;
        case Qt::MiddleButton:
            emit disposed();
            close();
            break;
        default:
            break;
    }
}

void Toast::showEvent(QShowEvent* event) {
    if (m_timer.isActive()) {
        event->ignore();
        return;
    }

    updatePosition();
    m_timer.start();
}

void Toast::updatePosition() {
    QSize parentSize;
    QPoint parentPosition;
    QMargins margin{10, 10, 10, 10};

    auto parent = static_cast<QWidget*>(QFrame::parent());
    if (!parent) {
        auto screen = qApp->primaryScreen();
        parentSize = screen->geometry().size();
        margin.setBottom(60);
    }
    else {
        parentSize = parent->size();
        parentPosition = parent->pos();
    }

    resize(sizeHint());
    repaint();

    QSize size = Toast::size();

    int x = parentSize.width() - size.width() - margin.right();
    int y = parentSize.height() - size.height() - margin.bottom();
    move(x, y);
}
