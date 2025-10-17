#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTranslator>
#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void update_slider_label();

    void update_key_output();

    void init_all();

    void on_length_slider_valueChanged(int value);

    void on_checkBox_symbol_clicked(bool checked);

    void on_key_gen_btn_clicked();

    void on_key_copy_btn_clicked();

    void on_radio_rand_clicked(bool checked);

    void on_radio_number_clicked(bool checked);

    void init_translation();

    void changeLanguage(const QString &qmFile);

    void on_comboBox_language_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QTranslator translator;
};
#endif // MAINWINDOW_H
