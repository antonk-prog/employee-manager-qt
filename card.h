#ifndef CARD_H
#define CARD_H
#include <QWidget>
#include <employee.h>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
class Card_fire;
class Edit_card;
class Card : public QWidget

{
    Q_OBJECT
public:
    Card(QWidget * parent = nullptr);

    void set_contents(Employee* employee);
    void update(Employee* employee);
private:
    QPushButton * delete_button;
    QPushButton * fire_button;
    QPushButton * edit_button;
    QLabel* info;
    QLabel* info_fired;
    QLabel* image_container;
    Card_fire * card_fire;
    Edit_card * edit_card;
    Employee current_employee;


    //QString img_src;

signals:
    void on_delete_button_signal(Employee employee);
    void on_fire_button_signal();
    void send_employee_with_reason_fire(Employee employee);
    void send_employee_edit_button(Employee employee);
    void send_employee_to_delete(Employee employee);
    void send_save_employee(Employee employee);
public slots:
    void on_delete_button_clicked();
    void on_fire_button_clicked();
    void on_get_reason_fire(QString reason_fire);
    void on_clicked_edit_button();
    void on_employee_to_delete(Employee employee);
    void on_save_button_send(Employee employee);
};

#endif // CARD_H
