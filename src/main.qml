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

    property double fontScale: 1.0

    ListView {
        id:view

        property int lastIndex: 0

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
            if(lastIndex > currentIndex)
            {
                //显示右边的 item 请求下一天
                Backend.qmlRequestTomorrow()
            }
            else if(lastIndex < currentIndex)
            {
                //显示左边的 item 请求前一天
                Backend.qmlRequestYesterday()
            }
                else
            {
                //currentIndex  与 lastIndex 相等
                console.log("ListView currentIndex = lastIndex, value: " + currentIndex)
            }
            lastIndex = currentIndex
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
            }

            Connections
            {
                target: Backend
                onSig_requestSourceSucceed:
                {
                    if(dayRect.ListView.isCurrentItem)
                    {
                        day.imageSource = Backend.getImageURL()
                        day.dayText =  Backend.getDay()
                        day.monthWeekText = Backend.getWeek()
                        day.eventText = Backend.getEvent()
                        day.geoInfoText = Backend.getGeoInfo()
                        day.comment1Text = Backend.getComment1()
                        day.comment2Text = Backend.getComment2()
                        day.authorText = Backend.getAuthor()
                        day.comment1RECTColor = Backend.getBackgroundColor()
                        day.comment1RECTVisible = true
                        if(!Backend.hasShort())
                        {
                            day.comment2RECTColor = Backend.getBackgroundColor()
                            day.comment2RECTVisible = true
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted:
    {
        root.fontScale = Backend.getFontScale()
        view.currentIndex = 0;
        view.positionViewAtBeginning();

        Backend.requestSource();
    }
}
