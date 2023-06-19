//
// Created by TURIING on 2023/6/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow) {
    /* 初始化 */
    ui->setupUi(this);

    // IP编辑框
    ui->label_ip->setStyleSheet("color:red;");
    // GifCapture
    m_gifCapture = new GifCapture();
    m_gifCapture->setWindowFlags(Qt::WindowStaysOnTopHint | m_gifCapture->windowFlags());


    /* 信号槽 */
    connect(ui->btn_makeIP, &QPushButton::clicked, this, &MainWindow::onBtnMakeIPClicked);
    connect(ui->btn_clearIP, &QPushButton::clicked, this, &MainWindow::onBtnClearIPClicked);
    connect(ui->btn_gifPopup, &QPushButton::clicked, this, &MainWindow::onBtnGifPopupClicked);

}

MainWindow::~MainWindow() {
    delete m_gifCapture;
    delete ui;
}

void MainWindow::onBtnMakeIPClicked() {
    ui->label_ip->setText(ui->ipLineEdit->getIp());
}

void MainWindow::onBtnClearIPClicked() {
    ui->ipLineEdit->clear();
    ui->label_ip->clear();
}

void MainWindow::onBtnGifPopupClicked() {
    m_gifCapture->show();
}


