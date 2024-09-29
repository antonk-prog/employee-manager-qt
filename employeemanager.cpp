#include "employeemanager.h"
#include "special.h"
//Employee_manager::Employee_manager() {}

Employee_manager::Employee_manager() {
    if (!QFile::exists(DATABASE_PATH))
    {
        qDebug() << "there wasnt database so we are creating new";
        create_binary_database();
        write_gaps_binary();
    }
    read_binary_database();
}

Employee_manager::~Employee_manager() {
    write_gaps_binary();
}

void Employee_manager::create_binary_database() {
    QFile file(DATABASE_PATH);
    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "create_binary_database error";
    }
    file.resize(0);
    write_and_generate_random_info();
}

QList<QListWidgetItem*> Employee_manager::read_binary_database(){
    QList<QListWidgetItem*> read_data;

    QFile file(DATABASE_PATH);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "read_binary_database error";
    }

    QDataStream in(&file);
    Employee * employee = new Employee();
    int pos = 0;
    while (!in.atEnd()){
        //employee->print_employee();

        in >> *employee;
        all_names.insert(employee->get_second_name()+ " " + employee->get_first_name() + " " + employee->get_third_name());
        if (gaps_indexes.contains(pos)){
            pos++;
            continue;
        }
        else {
            QListWidgetItem * item = new QListWidgetItem();
            item->setData(Qt::UserRole, QVariant::fromValue(*employee));
            item->setText(employee->get_second_name() + " " + employee->get_first_name() + " " + employee->get_third_name());
            if (employee->get_reason_fire().size() != 0) {
                //employee->print_employee();
                item->setBackground(QBrush(QColor(Qt::red)));
            }
            read_data.append(item);
        }
        pos++;
    }
    file.close();
    delete employee;

    return read_data;
}

// void Employee_manager::write_binary_database(QList<QListWidgetItem *> write_data)
// {
//     QFile file(DATABASE_PATH);
//     if (!file.open(QIODevice::WriteOnly))
// }

bool Employee_manager::add_binary_database(Employee employee){
    if (find_employee_binary_database(employee) != -1) return false; // дубликат не добавляем
    QFile file(DATABASE_PATH);

    if (!file.open(QIODevice::Append)){
        qDebug() << "add_binary_database error";
        return false;
    }
    QDataStream out(&file);
    out << employee;
    file.close();
    return true;

}

void Employee_manager::delete_employee_binary_database(Employee employee)
{
    int pos = find_employee_binary_database(employee);
    if (pos == -1) return;
    gaps_indexes.append(pos);
    write_gaps_binary();
    if (gaps_indexes.size() > 2) {
        compress_gaps();
    }

}

int Employee_manager::find_employee_binary_database(Employee employee)
{   int pos = 0;
    QFile file(DATABASE_PATH);

    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "find_employee_binary_database read error";
    }
    QDataStream in(&file);
    Employee * temp_employee = new Employee();
    while (!in.atEnd()) {
        in >> *temp_employee;
        if (employee == *temp_employee){
            file.close();
            delete temp_employee;
            return pos;
        }
        pos++;
    }
    delete temp_employee;
    return -1;
}

bool Employee_manager::write_and_generate_random_info(){
    QVector<QString> second_name_vec;
    QVector<QString> first_name_vec;
    QVector<QString> third_name_vec;
    QVector<QString> titul_vec;
    QVector<QDate> birth_date_vec;
    QVector<QDate> company_start_date_vec;
    QVector<qint32> work_experience_vec;
    QVector<QString> job_title_vec;
    QVector<qint32> salary_vec;
    QVector<QString> f_paths;
    QVector<QString> m_paths;

    QStringList file_names;
    file_names << PEOPLE_PATH
               << TITUL_PATH
               << BIRTH_DATE_PATH
               << COMPANY_START_DATE_PATH
               << WORK_EXPERIENCE_PATH
               << JOB_TITLE_PATH
               << SALARY_PATH;
    // заполняем векторы данными
    for (const QString &file_name: file_names){
        QFile file(file_name);

        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            qDebug() << "Не удалось открыть файл:" << file_name;
            continue; // Продолжаем цикл, если файл не удалось открыть
        }


        QString text;
        QTextStream in(&file);
        if (file_name == PEOPLE_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                QStringList list = text.split(" ");
                second_name_vec.append(list[0]);
                first_name_vec.append(list[1]);
                third_name_vec.append(list[2]);
            }

        }

        if (file_name == TITUL_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                titul_vec.append(text);
            }
        }

        if (file_name == BIRTH_DATE_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                int day = ((QString)text[0] + (QString)text[1]).toInt();
                int month = ((QString)text[2] + (QString)text[3]).toInt();
                int year = ((QString)text[4] + (QString)text[5] + (QString)text[6] + (QString)text[7]).toInt();
                birth_date_vec.append(QDate(year, month, day));
            }

        }
        if (file_name == COMPANY_START_DATE_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                int day = ((QString)text[0] + (QString)text[1]).toInt();
                int month = ((QString)text[2] + (QString)text[3]).toInt();
                int year = ((QString)text[4] + (QString)text[5] + (QString)text[6] + (QString)text[7]).toInt();
                company_start_date_vec.append(QDate(year, month, day));
            }

        }
        if (file_name == WORK_EXPERIENCE_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                work_experience_vec.append(text.toInt());

            }
        }
        if (file_name == JOB_TITLE_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                job_title_vec.append(text);

            }
        }
        if (file_name == SALARY_PATH){
            while (!in.atEnd()){
                text = in.readLine();
                salary_vec.append(text.toInt());

            }
        }
        QDirIterator it1(":/f/data/res/people/f", QDirIterator::Subdirectories);
        while (it1.hasNext()) {
            f_paths.append(it1.next());
        }
        QDirIterator it2(":/m/data/res/people/m", QDirIterator::Subdirectories);
        while (it2.hasNext()) {
            m_paths.append(it2.next());
        }
        file.close();
    }
    int counter = 0;
    QVector<qint32> sequence;
    while (counter < 100){
        QString img_path;
        QString first_name = first_name_vec[QRandomGenerator::global()->bounded(0, first_name_vec.size()-1)];
        QString second_name;
        QString third_name;
        QString end_of_first = first_name.last(1); // последняя буква имени
        QSet<QString>vowels {"а", "и", "я"};
        bool is_female = (vowels.contains(end_of_first));
        if (is_female)
        {
            img_path = f_paths[QRandomGenerator::global()->bounded(0, f_paths.size()-1)];
            do{
                second_name = second_name_vec[QRandomGenerator::global()->bounded(0, second_name_vec.size()-1)];
            }
            while (!vowels.contains(second_name.last(1)));

            do{
                third_name = third_name_vec[QRandomGenerator::global()->bounded(0, third_name_vec.size()-1)];
            }
            while (!vowels.contains(third_name.last(1)));
        }
        else
        {
            img_path = m_paths[QRandomGenerator::global()->bounded(0, m_paths.size()-1)];
            do{
                second_name = second_name_vec[QRandomGenerator::global()->bounded(0, second_name_vec.size()-1)];
            }
            while (vowels.contains(second_name.last(1)));

            do{
                third_name = third_name_vec[QRandomGenerator::global()->bounded(0, third_name_vec.size()-1)];
            }
            while (vowels.contains(third_name.last(1)));

        }
        sequence.append(QRandomGenerator::global()->bounded(0, titul_vec.size()-1));
        sequence.append(QRandomGenerator::global()->bounded(0, birth_date_vec.size()-1));
        sequence.append(QRandomGenerator::global()->bounded(0, company_start_date_vec.size()-1));
        sequence.append(QRandomGenerator::global()->bounded(0, work_experience_vec.size()-1));
        sequence.append(QRandomGenerator::global()->bounded(0, job_title_vec.size()-1));
        sequence.append(QRandomGenerator::global()->bounded(0, salary_vec.size()-1));

        Employee * employee = new Employee(second_name,
                                          first_name,
                                          third_name,
                                          titul_vec[sequence[0]],
                                          birth_date_vec[sequence[1]],
                                          company_start_date_vec[sequence[2]],
                                          work_experience_vec[sequence[3]],
                                          job_title_vec[sequence[4]],
                                          salary_vec[sequence[5]],
                                          "",
                                          img_path);
        if (add_binary_database(*employee))
        {
            counter++;
        }
        //emit employees_changed(); //  нужно ли это здесь?
        sequence.clear();
    }
    return true;
}

void Employee_manager::write_gaps_binary()
{
    QFile file(GAPS_PATH);
    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "write_gaps_binary error";
    }
    QDataStream out(&file);
    out << gaps_indexes;
}

bool Employee_manager::read_gaps_binary()
{
    QFile file(GAPS_PATH);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "write_gaps_binary error(такого файла нет, первое открытыие бд)";
        return false;
    }
    QDataStream in(&file);
    in >> gaps_indexes;
    return true;
}

void Employee_manager::write_fired_employee(Employee employee) {
    QFile file_read(DATABASE_PATH);
    QFile file_write(DATABASE_PATH+".temp");

    file_read.open(QIODevice::ReadOnly);
    file_write.open(QIODevice::WriteOnly);
    QDataStream in(&file_read);
    QDataStream out(&file_write);

    Employee * employee_temp = new Employee;
    while (!in.atEnd()){
        in >> *employee_temp;
        if (*employee_temp == employee){ // проверка не учитывает fire_reason
            out << employee;

        } else {
            out << *employee_temp;
        }
    }
    gaps_indexes.clear();

    delete employee_temp;
    file_read.remove();


    if (!file_write.rename(DATABASE_PATH)) {
        qDebug() << file_write.errorString();
    }

}

void Employee_manager::compress_gaps()
{
    QFile file_read(DATABASE_PATH);
    QFile file_write(DATABASE_PATH+".temp");

    file_read.open(QIODevice::ReadOnly);
    file_write.open(QIODevice::WriteOnly);
    QDataStream in(&file_read);
    QDataStream out(&file_write);

    Employee * employee_temp = new Employee;
    int pos = 0;
    while (!in.atEnd()){
        in >> *employee_temp;
        if (!gaps_indexes.contains(pos)){
            out << *employee_temp;
        }
        pos++;
    }
    gaps_indexes.clear();

    delete employee_temp;
    file_read.remove();


    if (!file_write.rename(DATABASE_PATH)) {
        qDebug() << file_write.errorString();
    }
}

void Employee_manager::read_people()
{
    QFile file(PEOPLE_PATH);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        //qDebug() << "Не удалось открыть файл:" << file_name;
    }
    int counter = 0;
    QTextStream in(&file);
    while (!in.atEnd()){
        in.readLine();
        counter++;
    }

    all_people_file_count = counter;
}

// void Employee_manager::print_binary_database() {
//     for (int i = 0; i < employees.size(); i++){
//         employees[i]->print_employee();
//         qDebug();
//     }

//     qDebug() << employees.size();
// }




