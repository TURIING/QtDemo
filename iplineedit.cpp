//
// Created by TURIING on 2023/6/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IPLineEdit.h" resolved

#include "iplineedit.h"


IPLineEdit::IPLineEdit(QWidget *parent): QWidget(parent){
    /* 设置UI */
    m_bgColor = "#FFFFFF";
    m_borderColor = "#A6B5B8";
    m_borderRadius = 3.f;

    m_LabelDot1 = new QLabel(this);
    m_LabelDot1->setAlignment(Qt::AlignCenter);
    m_LabelDot1->setText("·");

    m_LabelDot2 = new QLabel(this);
    m_LabelDot2->setAlignment(Qt::AlignCenter);
    m_LabelDot2->setText("·");

    m_LabelDot3 = new QLabel(this);
    m_LabelDot3->setAlignment(Qt::AlignCenter);
    m_LabelDot3->setText("·");

    m_LineEditIp1 = new QLineEdit(this);
    m_LineEditIp1->setObjectName("LineEditIp1");
    m_LineEditIp1->setAlignment(Qt::AlignCenter);
    m_LineEditIp1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_LineEditIp1, &QLineEdit::textChanged, this, &IPLineEdit::onTextChanged);

    m_LineEditIp2 = new QLineEdit(this);
    m_LineEditIp2->setObjectName("LineEditIp2");
    m_LineEditIp2->setAlignment(Qt::AlignCenter);
    m_LineEditIp2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_LineEditIp2, &QLineEdit::textChanged, this, &IPLineEdit::onTextChanged);

    m_LineEditIp3 = new QLineEdit(this);
    m_LineEditIp3->setObjectName("LineEditIp3");
    m_LineEditIp3->setAlignment(Qt::AlignCenter);
    m_LineEditIp3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_LineEditIp3, &QLineEdit::textChanged, this, &IPLineEdit::onTextChanged);

    m_LineEditIp4 = new QLineEdit(this);
    m_LineEditIp4->setObjectName("LineEditIp4");
    m_LineEditIp4->setAlignment(Qt::AlignCenter);
    m_LineEditIp4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_LineEditIp4, &QLineEdit::textChanged, this, &IPLineEdit::onTextChanged);

    /* 设置正则校验数据 */
    QString pattern = "(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})";
    QRegularExpression regExp(pattern);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);

    m_LineEditIp1->setValidator(validator);
    m_LineEditIp2->setValidator(validator);
    m_LineEditIp3->setValidator(validator);
    m_LineEditIp4->setValidator(validator);

    // 绑定事件过滤器，识别键盘按下
    m_LineEditIp1->installEventFilter(this);
    m_LineEditIp2->installEventFilter(this);
    m_LineEditIp3->installEventFilter(this);
    m_LineEditIp4->installEventFilter(this);

    m_frame = new QFrame(this);
    m_frame->setObjectName("frameIP");
    QStringList qss;
    qss.append(QString("QFrame#frameIP{border:1px solid %1;border-radius:%2px;}").arg(m_borderColor).arg(m_borderRadius));
    qss.append(QString("QLabel{min-width:5px;background-color:%1;}").arg(m_bgColor));
    qss.append(QString("QLineEdit{background-color:%1;border:none;}").arg(m_bgColor));
    qss.append(QString("QLineEdit#LineEditIp1{border-top-left-radius:%1px;border-bottom-left-radius:%1px;}").arg(m_borderRadius));
    qss.append(QString("QLineEdit#LineEditIp4{border-top-right-radius:%1px;border-bottom-right-radius:%1px;}").arg(m_borderRadius));
    m_frame->setStyleSheet(qss.join(""));

    m_verticalLayout = new QVBoxLayout(this);
    m_verticalLayout->setContentsMargins(0, 0, 0, 0);
    m_verticalLayout->setSpacing(0);
    m_verticalLayout->addWidget(m_frame);

    m_horizontalLayout = new QHBoxLayout(m_frame);
    m_horizontalLayout->setContentsMargins(0 ,0 ,0 ,0);
    m_horizontalLayout->setSpacing(0);
    m_horizontalLayout->addWidget(m_LineEditIp1);
    m_horizontalLayout->addWidget(m_LabelDot1);
    m_horizontalLayout->addWidget(m_LineEditIp2);
    m_horizontalLayout->addWidget(m_LabelDot2);
    m_horizontalLayout->addWidget(m_LineEditIp3);
    m_horizontalLayout->addWidget(m_LabelDot3);
    m_horizontalLayout->addWidget(m_LineEditIp4);
}

IPLineEdit::~IPLineEdit() {}

/*
 * 事件过滤器
 */
bool IPLineEdit::eventFilter(QObject *watched, QEvent *event) {
    if(event->type() == QEvent::KeyPress) {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(watched);

        if(lineEdit == m_LineEditIp1 || lineEdit == m_LineEditIp2 || lineEdit == m_LineEditIp3 || lineEdit == m_LineEditIp4) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            // 如果当前按下了小数点则移动焦点到下一个输入框
            if(keyEvent->text() == ".")
                this->focusNextChild();
            // 如果按下了退格键并且当前文本框已经没有了内容则焦点往前移
            if(keyEvent->key() == Qt::Key_Backspace) {
                if(lineEdit->text().length() <= 1)
                    this->focusNextPrevChild(false);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void IPLineEdit::onTextChanged(const QString &_text) {
    int value = _text.toInt();
    //判断当前是否输入完成一个网段,是的话则自动移动到下一个输入框
    if(value >= 100 && value <= 255)
        this->focusNextChild();
    m_ip = QString("%1.%2.%3.%4").arg(m_LineEditIp1->text()).arg(m_LineEditIp2->text()).arg(m_LineEditIp3->text()).arg(m_LineEditIp4->text());
}

QString IPLineEdit::getIp() const {
    return m_ip;
}

QSize IPLineEdit::sizeHint() const {
    return QSize(250, 20);
}

QSize IPLineEdit::minSizeHint() const {
    return QSize(30, 10);
}

void IPLineEdit::setIp(const QString &_ip) {
    // 检测输入的IP地址是否合法
    QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    if(!regExp.exactMatch(_ip))
        return;

    if(m_ip != _ip) {
        m_ip = _ip;
        QStringList list = m_ip.split(".");
        m_LineEditIp1->setText(list.at(0));
        m_LineEditIp2->setText(list.at(1));
        m_LineEditIp3->setText(list.at(2));
        m_LineEditIp4->setText(list.at(3));
    }
}

void IPLineEdit::clear() {
    m_LineEditIp1->clear();
    m_LineEditIp2->clear();
    m_LineEditIp3->clear();
    m_LineEditIp4->clear();
    m_LineEditIp1->setFocus();
}

void IPLineEdit::setBgColor(const QString &_bgColor) {
    if(m_bgColor != _bgColor)
        m_bgColor = _bgColor;
}

void IPLineEdit::setBorderColor(const QString &_borderColor) {
    if(m_borderColor != _borderColor)
        m_borderColor = _borderColor;
}

void IPLineEdit::setBorderRadius(float _borderRadius) {
    if(m_borderRadius != _borderRadius)
        m_borderRadius = _borderRadius;
}

