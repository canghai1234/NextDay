import QtQuick 2.10
import QtQuick.Window 2.10
import NextDay 0.1
import QtQuick.Layouts 1.3

Window {
    id: root
    visible: true
    width: 405
    height: 720
    title: qsTr("NextDay")

    FontLoader { id: avenirLight; source: "qrc:/font/Avenir Next Ultra Light.ttf" }
    FontLoader { id: avenirRegular; source: "qrc:/font/AvenirNextW01ThinRegular.ttf" }
    FontLoader { id: sourceHanSans; source: "qrc:/font/SourceHanSansCN-Light.ttf" }

    Rectangle
    {
        id: rootRect
        anchors.fill: parent
        Image {
            id: image
            fillMode: Image.PreserveAspectCrop
            anchors.fill: rootRect
        }

        Text {
            id: day
            font.pixelSize: 120
            font.weight: Font.ExtraLight
            //style: Text.Raised
            //styleColor: "#000000"
            color: "#FFFFFF"
            anchors.bottom: monthWeek.top
            anchors.bottomMargin: 3
            anchors.left: rootRect.left
            anchors.leftMargin: 24
            font.family: avenirLight.name
        }

        Text {
            id: monthWeek
            font.pixelSize: 25
            color: "#FFFFFF"
            anchors.bottom: geoInfo.top
            anchors.bottomMargin: 84
            anchors.left: rootRect.left
            anchors.leftMargin: 24
            font.family: avenirRegular.name
        }

        Text {
            id: event
            font.pixelSize: 25
            color: "#FFFFFF"
            anchors.bottom: geoInfo.top
            anchors.bottomMargin: 84
            anchors.left: monthWeek.right
            anchors.leftMargin: 0
            font.family: sourceHanSans.name
        }

        Text {
            id: geoInfo
            font.pixelSize: 14
            color: "#FFFFFF"
            anchors.bottom: comment1RECT.top
            anchors.bottomMargin: 5
            anchors.left: rootRect.left
            anchors.leftMargin: 24
            font.family: sourceHanSans.name
        }

        Rectangle
        {
            id:comment1RECT
            Row{
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.rightMargin: 2
                anchors.leftMargin: 2
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.topMargin: 2
                anchors.bottomMargin: 2
                Text {
                    id: comment1
                    font.weight: Font.Bold
                    font.pixelSize: 16
                    color: "#FFFFFF"
                    font.family: sourceHanSans.name
                }
            }
            width: comment1.width + 4
            height: comment1.height + 4
            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: 105
            anchors.left: rootRect.left
            anchors.leftMargin: 22
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
                    font.pixelSize: 13
                    color: "#FFFFFF"
                    font.family: sourceHanSans.name
                }
            }
            width: comment2.width
            height: comment2.height
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 67
            anchors.left: rootRect.left
            anchors.leftMargin: 13
        }

        Text {
            id: author
            font.pixelSize: 11
            color: "#FFFFFF"
            anchors.bottom: rootRect.bottom
            anchors.bottomMargin: 25
            anchors.right: rootRect.right
            anchors.rightMargin: 20
            font.family: sourceHanSans.name
        }
    }

    Component.onCompleted:
    {
        Backend.requestSource()
    }

    function toDBC(text)
    {
        var tmp = "";
        for(var i=0; i < text.length; i++)
        {
            if(text.charCodeAt(i) === 32)
                tmp = tmp + String.fromCharCode(12288);
            else if(text.charCodeAt(i) < 127)
                tmp = tmp + String.fromCharCode(text.charCodeAt(i) + 65248);
            else
                tmp = tmp + String.fromCharCode(text.charCodeAt(i));
        }
        return tmp;
    }

    Connections
    {
        target: Backend
        onSig_requestSourceSucceed:
        {
            image.source = Backend.getImageURL()
            day.text = Backend.getDay()
            monthWeek.text = toDBC(Backend.getWeek())
            event.text = toDBC(Backend.getEvent())
            geoInfo.text = toDBC(Backend.getGeoInfo())
            comment1RECT.color = Backend.getBackgroundColor()
            comment2RECT.color = Backend.getBackgroundColor()
            comment1.text = toDBC(Backend.getComment1())
            comment2.text = toDBC(Backend.getComment2())
            author.text = Backend.getAuthor()
        }
    }
}
