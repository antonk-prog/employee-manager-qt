#include "customdateinput.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpressionValidator>
Custom_date_input::Custom_date_input(QWidget * parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);


    dayEdit = new QLineEdit(this);
    dayEdit->setPlaceholderText("дд");
    dayEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])$"), this));
    monthEdit = new QLineEdit(this);
    monthEdit->setPlaceholderText("мм");
    monthEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^(0[1-9]|1[0-2])$"), this));
    yearEdit = new QLineEdit(this);
    yearEdit->setPlaceholderText("гггг");
    yearEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^(19[0-9]{2}|20[0-2][0-9]|202[0-3])$"), this));

    layout->addWidget(dayEdit);
    layout->addWidget(monthEdit);
    layout->addWidget(yearEdit);


    setLayout(layout);

}

QDate& Custom_date_input::get_date()
{
    return date;
}

void Custom_date_input::set_date(const QDate& date) {
    this->date = date;
    this->dayEdit->setText(QString::number(date.day()));
    this->monthEdit->setText(QString::number(date.month()));
    this->yearEdit->setText(QString::number(date.year()));

}


