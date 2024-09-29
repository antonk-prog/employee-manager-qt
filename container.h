#ifndef CONTAINER_H
#define CONTAINER_H
#include "addingcard.h"
#include "table_widget.h"
#include <QWidget>
class Card;
class QPushButton;
class QLineEdit;
class Employee_list_widget;
class QListWidgetItem;
class QComboBox;
class Container : public QWidget
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);
public slots:
    void on_item_double_clicked(QListWidgetItem * item);
    void on_search_button_clicked();
    void on_search_combo_box_changed(int index);
    void on_add_button_clicked();
    void on_add_button_adding_card_clicked(Employee employee);
    void on_adding_card_closed();
    void on_button_show_as_table_clicked();
signals:
    void on_add_button_send_employee(Employee employee);
private:
    Employee_list_widget * employee_list_widget;
    QPushButton * search_button;
    QPushButton * show_all_button;
    QLineEdit * search_line_edit;
    QComboBox * search_combo_box;
    QPushButton * add_button;
    QPushButton * button_generate_employees;
    Card * card;
    Adding_card * adding_card;
    QPushButton * button_open_as_table;
    Table_widget * table_widget;

    int current_search_combo_box;

};

#endif // CONTAINER_H
