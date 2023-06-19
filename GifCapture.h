//
// Created by TURIING on 2023/6/14.
//

#ifndef QTDEMO_GIFCAPTURE_H
#define QTDEMO_GIFCAPTURE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QStyle>
#include <QFileDialog>
#include <QApplication>
#include <QTextCodec>
#include <QTimer>
#include <QDesktopServices>
#include <QScreen>
#include <QMouseEvent>
#include <QPainter>
#include "gif.h"

class GifCapture: public QDialog{
    Q_OBJECT


public:
    explicit GifCapture(QWidget *_parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void m_initWindow();
    void m_initUI();


private slots:
    void onBtnCloseWindow();
    void onBtnStartCapture();
    void onSaveImage();
    void onResizeWindow();


private:
    QVBoxLayout *m_verticalLayout;
    /* UI */
    QColor m_winBgColor;                                      // 窗体颜色
    /* Top */
    QHBoxLayout *m_horizontalLayoutTop;
    QWidget *m_widgetTop;                                     // 标题栏
    QPushButton *m_btnIcon;                                   // 窗口图标
    QLabel *m_labelTitle;                                     // 窗口标题
    QPushButton *m_btnCloseWindow;                            // 关闭按钮
    QSpacerItem *m_spacerTop;

    /* Center */
    QWidget *m_widgetCenter;                                  // 中间部分
    size_t m_borderWidth;                                     // 边框宽度

    /* Bottom */
    QWidget *m_widgetBottom;                                   // 底部
    QHBoxLayout *m_horizontalLayoutBottom;
    QLabel *m_labelFps;
    QLineEdit *m_lineEditFps;                                  // 帧率编辑框
    QLabel *m_labelWidth;
    QLineEdit *m_lineEditWidth;                                // 窗口宽度编辑框
    QLabel *m_labelHeight;
    QLineEdit *m_lineEditHeight;                               // 窗口高度编辑框
    QLabel *m_labelCaptureStatus;                              // 录制状态
    QPushButton *m_btnStart;                                   // 开始捕获

    Gif *m_gifObj;                                             // Gif类对象
    Gif::GifWriter *m_gifWriter;
    bool m_isCapturing;                                        // 是否正在捕获
    QString m_fileSavePath;                                    // 文件保存路径
    size_t m_fps;                                              // 帧率
    size_t m_count;                                            // 帧数
    QTimer *m_timer;                                           // 用于截屏
    QRect m_captureArea;                                       // 截屏区域



};


#endif //QTDEMO_GIFCAPTURE_H
