import QtQuick 2.10
import QtQuick.Controls 2.2

Popup {
    id: root
    implicitWidth: 100
    implicitHeight: 200

    property alias themeColor: buttonTheme.color
    property alias titleRectText: titleRect.text
    property alias buttonTextText: buttonText.text
    property alias messageText: messageRect.text

    property int themeRectHeight:
    {
        if(root.height / 50 > 3)
            return 3
        else if(root.height / 50 < 1)
            return 1
        else
            return root.height / 50
    }

    property int titleRectHeight: root.height / 6 <= 30 ? 30 : root.height / 6
    property int buttonRectHeight: root.titleRectHeight

    property int titlePixelSize: root.titleRectHeight / 2

    modal: false
    dim: true //淡化背景
    closePolicy: Popup.CloseOnPressOutside
    //contentItem 边距
    topPadding: root.themeRectHeight + root.titleRectHeight
    leftPadding: 20
    rightPadding: 20
    bottomPadding: root.buttonRectHeight

    //实际对话框内容
    contentItem: Rectangle{
        id: contentRect
        Text {
            id: messageRect
            anchors.topMargin: root.themeRectHeight * 2
            anchors.fill: parent
            wrapMode: Text.Wrap
            lineHeight: 1.5
            font.pixelSize: titleRect.font.pixelSize * 0.8
        }
    }

    //背景
    background: Rectangle{
        id: rectangle
        color: '#ffffff'
        anchors.fill: parent

        //标题
        Text {
            id: titleRect
            height: root.titleRectHeight
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: root.titlePixelSize
            font.bold: true
            color: "#000000"
            text: "提示"

        }

        //底部按钮
        Button {
            id: buttonRect
            height: root.buttonRectHeight
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            Rectangle{
                id: buttonTheme
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: root.themeRectHeight
                color: "#2186F6"
            }

            Text {
                id: buttonText
                text: "OK"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: root.titlePixelSize
                font.bold: true
            }
            background: Rectangle{
                id: m_commit_bak
                color: "#FFFFFF"
                border.width: 0
            }
            onClicked: root.close()
        }
    }

}
