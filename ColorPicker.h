//
// Created by TURIING on 2023/6/13.
//

#ifndef QTDEMO_COLORPICKER_H
#define QTDEMO_COLORPICKER_H
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>

class ColorPicker: public QWidget{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = nullptr);
    virtual ~ColorPicker();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;




private:
    QHBoxLayout *m_hBoxLayout;
    QGridLayout *m_gridLayout;
    QVBoxLayout *m_verticalLayout;
    QLabel *m_labelColor;
    QLabel *m_labelText;
    QLabel *m_labelWeb;
    QLineEdit *m_lineEditWeb;
    QLabel *m_labelRgb;
    QLineEdit *m_lineEditRgb;
    QLabel *m_labelLocation;
    QLineEdit *m_lineEditLocation;

    QClipboard *m_clipBoard;
    bool m_isPressd;
    QTimer *m_timer;

private slots:
    void pickColor();
};


#endif //QTDEMO_COLORPICKER_H
