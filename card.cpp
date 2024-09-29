#include "card.h"
#include "cardfire.h"
#include "editcard.h"
Card::Card(QWidget *parent)
{

    QVBoxLayout * vertical_layout = new QVBoxLayout();
    QHBoxLayout* common_layout = new QHBoxLayout(parent);
    QHBoxLayout * button_layout = new QHBoxLayout();
    image_container = new QLabel();
    info = new QLabel();
    info_fired = new QLabel();

    common_layout->addWidget(info);
    vertical_layout->addWidget(info_fired);
    common_layout->addWidget(image_container);

    vertical_layout->addLayout(common_layout);

    vertical_layout->addWidget(delete_button);


    delete_button = new QPushButton("Удалить");
    fire_button = new QPushButton("Уволить");
    edit_button = new QPushButton("Редактировать");
    button_layout->addWidget(delete_button);
    button_layout->addWidget(fire_button);
    button_layout->setStretchFactor(delete_button, 3);
    button_layout->setStretchFactor(fire_button, 1);

    vertical_layout->addLayout(common_layout);
    vertical_layout->addWidget(edit_button);
    vertical_layout->addLayout(button_layout);
    this->setLayout(vertical_layout);

    connect(delete_button, &QPushButton::clicked, this, &Card::on_delete_button_clicked);
    connect(fire_button, &QPushButton::clicked, this, &Card::on_fire_button_clicked);
    connect(edit_button, &QPushButton::clicked, this, &Card::on_clicked_edit_button);
}

void Card::set_contents(Employee* employee)
{
    current_employee = *employee;
    double years_difference = static_cast<double>((employee->get_birth_date().daysTo(QDate().currentDate()))) / 365.25;
    double years_in_company = static_cast<double>((employee->get_company_start_date().daysTo(QDate().currentDate()))) / 365.25;

    QString formed_info =
        "Имя: " + employee->get_first_name() + "\n" +
        "Фамилия: " + employee->get_second_name() + "\n" +
        "Отчество: " +employee->get_third_name() + "\n" +
        "Титул: " + employee->get_titul() + "\n" +

        "Дата рождения: " + employee->get_birth_date().toString("dd.MM.yyyy") + "(" + QString::number((int)years_difference) + ")" + "\n" +
        "Дата начала работы: " + employee->get_company_start_date().toString("dd.MM.yyyy") + "\n" +
        "Лет в компании: " + QString::number((int)years_in_company) + '\n' +
        "Опыт работы: " + QString::number(employee->get_work_experience()) + "\n" +
        "Должность: " + employee->get_job_title() + "\n" +
        "Зарплата: " + QString::number(employee->get_salary()) + " руб.";
    info->setText(formed_info);
    if (employee->get_reason_fire() != "")
    {
        info_fired->setText("<font color='red'>Причина увольнения: " + QString(employee->get_reason_fire()) + "</font>");
    }
    else info_fired->setText("");
    QPixmap image(100, 100);
    if(image.load(employee->get_image_path()))
    {
        image = image.scaled(QSize(100, 100),Qt::KeepAspectRatio);
    }
    else
    {
        image.fill(Qt::white);
    }
    image_container->setPixmap(image);
}

void Card::on_delete_button_clicked() {
    this->hide();
    emit on_delete_button_signal(current_employee);
}

void Card::on_fire_button_clicked()
{
    card_fire = new Card_fire();
    card_fire->show();
    connect(card_fire, &Card_fire::send_reason_fire_when_clicked, this, &Card::on_get_reason_fire);
    emit on_fire_button_signal();
}

void Card::on_get_reason_fire(QString reason_fire)
{
    current_employee.set_reason_fire(reason_fire);
    emit send_employee_with_reason_fire(current_employee);
    current_employee.print_employee();
    card_fire->close();
    this->close();
}

void Card::on_clicked_edit_button()
{
    edit_card = new Edit_card();
    edit_card->show();
    connect(this, &Card::send_employee_edit_button, edit_card, &Edit_card::on_get_employee);
    emit send_employee_edit_button(current_employee);
    connect(edit_card, &Edit_card::send_employee_to_delete, this, &Card::on_employee_to_delete);
    connect(edit_card, &Edit_card::save_button_clicked_signal, this, &Card::on_save_button_send);

}

void Card::on_employee_to_delete(Employee employee)
{
    emit send_employee_to_delete(employee);
}

void Card::on_save_button_send(Employee employee)
{
    emit send_save_employee(employee);
    edit_card->close();
    this->close();
}
