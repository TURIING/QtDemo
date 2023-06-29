//
// Created by TURIING on 2023/6/29.
//

#ifndef QTDEMO_GRAPHICSEFFECT_H
#define QTDEMO_GRAPHICSEFFECT_H

#include <QWidget>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsDropShadowEffect>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphicsEffect; }
QT_END_NAMESPACE

class GraphicsEffect : public QWidget {
Q_OBJECT

public:
    explicit GraphicsEffect(QWidget *parent = nullptr);

    ~GraphicsEffect() override;

private:
    Ui::GraphicsEffect *ui;

    QGraphicsBlurEffect *m_blurEffect = Q_NULLPTR;                                      // 模糊
    QGraphicsOpacityEffect *m_opacityEffect = Q_NULLPTR;                                // 透明
    QGraphicsColorizeEffect *m_colorizeEffect = Q_NULLPTR;                              // 颜色
    QGraphicsDropShadowEffect *m_dropShadowEffect = Q_NULLPTR;                          // 阴影
};


#endif //QTDEMO_GRAPHICSEFFECT_H
