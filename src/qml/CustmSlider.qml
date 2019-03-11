import QtQuick 2.7
import QtQuick.Controls 2.2

Slider {
    id: root
//    property alias backgroundColor: backgroundRect.color

    implicitHeight: 30
    implicitWidth: 300
    bottomPadding: 0
    topPadding: 0
    from: 50
    to: 150
    live: true //立刻更新数值
    stepSize: 1
    value: 100
    background: Rectangle {
        id: backgroundRect
        x: root.leftPadding
        //y: root.topPadding + root.availableHeight / 2 - height / 2

        anchors.verticalCenter: parent.verticalCenter

        width: root.availableWidth
        height: root.availableHeight / 3
        radius: backgroundRect.height / 2
        color: "#2186f6"

//        Rectangle {
//            width: root.visualPosition * parent.width
//            height: parent.height
//            color: "#2186f6"
//            radius: parent.height / 2
//        }
    }

    handle: Rectangle {
        height: root.availableHeight
        width: height
        radius: height / 2

        x: root.leftPadding + root.visualPosition
           * (root.availableWidth) - width/2
        anchors.verticalCenter: parent.verticalCenter

        border.color: '#2186f6'
        color: '#2186f6'
        Text {
            anchors.centerIn: parent
            color: '#FFFFFF'
            font.pixelSize: backgroundRect.height
            text: root.value + "%"
        }
    }
}
