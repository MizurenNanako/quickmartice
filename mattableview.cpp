#include "mattableview.h"
#include <QItemSelectionModel>
#include <QModelIndexList>

#define CODE_PATTERN_1 \
	sel_mod->model()->setData(k, model()->data(i));\
	sel_mod->select(i, QItemSelectionModel::Deselect);\
	sel_mod->select(k, QItemSelectionModel::Select);

#define CODE_PATTERN_2 \
	QVariant datak = model()->data(k);\
	sel_mod->model()->setData(k, model()->data(i));\
	sel_mod->model()->setData(i, datak);\
	sel_mod->select(i, QItemSelectionModel::Deselect);\
	sel_mod->select(k, QItemSelectionModel::Select);

matTableView::matTableView(QWidget *parent)
	: QTableView(parent)
{
}

void matTableView::keyPressEvent(QKeyEvent *event)
{
	QItemSelectionModel *sel_mod = selectionModel();
	QModelIndexList sel_id_list = sel_mod->selectedIndexes();

	if (event->modifiers() == (Qt::ControlModifier)) {
		switch (event->key()) {
		case Qt::Key::Key_Down:
			foreach(QModelIndex i, sel_id_list) {
				if (i.row() < model()->rowCount() - 1) {
					QModelIndex k = model()->index(i.row() + 1, i.column());
					CODE_PATTERN_1
				}
			}

			break;

		case Qt::Key::Key_Up:
			foreach(QModelIndex i, sel_id_list) {
				if (i.row() > 0) {
					QModelIndex k = model()->index(i.row() - 1, i.column());
					CODE_PATTERN_1
				}
			}

			break;

		case Qt::Key::Key_Left:
			foreach(QModelIndex i, sel_id_list) {
				if (i.column() > 0) {
					QModelIndex k = model()->index(i.row(), i.column() - 1);
					CODE_PATTERN_1
				}
			}

			break;

		case Qt::Key::Key_Right:
			foreach(QModelIndex i, sel_id_list) {
				if (i.column() < model()->columnCount() - 1) {
					QModelIndex k = model()->index(i.row(), i.column() + 1);
					CODE_PATTERN_1
				}
			}

			break;

		case Qt::Key_E:
			foreach(QModelIndex i, sel_id_list) {
				model()->setData(i, sel_mod->currentIndex().data());
			}

			break;

		default:
			QTableView::keyPressEvent(event);
			break;
		}
	}

	else if (event->modifiers() == (Qt::AltModifier)) {
		switch (event->key()) {
		case Qt::Key::Key_Down:
			foreach(QModelIndex i, sel_id_list) {
				if (i.row() < model()->rowCount() - 1) {
					QModelIndex k = model()->index(i.row() + 1, i.column());
					CODE_PATTERN_2
				}
			}

			break;

		case Qt::Key::Key_Up:
			foreach(QModelIndex i, sel_id_list) {
				if (i.row() > 0) {
					QModelIndex k = model()->index(i.row() - 1, i.column());
					CODE_PATTERN_2
				}
			}

			break;

		case Qt::Key::Key_Left:
			foreach(QModelIndex i, sel_id_list) {
				if (i.column() > 0) {
					QModelIndex k = model()->index(i.row(), i.column() - 1);
					CODE_PATTERN_2
				}
			}

			break;

		case Qt::Key::Key_Right:
			foreach(QModelIndex i, sel_id_list) {
				if (i.column() < model()->columnCount() - 1) {
					QModelIndex k = model()->index(i.row(), i.column() + 1);
					CODE_PATTERN_2
				}
			}

			break;

		default:
			QTableView::keyPressEvent(event);
			break;
		}
	}

	else {
		switch (event->key()) {
		case Qt::Key_Delete:
			foreach(QModelIndex i, sel_id_list) {
				model()->setData(i, "");
			}

			break;

		default:
			QTableView::keyPressEvent(event);
			break;
		}
	}
}

