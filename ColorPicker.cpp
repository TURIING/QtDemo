//
// Created by TURIING on 2023/6/13.
//

#include "ColorPicker.h"

ColorPicker::ColorPicker(QWidget *parent): QWidget(parent) {
    /* m_hBoxLayout */
    m_hBoxLayout = new QHBoxLayout(this);
    m_hBoxLayout->setSpacing(20);
    m_hBoxLayout->setContentsMargins(0, 5, 0, 0);

    /* m_gridLayout */
    m_gridLayout = new QGridLayout();
    m_gridLayout->setSpacing(6);

    /* m_verticalLayout */
    m_verticalLayout = new QVBoxLayout();
    m_verticalLayout->setSpacing(0);
    m_verticalLayout->setContentsMargins(0, 12, 0, 12);

    /* m_labelColor */
    m_labelColor = new QLabel(this);
    m_labelColor->setText("+");
    m_labelColor->setStyleSheet("background-color: rgb(255, 107, 107); color: rgb(250, 250, 250);");
    m_labelColor->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPixelSize(35);
    font.setBold(true);
    m_labelColor->setFont(font);

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_labelColor->sizePolicy().hasHeightForWidth());
    m_labelColor->setSizePolicy(sizePolicy);

    m_labelColor->setMinimumSize(QSize(80, 70));
    m_labelColor->setMaximumSize(QSize(80, 70));
    m_labelColor->setCursor(QCursor(Qt::CrossCursor));
    m_labelColor->setFrameShape(QFrame::StyledPanel);
    m_labelColor->setFrameShadow(QFrame::Sunken);

    m_verticalLayout->addWidget(m_labelColor);

    /* labelText */
    m_labelText = new QLabel(this);
    m_labelText->setMinimumSize(QSize(0, 18));
    m_labelText->setStyleSheet("background-color: rgb(0, 0, 0); color: rgb(200, 200, 200);");
    m_labelText->setAlignment(Qt::AlignCenter);
    m_labelText->setText("点击捕获");

    m_verticalLayout->addWidget(m_labelText);
    m_hBoxLayout->addLayout(m_verticalLayout);

    /* m_labelWeb、m_lineEditWeb */
    m_labelWeb = new QLabel(this);
    m_labelWeb->setText("HEX:");
    m_gridLayout->addWidget(m_labelWeb, 0, 0, 1, 1);

    m_lineEditWeb = new QLineEdit(this);
    m_gridLayout->addWidget(m_lineEditWeb, 0, 1, 1, 1);

    /* m_labelRgb、m_lineEditRgb */
    m_labelRgb = new QLabel(this);
    m_labelRgb->setText("RGB:");
    m_gridLayout->addWidget(m_labelRgb, 1, 0, 1, 1);

    m_lineEditRgb = new QLineEdit(this);
    m_gridLayout->addWidget(m_lineEditRgb, 1, 1, 1, 1);

    /* m_labelLocation、m_lineEditLocation */
    m_labelLocation = new QLabel(this);
    m_labelLocation->setText("坐标:");
    m_gridLayout->addWidget(m_labelLocation, 2, 0, 1, 1);

    m_lineEditLocation = new QLineEdit(this);
    m_gridLayout->addWidget(m_lineEditLocation, 2, 1, 1, 1);

    m_hBoxLayout->addLayout(m_gridLayout);

    /* ColorPicker */
    this->setLayout(m_hBoxLayout);
    this->setFixedSize(300, 108);

    m_clipBoard = QApplication::clipboard();
    m_isPressd = false;

    /* m_timer */
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &ColorPicker::pickColor);
    m_timer->start();
}

void ColorPicker::pickColor() {
    if(!m_isPressd)
        return;
    /* 获取鼠标位置坐标 */
    auto cursor_x = QCursor::pos().x();
    auto cursor_y = QCursor::pos().y();
    m_lineEditLocation->setText(QString("X:%1  Y:%2").arg(cursor_x).arg(cursor_y));
    /* 捕获鼠标位置的像素 */
    QScreen *screen = qApp->primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, cursor_x, cursor_y, 1, 1);
    if(pixmap.isNull())
        return;
    QString decimalValue;
    QImage image = pixmap.toImage();
    if(image.valid(0, 0)){
        QColor color = image.pixel(0, 0);
        decimalValue = QString("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        m_lineEditRgb->setText(decimalValue);
        m_lineEditWeb->setText(color.name().toUpper());
    }
    /* 实时更新捕获的颜色 */
    m_labelColor->setStyleSheet(QString("background: rgb(%1)").arg(decimalValue));
}

void ColorPicker::mousePressEvent(QMouseEvent *event) {
    /* 判断鼠标按下时，是否在取色区域 */
    if(m_labelColor->rect().contains(event->pos())) {
        m_isPressd = true;
    }
}

void ColorPicker::mouseReleaseEvent(QMouseEvent *event) {
    m_isPressd = false;
}

ColorPicker::~ColorPicker() {

}



