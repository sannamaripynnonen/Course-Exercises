#include "startdialog.hh"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->useTimeButton, &QPushButton::clicked, this, &StartDialog::useGivenTime);
    QObject::connect(ui->useTimeButton, &QPushButton::clicked, this, &StartDialog::accept);

    QObject::connect(ui->useDefaultButton, &QPushButton::clicked, this, &StartDialog::useDefault);
    QObject::connect(ui->useDefaultButton, &QPushButton::clicked, this, &StartDialog::reject);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::useGivenTime()
{
    useName();
    int minutes = ui->minutesSpinBox->value();
    int seconds = ui->secondsSpinBox->value();
    if ((minutes == 0 && seconds < 5) || minutes > 5)
    {
        minutes = 2;
    }
    emit gameTimeGiven(seconds, minutes);
}

void StartDialog::useDefault()
{
    useName();
    int minutes = 0;
    int seconds = 30;
    emit gameTimeGiven(seconds, minutes);
}

void StartDialog::useName()
{
    QString name = ui->nameLineEdit->text();
    int maxLength = 15;
    if (name.length() == 0 || name.length() > maxLength || name.toStdString().find('>') != std::string::npos)
    {
        QString defaultName = "anonymous";
        emit nameGiven(defaultName);
    }
    else
    {
        emit nameGiven(name);
    }
}
