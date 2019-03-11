import QtQuick 2.10
import QtMultimedia 5.9
import QtQuick.Controls 2.2

Item {
    id: root

    signal sig_settingShow()

    function setMusicURL(url)
    {
        if(isPlaying)
        {
            newUrl = url
            newUrlReceived = true

            if(newUrl == playMusic.source)
                playStatus.source = "qrc:/icon/icon/pause.png"
            else
                playStatus.source = "qrc:/icon/icon/stop.png"
        }
        else
            playMusic.source = url
    }

    function setMusicTitle(title)
    {
        if(isPlaying)
            newMusicTitle = title;
        else
            musicName.text = title
    }

    function setMusicArtist(artist)
    {
        if(isPlaying)
            newMusicArtist = artist;
        else
            musicArtist.text = artist
    }

    property alias musicNameFont: musicName.font.family //音乐名 字体
    property alias musicArtistFont: musicName.font.family //演唱者 字体
    property alias textScale: root.fontScale //字体缩放比例
    property alias windowHeight: root.parentHeight //父窗口高度

    property alias isMusicPlaying: root.isPlaying

    //内部属性定义
    property bool isPlaying: false
    property bool newUrlReceived: false
    property string newUrl: ""
    property string newMusicTitle: ""
    property string newMusicArtist: ""

    property double leftOffset: 0.050 //文字到左侧边框的距离
    property int parentHeight: 2208
    property double progressHeight: 0.00136 * windowHeight
    property double fontScale: 1.0
    property double musicTextSize: 14 * fontScale
    property double artistTextSize: 9 * fontScale

    property int iconHeight: root.height * 0.6
    property int progressBottomMargin: root.height * 0.4 * 0.3

    function setFont(fontFamily)
    {
        musicName.font.family = fontFamily;
        musicArtist.font.family = fontFamily;
    }

    function playStatusChanged()
    {
        if(playMusic.playbackState == Audio.StoppedState)
        {
            isPlaying = true
            progress.visible = true
            playMusic.play()
            playStatus.source = "qrc:/icon/icon/pause.png"
        }
        else if(playMusic.playbackState == Audio.PausedState)
        {
            isPlaying = true
            playMusic.play()
            playStatus.source = "qrc:/icon/icon/pause.png"
        }
        else //当前处于播放状态
        {
            if(newUrlReceived)
            {
                playMusic.stop()
                progress.visible = false
                playMusic.source = newUrl
                musicName.text = newMusicTitle
                musicArtist.text = newMusicArtist
                newUrlReceived = false
                newUrl = ""
                newMusicTitle = ""
                newMusicArtist = ""
            }
            else
            {
                playMusic.pause()
            }
            isPlaying = false
            playStatus.source = "qrc:/icon/icon/play.png"
        }
    }

    Audio {
        id: playMusic
        audioRole: Audio.MusicRole
        autoLoad: false
        autoPlay: false
        onPositionChanged: {
            progress.value = position}
        onDurationChanged: {
            progress.visible = true
            progress.to = duration }
    }

    MouseArea
    {
        anchors.fill: parent
        pressAndHoldInterval: 2000
        onPressAndHold: {
            sig_settingShow()
        }
    }

    Image {
        id: playStatus
        height: root.iconHeight
        anchors.left: parent.left
        anchors.leftMargin: leftOffset * root.width
        width: root.iconHeight
        source: "qrc:/icon/icon/play.png"
        fillMode: Image.Stretch
        MouseArea
        {
            anchors.fill: parent
            onClicked: {
                playStatusChanged()
            }
        }
    }

    Text {
        id: musicName
        color: "#FFFFFF"
        textFormat: Text.AutoText
        font.weight: Font.Normal
        font.pointSize: root.musicTextSize
        lineHeightMode: Text.FixedHeight
        lineHeight: font.pixelSize

        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: playStatus.right
        anchors.leftMargin: 0
    }

    Text {
        id: musicArtist
        color: "#FFFFFF"
        font.weight: Font.ExtraLight
        font.pointSize: root.artistTextSize
        lineHeightMode: Text.FixedHeight
        lineHeight: font.pixelSize

        anchors.left: playStatus.right
        anchors.leftMargin: 0
        anchors.bottom: playStatus.bottom
        anchors.bottomMargin: 0
    }

    ProgressBar {
        id: progress
        from: 0
        value: 0

        visible: false
        height: progressHeight
        anchors.bottom: parent.bottom
        anchors.bottomMargin: progressBottomMargin

        anchors.right: root.right
        anchors.rightMargin: leftOffset * root.width + root.iconHeight
        anchors.left: playStatus.right
        anchors.leftMargin: 0

        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "#FFFFFF"
            opacity: 0.3
        }

        contentItem: Item {
            implicitWidth: parent.width
            implicitHeight: parent.height

            Rectangle {
                width: progress.visualPosition * parent.width
                height: parent.height
                color: "#FFFFFF"
            }
        }
    }

}
