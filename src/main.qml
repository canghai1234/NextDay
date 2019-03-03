import QtQuick 2.10
import QtQuick.Window 2.10
import NextDay 0.1
import QtQuick.Controls 2.2

import "./qml"

Window {
    id: root
    visible: true
    width: 608
    height: 1080
    title: qsTr("NextDay")
//    flags: Qt.FramelessWindowHint

    FontLoader { id: avenirLight; source: "qrc:/font/Avenir Next Ultra Light.ttf" }
    FontLoader { id: avenirRegular; source: "qrc:/font/AvenirNextW01ThinRegular.ttf" }
    FontLoader { id: sourceHanSans; source: "qrc:/font/SourceHanSansCN-Light.ttf" }

    property double fontScale: 1.0

    ListView {
        id:view

        anchors.fill: parent
        anchors.margins: 0
        model: todayModelManage.dateModel()
        delegate: dayDelegate
        spacing: 0
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem
        layoutDirection: Qt.RightToLeft
        highlightRangeMode: ListView.StrictlyEnforceRange

        onCurrentIndexChanged:
        {
            Backend.qmlIndexChanged(currentIndex)
        }
    }

    Component {
        id: dayDelegate

        Rectangle {
            id: dayRect
            width: view.width
            height: view.height
            color: "#EEE9E9"

            MainRect
            {
                id: day
                width: view.width
                height: view.height
                dayFontfamily: avenirLight.name
                monthWeekFontfamily: avenirRegular.name
                eventFontfamily: sourceHanSans.name
                geoInfoFontfamily: sourceHanSans.name
                comment1Fontfamily: sourceHanSans.name
                comment2Fontfamily:sourceHanSans.name
                authorFontfamily: sourceHanSans.name
                textScale: root.fontScale

                imageSource: model.modelData.imageURL
                dayText: model.modelData.day
                monthWeekText: model.modelData.week
                eventText: model.modelData.event
                geoInfoText: model.modelData.geoInfo
                comment1Text: model.modelData.comment1
                comment2Text: model.modelData.comment2
                authorText: model.modelData.author
                comment1RECTColor: model.modelData.backgroundColor
                comment2RECTColor: model.modelData.backgroundColor
                comment1RECTVisible: true
                comment2RECTVisible: !model.modelData.hasShort

            }
        }
    }


    Music
    {
        id: musicControl
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        height: root.height * 0.0634
        textScale: root.fontScale
        windowHeight: root.height

        musicNameFont: sourceHanSans.name
        musicArtistFont: sourceHanSans.name
    }

    Connections
    {
        target: Backend
        onSig_hasMusic:
        {
            if(hasMusic)
            {
                musicControl.visible = true
            }
            else
            {
                if(musicControl.isMusicPlaying)
                    musicControl.visible = true
                else
                    musicControl.visible = false
            }
        }
        onSig_musicURL:
        {
            musicControl.setMusicURL(url)
        }
        onSig_musicTitle:
        {
            musicControl.setMusicTitle(title)
        }
        onSig_musicArtist:
        {
            musicControl.setMusicArtist(artist)
        }
    }

    Component.onCompleted:
    {
        root.fontScale = Backend.getFontScale()
        view.currentIndex = 0
    }
}
