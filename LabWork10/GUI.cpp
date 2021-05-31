#include "GUI.h"
#include <qformlayout.h>
#include <sstream>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qmenu.h>
#include <qstringlist.h>
#include <qpalette.h>


GUI::GUI(Service& service) : service{ service }
{
    this->setWindowIcon(QIcon("main_icon.ico"));
    this->setWindowTitle("Events Organizer");
	this->mainLayout = new QVBoxLayout{ this };
	this->max_month = 0;
	this->initGUI();
}

void GUI::initGUI()
{
	GUI::clearLayout(this->mainLayout);
	// Initialization of the graphical elements.
	this->eventsTableView = new QTableView{};
	this->undoShortcut = new QShortcut(QKeySequence("CTRL+Z"), this);
	this->redoShortcut = new QShortcut(QKeySequence("CTRL+Y"), this);
	this->listingEventsWidget = new QListWidget{};
	this->addAdminButton = new QPushButton{"Add"};
	this->deleteAdminButton = new QPushButton{"Delete"};
	this->updateAdminButton = new QPushButton{ "Update" };
	this->addUserButton = new QPushButton{ "Add" };
	this->deleteUserButton = new QPushButton{ "Delete" };
	this->listUserButton = new QPushButton{ "List" };
	this->openUserButton = new QPushButton{ "Open" };
	this->nextButton = new QPushButton{ "Next" };
	this->exitButton = new QPushButton{ "Exit" };
	this->backButton = new QPushButton{"Back"};
	this->clearButton = new QPushButton{"Clear"};
	this->undoButton = new QPushButton{"Undo"};
	this->redoButton = new QPushButton{ "Redo" };

	this->adminButton = new QPushButton{ "Admin" };
	this->userButton = new QPushButton{ "User" };

    emit this->make_connections();
	QLabel* label = new QLabel{ "Please select the mode!" };
	
	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(this->adminButton, 0, 0);
	buttonsLayout->addWidget(this->userButton, 0, 1);

	mainLayout->addWidget(label);
	mainLayout->addLayout(buttonsLayout);

}

void GUI::initEvents()
{
	if (this->eventsTableView->model() != nullptr) {
		delete this->eventsTableView->model();
	}
	EventsTableModel* model = new EventsTableModel{ &this->service.getRepo(mode) };
	this->eventsTableView->setModel(model);
	this->eventsTableView->setItemDelegate(new ButtonDelegate{&this->service.getRepo(mode)});
}

void GUI::initAdmin()
{
	// Initializing the Admin Window.
	this->mode = "admin";
	this->clearLayout(this->mainLayout);
	this->eventsBox = new QGroupBox{};
	this->chartBox = new QGroupBox{};

	this->tabWidget = new QTabWidget{};

	this->titleLineEdit = new QLineEdit{};
	this->descriptionLineEdit = new QLineEdit{};
	this->linkLineEdit = new QLineEdit{};
	this->dateLineEdit = new QLineEdit{};
	this->peopleLineEdit = new QLineEdit{};
	QFormLayout* eventDetails = new QFormLayout{};

	eventDetails->addRow("Title", this->titleLineEdit);
	eventDetails->addRow("Description", this->descriptionLineEdit);
	eventDetails->addRow("Date", this->dateLineEdit);
	eventDetails->addRow("People", this->peopleLineEdit);
	eventDetails->addRow("Link", this->linkLineEdit);

	QGridLayout* temporaryEvent = new QGridLayout{};
	temporaryEvent->addWidget(addAdminButton, 0, 0);
	temporaryEvent->addWidget(undoButton, 0, 1, 2, 1);
	temporaryEvent->addWidget(deleteAdminButton, 1, 0);
	temporaryEvent->addWidget(updateAdminButton, 2, 0);
	temporaryEvent->addWidget(redoButton, 2, 1, 2, 1);
	temporaryEvent->addWidget(clearButton, 3, 0);
	temporaryEvent->addLayout(eventDetails, 0, 2, 4, 1);

	this->eventsBox->setLayout(temporaryEvent);
	tabWidget->addTab(this->eventsBox, "Events");

	// the code that will initialize the chart tab from the tabWidget will be in the
	// function initChart();

	this->initChart();

	this->mainLayout->addWidget(tabWidget);
	QLabel* info = new QLabel{ "Registered Events." };
	QFont font("Courier", 40, 10, true);
	info->setFont(font);
	
	this->mainLayout->addWidget(info);

	this->mainLayout->addWidget(this->eventsTableView);
	this->mainLayout->addWidget(this->backButton);

	emit this->initEvents();
}

void GUI::initUser()
{
	// Initializing the user window
	this->mode = "user";
	this->clearLayout(this->mainLayout);
	QLabel* info = new QLabel{ "My Events." };
	QFont font("Courier", 30, 10, true);
	info->setFont(font);

	this->mainLayout->addWidget(info);

	this->mainLayout->addWidget(this->eventsTableView);
	this->monthLineEdit = new QLineEdit{};

	QGridLayout *functionalitiesLayout = new QGridLayout{};
	functionalitiesLayout->addWidget(this->listingEventsWidget, 0, 0, 1, 3);
	functionalitiesLayout->addWidget(this->addUserButton, 1, 0);
	functionalitiesLayout->addWidget(this->deleteUserButton, 1, 1);
	functionalitiesLayout->addWidget(this->undoButton, 1, 2);
	functionalitiesLayout->addWidget(this->listUserButton, 2, 0);
	functionalitiesLayout->addWidget(this->openUserButton, 2, 1);
	functionalitiesLayout->addWidget(this->redoButton, 2, 2);
	functionalitiesLayout->addWidget(new QLabel{ "Month" }, 3, 0);
	functionalitiesLayout->addWidget(this->monthLineEdit, 3, 1, 1, 2);

	functionalitiesLayout->addWidget(this->nextButton, 4, 0);
	functionalitiesLayout->addWidget(this->exitButton, 4, 1);
	functionalitiesLayout->addWidget(this->backButton, 5, 0, 1, 2);
	this->nextButton->setVisible(false);
	this->exitButton->setVisible(false);
	this->mainLayout->addLayout(functionalitiesLayout);

	emit this->initEvents();
}

void GUI::initChart()
{
    this->set = new QBarSet("Number of events in that month");

    vector<int> monthsEvents = this->service.monthEvents();
    for(int i = 1; i <= 12 ; i++) {
        *this->set << monthsEvents[i-1];
    }

    QBarSeries *series = new QBarSeries();
    series->append(this->set);
	this->eventsChart = new QChart{};

	this->eventsChart->addSeries(series);
	this->eventsChart->setTitle("Event registered per month.");
	this->eventsChart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList months;
	months << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    QBarCategoryAxis* Xaxis = new QBarCategoryAxis{};
    Xaxis->append(months);
    this->eventsChart->addAxis(Xaxis, Qt::AlignBottom);
    series->attachAxis(Xaxis);

    QValueAxis* Yaxis = new QValueAxis{};
    qreal n = 10;
    Yaxis->setRange(0, n);
    this->eventsChart->addAxis(Yaxis, Qt::AlignLeft);
    series->attachAxis(Yaxis);

	QFormLayout* layout = new QFormLayout{};
	QChartView* chartView = new QChartView{ this->eventsChart };
	chartView->setRenderHint(QPainter::Antialiasing);

	layout->addWidget(chartView);
    if(this->chartBox->layout() != nullptr)
        delete this->chartBox->layout();
	this->chartBox->setLayout(layout);
	this->tabWidget->addTab(this->chartBox, "Chart");
}

void GUI::make_connections()
{

    QObject::connect(this->backButton, &QPushButton::clicked, this, [this](){
        this->initGUI();
    });
	QObject::connect(this->adminButton, &QPushButton::clicked, this, [this]() { 
			this->initAdmin();
	});
	QObject::connect(this->userButton, &QPushButton::clicked, this, [this]() {
			this->initUser();
	});

	QObject::connect(this->addAdminButton, &QPushButton::clicked, this, &GUI::addEvent);
	QObject::connect(this->deleteAdminButton, &QPushButton::clicked, this, &GUI::deleteEvent);
	QObject::connect(this->updateAdminButton, &QPushButton::clicked, this, &GUI::updateEvent);
	QObject::connect(this->openUserButton, &QPushButton::clicked, this, [this]() {
		this->service.open();
	});

	QObject::connect(this->addUserButton, &QPushButton::clicked, this, [this]() {
		int index = getPosition(this->listingEventsWidget, 2);
		if (index < 0) {
			QMessageBox::critical(this, "Error", "You have not chosen any event.");
			return;
		}
		// We have to get the element from the repo, and since we show one at a time, we don't
		// know the real position in the array.
		QString event_data = this->listingEventsWidget->item(0)->text();
		string event = event_data.toStdString();
		string title_identifier = event.substr(0, event.find(" -"));
		// we will find the element using find from stl
		vector<Event> temporary = this->service.getRepo("admin").get_all();
		auto it = find_if(temporary.begin(), temporary.end(), [&title_identifier](const Event& e) {return e.getTitle() == title_identifier; });
		Event element = temporary[distance(temporary.begin(), it)];
		
		if (this->service.addService(element.getTitle(),
			element.getDescription(),
			element.getDate(),	
			element.getPeopleNr(),
			element.getLink(), "user")) {
			emit this->initEvents();
			emit this->nextButton->clicked();
			this->addUserButton->setDisabled(true);
		}
		else {
            this->addUserButton->setDisabled(true);
            QMessageBox::critical(this, "Warning", "You have already this event in your list");
        }
	});
	// Connection of the delete user button, that will delete a selected event.
	QObject::connect(this->deleteUserButton, &QPushButton::clicked, this, [this]() {
		QModelIndex index = this->eventsTableView->currentIndex();
		int row = index.row();
		if (row < 0) {
			QMessageBox::critical(this, "Error", "You have not chosen any event.");
			return;
		}

		Event element = this->service.getRepo("user").get_element(row);

		if (this->service.deleteService(element.getTitle(),"user")) {
			emit this->initEvents();
		}
		else QMessageBox::critical(this, "Warning", "You have already this event in your list");

	});
	// Connection of the listbutton, that initializes the listingEventsWidget
	QObject::connect(this->listUserButton, &QPushButton::clicked, this, [this]() {
		this->current_index = 0;
		this->listEvent(this->current_index);

		this->addUserButton->setDisabled(true);
		this->deleteUserButton->setDisabled(true);
		this->listUserButton->setDisabled(true);
		this->openUserButton->setDisabled(true);
        this->backButton->setDisabled(true);

		this->nextButton->setVisible(true);
		this->exitButton->setVisible(true);
	});
	// Connection of the nextButton from the user menu, to get to the next element. 
	QObject::connect(this->nextButton, &QPushButton::clicked, this, [this]() {
		this->current_index++;
		this->listEvent(this->current_index);
	});
	// Connection of ther exitButton from the user menu, to exit and clear.
	QObject::connect(this->exitButton, &QPushButton::clicked, this, [this]() {
		this->current_index = 0;
		this->monthLineEdit->clear();
		this->listingEventsWidget->clear();
        this->addUserButton->setDisabled(false);
        this->deleteUserButton->setDisabled(false);
        this->listUserButton->setDisabled(false);
        this->openUserButton->setDisabled(false);
        this->backButton->setDisabled(false);

		this->nextButton->setVisible(false);
		this->exitButton->setVisible(false);
	});

	QObject::connect(this->eventsTableView, &QTableView::clicked, this, [=](const QModelIndex& index) {
		int row = index.row();
		if (mode == "admin") {
			TElem event = this->service.getRepo(mode).get_element(row);
			this->titleLineEdit->setText(QString::fromStdString(event.getTitle()));
			this->descriptionLineEdit->setText(QString::fromStdString(event.getDescription()));
			this->linkLineEdit->setText(QString::fromStdString(event.getLink()));
			this->dateLineEdit->setText(QString::fromStdString(event.getDate().toString()));
			this->peopleLineEdit->setText(QString::fromStdString(to_string(event.getPeopleNr())));
		}
	});

	QObject::connect(this->listingEventsWidget, &QListWidget::itemSelectionChanged, [this](){
	    this->addUserButton->setDisabled(false);
	});

	QObject::connect(this->clearButton, &QPushButton::clicked, this, [this](){
	    emit this->clearLines(1);
	});

	QObject::connect(this->undoButton, &QPushButton::clicked, this, [this]() {
		bool undoSuccessfully = this->service.Undo(mode);
		if (!undoSuccessfully)
		{
			QMessageBox::critical(this, "Error", "Nothing to undo.");
		}
		else {
			if(this->mode == "admin")
				emit this->initChart();
			emit this->initEvents();
		}
	});

	QObject::connect(this->redoButton, &QPushButton::clicked, this, [this]() {
		bool redoSuccessfully = this->service.Redo(mode);
		if (!redoSuccessfully)
		{
			QMessageBox::critical(this, "Error", "Nothing to redo.");
		}
		else {
			if (this->mode == "admin")
				emit this->initChart();
			emit this->initEvents();
		}
	});

	QObject::connect(this->undoShortcut, &QShortcut::activated, this, [this]() {
		emit this->undoButton->clicked();
	});

	QObject::connect(this->redoShortcut, &QShortcut::activated, this, [this]() {
		emit this->redoButton->clicked();
	});
}

int GUI::getPosition(QListWidget *listWidget, int Case)
{
	/// <summary>
	/// This function will return the selected index of a given listWidget
	/// </summary>
	/// <param name="listWidget">A listWidget</param>
	/// <param name="Case">A case that can be either 1 or 2, 1 for admin mode, 2 for user mode</param>
	/// <returns></returns>
	QModelIndexList all_indexes = listWidget->selectionModel()->selectedIndexes();

	if (all_indexes.size() == 0) {
		this->clearLines(Case);
		return -1;
	}
	int index = all_indexes.at(0).row();

	return index;
}

void GUI::listEvent(int position)
{
	/// <summary>
	/// This function will be called only in user mode. It will fill the listingEventsWidget
	/// with the element that is on the position 'current_index'
	/// </summary>
	/// <param name="position">The position of an element in the list.</param>
	string month = this->monthLineEdit->text().toStdString();
	this->listingEventsWidget->clear();
	try {
		vector<Event> filteredEvents(this->service.getRepo("admin").size());
		if (month.empty())
			filteredEvents = this->service.seeAllEvents("admin");
		else
			filteredEvents = this->service.filterEvents(filteredEvents, month, "admin");
		if (this->current_index+1 > filteredEvents.size()) {
			if (this->current_index > 0)
				this->current_index = 0;
			else
				throw ImplementedException("There are no events in that month.");
		}
		Event events = filteredEvents[this->current_index];
		string row = events.getTitle() + " - " + events.getDescription() + " - " + events.getDate().toString() + " - " + to_string(events.getPeopleNr()) + " - " + events.getLink();
		string command = "start " + events.getLink();
		system(command.c_str());
		this->listingEventsWidget->addItem(QString::fromStdString(row));
	}
	catch (ImplementedException& e) {
		QMessageBox::critical(this, "Error", "Invalid month entered.");
		this->monthLineEdit->clear();
		this->nextButton->setVisible(false);
		this->exitButton->setVisible(false);
	}
}

void GUI::addEvent()
{
	/// <summary>
	/// This function will be called only in the admin mode.
	/// It will convert the data from the QLineEdits, and try to add the event corresponding to the data.
	/// </summary>
	string title = this->titleLineEdit->text().toStdString();
	string description = this->descriptionLineEdit->text().toStdString();
	string date = this->dateLineEdit->text().toStdString();
	string link = this->linkLineEdit->text().toStdString();
	string people = this->peopleLineEdit->text().toStdString();

	try {
		int ppl = stoi(people);
		Date d{ date };

		if (!this->service.addService(title, description, d, ppl, link, "admin")) {
			throw ImplementedException("The Event is already registered.");
		}

		this->initEvents();
		this->clearLines(1);
		emit this->initChart();
	}
	catch (ImplementedException& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", "There is an error, that could be caused by an empty field/invalid input.");
	}

}

void GUI::deleteEvent()
{
	/// <summary>
	/// This function will be called only in the admin mode.
	/// It will convert the data from the QLineEdits, and try to delete the event corresponding to the data.
	/// </summary>
	string title = this->titleLineEdit->text().toStdString();
	string description = this->descriptionLineEdit->text().toStdString();
	string date = this->dateLineEdit->text().toStdString();
	string link = this->linkLineEdit->text().toStdString();
	string people = this->peopleLineEdit->text().toStdString();

	try {
		if(title.empty() || description.empty() || date.empty() || link.empty() || people.empty())
			throw ImplementedException("Invalid input data.");

		int ppl = stoi(people);
		Date d{ date };
		Event ev{ title, description, d, ppl, link };
		if (!this->service.getRepo(mode).search(ev)) {
			throw ImplementedException("Invalid input data.");
		}
		this->service.deleteService(title, mode);

		this->initEvents();
		this->clearLines(1);
        emit this->initChart();
	}
	catch (ImplementedException& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", "There is an error, that could be caused by an empty field/invalid input.");
	}
}

void GUI::updateEvent()
{
	string title = this->titleLineEdit->text().toStdString();
	string description = this->descriptionLineEdit->text().toStdString();
	string date = this->dateLineEdit->text().toStdString();
	string link = this->linkLineEdit->text().toStdString();
	string people = this->peopleLineEdit->text().toStdString();

	try {
		if (title.empty() || description.empty() || date.empty() || link.empty() || people.empty())
			throw ImplementedException("Invalid input data.");

		int ppl = stoi(people);
		Date d{ date };
		if (!this->service.updateService(title, "date", d, ppl, mode)) {
			throw ImplementedException("An error has occured during saving!.");
		}

		this->initEvents();
		this->clearLines(1);
        emit this->initChart();
	}
	catch (ImplementedException& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", "There is an error, that could be caused by an empty field/invalid input.");
	}
}

// This function will clear the lines if we are in the admin mode.
// The case is 1 if we are in admin mode/ 2 if we are in user mode
void GUI::clearLines(int Case)
{
	if (Case == 1) {
		this->titleLineEdit->clear();
		this->descriptionLineEdit->clear();
		this->linkLineEdit->clear();
		this->dateLineEdit->clear();
		this->peopleLineEdit->clear();
	}
}

void GUI::clearLayout(QLayout* layout)
{
	// This function will clear an entire layout.
	while (layout->count() > 0)
	{
		QLayoutItem* item = layout->takeAt(0);

		QWidget* widget = item->widget();
		if (widget)
		{
			widget->deleteLater();
		}
		else
		{
			QLayout* layout = item->layout();
			if (layout)
			{
				clearLayout(layout);
				layout->deleteLater();
			}
		}
		delete item;
	}
}
