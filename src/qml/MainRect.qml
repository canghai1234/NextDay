import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Window 2.10

Rectangle
{
    id: rootRect
    anchors.fill: parent

    width: 608
    height: 1080

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
    property double daytTextSize: 126.5
    property double monthWeekTextSize: 25
    property double geoTextSize: 16
    property double commentTextSize: 18
    property double authorTextSize: 16

    function setDayFont(font)
    {
        day.font.family = font
    }

    function setWeekFont(font)
    {
        monthWeek.font.family = font
    }

    function setChineseFont(font)
    {
        event.font.family = font
        geoInfo.font.family = font
        comment1.font.family = font
        comment2.font.family = font
        author.font.family = font
    }

    function setImage(imagePath)
    {
        image.source = imagePath
    }

    function setDayText(text)
    {
        day.text = text
    }

    function setMonthWeekText(text)
    {
        monthWeek.text = text
    }

    function setEventText(text)
    {
        event.text = text
    }

    function setGeoInfoText(text)
    {
        geoInfo.text = text
    }

    function setComment1Text(text)
    {
        comment1.text = text
    }

    function setComment2Text(text)
    {
        comment2.text = text
    }

    function setAuthorText(text)
    {
        author.text = text
    }

    function setComment1Color(color)
    {
        comment1RECT.color = color
    }

    function setComment2Color(color)
    {
        comment2RECT.color = color
        comment2RECT.visible = true
    }



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
                font.family: avenirRegular.name
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
        anchors.bottomMargin: root.height * rootRect.geoInfotScale
        font.family: sourceHanSans.name
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

    Label {
        id: author
        font.weight: Font.ExtraLight
        font.pointSize: rootRect.authorTextSize
        color: "#FFFFFF"
        lineHeightMode: Text.FixedHeight
        lineHeight: font.pixelSize

        anchors.bottom: rootRect.bottom
        anchors.bottomMargin: root.height * rootRect.authortScale
        anchors.right: rootRect.right
        anchors.rightMargin: rootRect.width * rootRect.rightOffset
    }
}

