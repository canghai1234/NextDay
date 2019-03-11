import QtQuick 2.10
import NextDay 0.1
//import QtQuick.Window 2.3
//import QtQuick.Controls 2.2

Item
{
    id: rootRect

    anchors.fill: parent
    width: 608
    height: 1080

    property alias comment1RECTVisible: comment1RECT.visible
    property alias comment2RECTVisible: comment2RECT.visible

    //Image
    property alias imageSource: image.source

    //Font
    property alias dayFontfamily: day.font.family
    property alias monthWeekFontfamily: monthWeek.font.family
    property alias eventFontfamily: event.font.family
    property alias geoInfoFontfamily: geoInfo.font.family
    property alias comment1Fontfamily: comment1.font.family
    property alias comment2Fontfamily: comment2.font.family
    property alias authorFontfamily: author.font.family

    //Color
    property alias comment1RECTColor: comment1RECT.color
    property alias comment2RECTColor: comment2RECT.color

    //text
    property alias dayText: day.text
    property alias monthWeekText: monthWeek.text
    property alias eventText: event.text
    property alias geoInfoText: geoInfo.text
    property alias comment1Text: comment1.text
    property alias comment2Text: comment2.text
    property alias authorText: author.text
    property alias textScale: rootRect.fontScale

    //距离比例
    property double dayScale: 0.37 //日期文字到底部的距离比例
    property double monthWeekScale: 0.32 //星期、月份、事件到底部的距离比例
    property double geoInfotScale: 0.19 //地理位置文字到底部的距离比例
    property double comment1Scale: 0.15  //文本1到底部的距离比例
    property double comment2Scale: 0.12  //文本1到底部的距离比例

    property double authortScale: 0.032 //作者信息到底部的距离比例
    property double leftOffset: 0.062 //文字到左侧边框的距离
    property double rightOffset: 0.05

    //文本大小
    property double fontScale: 1.0
    property double daytTextSize: 110 * fontScale
    property double monthWeekTextSize: 22 * fontScale
    property double geoTextSize: 13.9 * fontScale
    property double commentTextSize: 15.66 * fontScale
    property double authorTextSize: 13.9 * fontScale

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
            font.pointSize: rootRect.daytTextSize
            color: "#FFFFFF"
            anchors.bottom: parent.bottom
            lineHeightMode: Text.FixedHeight
            lineHeight: font.pixelSize
        }
        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: rootRect.height * rootRect.dayScale
        anchors.left: rootRect.left
        anchors.leftMargin: rootRect.width * rootRect.leftOffset
    }

    Rectangle
    {
        id:monthWeekRECT
        Row{
            anchors.fill: parent
            Text {
                id: monthWeek
                font.weight: Font.Normal
                font.pointSize: rootRect.monthWeekTextSize
                font.bold: true
                color: "#FFFFFF"
                anchors.bottom: parent.bottom
                lineHeightMode: Text.FixedHeight
                lineHeight: font.pixelSize
            }
            Text {
                id: event
                font.weight: Font.Normal
                font.bold: true
                font.pointSize: rootRect.monthWeekTextSize
                color: "#FFFFFF"
                anchors.baseline: monthWeek.baseline
                lineHeightMode: Text.FixedHeight
                lineHeight: font.pixelSize
            }
        }

        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: rootRect.height * rootRect.monthWeekScale
        anchors.left: rootRect.left
        anchors.leftMargin: rootRect.width * rootRect.leftOffset
    }

    Text {
        id: geoInfo
        font.weight: Font.ExtraLight
        font.pointSize: rootRect.geoTextSize
        color: "#FFFFFF"
        style: Text.Raised
        styleColor: "#000000"
        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: rootRect.height * rootRect.geoInfotScale
        lineHeightMode: Text.FixedHeight
        lineHeight: font.pixelSize
        anchors.left: rootRect.left
        anchors.leftMargin: rootRect.width * rootRect.leftOffset
    }

    Rectangle
    {
        id: comment1RECT

        Text {
            id: comment1
            font.weight: Font.ExtraLight
            font.pointSize: rootRect.commentTextSize
            color: "#FFFFFF"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            lineHeightMode: Text.FixedHeight
            lineHeight: font.pixelSize
            anchors.horizontalCenter: parent.horizontalCenter
        }
        height: comment1.height + comment1.font.pixelSize / 3
        width: comment1.width + comment1.font.pixelSize / 3
        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: rootRect.height * rootRect.comment1Scale
        anchors.left: rootRect.left
        anchors.leftMargin: rootRect.width * rootRect.leftOffset -(comment1.font.pixelSize / 6)
        visible: false
    }

    Rectangle
    {
        id:comment2RECT
        Text {
            id: comment2
            font.weight: Font.ExtraLight
            font.pointSize: rootRect.commentTextSize
            color: "#FFFFFF"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            lineHeightMode: Text.FixedHeight
            lineHeight: font.pixelSize
            anchors.horizontalCenter: parent.horizontalCenter
        }
        height: comment2.height + comment2.font.pixelSize / 3
        width: comment2.width + comment2.font.pixelSize / 3
        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: rootRect.height * rootRect.comment2Scale
        anchors.left: rootRect.left
        anchors.leftMargin: rootRect.width * rootRect.leftOffset -(comment2.font.pixelSize / 6)
        visible: false
    }

    Text {
        id: author
        font.weight: Font.ExtraLight
        font.pointSize: rootRect.authorTextSize
        color: "#FFFFFF"
        lineHeightMode: Text.FixedHeight
        lineHeight: font.pixelSize

        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: rootRect.height * rootRect.authortScale
        anchors.right: rootRect.right
        anchors.rightMargin: rootRect.width * rootRect.rightOffset
    }
}
