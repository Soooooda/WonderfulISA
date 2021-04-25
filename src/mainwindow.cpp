#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //cache
    ui->cacheTable->setRowCount(16);
    ui->cacheTable->setColumnCount(7);
    ui->cacheTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cacheTable->resizeRowsToContents();
    ui->cacheTable->setWindowTitle("Cache View");
    QStringList cache_header;
    cache_header<<"header"<<"valid"<<"dirty"<<"offset0"<<"offset1"<<"offset2"<<"offset3"<<"lru";
    ui->cacheTable->setHorizontalHeaderLabels(cache_header);

    //memory
    ui->memoryTable->setRowCount(10000);
    ui->memoryTable->setColumnCount(2);
    ui->memoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memoryTable->resizeRowsToContents();
    ui->memoryTable->setWindowTitle("Memory View");
    QStringList memory_header;
    memory_header<<"address"<<"value";
    ui->memoryTable->setHorizontalHeaderLabels(memory_header);

    //pipeline
    ui->pipelineTable->setRowCount(5);
    ui->pipelineTable->setColumnCount(2);
    ui->pipelineTable->setItem(0,0,new QTableWidgetItem("fetch"));
    ui->pipelineTable->setItem(1,0,new QTableWidgetItem("decode"));
    ui->pipelineTable->setItem(2,0,new QTableWidgetItem("alu"));
    ui->pipelineTable->setItem(3,0,new QTableWidgetItem("memory"));
    ui->pipelineTable->setItem(4,0,new QTableWidgetItem("write_back"));
    ui->pipelineTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pipelineTable->resizeRowsToContents();
    QStringList pipline_header;
    pipline_header<<"stage"<<"Instruction";
    ui->pipelineTable->setHorizontalHeaderLabels(pipline_header);

    //registers
    ui->registerTable->setRowCount(16);
    ui->registerTable->setColumnCount(1);
    ui->registerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->registerTable->resizeRowsToContents();
    QStringList register_header;
    register_header<<"value";
    ui->registerTable->setHorizontalHeaderLabels(register_header);

    //vector registers
    ui->vectorRegisterTable->setRowCount(16);
    ui->vectorRegisterTable->setColumnCount(2);
    ui->vectorRegisterTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->vectorRegisterTable->resizeRowsToContents();
    QStringList vector_register_header;
    vector_register_header<<"vector 0"<<"vector 1";
    ui->vectorRegisterTable->setHorizontalHeaderLabels(vector_register_header);


    //pipeline mode
    ui->pipelineModeBox->addItem("No Pipeline");
    ui->pipelineModeBox->addItem("With Pipeline");

    //cache mode
    ui->CacheModeBox->addItem("No Cache");
    ui->CacheModeBox->addItem("With Cache");

    //cycle count
    ui->TimeCycleText->setText("0");
    time_cycle_count = 0;

    //has instruction clicked before next cycle button?
    instruction_clicked = false;

    pipeline.simulator.instantiate();

    //initial Memory
    pipeline.simulator.write_memory(0,30);
    pipeline.simulator.write_memory(1,3);
    pipeline.simulator.write_memory(2,2);
    pipeline.simulator.write_memory(3,70);
    pipeline.simulator.write_memory(4,4);
    pipeline.simulator.write_memory(5,3);
    pipeline.simulator.write_memory(6,400);
    pipeline.simulator.write_memory(7,1);
    pipeline.simulator.write_memory(30,5);
    pipeline.simulator.write_memory(31,32);
    pipeline.simulator.write_memory(32,1);
    pipeline.simulator.write_memory(33,5);
    pipeline.simulator.write_memory(34,2);
    pipeline.simulator.write_memory(35,3);
    pipeline.simulator.write_memory(70,3);
    pipeline.simulator.write_memory(71,6);
    pipeline.simulator.write_memory(72,43);
    pipeline.simulator.write_memory(73,6);
    pipeline.simulator.write_memory(74,76);
    pipeline.simulator.write_memory(75,3);
    pipeline.simulator.write_memory(76,4);
    pipeline.simulator.write_memory(77,7);
    pipeline.simulator.write_memory(78,8);
    pipeline.simulator.write_memory(79,6);
    pipeline.simulator.write_memory(80,4);
    pipeline.simulator.write_memory(81,2);

    refresh_cache();
    refresh_memory();
    refresh_pipeline();
    refresh_register();
    refresh_vector_register();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_cache()
{
    CacheLine* cache = pipeline.simulator.l1_cache.cache;

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
    int16_t* memory = pipeline.simulator.memory;
//    CacheLine* cache = simulator.l1_cache.cache;

    for(int16_t ptr = 0; ptr<10000;ptr+=1)
    {
        ui->memoryTable->setItem(ptr,0,new QTableWidgetItem(QString::fromStdString(to_string(ptr))));
        ui->memoryTable->setItem(ptr,1,new QTableWidgetItem(QString::fromStdString(to_string(memory[ptr]))));
    }
    ui->memoryTable->show();
}

void MainWindow::refresh_register()
{
    for(int16_t ptr = 0; ptr<16;ptr+=1)
    {
        ui->registerTable->setItem(ptr,0,new QTableWidgetItem(QString::fromStdString(to_string(pipeline.registe.get(ptr)))));
    }
    ui->registerTable->show();
}

void MainWindow::refresh_vector_register()
{
    //getvector

    for(int16_t vector_idx = 0; vector_idx<2; vector_idx++)
    {
        for(int16_t ptr = 0; ptr<16;ptr+=1)
        {
            ui->vectorRegisterTable->setItem(ptr,vector_idx,new QTableWidgetItem(QString::fromStdString(to_string(pipeline.registe.getvector(vector_idx, ptr)))));
        }
    }

    ui->vectorRegisterTable->show();
}

void MainWindow::refresh_pipeline()
{
    for(int16_t ptr = 0; ptr<5;ptr+=1)
    {
        ui->pipelineTable->setItem(ptr,1,new QTableWidgetItem(QString::fromStdString(pipeline.pipeLine_pc[ptr])));
    }
    ui->pipelineTable->show();
}

void MainWindow::refresh_machine_code(int32_t* machine_code, int16_t size)
{
    for (int i = 0; i < size; i++) {
        QListWidgetItem *newItem = new QListWidgetItem;
        string binary = std::bitset<32>(machine_code[i]).to_string();
        cout<<binary<<endl;
        newItem->setText(QString::fromStdString(binary));
        ui->MachineCodeWidget->insertItem(0, newItem);
    }
}

//get value from memory
void MainWindow::on_pushButton_2_clicked()
{
    int16_t address = ui->inputMemory->toPlainText().toInt();
    int16_t value = pipeline.simulator.read_memory(address);
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
        pipeline.simulator.write_memory(address,value);
        refresh_cache();
        refresh_memory();
}


void MainWindow::on_instructionReadButton_clicked()
{

    QStringList Lines = ui->InstructionInput->toPlainText().split('\n');
    string* instructions = new string[Lines.size()];
    for (int i = 0; i < Lines.size(); i++) {
        instructions[i] = Lines[i].toStdString();
    }
    int32_t machine_code[Lines.size()];
    pipeline.initialize(instructions, Lines.size(),machine_code);
    refresh_machine_code(machine_code, Lines.size());
    instruction_clicked = true;
}

int32_t MainWindow::getRunningStatus()
{
    //#define ENABLE_PIPELINE_ENABLE_CACHE 1
    //#define ENABLE_PIPELINE_NO_CACHE 2
    //#define NO_PIPELINE_ENABLE_CACHE 3
    //#define NO_PIPELINE_NO_CACHE 4
    //4是cache pip， 3 是no pip， 2 是弄cache， 1 是no both
    return ui->CacheModeBox->currentIndex()*2+ui->pipelineModeBox->currentIndex()+1;
}

void MainWindow::on_next_clicked()
{
    if(instruction_clicked)
    {
        pipeline.run_cycle(getRunningStatus());
        refresh_register();
        refresh_memory();
        refresh_cache();
        refresh_pipeline();
        refresh_vector_register();
        time_cycle_count+=1;
        ui->TimeCycleText->setText(QString::fromStdString(to_string(time_cycle_count)));
    }
}



void MainWindow::on_nextHundred_clicked()
{
    if(instruction_clicked)
    {
        int32_t mode = getRunningStatus();
        for(int i = 0;i<100;i++)
        {
            pipeline.run_cycle(mode);
        }
        refresh_register();
        refresh_memory();
        refresh_cache();
        refresh_pipeline();
        refresh_vector_register();
        time_cycle_count+=100;
        ui->TimeCycleText->setText(QString::fromStdString(to_string(time_cycle_count)));
    }
}
