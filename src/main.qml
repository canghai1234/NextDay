import QtQuick 2.10
import QtQuick.Window 2.10
import NextDay 0.1


import "./qml"

Window {
    id: root
    visible: true
    width: 608
    height: 1080
    title: qsTr("NextDay")
    flags: Qt.FramelessWindowHint

    MainRect
    {
        id: mainRect
        anchors.fill: parent

        onSig_showSettingPage:
        {
            settingPage.visible = true
        }
    }

    NextDayDialog
    {
        id: dialogRect
        height: parent.height / 4
        width: parent.width / 2
        x: parent.width / 4
        y: parent.height * 3/8
//        anchors.centerIn: parent
    }

    Settings
    {
        id: settingPage
        anchors.fill: parent
        visible: false
        onSig_fontScaleChanged: mainRect.userFontScale = value

        onSig_saveToday:
        {
            mainRect.saveTodayImage(Backend.getTodayImagePath())
        }
        onSig_saveBackgroundImage:
        {
            Backend.saveTodayBackgroundImage()
        }
    }

    Connections
    {
        target: NotificationDialog
        onSig_newNotify:
        {
            dialogRect.messageText = errString
            switch(errType)
            {
            case 1:
                dialogRect.themeColor = "#2186F6"
                dialogRect.titleRectText = "提示"
                break;
            case 2:
                dialogRect.themeColor = "#FFFF00"
                dialogRect.titleRectText = "警告"
                break;
            case 3:
                dialogRect.themeColor = "#FF0000"
                dialogRect.titleRectText = "错误"
                break;
            }

            if(!dialogRect.opened)
            {
                dialogRect.open()
            }
        }
    }

    Component.onCompleted:
    {
        settingPage.itemHeight = 2 * Backend.getSettingItemHeight()
    }
}
