#ifndef EDITCARD_H
#define EDITCARD_H
#include <QWidget>
#include "employee.h"
class QLabel;
class QLineEdit;
class QDateEdit;
class QSpinBox;
class QPushButton;
class Custom_date_input;
class Edit_card : public QWidget
{
    Q_OBJECT
public:
    Edit_card(QWidget * parent=nullptr);
public slots:
    void on_save_button_clicked();
    void on_button_image_path_clicked();
    void on_get_employee(Employee employee);
signals:
    void save_button_clicked_signal(Employee employee);
    void send_employee_to_delete(Employee employee);
private:
    QLabel * label_first_name;
    QLineEdit * line_edit_first_name;
    QLabel * label_second_name;
    QLineEdit * line_edit_second_name;
    QLabel * label_third_name;
    QLineEdit * line_edit_third_name;
    QLabel * label_titul;
    QLineEdit * line_edit_titul;
    QLabel * label_birth_date;
    Custom_date_input * edit_birth_date;
    QLabel * label_company_start_date;
    Custom_date_input * edit_company_start_date;
    QLabel * label_work_experience;
    QSpinBox * spin_box_experience;
    QLabel * label_job_title;
    QLineEdit * line_edit_job_title;
    QLabel * label_salary;
    QLineEdit * line_edit_salary;
    QPushButton * button_image_path;
    QLabel * label_image_path;
    QLabel * label_image;
    QPushButton * save_button;
    Employee current_employee;
};

#endif // EDITCARD_H
