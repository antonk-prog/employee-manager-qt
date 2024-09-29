#include "addingcard.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QSpinBox>
#include <QValidator>
#include <QRegularExpressionValidator>

#include "customdateinput.h"
Adding_card::Adding_card(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(500);
    QVBoxLayout * common_layout = new QVBoxLayout();
    QHBoxLayout * hor_first_name = new QHBoxLayout();
    QHBoxLayout * hor_second_name = new QHBoxLayout();
    QHBoxLayout * hor_third_name  = new QHBoxLayout();
    QHBoxLayout * hor_titul  = new QHBoxLayout();
    QHBoxLayout * hor_birth_date  = new QHBoxLayout();
    QHBoxLayout * hor_company_start_date  = new QHBoxLayout();
    QHBoxLayout * hor_work_experience  = new QHBoxLayout();
    QHBoxLayout * hor_job_title  = new QHBoxLayout();
    QHBoxLayout * hor_salary  = new QHBoxLayout();
    QHBoxLayout * hor_image_path = new QHBoxLayout();


    QRegularExpression reg_expr_for_string("[a-zA-Zа-яА-Я]+");
    QRegularExpressionValidator * validator = new QRegularExpressionValidator(reg_expr_for_string);

    label_first_name = new QLabel("&Имя:");
    line_edit_first_name = new QLineEdit();
    label_first_name->setBuddy(line_edit_first_name);
    line_edit_first_name->setValidator(validator);

    label_second_name = new QLabel("&Фамилия");
    line_edit_second_name = new QLineEdit();
    label_second_name->setBuddy(line_edit_second_name);
    line_edit_second_name->setValidator(validator);

    label_third_name = new QLabel("&Отчество:");
    line_edit_third_name = new QLineEdit();
    label_third_name->setBuddy(line_edit_third_name);
    line_edit_third_name->setValidator(validator);

    label_titul = new QLabel("&Титул:");
    line_edit_titul = new QLineEdit();
    label_titul->setBuddy(line_edit_titul);

    label_birth_date = new QLabel("Дата рождения:");
    edit_birth_date = new Custom_date_input();

    label_company_start_date = new QLabel("Начал работать в компании:");
    edit_company_start_date = new Custom_date_input();

    label_work_experience = new QLabel("&Суммарный опыт работы");
    spin_box_experience = new QSpinBox();
    label_work_experience->setBuddy(spin_box_experience);

    label_job_title = new QLabel("До&лжность:");
    line_edit_job_title = new QLineEdit();
    label_job_title->setBuddy(line_edit_job_title);

    label_salary = new QLabel("&Зарплата:");
    line_edit_salary = new QLineEdit();
    QValidator * validator_int = new QIntValidator(1000, 1000000);

    button_image_path = new QPushButton("Выбрать изображение:");
    label_image_path = new QLabel();
    label_image_path->setBuddy(button_image_path);
    label_image = new QLabel();

    add_button = new QPushButton("Добавить работника");

    line_edit_salary->setValidator(validator_int);
    label_salary->setBuddy(line_edit_salary);


    hor_first_name->addWidget(label_first_name);
    hor_first_name->addWidget(line_edit_first_name);

    hor_second_name->addWidget(label_second_name);
    hor_second_name->addWidget(line_edit_second_name);

    hor_third_name->addWidget(label_third_name);
    hor_third_name->addWidget(line_edit_third_name);

    hor_titul->addWidget(label_titul);
    hor_titul->addWidget(line_edit_titul);

    hor_birth_date->addWidget(label_birth_date);
    hor_birth_date->addWidget(edit_birth_date);

    hor_company_start_date->addWidget(label_company_start_date);
    hor_company_start_date->addWidget(edit_company_start_date);

    hor_work_experience->addWidget(label_work_experience);
    hor_work_experience->addWidget(spin_box_experience);

    hor_job_title->addWidget(label_job_title);
    hor_job_title->addWidget(line_edit_job_title);

    hor_salary->addWidget(label_salary);
    hor_salary->addWidget(line_edit_salary);

    hor_image_path->addWidget(button_image_path);
    hor_image_path->addWidget(label_image_path);

    label_first_name->setFixedWidth(170);
    label_second_name->setFixedWidth(170);
    label_third_name->setFixedWidth(170);
    label_titul->setFixedWidth(170);
    label_birth_date->setFixedWidth(170);
    label_company_start_date->setFixedWidth(170);
    label_work_experience->setFixedWidth(170);
    label_job_title->setFixedWidth(170);
    label_salary->setFixedWidth(170);



    common_layout->addLayout(hor_first_name);
    common_layout->addLayout(hor_second_name);
    common_layout->addLayout(hor_third_name);
    common_layout->addLayout(hor_titul);
    common_layout->addLayout(hor_birth_date);
    common_layout->addLayout(hor_company_start_date);
    common_layout->addLayout(hor_work_experience);
    common_layout->addLayout(hor_job_title);
    common_layout->addLayout(hor_salary);
    common_layout->addLayout(hor_image_path);
    common_layout->addWidget(label_image);

    common_layout->addWidget(add_button);


    this->setLayout(common_layout);

    connect(add_button, &QPushButton::clicked, this, &Adding_card::on_add_button_clicked);
    connect(button_image_path, &QPushButton::clicked, this, &Adding_card::on_button_image_path_clicked);

}

void Adding_card::on_add_button_clicked()
{
    if (line_edit_first_name->text().size() == 0 ||
        line_edit_second_name->text().size() == 0 ||
        line_edit_third_name->text().size() == 0 ||
        line_edit_titul->text().size() == 0 ||
        line_edit_job_title->text().size() == 0 ||
        line_edit_salary->text().size() == 0 ||
        edit_birth_date->dayEdit->text().size() == 0 ||
        edit_birth_date->monthEdit->text().size() == 0 ||
        edit_birth_date->yearEdit->text().size() == 0 ||
        edit_company_start_date->dayEdit->text().size() == 0 ||
        edit_company_start_date->monthEdit->text().size() == 0 ||
        edit_company_start_date->yearEdit->text().size() == 0

        ) {
        QDialog * dialog = createCustomDialog("Все поля должны быть заполнены");
        dialog->exec();
        delete dialog;
    } else {

        Employee employee;
        employee.set_first_name(line_edit_first_name->text());
        employee.set_second_name(line_edit_second_name->text());
        employee.set_third_name(line_edit_third_name->text());
        employee.set_titul(line_edit_titul->text());
        edit_birth_date->date.setDate(edit_birth_date->yearEdit->text().toInt(),
                                       edit_birth_date->monthEdit->text().toInt(),
                                       edit_birth_date->dayEdit->text().toInt());
        employee.set_birth_date(edit_birth_date->get_date());
        edit_company_start_date->date.setDate(edit_company_start_date->yearEdit->text().toInt(),
                                               edit_company_start_date->monthEdit->text().toInt(),
                                               edit_company_start_date->dayEdit->text().toInt());
        employee.set_company_start_date(edit_company_start_date->get_date());
        employee.set_work_experience(spin_box_experience->value());
        employee.set_job_title(line_edit_job_title->text());
        employee.set_salary(line_edit_salary->text().toInt());
        employee.set_image_path(label_image_path->text());

        emit on_add_button_clicked_signal(employee);
    }
}

void Adding_card::on_button_image_path_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open image", QDir::currentPath(), "Image Files (*.png *.jpg *.bmp)");

    QPixmap image(100, 100);
    if(image.load(fileName))
    {
        label_image_path->setText(fileName);
        image = image.scaled(QSize(100, 100),Qt::KeepAspectRatio);
        label_image->setPixmap(image);
    }

}
