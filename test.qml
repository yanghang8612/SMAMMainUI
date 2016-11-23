import QtQuick 1.0

Rectangle {
    width: 100
    height: 62

    Item {
        id: item1
        x: 118
        y: 66
        width: 172
        height: 162

        Image {
            id: image2
            x: 100
            y: 161
            source: "res/icon/1.ico"
        }
    }

    Image {
        id: image1
        x: 185
        y: 128
        source: "res/icon/2.ico"
    }
}

