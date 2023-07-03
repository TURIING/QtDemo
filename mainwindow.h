//
// Created by TURIING on 2023/6/13.
//

#ifndef QTDEMO_MAINWINDOW_H
#define QTDEMO_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsDropShadowEffect>
#include <QStandardItemModel>

#include "iplineedit.h"
#include "ColorPicker.h"
#include "GifCapture.h"
#include "ScrollText.h"
#include "SphericalProgressBar.h"
#include "SwitchButton.h"
#include "graphicseffect.h"
#include "AnimationButton.h"
#include "MovableTableView/MovableTableView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
private:
    void initTable();

private:
    Ui::MainWindow *ui;
    GifCapture *m_gifCapture = nullptr;
    SphericalProgressBar *m_sphericalProgressBar = nullptr;
    GraphicsEffect *m_graphicsEffect = nullptr;

private slots:
    void onBtnMakeIPClicked();
    void onBtnClearIPClicked();
    void onBtnGifPopupClicked();
    void onBtnScrollTextClicked();
    void onBtnSphericalProgressBarPopClicked();
    void onBtnAnimationButtonClicked();
    void onActionAddRowTriggered();
    void onActionDeleteRowTriggered();
    void onActionClearTableTriggered();
};


#endif //QTDEMO_MAINWINDOW_H
