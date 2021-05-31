#pragma once
#include <qshortcut.h>
#include <qkeysequence.h>
#include <qset.h>
#include <qwidget.h>
#include "service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qabstractbutton.h>
#include <qtabwidget.h>
#include <qgroupbox.h>
#include <qvector.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qbarseries.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qvalueaxis.h>
#include <qtableview.h>
#include "EventsTableModel.h"
#include "MyDelegate.h"

using namespace QtCharts;
class GUI : public QWidget {

    Q_OBJECT

private:
	Service& service;
	// graphical elements
	QTableView* eventsTableView;
	QListWidget *listingEventsWidget{};
	QLineEdit* descriptionLineEdit{}, *titleLineEdit{}, *dateLineEdit{}, *linkLineEdit{}, *peopleLineEdit{}, *monthLineEdit{};
	QPushButton* addAdminButton{}, *deleteAdminButton{}, *updateAdminButton{}, *adminButton{}, *userButton{}, *addUserButton{}, *deleteUserButton{}, *listUserButton{}, *openUserButton{}, *nextButton{}, *exitButton{}, *backButton, *clearButton;
	QPushButton* undoButton, * redoButton;
	QVBoxLayout* mainLayout;
	QGroupBox* eventsBox{}, *chartBox{};
	QTabWidget* tabWidget{};
	QChart* eventsChart{};
	// The vector will be used for the chart Bar
	QBarSet* set;
	QShortcut* undoShortcut;
	QShortcut* redoShortcut;
	// This will keep the current_index of the event that will be displayed to the user.
	int current_index;
	int max_month;
	// entry mode
	string mode;

public:
	explicit GUI(Service& service);

private:
	// initGUI() will initialize the starting window of the app, by adding 2 buttons and 2 checkboxes
	void initGUI();
	// initEvents() will initialize the events List, where we will have all the Events listed.
	void initEvents();
	// initAdmin() will initialize the admin menu.
	void initAdmin();
	// initUser() will initialize the user menu
	void initUser();
	// initChart() will initialize the chart
	void initChart();
//	void initSet();
	// make_connections() will initialize all the connections from the beginning.
	void make_connections();
	int getPosition(QListWidget* listWidget, int Case);
	void listEvent(int position);
	// Admin buttons
	void addEvent();
	void deleteEvent();
	void updateEvent();
	void clearLines(int Case);

	static void clearLayout(QLayout* layout);
};

