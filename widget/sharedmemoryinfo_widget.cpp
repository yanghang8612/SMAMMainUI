#include <QDebug>

#include "sharedmemoryinfo_widget.h"
#include "ui_sharedmemoryinfo_widget.h"
#include "main_component_header.h"
#include "utilies/shared_buffer.h"

SharedMemoryInfoWidget::SharedMemoryInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SharedMemoryInfoWidget), buffer(0), hexTableChanging(false), charTableChanging(false)
{
    ui->setupUi(this);
    ui->memoryHexInfoTable->setColumnCount(16);
    ui->memoryHexInfoTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->memoryHexInfoTable->setShowGrid(false);
    ui->memoryHexInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memoryCharInfoTable->setColumnCount(16);
    ui->memoryCharInfoTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->memoryCharInfoTable->setShowGrid(false);
    ui->memoryCharInfoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

SharedMemoryInfoWidget::~SharedMemoryInfoWidget()
{
    delete ui;
}

void SharedMemoryInfoWidget::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)
    updateView();
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
        void* sharedMemoryPointer = FindMemoryInfoFunc(memoryID, 180);
        buffer = new SharedBuffer(SharedBuffer::LOOP_BUFFER, SharedBuffer::ONLY_READ, sharedMemoryPointer);
        updateView();
    }
}

void SharedMemoryInfoWidget::on_autoUpdateButton_clicked(bool checked)
{
    static int timerID;
    if (checked) {
        ui->autoUpdateButton->setText(tr("停止刷新"));
        timerID = startTimer(100);
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
