#ifndef EMPLOYEELISTWIDGET_H
#define EMPLOYEELISTWIDGET_H
#include "employeemanager.h"
#include "special.h" // перенести в cpp не забыть
#include <QListWidget>

class Employee_list_widget : public QListWidget
{
    Q_OBJECT
public:
    enum search_flags {only_name, only_surname, only_patronymic, only_titul};
    explicit Employee_list_widget(QWidget *parent = nullptr);
    QList<QListWidgetItem*> find_items(const QString & text, int flag);
public slots:
    void on_show_all_button_clicked();
    void on_click_delete_button(Employee employee);
    void on_click_fire_button(Employee employee);
    void on_send_employee_slot(Employee employee);
    void update_list_widget();
    void on_click_generate_button();
    void delete_employee(Employee employee);
private:
    // search_flags search_flag;
    Employee_manager employee_manager;

};
#endif // EMPLOYEELISTWIDGET_H
