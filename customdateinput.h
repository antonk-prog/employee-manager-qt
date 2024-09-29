#ifndef CUSTOMDATEINPUT_H
#define CUSTOMDATEINPUT_H
#include <QWidget>
#include <QDate>
class QLineEdit;
class QPushButton;

class Custom_date_input : public QWidget
{
public:
    // void Employee::set_birth_date(const QDate &birthDate) {
    //     this->birth_date = birthDate;
    // }
    QLineEdit * dayEdit;
    QLineEdit * monthEdit;
    QLineEdit * yearEdit;
    QPushButton * setDateButton;
    QDate date;
    Custom_date_input(QWidget * parent = nullptr);
    QDate& get_date();
    void set_date(const QDate & date);
public slots:


};

#endif // CUSTOMDATEINPUT_H
