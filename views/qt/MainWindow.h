#ifndef ANDORMEDA_QT_MAINWINDOW_H
#define ANDORMEDA_QT_MAINWINDOW_H

#include "SchematicWindow.h"
#include <qt4/QtGui/QToolBar>
#include <qt4/QtGui/QStatusBar>
#include <qt4/QtGui/QWidget>
#include <qt4/QtGui/QMainWindow>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);
protected:
	SchematicWindow *schem;
	QStatusBar *status;
};

#endif
