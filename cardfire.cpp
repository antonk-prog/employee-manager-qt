#include "cardfire.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include "employee.h"
Card_fire::Card_fire(QWidget * parent) : QWidget(parent) {
    QVBoxLayout * main_layout = new QVBoxLayout();
    QLabel * label = new QLabel;
    label->setText("Причина увольнения: ");
    line_edit = new QLineEdit();
    label->setBuddy(line_edit);

    card_fire_button = new QPushButton("Уволить");

    main_layout->addWidget(label);
    main_layout->addWidget(line_edit);
    main_layout->addWidget(card_fire_button);

    connect(card_fire_button, &QPushButton::clicked, this, &Card_fire::on_card_fire_button_clicked);

    this->setLayout(main_layout);

}

void Card_fire::on_card_fire_button_clicked()
{
    if (line_edit->text().size() != 0){
        QString reason_fire = line_edit->text();
        emit send_reason_fire_when_clicked(reason_fire);
    } else {
        QDialog * dialog = createCustomDialog("Поле не должно быть пустым.");
        dialog->exec();
        delete dialog;
    }
}
