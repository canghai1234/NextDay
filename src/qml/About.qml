import QtQuick 2.10
import QtMultimedia 5.9
import QtQuick.Controls 2.2

Rectangle {
    id: root
    property alias itemHeight: root.controlHeight
    property int controlHeight: 100
    property double leftSpace: 0.062 * root.width

    Item
    {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: root.controlHeight
        Image {
            id: back
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: root.leftSpace
            height: root.controlHeight * 0.4
            width: height
            source: "qrc:/icon/icon/back.png"

            MouseArea
            {
                anchors.fill: parent
                onClicked: root.visible = false
            }
        }
    }


    Image {
        id: logo
        width: root.controlHeight * 2
        height: width
        anchors.top: title.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/icon/icon/icon.png"
    }



    Text {
        id: text1
        text: qsTr("本软件非 NextDay 官方版。")
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        font.pointSize: 16
        anchors.top: logo.bottom
        anchors.topMargin: root.controlHeight
        anchors.right: parent.right
        anchors.rightMargin: root.leftSpace
        anchors.left: parent.left
        anchors.leftMargin: root.leftSpace
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    Text {
        id: text2
        text: qsTr("本软件使用使用 Qt 编写，使用 NextDay API 获取相应数据，所有数据版权归原作者所有。")
        anchors.topMargin: 20
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        font.pointSize: 16
        anchors.top: text1.bottom
        anchors.right: parent.right
        anchors.rightMargin: root.leftSpace
        anchors.left: parent.left
        anchors.leftMargin: root.leftSpace
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    Text {
        id: text3
        text: qsTr(" 源代码地址：https://github.com/canghai1234/NextDay")
        anchors.topMargin: 20
        textFormat: Text.RichText
        wrapMode: Text.WordWrap
        font.pointSize: 16
        anchors.top: text2.bottom
        anchors.right: parent.right
        anchors.rightMargin: root.leftSpace
        anchors.left: parent.left
        anchors.leftMargin: root.leftSpace
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }



}

