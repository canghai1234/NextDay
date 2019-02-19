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

    FontLoader { id: avenirLight; source: "qrc:/font/Avenir Next Ultra Light.ttf" }
    FontLoader { id: avenirRegular; source: "qrc:/font/AvenirNextW01ThinRegular.ttf" }
    FontLoader { id: sourceHanSans; source: "qrc:/font/SourceHanSansCN-Light.ttf" }

    MainRect
    {
        id:main
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        main.setDayFont(avenirLight.name)
        main.setWeekFont(avenirRegular.name)
        main.setChineseFont(sourceHanSans.name)

//        Backend.setCurrentShowDate(Backend.getTodayByte())
        Backend.requestSource(Backend.getTodayByte())
    }

    Connections
    {
        target: Backend
        onSig_requestSourceSucceed:
        {
            main.setImage( Backend.getImageURL())

            main.setDayText( Backend.getDay())
            main.setMonthWeekText( Backend.getWeek())
            main.setEventText( Backend.getEvent())
            main.setGeoInfoText( Backend.getGeoInfo())
            main.setComment1Text( Backend.getComment1())
            main.setComment2Text( Backend.getComment2())
            main.setAuthorText( Backend.getAuthor())
            main.setComment1Color( Backend.getBackgroundColor())
            if(!Backend.hasShort())
            {
                main.setComment2Color( Backend.getBackgroundColor())
                main.setComment2Text( Backend.getComment2())
            }

            console.log("----loaded" )
        }
    }
}
