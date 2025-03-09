#pragma once

#include <QAbstractListModel>

class ListViewModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit ListViewModel(QObject* parent = nullptr);
    ~ListViewModel() = default;

public:
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    void append(const QString& item);

private:
    QStringList m_data;
};
