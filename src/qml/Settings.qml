import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import NextDay 0.1

import "./"

Rectangle {
    id: root
    height: 1080
    width: 607.5
    opacity: 1
    color: "#EDEDED"

    signal sig_fontScaleChanged(double value)
    signal sig_saveBackgroundImage()
    signal sig_saveToday()
    signal sig_about()

    property alias itemHeight: root.controlHeight

    property int itemSpace: 20
    property int controlSpace: root.controlHeight / 5
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

        Text {
            id: titleText
            text: "设置"
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: root.controlHeight * 0.4
        }

        Image {
            id: back
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: root.leftSpace
            height: titleText.font.pixelSize
            width: height
            source: "qrc:/icon/icon/back.png"

            MouseArea
            {
                anchors.fill: parent
                onClicked: root.visible = false
            }
        }

    }



    Item {
        id: saveItem
        anchors.top: title.bottom
        anchors.topMargin: root.itemSpace
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: buttonSaveImage.height + buttonSaveBackground.height + root.controlSpace

        CustmButton
        {
            id: buttonSaveImage
            height: root.controlHeight
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            leftSpace: root.leftSpace

            iconSource: "qrc:/icon/icon/downloadScreen.png"
            buttonText: "保存当日图片"
            onButtonClicked: sig_saveToday()
        }

        CustmButton
        {
            id: buttonSaveBackground
            height: root.controlHeight
            buttonText: "保存当日背景图片"
            anchors.top: buttonSaveImage.bottom
            anchors.topMargin: root.controlSpace
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            leftSpace: root.leftSpace
            iconSource: "qrc:/icon/icon/downImage.png"
            onButtonClicked: sig_saveBackgroundImage()
        }

    }

    Rectangle {
        id: slideItem
        height: root.controlHeight
        anchors.top: saveItem.bottom
        anchors.topMargin: root.itemSpace
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "#FFFFFF"

        CustmSlider
        {
            id: slider
            height: parent.height * 0.6

            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: root.leftSpace
            anchors.left: parent.left
            anchors.leftMargin: root.leftSpace

            onValueChanged: sig_fontScaleChanged(value)

            value: Backend.getTextScaleUser()

            onPressedChanged:
            {
                if(slider.pressed)
                {
                    aboutItem.visible = false
                    sliderText.visible = false
                    saveItem.visible = false
                    title.visible = false
                    root.color = "#00000000"
                    slideItem.color = "#00000000"
                }
                else
                {
                    aboutItem.visible = true
                    sliderText.visible = true
                    saveItem.visible = true
                    title.visible = true
                    root.color = "#EDEDED"
                    slideItem.color = "#FFFFFF"
                    Backend.setTextScaleUser(slider.value)
                }
            }
        }
    }

    Text {
        id: sliderText
        text: "因不同厂商默认字体字号大小，以及用户在系统设置中自定义的字号大小不同，可能导致页面上文字过小，或文字超出页面范围的情况。你可以通过调整上方滑条以改变字体的缩放比，从而达到最佳的视觉效果。"
        wrapMode: Text.WordWrap
        font.weight: Font.Light
        font.family: "Courier"
        anchors.top: slideItem.bottom
        anchors.topMargin: root.controlSpace * 0.5
        verticalAlignment: Text.AlignTop
        anchors.right: parent.right
        anchors.rightMargin: root.leftSpace
        anchors.left: parent.left
        anchors.leftMargin: root.leftSpace
        font.pixelSize: root.controlHeight * 0.2
    }

    Item {
        id: aboutItem
        height: root.controlHeight
        anchors.bottom: root.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        CustmButton
        {
            id: aboutButton
            anchors.fill: parent
            buttonText: "关于"
            leftSpace: root.leftSpace
            iconSource: "qrc:/icon/icon/about.png"
            onButtonClicked:
            {
                about.visible = true
            }
        }
    }


    About
    {
        id: about
        anchors.fill: parent
        visible: false
        itemHeight: root.controlHeight
    }
}
