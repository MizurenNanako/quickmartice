#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include "settingwindow.h"
#include <QResizeEvent>

#define VERSION "1.1.4"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void setmodelsize();
	QString genlatex();
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
	void on_subwin_closed(SettingWindow *which);

	void on_pushButton_copy_clicked();

	void on_pushButton_generate_clicked();

	void on_radioButton_lines_clicked();

	void on_radioButton_b1_clicked();

	void on_radioButton_b2_clicked();

	void on_radioButton_flower_clicked();

	void on_radioButton_none_clicked();

	void on_pushButton_new_clicked();

	void on_pushButton_change_clicked();

	void on_checkBox_natural_stateChanged(int arg1);

    void on_radioButton_cas1_clicked();

    void on_radioButton_cas2_clicked();

private:
	Ui::MainWindow *ui;
	int w_imodel = 4;
	int h_imodel = 4;
	bool isnatural = false;
    QString matmodifier{"[]"};
	bool onsetting = false;
	QStandardItemModel *imodel;
	QString modifier{"vmatrix"};
};
#endif // MAINWINDOW_H
