#ifndef CARDFIRE_H
#define CARDFIRE_H
#include <QWidget>
class QPushButton;
class QLineEdit;
class Card_fire : public QWidget
{
    Q_OBJECT
public:
    Card_fire(QWidget * parent=nullptr);
private:
    QPushButton * card_fire_button;
    QLineEdit * line_edit;
public slots:
    void on_card_fire_button_clicked();
signals:
    void send_reason_fire_when_clicked(QString reason_fire);
};

#endif // CARDFIRE_H
