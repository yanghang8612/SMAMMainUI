#include <QMessageBox>
#include <QScrollBar>
#include <QWheelEvent>
#include <QDebug>

#include "sharedmemoryinfo_widget.h"
#include "ui_sharedmemoryinfo_widget.h"

#include "main_component_header.h"

SharedMemoryInfoWidget::SharedMemoryInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SharedMemoryInfoWidget), buffer(0), hexTableChanging(false), charTableChanging(false)
{
    ui->setupUi(this);
    this->hide();
    ui->memoryHexInfoTable->setColumnCount(16);
    ui->memoryHexInfoTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->memoryHexInfoTable->setShowGrid(false);
    ui->memoryHexInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memoryHexInfoTable->verticalScrollBar()->installEventFilter(this);
    ui->memoryCharInfoTable->setColumnCount(16);
    ui->memoryCharInfoTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->memoryCharInfoTable->setShowGrid(false);
    ui->memoryCharInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memoryCharInfoTable->verticalScrollBar()->installEventFilter(this);
}

SharedMemoryInfoWidget::~SharedMemoryInfoWidget()
{
    delete ui;
}

void SharedMemoryInfoWidget::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    updateView();
}

bool SharedMemoryInfoWidget::eventFilter(QObject* target, QEvent* event)
{
    if(event->type() == QEvent::Wheel)
    {
        QScrollBar* scrollBar = 0;
        if (target == ui->memoryHexInfoTable->verticalScrollBar()){
            scrollBar = ui->memoryCharInfoTable->verticalScrollBar();
        }
        if (target == ui->memoryCharInfoTable->verticalScrollBar()){
            scrollBar = ui->memoryHexInfoTable->verticalScrollBar();
        }
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
        scrollBar->setValue(scrollBar->value() - wheelEvent->delta() / 40);
    }
    return QTabWidget::eventFilter(target, event);
}

void SharedMemoryInfoWidget::on_viewButton_clicked()
{
    if (ui->memoryIDEdit->text().isEmpty()) {
        return;
    }
    bool ok;
    int memoryID = ui->memoryIDEdit->text().toInt(&ok);
    if (!ok) {
        return;
    }
    else {
        sharedMemoryPointer = FindMemoryInfoFunc(memoryID, 0);
        if (ui->bufferTypeBox->currentIndex() == 0) {
            buffer = new SharedBuffer(sharedMemoryPointer);
            if (buffer->getBufferSize() == 0) {
                QMessageBox::warning(this, tr("提示"), tr("访问了未申请过的共享缓冲区"), QMessageBox::Ok);
                return;
            }
        }
        updateView();
    }
}

void SharedMemoryInfoWidget::on_autoUpdateButton_clicked(bool checked)
{
    static int timerID;
    if (checked) {
        ui->autoUpdateButton->setText(tr("停止刷新"));
        timerID = startTimer(300);
    }
    else {
        ui->autoUpdateButton->setText(tr("开始刷新"));
        killTimer(timerID);
    }
}

void SharedMemoryInfoWidget::on_memoryHexInfoTable_itemSelectionChanged()
{
    if (charTableChanging) {
        return;
    }
    hexTableChanging = true;
    ui->memoryCharInfoTable->clearSelection();
    foreach (QTableWidgetSelectionRange range, ui->memoryHexInfoTable->selectedRanges()) {
        ui->memoryCharInfoTable->setRangeSelected(range, true);
    }
    hexTableChanging = false;
}

void SharedMemoryInfoWidget::on_memoryCharInfoTable_itemSelectionChanged()
{
    if (hexTableChanging) {
        return;
    }
    charTableChanging = true;
    ui->memoryHexInfoTable->clearSelection();
    foreach (QTableWidgetSelectionRange range, ui->memoryCharInfoTable->selectedRanges()) {
        ui->memoryHexInfoTable->setRangeSelected(range, true);
    }
    charTableChanging = false;
}

void SharedMemoryInfoWidget::updateView()
{
    if (ui->bufferTypeBox->currentIndex() == 0) {
        if (buffer == 0) {
            return;
        }
        ui->bufferSizeEdit->setText(QString::number(buffer->getBufferSize()));
        ui->blockSizeEdit->setText(QString::number(buffer->getBlockSize()));
        ui->writePointerEdit->setText(QString::number(buffer->getWritePointer()));
        ui->readWriteLockEdit->setText(QString::number(buffer->getReadWriteLock()));
        ui->stationIDEdit->setText(QString::number(buffer->getStationID()));
        ui->ipAddressEdit->setText(QString::number(buffer->getIPAddress()));
        ui->memoryHexInfoTable->setRowCount((int)(buffer->getBufferSize() / 16) + 1);
        ui->memoryCharInfoTable->setRowCount((int)(buffer->getBufferSize() / 16) + 1);
        quint8* dataStartPointer = (quint8*) buffer->getDataStartPointer();
        for (quint32 i = 0; i < buffer->getBufferSize(); i++) {
            quint8 singleByte = *(dataStartPointer + i);
            QTableWidgetItem* hexItem = new QTableWidgetItem(((singleByte > 15) ? "" : "0") + QString::number(singleByte, 16).toUpper());
            hexItem->setTextAlignment(Qt::AlignCenter);
            QTableWidgetItem* charItem = new QTableWidgetItem(((qint8) singleByte <= 0) ? "-" : QString(singleByte));
            charItem->setTextAlignment(Qt::AlignCenter);
            ui->memoryHexInfoTable->setItem(i / 16, i % 16, hexItem);
            ui->memoryCharInfoTable->setItem(i / 16, i % 16, charItem);
        }
    }
    else {
        quint32 bufferSize = 6666;
        ui->memoryHexInfoTable->setRowCount((int)(bufferSize / 16) + 1);
        ui->memoryCharInfoTable->setRowCount((int)(bufferSize / 16) + 1);
        quint8* dataStartPointer = (quint8*) sharedMemoryPointer;
        for (quint32 i = 0; i < bufferSize; i++) {
            quint8 singleByte = *(dataStartPointer + i);
            QTableWidgetItem* hexItem = new QTableWidgetItem(((singleByte > 15) ? "" : "0") + QString::number(singleByte, 16).toUpper());
            hexItem->setTextAlignment(Qt::AlignCenter);
            QTableWidgetItem* charItem = new QTableWidgetItem(((qint8) singleByte <= 0) ? "-" : QString(singleByte));
            charItem->setTextAlignment(Qt::AlignCenter);
            ui->memoryHexInfoTable->setItem(i / 16, i % 16, hexItem);
            ui->memoryCharInfoTable->setItem(i / 16, i % 16, charItem);
        }
    }
}
