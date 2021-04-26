#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../include/PipeLine.hpp"
#include <QMainWindow>
//#define ENABLE_PIPELINE_ENABLE_CACHE 0
//#define ENABLE_PIPELINE_NO_CACHE 1
//#define NO_PIPELINE_ENABLE_CACHE 2
//#define NO_PIPELINE_NO_CACHE 3

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
    int32_t time_cycle_count;
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void refresh_cache();

    void refresh_memory();

    void refresh_register();

    void refresh_vector_register();

    void refresh_pipeline();

    void refresh_machine_code(int32_t* machine_code, int16_t size);

    void on_instructionReadButton_clicked();

    void on_next_clicked();

    int32_t getRunningStatus();

    void on_nextHundred_clicked();



    void on_RunToFinalButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
