#ifndef MATTABLEVIEW_H
#define MATTABLEVIEW_H

#include <QTableView>
#include <QKeyEvent>

class matTableView : public QTableView {
public:
	matTableView(QWidget *parent = nullptr);
private:
	void keyPressEvent(QKeyEvent *event) override;
};

#endif // MATTABLEVIEW_H
