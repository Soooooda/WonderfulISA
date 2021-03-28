#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //cache
    //cache consists of 16 cachelines
    ui->cacheTable->setRowCount(16);
    ui->cacheTable->setColumnCount(7);
    ui->cacheTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cacheTable->resizeRowsToContents();
    ui->cacheTable->setWindowTitle("Cache View");
    QStringList cache_header;
    cache_header<<"header"<<"valid"<<"dirty"<<"offset0"<<"offset1"<<"offset2"<<"offset3"<<"lru";
    ui->cacheTable->setHorizontalHeaderLabels(cache_header);

    //memory
    //memory = (int16_t*) malloc(sizeof(int16_t) *1024*64); //memory is 2^16 * word(16bit)
    ui->memoryTable->setRowCount(10000);
    ui->memoryTable->setColumnCount(2);
    ui->memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memoryTable->setWindowTitle("Memory View");
    QStringList memory_header;
    memory_header<<"address"<<"value";
    ui->memoryTable->setHorizontalHeaderLabels(memory_header);


    simulator.instantiate();

    refresh_cache();
    refresh_memory();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_cache()
{
    CacheLine* cache = simulator.l1_cache.cache;

    for(int16_t ptr = 0; ptr<16;ptr+=1)
    {
        ui->cacheTable->setItem(ptr,0,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].header&TAG_INDEX_FLAG))));
        ui->cacheTable->setItem(ptr,1,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].header&VALID_FLAG))));
        ui->cacheTable->setItem(ptr,2,new QTableWidgetItem(QString::fromStdString(to_string((cache[ptr].header&DIRTY_FLAG)>>1))));
        ui->cacheTable->setItem(ptr,3,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].offset[0]))));
        ui->cacheTable->setItem(ptr,4,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].offset[1]))));
        ui->cacheTable->setItem(ptr,5,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].offset[2]))));
        ui->cacheTable->setItem(ptr,6,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].offset[3]))));
        ui->cacheTable->setItem(ptr,7,new QTableWidgetItem(QString::fromStdString(to_string(cache[ptr].lru))));
    }
    ui->cacheTable->show();
}

void MainWindow::refresh_memory()
{
    int16_t* memory = simulator.memory;
//    CacheLine* cache = simulator.l1_cache.cache;

    for(int16_t ptr = 0; ptr<10000;ptr+=1)
    {
        ui->memoryTable->setItem(ptr,0,new QTableWidgetItem(QString::fromStdString(to_string(ptr))));
        ui->memoryTable->setItem(ptr,1,new QTableWidgetItem(QString::fromStdString(to_string(memory[ptr]))));
    }
    ui->memoryTable->show();
}


//get value from memory
void MainWindow::on_pushButton_2_clicked()
{
    int16_t address = ui->inputMemory->toPlainText().toInt();
    int16_t value = simulator.read_memory(address);
    refresh_cache();
    refresh_memory();
    //set read value
    ui->inputValue->setText(QString::fromStdString(to_string(value)));
}

//write to memory
void MainWindow::on_pushButton_3_clicked()
{
        int16_t value = ui->inputValue->toPlainText().toInt();
        int16_t address = ui->inputMemory->toPlainText().toInt();
        simulator.write_memory(address,value);
        refresh_cache();
        refresh_memory();
}
