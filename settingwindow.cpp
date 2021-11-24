#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent,
                             int currows,
                             int curcols) :
	QMainWindow(parent),
	ui(new Ui::SettingWindow)
{
	rows = currows;
	cols = curcols;
	ui->setupUi(this);
	QPoint cenpos = parent->geometry().center()
	                - QPoint(geometry().width() / 2, geometry().height() / 2);
	move(cenpos);
	ui->lineEdit_r->setText(QString::number(rows));
	ui->lineEdit_c->setText(QString::number(cols));
}

SettingWindow::~SettingWindow()
{
	delete ui;
}

void SettingWindow::on_pushButton_confirm_clicked()
{
	rows = ui->lineEdit_r->text().toInt();
	cols = ui->lineEdit_c->text().toInt();
	qDebug("r: %d, c: %d", rows, cols);
	hide();
	emit on_close(this);
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
    emit on_close(this);
}


void SettingWindow::on_lineEdit_r_returnPressed()
{
    ui->lineEdit_c->setFocus();
}

