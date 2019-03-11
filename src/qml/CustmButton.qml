import QtQuick 2.0

Rectangle {
    id: root

    signal buttonClicked()

    property alias iconSource: iconRect.source
    property alias buttonText: textRect.text
    property alias leftSpace: root.imageLeftSpace

    property double imageLeftSpace: 0.062 * root.width
    property int textHeight: root.height * 0.3
    property int imageHeight: root.height * 0.4
    property alias rootColor: root.color

    Image {
        id: iconRect
        width: root.imageHeight
        height: root.imageHeight
        anchors.left: parent.left
        anchors.leftMargin: imageLeftSpace
        anchors.verticalCenter: parent.verticalCenter
    }
    Text {
        id: textRect
        font.pixelSize: root.textHeight
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: iconRect.right
        anchors.leftMargin: imageLeftSpace / 2
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: buttonClicked()

        onPressed: rootColor = "#E4E4E4"
        onReleased: rootColor = "#FFFFFF"
        onCanceled: rootColor = "#FFFFFF"
    }
}
