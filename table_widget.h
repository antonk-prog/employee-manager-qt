#ifndef TABLE_WIDGET_H
#define TABLE_WIDGET_H

#include "employeelistwidget.h"
#include <QTableWidget>

class Table_widget : public QWidget
{
    Q_OBJECT
private:
    QStringList headers;
    QTableWidget* table;
    Employee_list_widget* list_widget;
public:
    Table_widget(QWidget *parent = nullptr);
    void set_contents_and_update(Employee_list_widget* employee_list_widget);
    ~Table_widget();

};
#endif // MY_TABLE_WIDGET_H
