#include "ListView.h"

#include <QMenu>

#include "Application.h"
#include "ListViewDelegate.h"
#include "Logger.h"

ListView::ListView(QWidget* parent)
    : QWidget(parent) {
    ui.setupUi(this);

    ui.addAction->setIcon(App->icon("plus"));
    ui.editAction->setIcon(App->icon("pencil"));
    ui.deleteAction->setIcon(App->icon("trash"));

    connect(ui.addAction, &QAction::triggered, this, &ListView::onAdd);
    connect(ui.editAction, &QAction::triggered, this, &ListView::onEdit);
    connect(ui.deleteAction, &QAction::triggered, this, &ListView::onDelete);

    ui.addButton->setDefaultAction(ui.addAction);
    ui.editButton->setDefaultAction(ui.editAction);
    ui.deleteButton->setDefaultAction(ui.deleteAction);

    ui.listView->setModel(&m_model);
    ui.listView->setItemDelegate(new ListViewDelegate);
    connect(ui.listView, &QListView::customContextMenuRequested, this, &ListView::onContextMenuRequest);
    connect(ui.listView, &QListView::clicked, this, &ListView::onListSelectionChanged);
    if (auto* selectionModel = ui.listView->selectionModel()) {
        connect(selectionModel, &QItemSelectionModel::currentRowChanged, this, &ListView::onListSelectionChanged);
    }

    m_model.append("Item 1");
    //m_model.append("Item 2");
    //m_model.append("Item 3");
    //m_model.append("Item 4");

    onListSelectionChanged();
}

void ListView::onAdd() {
    m_model.insertRow(m_model.rowCount());
}

void ListView::onEdit() {
    ui.listView->edit(ui.listView->currentIndex());
}

void ListView::onDelete() {
    m_model.removeRow(ui.listView->currentIndex().row());
}

void ListView::onContextMenuRequest(const QPoint& position) {
    QMenu menu;
    menu.addAction(ui.addAction);

    if (ui.listView->indexAt(position).isValid()) {
        menu.addAction(ui.editAction);
        menu.addSeparator();
        menu.addAction(ui.deleteAction);
    }

    menu.exec(ui.listView->viewport()->mapToGlobal(position));
}

void ListView::onListSelectionChanged() {
    const bool enabled = ui.listView->currentIndex().isValid();
    ui.editAction->setEnabled(enabled);
    ui.deleteAction->setEnabled(enabled);
}