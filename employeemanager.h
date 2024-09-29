#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H
#include <QObject>
#include "employee.h"
#include <QVector>
#include <QMap>


class Employee_manager : public QObject
{
    Q_OBJECT
public:

    Employee_manager();
    ~Employee_manager();
    void create_binary_database();
    QList<QListWidgetItem*> read_binary_database();
    bool add_binary_database(Employee employee);
    void delete_employee_binary_database(Employee employee);
    int find_employee_binary_database(Employee employee);
    QVector<int> find_employees_with_attrs(QMap<QString, QVariant> &attrs);
    void write_fired_employee(Employee employee);
    void write_binary_database(QList<QListWidgetItem*> write_data);
    bool write_and_generate_random_info();
    void write_gaps_binary();
    bool read_gaps_binary();
    void compress_gaps();
    void print_binary_database();
    void read_people();
private:
    QVector<int> gaps_indexes;
    QSet<QString> all_names;
    int all_people_file_count;
signals:
    void employees_changed();
};



#endif // EMPLOYEEMANAGER_H
