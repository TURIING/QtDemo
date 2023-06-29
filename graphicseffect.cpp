//
// Created by TURIING on 2023/6/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GraphicsEffect.h" resolved

#include "graphicseffect.h"
#include "ui_GraphicsEffect.h"


GraphicsEffect::GraphicsEffect(QWidget *parent) :QWidget(parent), ui(new Ui::GraphicsEffect) {
    ui->setupUi(this);
    /* blur */
    m_blurEffect = new QGraphicsBlurEffect(this);
    assert(m_blurEffect != nullptr);
    m_blurEffect->setBlurRadius(0);
    ui->label_blur->setGraphicsEffect(m_blurEffect);

    /* opacity */
    m_opacityEffect = new QGraphicsOpacityEffect(this);
    assert(m_opacityEffect != nullptr);
    m_opacityEffect->setOpacity(1);
    ui->label_opacity->setGraphicsEffect(m_opacityEffect);

    /* colorize */
    m_colorizeEffect = new QGraphicsColorizeEffect(this);
    assert(m_colorizeEffect != nullptr);
    m_colorizeEffect->setColor(QColor(0, 0, 0, 100));
    m_colorizeEffect->setStrength(0.0);
    ui->label_colorize->setGraphicsEffect(m_colorizeEffect);

    /* dropShadow */
    m_dropShadowEffect = new QGraphicsDropShadowEffect(this);
    assert(m_dropShadowEffect != nullptr);
    m_dropShadowEffect->setColor(Qt::black);
    m_dropShadowEffect->setOffset(0, 0);
    m_dropShadowEffect->setBlurRadius(0);
    ui->label_dropShadow->setGraphicsEffect(m_dropShadowEffect);

    connect(ui->slider_blur, &QSlider::valueChanged, this, [=](int _value) { m_blurEffect->setBlurRadius(_value);});
    connect(ui->slider_opacity, &QSlider::valueChanged, this, [=](int _value) {
        auto value = 1.0 - (_value / 10.0);
        m_opacityEffect->setOpacity(value);
    });
    connect(ui->slider_colorize, &QSlider::valueChanged, this, [=](int _value) { m_colorizeEffect->setStrength(_value / 10.0);});
    connect(ui->slider_shadow, &QSlider::valueChanged, this, [=](int _value) {m_dropShadowEffect->setBlurRadius(_value);});


}

GraphicsEffect::~GraphicsEffect() {
    delete ui;
}
