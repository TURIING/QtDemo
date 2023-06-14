//
// Created by TURIING on 2023/6/13.
//

#ifndef QTDEMO_MAINWINDOW_H
#define QTDEMO_MAINWINDOW_H

#include <QMainWindow>
#include "iplineedit.h"
#include "ColorPicker.h"
#include <QPushButton>

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

private slots:
    void onBtnMakeIPClicked();
    void onBtnClearIPClicked();
    void onBtnOpenColorPickerClicked();
};


#endif //QTDEMO_MAINWINDOW_H
