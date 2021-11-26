#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("Quick Martice " VERSION);
	QPoint cenpos = QApplication::desktop()->geometry().center()
	                - QPoint(geometry().width() / 2, geometry().height() / 2);
	move(cenpos);
	imodel = new QStandardItemModel;
	setmodelsize();
	ui->tableView_edit->setModel(imodel);
	ui->tableView_edit->horizontalHeader()->setDefaultSectionSize(40);
	ui->tableView_edit->horizontalHeader()->setMinimumSectionSize(36);
	ui->tableView_edit->update();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QRect newgeo;
	newgeo.setHeight(event->size().height());
	newgeo.setWidth(event->size().width());
    QRect newwig;
    newwig.setHeight(event->size().height()-25);
	newwig.setWidth(event->size().width());
	ui->gridLayout->setGeometry(newwig);
	ui->gridLayoutWidget->setGeometry(newwig);
}

QString MainWindow::genlatex()
{
	if (isnatural) {
		QString r{matmodifier[0]};

		for (int i = 0; i < h_imodel; ++i) {
			r += matmodifier[0];

			for (int j = 0; j < w_imodel; ++j) {
				QModelIndex index = imodel->index(i, j);
				QString cont = imodel->data(index).toString();
				r += cont;

				if(j + 1 != w_imodel) r += ", ";
			}

			r += matmodifier[1];

			if(i + 1 != h_imodel)
				r += ", ";
		}

		r += matmodifier[1];
		return r;
	}

	QString r(R"(\begin{)");
	r += modifier + "}\n";

	for (int i = 0; i < h_imodel; ++i) {
		r += '\t';

		for (int j = 0; j < w_imodel; ++j) {
			QModelIndex index = imodel->index(i, j);
			QString cont = imodel->data(index).toString();

			//special changes
			if(cont == "..." || cont == ".") {
				if (i == j) {
					cont = R"(\ddots)";
				}

				else if (j == 0 || j == w_imodel - 1) {
					cont = R"(\vdots)";
				}

				else {
					cont = R"(\cdots)";
				}
			}

			r += cont;

			if(j + 1 != w_imodel) r += '&';
		}

		r += R"(\\)""\n";
	}

	r += R"(\end{)" + modifier + "}";
	return r;
}

void MainWindow::setmodelsize()
{
	imodel->setColumnCount(w_imodel);
	imodel->setRowCount(h_imodel);
}


void MainWindow::on_pushButton_copy_clicked()
{
	QClipboard *qb = QApplication::clipboard();
	qb->setText(ui->textBrowser_output->toPlainText());
}


void MainWindow::on_pushButton_generate_clicked()
{
	ui->textBrowser_output->setText(genlatex());
}


void MainWindow::on_radioButton_lines_clicked()
{
	modifier = "vmatrix";
}


void MainWindow::on_radioButton_b1_clicked()
{
	modifier = "pmatrix";
}


void MainWindow::on_radioButton_b2_clicked()
{
	modifier = "bmatrix";
}


void MainWindow::on_radioButton_flower_clicked()
{
	modifier = "Bmatrix";
}


void MainWindow::on_radioButton_none_clicked()
{
	modifier = "matrix";
}


void MainWindow::on_pushButton_new_clicked()
{
	imodel->clear();
	setmodelsize();
}


void MainWindow::on_pushButton_change_clicked()
{
	if (onsetting == true)return;

	onsetting = true;
	QMainWindow *subwin = new SettingWindow(this, h_imodel, w_imodel);
	connect(subwin, SIGNAL(on_close(SettingWindow*)),
	        this, SLOT(on_subwin_closed(SettingWindow*)));
	ui->pushButton_change->setDisabled(true);
	subwin->show();
	//setmodelsize();
}

void MainWindow::on_subwin_closed(SettingWindow *which)
{
	if(!which)return;

	w_imodel = which->get_c();
	h_imodel = which->get_r();
	delete which;
	setmodelsize();
	qDebug("w: %d, h: %d", w_imodel, h_imodel);
	onsetting = false;
	ui->pushButton_change->setDisabled(false);
}

void MainWindow::on_checkBox_natural_stateChanged(int arg1)
{
	switch(arg1) {
	case Qt::Checked:
		ui->radioButton_cas1->setDisabled(false);
		ui->radioButton_cas2->setDisabled(false);
		isnatural = true;
		break;

	default:
		ui->radioButton_cas2->setDisabled(true);
		ui->radioButton_cas1->setDisabled(true);
		isnatural = false;
		break;
	}
}

void MainWindow::on_radioButton_cas1_clicked()
{
	matmodifier = "[]";
}


void MainWindow::on_radioButton_cas2_clicked()
{
	matmodifier = "{}";
}

