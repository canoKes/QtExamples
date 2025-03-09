#pragma once

#include <QFrame>
#include <QTimer>

class Toast : public QFrame {
    Q_OBJECT

signals:
    void clicked();
    void disposed();

public:
    explicit Toast(const QString& message, QWidget* parent = nullptr);
    explicit Toast(const QString& message, int durationSeconds, QWidget* parent = nullptr);
    ~Toast() = default;

public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

protected:
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void showEvent(QShowEvent* event) override;

private:
    void updatePosition();

private:
    QTimer m_timer;
};
