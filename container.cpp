#include "container.h"
#include "card.h"
#include "employeelistwidget.h"
#include <QListWidgetItem>
#include <QComboBox>
#include <QMessageBox>


Container::Container(QWidget *parent)
    : QWidget{parent}
{
    current_search_combo_box=0;
    QVBoxLayout * common_layout = new QVBoxLayout();


    employee_list_widget = new Employee_list_widget();

    search_button = new QPushButton("Найти");
    show_all_button = new QPushButton("Показать всех");
    add_button = new QPushButton("Добавить работника");
    button_generate_employees = new QPushButton("Сгенерировать");
    search_line_edit = new QLineEdit();
    search_combo_box = new QComboBox();
    button_open_as_table = new QPushButton("Открыть в виде таблицы");

    card = new Card();
    card->hide();
    QStringList lst;
    lst << "Имя" << "Фамилия" << "Отчество" << "Должность";
    search_combo_box->addItems(lst);
    QHBoxLayout * top_layout = new QHBoxLayout();
    QHBoxLayout * bottom_layout = new QHBoxLayout();
    top_layout->addWidget(search_line_edit);
    top_layout->addWidget(search_combo_box);

    top_layout->addWidget(search_button);
    top_layout->addWidget(show_all_button);
    common_layout->addLayout(top_layout);
    bottom_layout->addWidget(add_button);
    bottom_layout->addWidget(button_generate_employees);
    bottom_layout->setStretchFactor(add_button, 7);
    bottom_layout->setStretchFactor(button_generate_employees, 1);
    common_layout->addWidget(employee_list_widget);
    common_layout->addLayout(bottom_layout);
    common_layout->addWidget(button_open_as_table);


    connect(employee_list_widget, &Employee_list_widget::itemDoubleClicked, this, &Container::on_item_double_clicked);
    connect(search_button, &QPushButton::clicked, this, &Container::on_search_button_clicked);
    connect(search_combo_box, &QComboBox::currentIndexChanged, this, &Container::on_search_combo_box_changed);
    connect(show_all_button, &QPushButton::clicked, employee_list_widget, &Employee_list_widget::on_show_all_button_clicked);
    connect(card, &Card::on_delete_button_signal, employee_list_widget, &Employee_list_widget::on_click_delete_button);
    connect(add_button, &QPushButton::clicked, this, &Container::on_add_button_clicked);
    connect(this, &Container::on_add_button_send_employee, employee_list_widget, &Employee_list_widget::on_send_employee_slot);
    connect(button_generate_employees, &QPushButton::clicked, employee_list_widget, &Employee_list_widget::on_click_generate_button);
    connect(card, &Card::send_employee_with_reason_fire, employee_list_widget, &Employee_list_widget::on_click_fire_button);
    connect(card, &Card::send_employee_to_delete, employee_list_widget, &Employee_list_widget::delete_employee);
    connect(card, &Card::send_save_employee, employee_list_widget, &Employee_list_widget::on_send_employee_slot);
    connect(button_open_as_table, &QPushButton::clicked, this, &Container::on_button_show_as_table_clicked);
    this->setLayout(common_layout);
}

void Container::on_item_double_clicked(QListWidgetItem *item)
{
    QVariant employeeData = item->data(Qt::UserRole);
    if (employeeData.canConvert<Employee>()){
        Employee employee = employeeData.value<Employee>();
        card->set_contents(&employee);
        card->show();
    //     qDebug() << employee.get_first_name() << " "
    //              << employee.get_second_name() << " "
    //              << employee.get_third_name() << " ";
    //     qDebug() << employee.get_birth_date() << " "
    //              << employee.get_company_start_date();
    //     qDebug() << employee.get_titul() << " "
    //              << employee.get_salary();
    // }
    }
}

void Container::on_search_button_clicked()
{
    QString searching_text = search_line_edit->text();
    // поменять Qt::MatchExactly
    qDebug() << "here";
    qDebug() << current_search_combo_box;
    QList<QListWidgetItem *> list_founded_items = employee_list_widget->find_items(searching_text, current_search_combo_box);

    QList<QListWidgetItem*> copies_list_founded_items;
    for (int i = 0; i < list_founded_items.size(); i++){
        QListWidgetItem * new_item = new QListWidgetItem(*list_founded_items[i]);
        copies_list_founded_items.append(new_item);
    }
    if (list_founded_items.size() != 0){
        for (int i = 0; i < list_founded_items.size(); i++){
            qDebug() << list_founded_items[i]->text();
        }
        employee_list_widget->clear();
        for (int i = 0; i < copies_list_founded_items.size(); i++){
            employee_list_widget->addItem(copies_list_founded_items[i]);
        }
        // for (int i = 0; i < list_founded_items.size(); i++){
        //     employee_list_widget->addItem(list_founded_items[i]);
        // }
    } else {
        QDialog * dialog = createCustomDialog("Работник не найден.");
        dialog->exec();
        delete dialog;
    }

}

void Container::on_search_combo_box_changed(int index)
{
    current_search_combo_box = index;
}

void Container::on_add_button_clicked()
{
    adding_card = new Adding_card();
    adding_card->show();
    connect(adding_card, &Adding_card::on_add_button_clicked_signal, this, &Container::on_add_button_adding_card_clicked);
    connect(adding_card, &Adding_card::on_add_button_clicked_signal, this, &Container::on_adding_card_closed);
}

void Container::on_add_button_adding_card_clicked(Employee employee)
{
    emit on_add_button_send_employee(employee);
}

void Container::on_adding_card_closed()
{
    adding_card->close();
}

void Container::on_button_show_as_table_clicked()
{
    table_widget = new Table_widget();
    table_widget->set_contents_and_update(employee_list_widget);
    table_widget->show();
}
