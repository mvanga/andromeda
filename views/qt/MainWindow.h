#ifndef ANDORMEDA_QT_MAINWINDOW_H
#define ANDORMEDA_QT_MAINWINDOW_H

#include "SchematicWindow.h"
#include <qt4/QtGui/QToolBar>
#include <qt4/QtGui/QStatusBar>
#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QMainWindow>
#include <qt4/QtGui/QLabel>

class MainWindow : public QMainWindow {
	Q_OBJECT

public slots:
	void netToolSelect();

public:
	MainWindow(QWidget *parent = 0);

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	/* The schematic window */
	SchematicWindow *schem;
	/* The status bar */
	QStatusBar *status;
	QLabel *message;

	/* Tools */
	QAction *drawNet;	/* Net/Wire tool */
	Layer *m_clayer;
};

#endif
