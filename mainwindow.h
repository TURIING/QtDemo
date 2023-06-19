//
// Created by TURIING on 2023/6/13.
//

#ifndef QTDEMO_MAINWINDOW_H
#define QTDEMO_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "iplineedit.h"
#include "ColorPicker.h"
#include "GifCapture.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    GifCapture *m_gifCapture;

private slots:
    void onBtnMakeIPClicked();
    void onBtnClearIPClicked();
    void onBtnGifPopupClicked();
};


#endif //QTDEMO_MAINWINDOW_H
