#include "table_widget.h"
#include <QLabel>
#include <QStringList>
#include <QPushButton>

Table_widget::Table_widget(QWidget *parent) : QWidget(parent)
{

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    table = new QTableWidget(1, 10, centralWidget);
    table->setRowCount(5);
    table->setColumnCount(11);

    // Set headers
    headers << "Фамилия" << "Имя" << "Отчество" << "Титул"
            << "Дата рождения" << "Начало работы" << "Лет в компании"
            << "Опыт работы" << "Должность" << "Зарплата" << "Причина увольнения\n(если есть)";
    table->setHorizontalHeaderLabels(headers);

    layout->addWidget(table);
    layout->addWidget(centralWidget);

    table->setMinimumWidth(1200);
    table->setMinimumHeight(600);

    this->setGeometry(0, 0, 1200, 600);
}
Table_widget::~Table_widget() {}

void Table_widget::set_contents_and_update(Employee_list_widget* list)
{
    //table->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < list->count(); i++)
    {
        QListWidgetItem * here_item = list->item(i);
        QVariant here_item_data = here_item->data(Qt::UserRole);
        if (here_item_data.canConvert<Employee>()){
            Employee employee = here_item_data.value<Employee>();
            table->insertRow(table->rowCount());
            table->setItem(i, 0, new QTableWidgetItem(QString(employee.get_first_name())));
            table->setItem(i, 1, new QTableWidgetItem(QString(employee.get_second_name())));
            table->setItem(i, 2, new QTableWidgetItem(QString(employee.get_third_name())));
            table->setItem(i, 3, new QTableWidgetItem(QString(employee.get_titul())));
            table->setItem(i, 4, new QTableWidgetItem(QString(employee.get_birth_date().toString("dd.MM.yyyy"))));
            table->setItem(i, 5, new QTableWidgetItem(QString(employee.get_company_start_date().toString("dd.MM.yyyy"))));
            table->setItem(i, 7, new QTableWidgetItem(QString::number(employee.get_work_experience())));
            table->setItem(i, 6, new QTableWidgetItem(QString::number(static_cast<int>((employee.get_company_start_date().daysTo(QDate().currentDate())) / 365.25))));
            table->setItem(i, 8, new QTableWidgetItem(QString(employee.get_job_title())));
            table->setItem(i, 9, new QTableWidgetItem(QString::number(employee.get_salary())));
            table->setItem(i, 10, new QTableWidgetItem(QString(employee.get_reason_fire())));
        }
    }
}
