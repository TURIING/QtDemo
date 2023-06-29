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

    /* Marquee */
    ui->labelMarquee->setText(QStringLiteral("去留无意，闲看庭前花开花落；宠辱不惊，漫随天外云卷云舒"));

    /* SwitchButton */
    ui->widgetSwitchButton->append(QStringLiteral("Pretty"), 90);


    ui->widgetSwitchButton->append(QStringLiteral("Raw"), 70);
    ui->widgetSwitchButton->append(QStringLiteral("Preview"), 100);
    ui->widgetSwitchButton->append(QStringLiteral("Visualize"), 100);
    ui->widgetSwitchButton->setCurrentIndex(1);

    /* MenuSwitcher */
    ui->widgetMenuSwitcher->append(QStringLiteral("Collections"), QStringLiteral("../Resources/collections_active.svg"), QStringLiteral("../Resources/collections_unactive.svg"), QStringLiteral("../Resources/collections_active.svg"));
    ui->widgetMenuSwitcher->append(QStringLiteral("APIs"), QStringLiteral("../Resources/apis_active.svg"), QStringLiteral("../Resources/apis_unactive.svg"), QStringLiteral("../Resources/apis_active.svg"));
    ui->widgetMenuSwitcher->append(QStringLiteral("Environments"), QStringLiteral("../Resources/environments_active.svg"), QStringLiteral("../Resources/environments_unactive.svg"), QStringLiteral("../Resources/environments_active.svg"));
    ui->widgetMenuSwitcher->append(QStringLiteral("Mock Servers"), QStringLiteral("../Resources/mock_servers_active.svg"), QStringLiteral("../Resources/mock_servers_unactive.svg"), QStringLiteral("../Resources/mock_servers_active.svg"));
    ui->widgetMenuSwitcher->append(QStringLiteral("Monitors"), QStringLiteral("../Resources/monitors_active.svg"), QStringLiteral("../Resources/monitors_unactive.svg"), QStringLiteral("../Resources/monitors_active.svg"));
    ui->widgetMenuSwitcher->append(QStringLiteral("History"), QStringLiteral("../Resources/history_active.svg"), QStringLiteral("../Resources/history_unactive.svg"), QStringLiteral("../Resources/history_active.svg"));
    ui->widgetMenuSwitcher->setDefaultItem(0);
    connect(ui->widgetMenuSwitcher, &MenuSwitcher::indexChanged, this, [=](int _index) { qDebug() << "currentItem = " << _index; });

    /* GraphicsEffect */
    m_graphicsEffect = new GraphicsEffect();
    connect(ui->btn_graphicsEffect, &QPushButton::clicked, this, [=]{ m_graphicsEffect->show();});
}

MainWindow::~MainWindow() {
    delete m_graphicsEffect;
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


