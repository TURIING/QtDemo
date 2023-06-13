//
// Created by TURIING on 2023/6/12.
//

#ifndef QTDEMO_IPLINEEDIT_H
#define QTDEMO_IPLINEEDIT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class IPLineEdit; }
QT_END_NAMESPACE

class IPLineEdit : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString m_ip READ getIp WRITE setIp)
public:
    explicit IPLineEdit(QWidget *parent = nullptr);
    virtual ~IPLineEdit() override;

    QString getIp() const;
    QSize sizeHint() const;
    QSize minSizeHint() const;
    void setIp(const QString &_ip);
    void clear();
    void setBgColor(const QString &_bgColor);
    void setBorderColor(const QString &_borderColor);
    void setBorderRadius(float _borderRadius);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;


private:

    QLabel *m_LabelDot1;                                        // 第一个小圆点
    QLabel *m_LabelDot2;                                        // 第二个小圆点
    QLabel *m_LabelDot3;                                        // 第三个小圆点

    QLineEdit *m_LineEditIp1;                                   // 第一个IP输入框
    QLineEdit *m_LineEditIp2;                                   // 第二个IP输入框
    QLineEdit *m_LineEditIp3;                                   // 第三个IP输入框
    QLineEdit *m_LineEditIp4;                                   // 第四个IP输入框

    QFrame *m_frame;
    QVBoxLayout *m_verticalLayout;
    QHBoxLayout *m_horizontalLayout;

    QString m_ip;

    QString m_bgColor;                                          // 背景颜色
    QString m_borderColor;                                      // 边框颜色
    float m_borderRadius;                                      // 边框圆角角度

private slots:
    void onTextChanged(const QString &_text);

public: signals:
};


#endif //QTDEMO_IPLINEEDIT_H
