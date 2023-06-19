//
// Created by TURIING on 2023/6/14.
//

#include "GifCapture.h"

GifCapture::GifCapture(QWidget *_parent): QDialog(_parent) {
    m_isCapturing = false;
    m_fps = 10;
    m_gifWriter = nullptr;
    m_gifObj = new Gif;

    m_initWindow();
    m_initUI();
}

void GifCapture::m_initWindow() {
    this->setObjectName("GifCapture");
    this->resize(800, 600);
    this->setSizeGripEnabled(true);

    /* m_verticalLayout */
    m_verticalLayout = new QVBoxLayout(this);
    m_verticalLayout->setSpacing(0);
    m_verticalLayout->setContentsMargins(11, 11, 11, 11);
    m_verticalLayout->setObjectName("m_verticalLayout");
    m_verticalLayout->setContentsMargins(0, 0, 0, 0);

    /* TOP */
    // m_widgetTop
    m_widgetTop = new QWidget(this);
    m_widgetTop->setObjectName("m_widgetTop");
    m_widgetTop->setMinimumSize(QSize(0, 35));
    m_widgetTop->setMaximumSize(QSize(16777215, 35));

    // m_horizontalLayoutTop
    m_horizontalLayoutTop = new QHBoxLayout(m_widgetTop);
    m_horizontalLayoutTop->setSpacing(0);
    m_horizontalLayoutTop->setContentsMargins(11, 11, 11, 11);
    m_horizontalLayoutTop->setObjectName("m_horizontalLayoutTop");
    m_horizontalLayoutTop->setContentsMargins(0, 0, 0, 0);

    // m_btnIcon
    m_btnIcon = new QPushButton(m_widgetTop);
    m_btnIcon->setObjectName("m_btnIcon");
    QSizePolicy sizePolicyForTop(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicyForTop.setHorizontalStretch(0);
    sizePolicyForTop.setVerticalStretch(0);
    sizePolicyForTop.setHeightForWidth(m_btnIcon->sizePolicy().hasHeightForWidth());
    m_btnIcon->setSizePolicy(sizePolicyForTop);
    m_btnIcon->setMinimumSize(QSize(35, 0));
    m_btnIcon->setFlat(true);
    m_btnIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    m_horizontalLayoutTop->addWidget(m_btnIcon);

    // m_labelTitle
    m_labelTitle = new QLabel(m_widgetTop);
    m_labelTitle->setObjectName("m_labelTitle");
    m_labelTitle->setText("GIF录屏工具");
    m_horizontalLayoutTop->addWidget(m_labelTitle);

    // m_spacerTop
    m_spacerTop = new QSpacerItem(87, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_horizontalLayoutTop->addItem(m_spacerTop);

    // m_btnCloseWindow
    m_btnCloseWindow = new QPushButton(m_widgetTop);
    m_btnCloseWindow->setObjectName("m_btnCloseWindow");
    sizePolicyForTop.setHeightForWidth(m_btnCloseWindow->sizePolicy().hasHeightForWidth());
    m_btnCloseWindow->setSizePolicy(sizePolicyForTop);
    m_btnCloseWindow->setMinimumSize(QSize(35, 0));
    m_btnCloseWindow->setFocusPolicy(Qt::NoFocus);
    m_btnCloseWindow->setFlat(true);
    m_btnCloseWindow->setIcon(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    connect(m_btnCloseWindow, &QPushButton::clicked, this, &GifCapture::onBtnCloseWindow);
    m_horizontalLayoutTop->addWidget(m_btnCloseWindow);

    m_verticalLayout->addWidget(m_widgetTop);

    /* Center */
    // m_widgetCenter
    m_widgetCenter = new QWidget(this);
    m_widgetCenter->setObjectName("m_widgetCenter");
    QSizePolicy sizePolicyForCenter(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicyForCenter.setHorizontalStretch(0);
    sizePolicyForCenter.setVerticalStretch(0);
    sizePolicyForCenter.setHeightForWidth(m_widgetCenter->sizePolicy().hasHeightForWidth());
    m_widgetCenter->setSizePolicy(sizePolicyForCenter);

    m_verticalLayout->addWidget(m_widgetCenter);

    /* Bottom */
    // m_widgetBottom
    m_widgetBottom = new QWidget(this);
    m_widgetBottom->setObjectName("m_widgetBottom");
    m_widgetBottom->setMinimumSize(QSize(0, 45));
    m_widgetBottom->setMaximumSize(QSize(16777215, 45));

    // m_horizontalLayoutBottom
    m_horizontalLayoutBottom = new QHBoxLayout(m_widgetBottom);
    m_horizontalLayoutBottom->setSpacing(6);
    m_horizontalLayoutBottom->setContentsMargins(11, 11, 11, 11);
    m_horizontalLayoutBottom->setObjectName("m_horizontalLayoutBottom");
    m_horizontalLayoutBottom->setContentsMargins(9, 9, -1, -1);

    // m_labelFps
    m_labelFps = new QLabel(m_widgetBottom);
    m_labelFps->setObjectName("m_labelFps");
    m_labelFps->setText("帧率");
    m_horizontalLayoutBottom->addWidget(m_labelFps);

    // m_lineEditFps
    m_lineEditFps = new QLineEdit(m_widgetBottom);
    m_lineEditFps->setObjectName("m_lineEditFps");
    m_lineEditFps->setMaximumSize(QSize(50, 16777215));
    m_lineEditFps->setAlignment((Qt::AlignCenter));
    m_horizontalLayoutBottom->addWidget(m_lineEditFps);

    // m_labelWidth
    m_labelWidth = new QLabel(m_widgetBottom);
    m_labelWidth->setObjectName("m_labelWidth");
    m_labelWidth->setText("宽度");
    m_horizontalLayoutBottom->addWidget(m_labelWidth);

    // m_lineEditWidth
    m_lineEditWidth = new QLineEdit(m_widgetBottom);
    m_lineEditWidth->setObjectName("m_lineEditWidth");
    m_lineEditWidth->setMaximumSize(QSize(50, 16777215));
    m_lineEditWidth->setAlignment(Qt::AlignCenter);
    m_horizontalLayoutBottom->addWidget(m_lineEditWidth);
    connect(m_lineEditWidth, &QLineEdit::editingFinished, this, &GifCapture::onResizeWindow);

    // m_labelHeight
    m_labelHeight = new QLabel(m_widgetBottom);
    m_labelHeight->setObjectName("m_labelHeight");
    m_labelHeight->setText("高度");
    m_horizontalLayoutBottom->addWidget(m_labelHeight);

    // m_lineEditHeight
    m_lineEditHeight = new QLineEdit(m_widgetBottom);
    m_lineEditHeight->setObjectName("m_lineEditHeight");
    m_lineEditHeight->setMaximumSize(QSize(50, 16777215));
    m_lineEditHeight->setAlignment(Qt::AlignCenter);
    m_horizontalLayoutBottom->addWidget(m_lineEditHeight);
    connect(m_lineEditHeight, &QLineEdit::editingFinished, this, &GifCapture::onResizeWindow);


    // m_labelCaptureStatus
    m_labelCaptureStatus = new QLabel(m_widgetBottom);
    m_labelCaptureStatus->setObjectName("m_labelCaptureStatus");
    QSizePolicy sizePolicyForStatus(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicyForStatus.setHorizontalStretch(0);
    sizePolicyForStatus.setVerticalStretch(0);
    sizePolicyForStatus.setHeightForWidth(m_labelCaptureStatus->sizePolicy().hasHeightForWidth());
    m_labelCaptureStatus->setSizePolicy(sizePolicyForStatus);
    m_labelCaptureStatus->setAlignment(Qt::AlignCenter);
    m_horizontalLayoutBottom->addWidget(m_labelCaptureStatus);

    // m_btnStart
    m_btnStart = new QPushButton(m_widgetBottom);
    m_btnStart->setObjectName("m_btnStart");
    m_btnStart->setText("开始录制");
    QSizePolicy sizePolicyForStart(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicyForStart.setHorizontalStretch(0);
    sizePolicyForStart.setVerticalStretch(0);
    sizePolicyForStart.setHeightForWidth(m_btnStart->sizePolicy().hasHeightForWidth());
    connect(m_btnStart, &QPushButton::clicked, this, &GifCapture::onBtnStartCapture);
    m_horizontalLayoutBottom->addWidget(m_btnStart);

    m_verticalLayout->addWidget(m_widgetBottom);
}

void GifCapture::onBtnCloseWindow() {
    if(m_gifWriter){
        delete m_gifWriter;
        m_gifWriter = nullptr;
    }
    this->close();
}

void GifCapture::onBtnStartCapture() {
    if(!m_isCapturing) {
        /* 弹出文件对话框 */
        m_fileSavePath = QFileDialog::getSaveFileName(this, "选择保存的位置", qApp->applicationDirPath(), "gif图片(*.gif)");
        if(m_fileSavePath.isEmpty())
            return;
        // 转换编码
        QTextCodec *code = QTextCodec::codecForName("utf-8");
        const char *name = code->fromUnicode(m_fileSavePath).constData();

        size_t width = m_lineEditWidth->text().toInt();
        size_t height = m_lineEditHeight->text().toInt();
        m_fps = m_lineEditFps->text().toInt();

        m_gifWriter = new Gif::GifWriter;
        bool res = m_gifObj->GifBegin(m_gifWriter, name, width, height, m_fps);
        if(!res) {
            delete m_gifWriter;
            m_gifWriter = nullptr;
            return;
        }

        m_count = 0;
        m_labelCaptureStatus->setText("准备捕获中");
        m_btnStart->setText("停止");
        m_isCapturing = true;
        // 延时启动
        m_timer->setInterval(1000 / m_fps);
        QTimer::singleShot(200, m_timer, SLOT(start()));
    } else {
        m_timer->stop();
        m_gifObj->GifEnd(m_gifWriter);
        delete m_gifWriter;
        m_gifWriter = nullptr;
        m_labelCaptureStatus->setText(QString("录制完成，共%1帧").arg(m_count));
        m_btnStart->setText("开始");
        m_isCapturing = false;
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_fileSavePath));
    }
}

void GifCapture::m_initUI() {
    m_borderWidth = 1;
    m_winBgColor = QColor(34, 163, 169);
    m_lineEditFps->setText(QString::number(m_fps));

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &GifCapture::onSaveImage);
    // 设置窗口属性
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);

    QStringList qss;
    qss.append("QLabel{color:#ffffff;}");
    qss.append("#m_btnCloseWindow,#m_btnIcon{border:none;border-radius:0px;}");
    qss.append("#m_btnCloseWindow:hover{background-color:#ff0000;}");
    qss.append("#m_btnCloseWindow{border-top-right-radius:5px;}");
    qss.append("#m_labelTitle{font:bold 16px;}");
    qss.append("#m_labelCaptureStatus{font:15px;}");
    this->setStyleSheet(qss.join(""));

    this->installEventFilter(this);
}

void GifCapture::onSaveImage() {
    if(!m_gifWriter)
        return;

    QScreen *screen = QApplication::primaryScreen();
    QPixmap pix = screen->grabWindow(0, this->x() + m_captureArea.x(), this->y() + m_captureArea.y(), m_captureArea.width(), m_captureArea.height());
    QImage image = pix.toImage().convertToFormat(QImage::Format_RGBA8888);

    m_gifObj->GifWriteFrame(m_gifWriter, image.bits(), m_captureArea.width(), m_captureArea.height(), m_fps);
    m_count++;
    m_labelCaptureStatus->setText(QString("正在录制第%1帧").arg(m_count));
}

bool GifCapture::eventFilter(QObject *watched, QEvent *event) {
    static QPoint mousePoint;
    static bool isMousePressed = false;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(mouseEvent->type() == QEvent::MouseButtonPress) {
        if(mouseEvent->button() == Qt::LeftButton) {
            isMousePressed = true;
            mousePoint = mouseEvent->globalPos() - this->pos();
            return true;
        }
    }
    else if(mouseEvent->type() == QEvent::MouseButtonRelease) {
        isMousePressed = false;
        return false;
    }
    else if(mouseEvent->type() == QEvent::MouseMove) {
        if(isMousePressed) {
            this->move(mouseEvent->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void GifCapture::resizeEvent(QResizeEvent *event) {
    // 更新数值
    m_lineEditWidth->setText(QString::number(m_widgetCenter->width()));
    m_lineEditHeight->setText(QString::number(m_widgetCenter->height()));

    QDialog::resizeEvent(event);
}

void GifCapture::paintEvent(QPaintEvent *event) {
    size_t width = m_lineEditWidth->text().toInt();
    size_t height = m_lineEditHeight->text().toInt();
    m_captureArea = QRect(m_borderWidth, m_widgetTop->height(), width - (m_borderWidth * 2), height);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_winBgColor);
    painter.drawRoundedRect(this->rect(), 5, 5);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.fillRect(m_captureArea, Qt::SolidPattern);
}

void GifCapture::onResizeWindow() {
    size_t width = m_lineEditWidth->text().toInt();
    size_t height = m_lineEditHeight->text().toInt();

    this->resize(width, height + m_widgetTop->height() + m_widgetBottom->height());
}
