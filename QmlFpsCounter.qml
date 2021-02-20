import QtQuick 2.15

import com.dln.common 1.0

Rectangle {
    width: text.width
    height: text.height
    radius: 5
    color: Qt.rgba(0.0, 0.0, 0.0, 0.8)
    z: 1000

    FpsCounter {
        id: fpsCounter

        interval: 500
    }

    Text {
        id: text

        padding: 10
        text: "FPS: " + fpsCounter.fps
        color: "green"
        font {
            bold: true
            pixelSize: 18
        }
    }
}
