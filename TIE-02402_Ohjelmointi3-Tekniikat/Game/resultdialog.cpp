#include "resultdialog.hh"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent, std::list<std::string>& results) :
    QDialog(parent),
    ui(new Ui::ResultDialog),
    results_(results)
{
    ui->setupUi(this);
    for (std::string data : results)
    {
        QLabel* label = new QLabel(this);

        int pos = data.find(">");
        std::string points = data.substr(pos+1);
        std::string name = data.substr(0, pos);

        label->setText(QString::fromStdString(name + ": " + points));
        ui->verticalLayout->addWidget(label);
    }
}

ResultDialog::~ResultDialog()
{
    delete ui;
}
