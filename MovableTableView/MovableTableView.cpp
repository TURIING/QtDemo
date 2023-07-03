//
// Created by TURIING on 2023/7/2.
//

#include "MovableTableView.h"

MovableTableView::MovableTableView(QWidget *_parent) : QTableView(_parent) {
    this->setAcceptDrops(true);

    m_indicateLabel = new QLabel(this);
    m_indicateLabel->setFixedHeight(2);
    m_indicateLabel->setGeometry(0, 1, this->width(), 2);
    m_indicateLabel->setStyleSheet("border: 1px solid #8B7500");
    m_indicateLabel->hide();
}

void MovableTableView::setModel(QStandardItemModel *_model) {
    m_model = _model;
    QTableView::setModel(_model);
}

void MovableTableView::setSelectionModel(QItemSelectionModel *_selectModel) {
    m_selectModel = _selectModel;
    QTableView::setSelectionModel(_selectModel);
}

/*
 * 在当前行的下一行新增行
 */
void MovableTableView::addRow() {
    int currentRow = m_selectModel->currentIndex().row();
    m_model->insertRow(currentRow + 1);
}

/*
 * 删除当前选中行
 */
void MovableTableView::deleteRow() {
    int currentRow = m_selectModel->currentIndex().row();
    m_model->removeRow(currentRow);
    resetOrder();
}

/*
 * 清空所有行
 */
void MovableTableView::clearRow() {
    m_model->removeRows(0, m_model->rowCount());
}

void MovableTableView::mousePressEvent(QMouseEvent *_event) {
    if(_event->button() == Qt::LeftButton){
        QModelIndex index = this->indexAt(_event->pos());
        QModelIndex topIndex = this->indexAt(QPoint(30, 0));

        int pixelOffset = computeOffset();

        // 清除上次保存的数据
        m_dragTextList.clear();

        if(index.isValid()) {
            m_isValidPress = true;
            m_dragStartPoint = _event->pos();
            for(auto i = 0; i < m_model->columnCount(); i++) {
                if(m_model->item(index.row(), i))
                    m_dragTextList.append(m_model->item(index.row(), i)->text());
            }
            int y = (index.row() - topIndex.row()) * m_rowHeight - pixelOffset;
            m_dragPointAtItem = m_dragStartPoint - QPoint(0, y);
            m_rowFrom = index.row();
        }
        else
            m_isValidPress = false;
    }

    QTableView::mousePressEvent(_event);
}

/*
 * 计算像素补偿，用于解决当顶部未显示一整行时候产生的像素偏差
 */
int MovableTableView::computeOffset() {
    QModelIndex index = this->indexAt(QPoint(15, 0));
    int topRow = index.row();
    for(auto columnPixel = 0; columnPixel < m_rowHeight; columnPixel++) {
        index = this->indexAt(QPoint(15, columnPixel));
        if(index.row() - topRow)
            return m_rowHeight - columnPixel;
    }
    return 0;
}

void MovableTableView::mouseMoveEvent(QMouseEvent *_event) {
    if(!m_isValidPress) return;
    if(!(_event->buttons() & Qt::LeftButton)) return;
    if((_event->pos() - m_dragStartPoint).manhattanLength() < QApplication::startDragDistance()) return;

    m_indicateLabel->show();
    executeDrag();
    m_indicateLabel->hide();
    m_isValidPress = false;
}

/*
 * 执行拖放
 */
void MovableTableView::executeDrag() {
    auto *mimeData = new QMimeData;
    mimeData->setText("m_dragTextList");

    auto *drag = new QDrag(this);
    drag->setMimeData(mimeData);

    // 设置拖动时的缩略图阴影
    QPixmap dragImg(this->width(), m_rowHeight);
    dragImg.fill(QColor(255, 255, 255, 100));

    QPainter painter(&dragImg);
    painter.setPen(QColor(0, 0 , 0, 200));
    auto rect = QRectF(40, 0, this->width(), m_rowHeight);
    painter.drawText(rect, m_dragTextList.join("       "), QTextOption(Qt::AlignVCenter));

    drag->setPixmap(dragImg);
    drag->setHotSpot(m_dragPointAtItem);
    if(drag->exec(Qt::MoveAction) == Qt::MoveAction)
        this->selectionModel()->clearSelection();
}

void MovableTableView::dragEnterEvent(QDragEnterEvent *_event) {
    if(_event->mimeData()->hasText())
        _event->acceptProposedAction();
    else{
        _event->ignore();
        QTableView::dragEnterEvent(_event);
    }
}

void MovableTableView::dragMoveEvent(QDragMoveEvent *_event) {
    if(_event->mimeData()->hasText()){
        int currentRowNum = 0;
        // 欲拖动行的索引
        QModelIndex index = this->indexAt(_event->pos());
        // 第一行（非表头）的索引
        QModelIndex topIndex = this->indexAt(QPoint(30, 0));

        int pixelOffset = computeOffset();
        // 拖动的y轴距离，用于确定指示条的y轴位置
        int y = 0;

        if(index.isValid()){
            y = (index.row() - topIndex.row()) * m_rowHeight - pixelOffset;
            // 如果鼠标当前位置大于某一行1/2的位置，则指示条应该置于该行下面
            if(_event->pos().y() - y >= m_rowHeight / 2)
                currentRowNum = index.row() + 1;
            else
                currentRowNum = index.row();
        }
        else
            currentRowNum = m_model->rowCount();

        m_rowTo = currentRowNum;
        y = (m_rowTo - topIndex.row() + 1) * m_rowHeight - pixelOffset;
        m_indicateLabel->setGeometry(1, y, this->width() - 2, 2);
        _event->acceptProposedAction();
        return;
    }

    _event->ignore();
    QTableView::dragMoveEvent(_event);
}

void MovableTableView::dropEvent(QDropEvent *_event) {
    if(_event->mimeData()->hasText()){
        if(m_rowTo != m_rowFrom) {
            moveRow(m_rowFrom, m_rowTo);
            m_dragTextList.clear();
        }
        _event->acceptProposedAction();
        return;
    }

    _event->ignore();
    QTableView::dropEvent(_event);
}

/*
 * 移动行
 */
void MovableTableView::moveRow(int rowFrom, int rowTo) {
    assert(rowFrom != rowTo);

    if(!(m_model->item(rowFrom, 1))) return;

    QList<QStandardItem *> items;
    QStandardItem *item = nullptr;
    for(auto i = 0; i < m_model->columnCount(); i++) {
        item = new QStandardItem(m_dragTextList.at(i));
        item->setTextAlignment(m_model->item(rowFrom)->textAlignment());
        items.append(item);
    }

    m_model->insertRow(rowTo, items);

    if(rowFrom < rowTo) {
        m_model->removeRow(rowFrom);
        this->selectRow(rowTo - 1);
    }
    else {
        m_model->removeRow(rowFrom + 1);
        this->selectRow(rowTo);
    }
    resetOrder();
    emit rowChanged(m_rowFrom, m_rowTo);
}

/*
 * 重排序号
 */
void MovableTableView::resetOrder() {
    for(auto i = 0; i < m_model->rowCount(); i++) {
        m_model->item(i, 0)->setText(QString::number(i + 1));
        m_model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    }
}
