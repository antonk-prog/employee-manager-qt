#include "employee.h"
Employee::Employee(const QString &second_name, const QString &first_name, const QString &third_name, const QString &titul, const QDate &birth_date, const QDate &company_start_date, qint32 work_experience, const QString &job_title, qint32 salary, const QString &reason_fire, const QString &image_path)
{
    this->second_name = second_name;
    this->first_name = first_name;
    this->third_name = third_name;
    this->titul = titul;
    this->birth_date = birth_date;
    this->company_start_date = company_start_date;
    this->work_experience = work_experience;
    this->job_title = job_title;
    this->salary = salary;
    this->reason_fire = reason_fire;
    this->image_path = image_path;

}

Employee::~Employee() {
}



void Employee::print_employee(){
    qDebug() << second_name;
    qDebug() << first_name;
    qDebug() << third_name;
    qDebug() << titul;
    qDebug() << birth_date;
    qDebug() << company_start_date;
    qDebug() << work_experience;
    qDebug() << job_title;
    qDebug() << salary;
    qDebug() << image_path;
}

QString &Employee::get_first_name() { return first_name; }

QString &Employee::get_second_name() { return second_name; }

QString &Employee::get_third_name() { return third_name; }

QString &Employee::get_titul() { return titul; }

QDate &Employee::get_birth_date() { return birth_date; }

QDate &Employee::get_company_start_date() { return company_start_date; }

qint32 &Employee::get_work_experience() { return work_experience; }

QString &Employee::get_job_title() { return job_title; }

qint32 &Employee::get_salary() { return salary; }

QString &Employee::get_reason_fire() { return reason_fire; }

QString &Employee::get_image_path() { return image_path; }

QString Employee::get_first_name() const { return first_name; }

QString Employee::get_second_name() const { return second_name; }

QString Employee::get_third_name() const { return third_name; }

QString Employee::get_titul() const { return titul; }

QDate Employee::get_birth_date() const { return birth_date; }

QDate Employee::get_company_start_date() const { return company_start_date; }

qint32 Employee::get_work_experience() const { return work_experience; }

QString Employee::get_job_title() const { return job_title; }

qint32 Employee::get_salary() const { return salary; }

QString Employee::get_reason_fire() const { return reason_fire; }

QString Employee::get_image_path() const { return image_path; }

void Employee::set_first_name(const QString &firstName) {
    this->first_name = firstName;
}

void Employee::set_second_name(const QString &secondName) {
    this->second_name = secondName;
}

void Employee::set_third_name(const QString &thirdName) {
    this->third_name = thirdName;
}

void Employee::set_titul(const QString &titul) {
    this->titul = titul;
}

void Employee::set_birth_date(const QDate &birthDate) {
    this->birth_date = birthDate;
}

void Employee::set_company_start_date(const QDate &companyStartDate) {
    this->company_start_date = companyStartDate;
}

void Employee::set_work_experience(qint32 workExperience) {
    this->work_experience = workExperience;
}


void Employee::set_job_title(const QString &jobTitle) {
    this->job_title = jobTitle;
}

void Employee::set_salary(qint32 salary) {
    this->salary = salary;
}

void Employee::set_reason_fire(QString text){
    reason_fire = text;
}

void Employee::set_image_path(const QString &image_path){
    this->image_path = image_path;
}

// QByteArray Employee::serialize() const { // Из Employee в QByteArray
//     QDataStream stream;
//     Employee * employee = new Employee(get_first_name(), get_second_name(),
//                                       get_third_name(), get_titul(),
//                                       get_birth_date(), get_company_start_date(),
//                                       get_work_experience(), get_job_title(),
//                                       get_salary(), get_reason_fire()
//                                       );
//     stream << 1;//*employee;

//     qDebug() << sizeof(Employee);
//     qDebug() << sizeof(stream.device()->readAll());
//     if (!stream.atEnd()) {
//         return stream.device()->readAll();
//     } else {
//         // Обработка ошибки: поток достиг конца, но мы ожидали больше данных
//     }
//     return stream.device()->readAll(); // читаем все данные и возвращаем в виде QByteArray

// }

// Employee Employee::deserialize(const QByteArray &data){ // из QByteArray в Employee
//     QDataStream stream(data);
//     QString first_name;
//     QString second_name;
//     QString third_name;
//     QString titul;
//     QDate birth_date;
//     QDate company_start_date;
//     qint32 work_experience;
//     QString job_title;
//     qint32 salary;
//     stream >> first_name >> second_name >> third_name
//         >> titul >> birth_date >> company_start_date
//         >> work_experience >> job_title >> salary;

//     return Employee(first_name, second_name, third_name, titul,
//                     birth_date, company_start_date,
//                     work_experience, job_title, salary,
//                     );
// }
bool operator==(const Employee& lhs, const Employee& rhs) {
    return lhs.get_first_name() == rhs.get_first_name() &&
           lhs.get_second_name() == rhs.get_second_name() &&
           lhs.get_third_name() == rhs.get_third_name() &&
           lhs.get_titul() == rhs.get_titul() &&
           lhs.get_birth_date() == rhs.get_birth_date() &&
           lhs.get_company_start_date() == rhs.get_company_start_date() &&
           lhs.get_work_experience() == rhs.get_work_experience() &&
           lhs.get_job_title() == rhs.get_job_title() &&
           lhs.get_salary() == rhs.get_salary();
}

QDataStream & operator<<(QDataStream&out, Employee& employee){
    out << employee.get_second_name() <<employee.get_first_name()
        << employee.get_third_name() << employee.get_titul() << employee.get_birth_date()
        << employee.get_company_start_date() << employee.get_work_experience()
        <<employee.get_job_title() << employee.get_salary() << employee.get_reason_fire() << employee.get_image_path();
    return out;
}

QDataStream & operator>>(QDataStream&in, Employee& employee){
    in >> employee.get_second_name() >> employee.get_first_name()
        >> employee.get_third_name() >> employee.get_titul()
        >> employee.get_birth_date()
        >> employee.get_company_start_date() >> employee.get_work_experience()
        >> employee.get_job_title() >> employee.get_salary() >> employee.get_reason_fire() >> employee.get_image_path();
    return in;
}

QDialog* createCustomDialog(QString text, QWidget* parent){
    QDialog* dialog = new QDialog(parent);
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* label = new QLabel(text, dialog);
    QPushButton* okButton = new QPushButton("OK", dialog);
    QObject::connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);

    layout->addWidget(label);
    layout->addWidget(okButton);


    return dialog;
}
