#include "GUI.h"

GUI::GUI(Service& service) : service{ service }
{
    this->mainLayout = new QVBoxLayout{ this };
    this->initGUI();
    this->initChecks();
    this->makeConnections();

}

void GUI::initGUI()
{
    this->list = new QListWidget{};
    btnBack = new QPushButton{ "Back" };
    this->Slider = new QSlider{ Qt::Horizontal };
    this->Slider->setValue(100);


    this->mainLayout->addWidget(list);
    this->mainLayout->addWidget(btnBack);
    this->mainLayout->addWidget(Slider);
    
    vector<string> desc;
    this->updateDesc(desc);

}

void GUI::clearLayout()
{
    this->Slider->setValue(100);
    this->sliderValue = 0;

    for (auto& d : checks) {
        d->setChecked(false);
    }
    
    vector<string> desc;
    emit this->updateDesc(desc);
}

void GUI::makeConnections()
{
    for (int i = 0; i < checks.size(); i++) {
        QObject::connect(this->checks[i], &QCheckBox::stateChanged, this, [this]() {
            vector<string> descrs;
            for (auto& btns : checks) {
                if (btns->isChecked()) {
                    descrs.push_back(btns->text().toStdString());
                }
            }

            emit this->updateDesc(descrs);

        });
    }

    QObject::connect(this->Slider, &QSlider::valueChanged, this, &GUI::change);

    QObject::connect(this->btnBack, &QPushButton::clicked, this, [this]() {
        emit this->clearLayout(); 
    });

}

void GUI::initWeathers()
{
    this->list->clear();
    vector<Weather> ws = this->service.allWeathers();
    for (auto& w : ws) {
        string l = w.getStarting() + " | " + w.getEnding() + " | " + w.getPrec() + " |-" + w.getDesc() + " | ";
        this->list->addItem(QString::fromStdString(l));
    }


}

void GUI::initChecks()
{
    vector<string> desc = this->service.getDiffDesc();
    QFormLayout* form = new QFormLayout{};
    for (auto& d : desc) {
        QCheckBox* check = new QCheckBox{ QString::fromStdString(d) };
        check->setChecked(true);
        checks.push_back(check);
        form->addWidget(check);
    }

    this->updateDesc(desc);
    this->mainLayout->addLayout(form);

}

void GUI::filterWeathers()
{
    this->list->clear();
    vector<Weather> ws = this->service.allWeathers();
    for (auto& w : ws) {
        if (stoi(w.getPrec()) < this->sliderValue) {
            string l = w.getStarting() + " | " + w.getEnding() + " | " + w.getPrec() + " | " + w.getDesc() + " | ";
            this->list->addItem(QString::fromStdString(l));
        }
    }
}

void GUI::updateDesc(vector<string> desc)
{
    this->list->clear();

    vector<Weather> ws = this->service.allWeathers();
    for (auto& w : ws) {
        bool found = false;

        for (int i = 0; i < desc.size() && found == false; i++) {
            if (w.getDesc() == desc[i])
                found = true;
        }

        if (found == true && stoi(w.getPrec()) < this->sliderValue) {
            string l = w.getStarting() + " | " + w.getEnding() + " | " + w.getPrec() + " | " + w.getDesc() + " | ";
            this->list->addItem(QString::fromStdString(l));
        }
    }
    
}



void GUI::change()
{

    vector<string> descrs;
    for (auto& btns : checks) {
        if (btns->isChecked()) {
            descrs.push_back(btns->text().toStdString());
        }
    }

    this->sliderValue = this->Slider->value();

    this->updateDesc(descrs);

}

