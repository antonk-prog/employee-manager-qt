#include "employeelistwidget.h"

// Employee_list_widget::Employee_list_widget() {

// }

Employee_list_widget::Employee_list_widget(QWidget *parent) : QListWidget(parent){
    if (!employee_manager.read_gaps_binary()) {
        employee_manager.write_gaps_binary();
    }
    employee_manager.read_people();

    // для проверки на превышение количества добавлений при генерации
    update_list_widget();


}

QList<QListWidgetItem *> Employee_list_widget::find_items(const QString &text, int flag)
{
    QList<QListWidgetItem*> founded_items;

    for (int i = 0; i < count(); i++){
        QListWidgetItem * here_item = item(i);
        QVariant here_item_data = here_item->data(Qt::UserRole);
        if (here_item_data.canConvert<Employee>()){
            Employee employee = here_item_data.value<Employee>();
            if (flag == search_flags::only_name){
                if (employee.get_first_name().toLower() == text.toLower()){
                    founded_items.append(here_item);
                }
            }
            if (flag == search_flags::only_surname) {
                if (employee.get_second_name().toLower() == text.toLower()){
                    founded_items.append(here_item);
                }
            }
            if (flag == search_flags::only_patronymic) {
                if (employee.get_third_name().toLower() == text.toLower()){
                    founded_items.append(here_item);
                }
            }
            if (flag == search_flags::only_titul) {
                if (employee.get_job_title().toLower() == text.toLower()){
                    founded_items.append(here_item);
                }
            }

        }
    }
    return founded_items;

}


void Employee_list_widget::on_show_all_button_clicked()
{
    update_list_widget();
}

void Employee_list_widget::on_click_delete_button(Employee employee)
{
    for (int i = 0; i < count(); i++){
        QVariant data_item = item(i)->data(Qt::UserRole);
        if (data_item.canConvert<Employee>()){
            Employee employee_list = data_item.value<Employee>();
            if (employee_list == employee){
                takeItem(i);
                employee_manager.delete_employee_binary_database(employee);
            }
        }
    }
    QDialog * dialog = createCustomDialog("Работник успешно удален");
    dialog->exec();
    delete dialog;
}

void Employee_list_widget::on_click_fire_button(Employee employee)
{
    employee_manager.write_fired_employee(employee);
    update_list_widget();
}

void Employee_list_widget::on_send_employee_slot(Employee employee)
{
    employee_manager.add_binary_database(employee);
    update_list_widget();

}

void Employee_list_widget::update_list_widget()
{
    if (count() != 0){
        clear();
    }
    QList<QListWidgetItem*> read_data = employee_manager.read_binary_database();
    QVector<QListWidgetItem*> fired_employees;
    for (int i = 0; i < read_data.size(); i++){
        QVariant data_item = read_data[i]->data(Qt::UserRole);
        if (data_item.canConvert<Employee>()){
            Employee employee_list = data_item.value<Employee>();
            if (employee_list.get_reason_fire().size() == 0){
                addItem(read_data[i]);
            } else {
                fired_employees.append(read_data[i]);
            }

        }

    }
    if (!fired_employees.empty()){
        for (int i = 0; i < fired_employees.size(); i++){
            addItem(fired_employees[i]);
        }
    }
}

void Employee_list_widget::on_click_generate_button()
{

    if (employee_manager.write_and_generate_random_info()) {

        update_list_widget();
    } else {
        qDebug() << "fd";
        QDialog * dialog = createCustomDialog("Увеличьте базу данных фио. Больше нельзя сгенерировать новые данные");
        dialog->exec();
        delete dialog;
    }
}

void Employee_list_widget::delete_employee(Employee employee)
{
    employee_manager.delete_employee_binary_database(employee);
}
