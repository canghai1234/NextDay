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

    Rectangle
    {
        id: rootRect
        anchors.fill: parent

        property double rootHeight: 1080

        //距离比例
        property double dayScale: 0.3709 //日期文字到底部的距离比例
        property double monthWeekScale: 0.3247 //星期、月份、事件到底部的距离比例
        property double geoInfotScale: 0.1821 //地理位置文字到底部的距离比例
        property double comment1Scale: 0.1499  //文本1到底部的距离比例
        property double authortScale: 0.0317 //作者信息到底部的距离比例

        //文本大小
        property double daytTextScale: 0.13
        property double monthWeekTextScale: 0.02355
        property double geoTextScale: 0.0163
        property double commentTextScale: 0.0199
        property double authorTextScale: 0.0163


        Image {
            id: image
            fillMode: Image.PreserveAspectCrop
            anchors.fill: rootRect
        }


        Rectangle
        {
            id:dayRECT

            Text {
                id: day
                font.weight: Font.ExtraLight
                font.pointSize: 126.5
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                font.family: avenirLight.name
                lineHeightMode: Text.FixedHeight
                lineHeight: font.pixelSize
            }
            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: rootRect.rootHeight * rootRect.dayScale
            anchors.left: rootRect.left
            anchors.leftMargin: 35
        }


//        Rectangle
//        {
//            id:dayItem
//            height: 530
//            anchors.bottom: rootRect.bottom
//            anchors.bottomMargin: rootRect.rootHeight * rootRect.dayScale
//            anchors.left: rootRect.left
//            anchors.leftMargin: 24
//            color: "#FF0000"

//            DayRect{
//                id: day
//                anchors.bottom: parent.bottom
//                anchors.left: parent.left

//            }
//        }


        Rectangle
        {
            id:monthWeekRECT
            Row{
                anchors.fill: parent
                Text {
                    id: monthWeek
                    font.weight: Font.ExtraLight
                    font.pointSize: 23
                    color: "#FFFFFF"
                    anchors.bottom: parent.bottom
                    font.family: avenirRegular.name
                    lineHeightMode: Text.FixedHeight
                    lineHeight: font.pixelSize
                }
            }

            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: rootRect.rootHeight * rootRect.monthWeekScale
            anchors.left: rootRect.left
            anchors.leftMargin: 35
        }


        Rectangle
        {
            id:eventRECT
            Row{
                anchors.fill: parent
                Text {
                    id: event
                    font.weight: Font.ExtraLight
                    font.pointSize: 39
                    color: "#FFFFFF"
                    anchors.bottom: parent.bottom
                    font.family: sourceHanSans.name
                    lineHeightMode: Text.FixedHeight
                    lineHeight: font.pixelSize
                }
            }
            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: rootRect.rootHeight * rootRect.monthWeekScale
            anchors.left: monthWeekRECT.left
        }

        Text {
            id: geoInfo
            font.weight: Font.ExtraLight
            font.pointSize: 16
            color: "#FFFFFF"
            style: Text.Raised
            styleColor: "#000000"
            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: root.height * rootRect.geoInfotScale
            font.family: sourceHanSans.name
            lineHeightMode: Text.FixedHeight
            lineHeight: font.pixelSize
            anchors.left: rootRect.left
            anchors.leftMargin: 35
        }

//        Label {
//            id: comment1
//            font.weight: Font.ExtraLight
//            font.pointSize: 18
//            color: "#FFFFFF"
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.AlignVCenter
//            font.family: sourceHanSans.name
//            lineHeightMode: Text.FixedHeight
//            lineHeight: font.pixelSize
//            anchors.bottom: rootRect.bottom
//            anchors.bottomMargin: rootRect.rootHeight * rootRect.comment1Scale
//            anchors.left: rootRect.left
//            anchors.leftMargin: 35
//            background: comment1RECT
//        }

//        Text {
//            id: comment1
//            font.weight: Font.ExtraLight
//            font.pointSize: 19.4
//            color: "#FFFFFF"
//            font.family: sourceHanSans.name
//            lineHeightMode: Text.FixedHeight
//            lineHeight: font.pixelSize
//            anchors.bottom: rootRect.bottom
//            anchors.bottomMargin: rootRect.rootHeight * rootRect.comment1Scale
//            anchors.left: rootRect.left
//            anchors.leftMargin: 22
//            z:2
//        }

//        Rectangle
//        {
//            id:comment1RECT
//            height: comment1.height + 4
//            width: comment1.width + 4
//            border.width: 0

//            anchors.bottom: comment1.bottom
//            anchors.bottomMargin: -2
//            anchors.left: comment1.left
//            anchors.leftMargin: -2
//            anchors.right: comment1.right
//            anchors.rightMargin: -2
//            anchors.top: comment1.top
//            anchors.topMargin: -2
//            z:1
//        }

        Rectangle
        {
            id: comment1RECT

            Text {
                id: comment1
                font.weight: Font.ExtraLight
                font.pointSize: 18
                color: "#FFFFFF"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.baseline: parent.bottom
                font.family: sourceHanSans.name
                lineHeightMode: Text.FixedHeight
                lineHeight: font.pixelSize
                anchors.horizontalCenter: parent.horizontalCenter
//                height: font.pixelSize
//                y:-1
            }
            height: comment1.height + 4
            width: comment1.width + 40
            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: rootRect.rootHeight * rootRect.comment1Scale
            anchors.left: rootRect.left
            anchors.leftMargin: 35
        }

        Rectangle
        {
            id:comment2RECT
            Row{
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                Text {
                    id: comment2
                    font.pixelSize: root.height * rootRect.commentTextScale
                    color: "#FFFFFF"
                    font.family: sourceHanSans.name
                }
            }
            width: comment2.width
            height: comment2.height
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 67
            anchors.left: rootRect.left
            anchors.leftMargin: 35
        }

        Label {
            id: author
            font.weight: Font.ExtraLight
            font.pointSize: 16
            color: "#FFFFFF"
//            style: Text.Raised
//            styleColor: "#000000"
            font.family: sourceHanSans.name
            lineHeightMode: Text.FixedHeight
            lineHeight: font.pixelSize

            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: root.height * rootRect.authortScale
            anchors.right: rootRect.right
            anchors.rightMargin: 20
        }
    }

    Component.onCompleted:
    {
//        day.setFont(avenirLight.name)
        Backend.requestSource()
    }

    Connections
    {
        target: Backend
        onSig_requestSourceSucceed:
        {
            image.source = Backend.getImageURL()
            day.text = Backend.getDay()
//            day.setText(Backend.getDay())
            monthWeek.text = Backend.getWeek()
            event.text = Backend.getEvent()
            geoInfo.text = Backend.getGeoInfo()
            comment1RECT.color = Backend.getBackgroundColor()
            comment2RECT.color = Backend.getBackgroundColor()
            comment1.text = Backend.getComment1()
            comment2.text = Backend.getComment2()
            author.text = Backend.getAuthor()
            console.log("----loaded" )

            console.log(comment1.font.pointSize)
            console.log(comment1.font.pixelSize)
            console.log(comment1.width)
            console.log(comment1.height)
            console.log(comment1.x)
            console.log(comment1.y)

//            console.log(day_metrics.width )
//            console.log(day_metrics.height)

//            console.log(day_metrics.tightBoundingRect.width )
//            console.log(day_metrics.tightBoundingRect.height)
//            console.log("--------->" )


//            console.log(day.contentHeight )
//            console.log(day.font.pixelSize )
//            console.log(day.lineHeight )
//            console.log(day.lineHeightMode )
//            console.log(day.padding)
////            console.log( )
//            console.log(day.paintedHeight )




//            day.font.pixelSize = root.height * rootRect.daytTextScale
//            day.anchors.bottomMargin = root.height * rootRect.daytScale

//            monthWeek.font.pixelSize = root.height * rootRect.monthWeekTextScale
//            monthWeek.anchors.bottomMargin = root.height * rootRect.monthWeekScale

//            event.font.pixelSize = root.height * rootRect.monthWeekTextScale
//            event.anchors.bottomMargin = root.height * rootRect.monthWeekScale

//            comment1.font.pixelSize = root.height * rootRect.commentTextScale
//            comment1RECT.anchors.bottomMargin = root.height * rootRect.comment1Scale
        }
    }
}
