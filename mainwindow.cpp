//
// Created by TURIING on 2023/6/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow) {
    /* 初始化 */
    ui->setupUi(this);

    /* IP编辑框 */
    ui->label_ip->setStyleSheet("color:red;");
    connect(ui->btn_makeIP, &QPushButton::clicked, this, &MainWindow::onBtnMakeIPClicked);
    connect(ui->btn_clearIP, &QPushButton::clicked, this, &MainWindow::onBtnClearIPClicked);
    /* GifCapture */
    m_gifCapture = new GifCapture();
    m_gifCapture->setWindowFlags(Qt::WindowStaysOnTopHint | m_gifCapture->windowFlags());
    connect(ui->btn_gifPopup, &QPushButton::clicked, this, &MainWindow::onBtnGifPopupClicked);

    /* Battery */
    connect(ui->horizontalSliderBattery, &QSlider::valueChanged, ui->widgetBattery, &Battery::setTargetValue);
    ui->horizontalSliderBattery->setValue(30);

    /* ScrollText */
    ui->widgetScrollText->setText("我是一段滚动的文字");
    connect(ui->btn_scrollText, &QPushButton::clicked, this, &MainWindow::onBtnScrollTextClicked);

    m_sphericalProgressBar = new SphericalProgressBar();
    connect(ui->btn_sphericalProgressBarPop, &QPushButton::clicked, this, &MainWindow::onBtnSphericalProgressBarPopClicked);
    connect(ui->btn_sphericalProgressBarStart, &QPushButton::clicked, m_sphericalProgressBar, &SphericalProgressBar::start);
    connect(ui->btn_sphericalProgressBarReset, &QPushButton::clicked, m_sphericalProgressBar, &SphericalProgressBar::reset);

}

MainWindow::~MainWindow() {
    delete m_sphericalProgressBar;
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

void MainWindow::onBtnScrollTextClicked() {
    ui->widgetScrollText->setText("我是一段滚动的文字");
}



void MainWindow::onBtnSphericalProgressBarPopClicked() {
    m_sphericalProgressBar->show();
}


