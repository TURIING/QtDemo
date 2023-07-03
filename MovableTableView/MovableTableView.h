//
// Created by TURIING on 2023/7/2.
//

#ifndef QTDEMO_MOVABLETABLEVIEW_H
#define QTDEMO_MOVABLETABLEVIEW_H

#include <QTableView>
#include <QLabel>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QPainter>

class MovableTableView : public QTableView{
    Q_OBJECT
public:
    explicit MovableTableView(QWidget *_parent = Q_NULLPTR);
    void setModel(QStandardItemModel *_model);
    void setSelectionModel(QItemSelectionModel *_selectModel) override;
    void addRow();
    void deleteRow();
    void clearRow();
protected:
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void dragEnterEvent(QDragEnterEvent *_event) override;
    void dragMoveEvent(QDragMoveEvent *_event) override;
    void dropEvent(QDropEvent *_event) override;
private:
    int computeOffset();
    void executeDrag();
    void moveRow(int rowFrom, int rowTo);
    void resetOrder();
private:
    QLabel *m_indicateLabel;                                            // 指示线
    QStandardItemModel *m_model = nullptr;
    QItemSelectionModel *m_selectModel = nullptr;
    int m_rowHeight = 30;                                               // 行高
    bool m_isValidPress = false;                                        // 移动前是否点击有效行
    int m_rowFrom = 0;                                                  // 拖放起始行
    int m_rowTo = 0;                                                    // 拖放目标行
    QStringList m_dragTextList;                                         // 保存拖动行的每列的内容
    QPoint m_dragStartPoint;                                            // 拖放起点
    QPoint m_dragPointAtItem;
public: signals:
    void rowChanged(int from, int to);
};


#endif //QTDEMO_MOVABLETABLEVIEW_H
