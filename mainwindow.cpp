#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"QDebug"
#include"utils.h"
#include"QString"
#include <QClipboard>
#include <QDir>
#include <QTranslator>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init_all();
    init_translation();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changeLanguage(const QString &qmFile) {
    qApp->removeTranslator(&translator);
    if (translator.load(qmFile)) {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        qDebug() << "Language loaded:" << qmFile;
    } else {
        qDebug() << "Failed to load:" << qmFile;
    }
}

void MainWindow::init_translation() {
    QDir dir("./translations");

    if (!dir.exists()) {
        QString appdir = qEnvironmentVariable("APPDIR");
        if (appdir.isEmpty()) {
            appdir = QCoreApplication::applicationDirPath();
        }
        dir.setPath(appdir + "/usr/share/RandKey-QT/translations");
    }

    QString uilang ;
    QStringList qmFiles = dir.entryList(QStringList() << "*.qm", QDir::Files);

    int defaultIndex = -1;

    for (int i = 0; i < qmFiles.size(); ++i) {
        const QString &file = qmFiles[i];
        QString langName = file.section('_', -2, -1).section('.', 0, 0);
        ui->comboBox_language->addItem(langName, file);
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale: uiLanguages) {
            uilang = QLocale(locale).name();
        }

        if (langName == uilang) {
            defaultIndex = i;
        }
    }

    if (defaultIndex >= 0) {
        ui->comboBox_language->setCurrentIndex(defaultIndex);
    }
}

void MainWindow::init_all() {
    update_slider_label();
    ui->checkBox_symbol->setChecked(true);
    ui->radio_rand->setChecked(true);
    ui->radio_rand->click();
    ui->radio_simple->hide();
}

void MainWindow::on_length_slider_valueChanged(int value) {
    update_slider_label();
}

void MainWindow::update_slider_label() {
    int length = ui->length_slider->value();
    ui->length_label->setText(QString::number(length));
}

void MainWindow::on_key_gen_btn_clicked() {
    update_key_output();
}

void MainWindow::update_key_output() {
    utils u;
    const int length = ui->length_slider->value();
    const bool include_num = ui->checkBox_num->isChecked();
    QString symbol = "";
    QString result = "";
    if (ui->radio_rand->isChecked()) {
        if (ui->checkBox_symbol->isChecked()) {
            if (ui->checkbox_at->isChecked()) symbol.append("@");
            if (ui->checkBox_asterisk->isChecked())symbol.append("*");
            if (ui->checkBox_brace->isChecked())symbol.append("{}");
            if (ui->checkBox_caret->isChecked())symbol.append("^");
            if (ui->checkBox_equal->isChecked())symbol.append("=");
            if (ui->checkBox_exclamation->isChecked())symbol.append("!");
            if (ui->checkBox_parenthesis->isChecked())symbol.append("()");
            if (ui->checkBox_hash->isChecked())symbol.append("#");
            if (ui->checkBox_hyphen->isChecked())symbol.append("-");
            if (ui->checkBox_plus->isChecked())symbol.append("+");
            if (ui->checkBox_squarebraket->isChecked())symbol.append("[]");
            if (ui->checkBox_than->isChecked())symbol.append("<>");
        }
        result = u.generate_random_string(length, include_num, symbol);
        result.replace("\n", "");
    } else if (ui->radio_number->isChecked()) {
        if (ui->checkBox_0->isChecked()) symbol.append("0");
        if (ui->checkBox_1->isChecked()) symbol.append("1");
        if (ui->checkBox_2->isChecked()) symbol.append("2");
        if (ui->checkBox_3->isChecked()) symbol.append("3");
        if (ui->checkBox_4->isChecked()) symbol.append("4");
        if (ui->checkBox_5->isChecked()) symbol.append("5");
        if (ui->checkBox_6->isChecked()) symbol.append("6");
        if (ui->checkBox_7->isChecked()) symbol.append("7");
        if (ui->checkBox_8->isChecked()) symbol.append("8");
        if (ui->checkBox_9->isChecked()) symbol.append("9");
        result = u.generate_random_num(length, symbol);
    } else if (ui->radio_simple->isChecked()) {
        // TO-DO
    }
    ui->key_output->setPlainText(result);
}

void MainWindow::on_key_copy_btn_clicked() {
    const QString text_value = ui->key_output->toPlainText();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text_value);
}

void MainWindow::on_checkBox_symbol_clicked(bool checked) {
    checked ? ui->widget_symbol->show() : ui->widget_symbol->hide();
}

void MainWindow::on_radio_rand_clicked(bool checked) {
    if (checked) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->length_slider->setValue(16);
        update_key_output();
    }
}

void MainWindow::on_radio_number_clicked(bool checked) {
    if (checked) {
        ui->stackedWidget->setCurrentIndex(1);
        ui->length_slider->setValue(8);
        update_key_output();
    }
}

void MainWindow::on_length_slider_sliderMoved(int position)
{
        update_key_output();
}


void MainWindow::on_comboBox_language_currentIndexChanged(int index)
{
    QString qmPath = ui->comboBox_language->itemData(index).toString();
    changeLanguage(qmPath);
}

