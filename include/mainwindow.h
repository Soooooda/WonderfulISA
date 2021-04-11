#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../include/PipeLine.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    PipeLine pipeline;
    bool instruction_clicked;
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void refresh_cache();

    void refresh_memory();

    void refresh_register();

    void refresh_pipeline();

    void refresh_machine_code(int32_t* machine_code, int16_t size);

    void on_instructionReadButton_clicked();

    void on_next_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
