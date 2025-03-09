#include "ListViewDelegate.h"

#include <QPainter>
#include <QStyle>

namespace {
    const int Margin = 1;
    const int Padding = 6;
    const int BorderRadius = 4;
}

void ListViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    if (!index.isValid()) {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(option.rect.x() + Margin, option.rect.y() + Margin);

    const int width = option.rect.width() - 2 * Margin;
    const int height = option.rect.height() - 2 * Margin;

    const auto text = index.data(Qt::DisplayRole).toString();
    auto textPen = QPen(option.palette.color(QPalette::WindowText));
    auto backgroundBrush = QBrush(Qt::NoBrush);

    if (option.state.testFlag(QStyle::State_Selected)) {
        textPen.setColor(option.palette.color(QPalette::HighlightedText));
        backgroundBrush = QBrush(option.palette.color(QPalette::Highlight));
    }

    {
        painter->save();
        painter->setBrush(backgroundBrush);
        painter->drawRoundedRect(0, 0, width, height, BorderRadius, BorderRadius);
        painter->restore();
    }

    {
        painter->save();
        painter->translate(Padding, (height / 2) + (option.fontMetrics.capHeight() / 2));
        painter->setPen(textPen);
        painter->drawText(0, 0, text);
        painter->restore();
    }

    painter->restore();
}

QSize ListViewDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    if (!index.isValid()) {
        return QStyledItemDelegate::sizeHint(option, index);
    }

    const int width = option.rect.width();
    const int height = Margin * 2 + Padding * 2 + option.fontMetrics.height();
    return QSize(width, height);
}

QWidget* ListViewDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return nullptr;
}

void ListViewDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
}

void ListViewDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
}
