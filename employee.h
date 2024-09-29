#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QtWidgets>

class Employee {
public:
    Employee(const QString&second_name="",
             const QString&first_name="",
             const QString&third_name="",
             const QString&titul="",
             const QDate& birth_date=QDate(),
             const QDate & company_start_date=QDate(),
             qint32 work_experience=0,
             const QString&job_title="",
             qint32 salary=0,
             const QString& reason_fire = "",
             const QString& image_path = ""
             );
    ~Employee();
    void print_employee();
    // геттеры
    QString& get_first_name();
    QString& get_second_name();
    QString& get_third_name();
    QString& get_titul();
    QDate& get_birth_date();
    QDate& get_company_start_date();
    qint32& get_work_experience();
    QString& get_job_title();
    qint32&  get_salary();
    QString& get_reason_fire();
    QString& get_image_path();

    QString get_first_name() const;
    QString get_second_name() const;
    QString get_third_name() const;
    QString get_titul() const;
    QDate get_birth_date() const;
    QDate get_company_start_date() const;
    qint32 get_work_experience() const;
    QString get_job_title() const;
    qint32  get_salary() const;
    QString get_reason_fire() const;
    QString get_image_path() const;

    friend bool operator==(const Employee& lhs, const Employee&rhs);

    // сеттеры
    void set_first_name(const QString& firstName);

    void set_second_name(const QString& secondName);

    void set_third_name(const QString& thirdName);

    void set_titul(const QString& titul);

    void set_birth_date(const QDate& birthDate);

    void set_company_start_date(const QDate& companyStartDate);

    void set_work_experience(qint32 workExperience);

    void set_job_title(const QString& jobTitle);

    void set_salary(qint32 salary);

    void set_reason_fire(QString text);

    void set_image_path(const QString& image_path);


    // QByteArray serialize() const;

    // Employee deserialize(const QByteArray & data);

    int get_my_id() {
        return my_id;
    }



private:
    int my_id = 0;



    QString first_name;
    QString second_name;
    QString third_name;
    QString titul;
    QDate birth_date;
    QDate company_start_date;
    qint32 work_experience;
    QString job_title;
    QString reason_fire;
    qint32 salary;
    QString image_path;

    QByteArray data;

};

QDataStream & operator>>(QDataStream&in, Employee& employee);
QDataStream & operator<<(QDataStream&in, Employee& employee);

QDialog* createCustomDialog(QString text, QWidget* parent = nullptr);
#endif // EMPLOYEE_H
