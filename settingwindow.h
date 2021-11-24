#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
	class SettingWindow;
}

class SettingWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit SettingWindow(QWidget *parent,
	                       int currows = 4,
	                       int curcols = 4);
	~SettingWindow();
	inline int get_r()
	{
		return rows;
	}
	inline int get_c()
	{
		return cols;
	}

private:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
	void on_close(SettingWindow *me);

private slots:
	void on_pushButton_confirm_clicked();

	void on_lineEdit_r_returnPressed();

private:
	Ui::SettingWindow *ui;
	int rows;
	int cols;
};

#endif // SETTINGWINDOW_H
