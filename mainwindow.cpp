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
    connect(ui->btn_graphicsEffect, &QPushButton::clicked, this, [this]{ m_graphicsEffect->show();});

    /* PageSwitcher */
    ui->widgetPageSwitcher->append(QStringLiteral("Params"));
    ui->widgetPageSwitcher->append(QStringLiteral("Authorization"));
    ui->widgetPageSwitcher->append(QStringLiteral("Headers"));
    ui->widgetPageSwitcher->append(QStringLiteral("Body"), true);
    ui->widgetPageSwitcher->append(QStringLiteral("Pre-request Script"));
    ui->widgetPageSwitcher->append(QStringLiteral("Tests"));
    ui->widgetPageSwitcher->append(QStringLiteral("Settings"));
    ui->widgetPageSwitcher->setCurrentItem(1);
    connect(ui->widgetPageSwitcher, &PageSwitcher::indexChanged, this, [=](int _index) { qDebug() << "PageSwitcher's current item:" << _index;});

    /* AnimationButton */
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(3, 5);
    shadowEffect->setColor(QColor("#44888888"));
    shadowEffect->setBlurRadius(20);
    ui->btn_animationButton->setGraphicsEffect(shadowEffect);
    connect(ui->btn_animationButton, &QPushButton::clicked, this, &MainWindow::onBtnAnimationButtonClicked);

    /* MovableTableView */
    initTable();
    connect(ui->actionAddRow, &QAction::triggered, this, &MainWindow::onActionAddRowTriggered);
    connect(ui->actionDeleteRow, &QAction::triggered, this, &MainWindow::onActionDeleteRowTriggered);
    connect(ui->actionClearTable, &QAction::triggered, this, &MainWindow::onActionClearTableTriggered);

    /* FrameLessWindow */
    m_framelessWindow = new FrameLessWindow();
    m_framelessWindow->resize(800, 600);
    m_framelessWindow->setFixedSize(800, 600);
    connect(ui->btnFrameLess, &QPushButton::clicked, this, &MainWindow::onBtnFrameLessClicked);

    /* MultiLevelMenu */
    //m_multiLevelMenu->addMenuItem("File");
    //m_multiLevelMenu->addMenuItem("Edit");
    //m_multiLevelMenu->addSeparator();
    //m_multiLevelMenu->addMenuItem("View");
    //m_multiLevelMenu->addMenuItem("Help");
    //connect(ui->btnMenu, &QPushButton::clicked, [this]{
    //    auto pos = ui->btnMenu->mapToGlobal(QPoint(0, 0));
    //    m_multiLevelMenu->move(pos.x(), pos.y() + ui->btnMenu->height());
    //    m_multiLevelMenu->show();
    //});

    m_sketchBoard = new SketchBoard();
    connect(ui->btnSketchBoard, &QPushButton::clicked, [this]{
        m_sketchBoard->show();
    });
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

void MainWindow::onBtnAnimationButtonClicked() {
    const int totalCount = 2;
    static int index = -1;
    int dx = 0;

    // -
    AnimationButton::Status status[totalCount];
    int i = 0;
    status[i].bgSize = QSize(50, 50);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 10;
    status[i].lineUseNum = 1;
    status[i].linePos[0] = QLineF(15, 15, 45, 15);
    status[i].lineHidePos[0] = QPointF(50, 50);
    status[i].lineColors[0] = QColor("#ed657d");

    // +
    i++;
    status[i].bgSize = QSize(-1, -1);
    status[i].bgColor = Qt::white;
    status[i].bgRadius = 30;
    status[i].lineUseNum = 2;
    status[i].linePos[0] = QLineF(35, 50, 65, 50);
    status[i].linePos[1] = QLineF(50, 65, 50, 35);
    status[i].lineHidePos[0] = QPointF(50, 50);
    status[i].lineHidePos[1] = QPointF(50, 50);
    status[i].lineColors[0] = QColor("#5baaf8");
    status[i].lineColors[1] = QColor("#5baaf8");

    if(++index >= totalCount)
        index = 0;
    ui->btn_animationButton->load(status[index]);
}

void MainWindow::initTable() {
    auto table = ui->tableViewMovable;
    /* 设置表格属性 */
    // 隐藏垂直方向的表头
    table->verticalHeader()->hide();
    // 设置列高度
    table->verticalHeader()->setDefaultSectionSize(30);
    // 最后一列自适应宽度
    table->horizontalHeader()->setStretchLastSection(true);
    // 设置双击编辑
    table->setEditTriggers(QTableView::DoubleClicked);
    // 一次选中整行
    table->setSelectionBehavior(QTableView::SelectRows);
    // 单行选中
    table->setSelectionMode(QTableView::SingleSelection);
    // 行间隔色
    table->setAlternatingRowColors(true);
    // 启用拖拽
    table->setDragDropMode(QAbstractItemView::DropOnly);

    table->horizontalHeader()->setMinimumHeight(30);

    table->setStyleSheet("QTableView { border: 1px solid gray; background: #E8E8E8; }\
                          QTableView::item{ color: black; }\
                          QTableView::item::selected{ color: black; background: #63B8FF;}");
    table->setColumnWidth(0, 80);

    /* 添加数据 */
    auto model = new QStandardItemModel();
    auto selectModel = new QItemSelectionModel(model);
    model->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("序号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("代号")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QStringLiteral("任务")));

    QStringList mark, mission;
    mark<<"111"<<"222"<<"333"<<"444"<<"555"<<"AAA"<<"BBB"<<"CCC"<<"DDD"<<"EEE";
    mission<<"0x00"<<"0x01"<<"0x02"<<"0x03"<<"0x04"<<"0x05"<<"0x06"<<"0x07"<<"0x08"<<"0x09";
    for(auto i = 0; i < mark.count(); i++) {
        model->setItem(i, 0, new QStandardItem(QString::number(i + 1)));
        model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, new QStandardItem(mark[i]));
        model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 2, new QStandardItem(mission[i]));
        model->item(i, 2)->setTextAlignment(Qt::AlignCenter);
    }
    table->setModel(model);
    table->setSelectionModel(selectModel);

    /* 设置右键菜单 */
    QList<QAction *> actions;
    actions << ui->actionAddRow << ui->actionDeleteRow << ui->actionClearTable;
    table->setContextMenuPolicy(Qt::ActionsContextMenu);
    table->addActions(actions);
}

void MainWindow::onActionAddRowTriggered() {
    ui->tableViewMovable->addRow();
}

void MainWindow::onActionDeleteRowTriggered() {
    ui->tableViewMovable->deleteRow();
}

void MainWindow::onActionClearTableTriggered() {
    ui->tableViewMovable->clearRow();
}

void MainWindow::onBtnFrameLessClicked() {
    m_framelessWindow->show();
}

void MainWindow::on_btn_curveChart_clicked() {
    if(!m_curveChart) m_curveChart = new CurveChart();

    m_curveChart->show();
}

void MainWindow::on_btn_areaChart_clicked() {
    if(!m_areaChart) m_areaChart = new AreaChart();

    m_areaChart->show();
}



