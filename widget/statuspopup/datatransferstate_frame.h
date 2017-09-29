#ifndef DATATRANSFERSTATE_FRAME_H
#define DATATRANSFERSTATE_FRAME_H

#include <QFrame>

namespace Ui {
class DataTransferStateFrame;
}

class DataTransferStateFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DataTransferStateFrame(QWidget *parent = 0);
    ~DataTransferStateFrame();

private:
    Ui::DataTransferStateFrame *ui;
};

#endif // DATATRANSFERSTATE_FRAME_H
