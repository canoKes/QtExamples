#pragma once

#include <QWidget>

#include "ListViewModel.h"
#include "ui_ListView.h"

class ListView : public QWidget {
    Q_OBJECT

public:
    explicit ListView(QWidget* parent = nullptr);
    ~ListView() = default;

private slots:
    void onAdd();
    void onEdit();
    void onDelete();
    void onContextMenuRequest(const QPoint& position);
    void onListSelectionChanged();

private:
    Ui::ListViewClass ui;
    ListViewModel m_model;
};
