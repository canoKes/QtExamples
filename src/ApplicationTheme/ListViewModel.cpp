#include "ListViewModel.h"

ListViewModel::ListViewModel(QObject* parent)
    : QAbstractListModel(parent) {
}

int ListViewModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant ListViewModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return m_data.at(row);
        default:
            break;
    }

    return QVariant();
}

bool ListViewModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid()) {
        return false;
    }

    const int row = index.row();
    if (row < 0 || row >= m_data.count()) {
        return false;
    }

    switch (role) {
        case Qt::EditRole: {
            m_data[row] = value.toString();
            emit dataChanged(index, index, {role});
            return true;
        } break;
        default:
            break;
    }

    return false;
}

Qt::ItemFlags ListViewModel::flags(const QModelIndex& index) const {
    auto flags = QAbstractListModel::flags(index);
    const int row = index.row();
    if (index.isValid() && row >= 0 && row < m_data.count()) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool ListViewModel::insertRows(int row, int count, const QModelIndex& parent) {
    const int first = qMin(m_data.count(), row);
    const int last = row + count - 1;
    beginInsertRows(parent, first, last);
    for (int i = 0; i < count; i++) {
        m_data.insert(first + i, "New Item");
    }
    endInsertRows();
    return true;
}

bool ListViewModel::removeRows(int row, int count, const QModelIndex& parent) {
    const int last = row + count - 1;
    if (row < 0 || last >= m_data.count()) {
        return false;
    }

    beginRemoveRows(parent, row, last);
    for (int i = 0; i < count; i++) {
        m_data.removeAt(row);
    }
    endRemoveRows();
    return true;
}

void ListViewModel::append(const QString& item) {
    const int row = m_data.count();
    insertRows(row, 1);
    m_data[row] = item;
}
