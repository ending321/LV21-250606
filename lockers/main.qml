import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.Controls
Window {
    id: window
    width: 480
    height: 854
    visible: true

    property int text_size: 25
    property int spacing_size: 10
    property string host: "192.168.31.148" //本机IP
    property int port:8888

    StackView {
            id: stack
            initialItem: mainView
            anchors.fill: parent
        }

        Component {
            id: mainView

            Column {
                spacing: spacing_size

                Image{
                    id:delivery_image
                    width:parent.width
                    fillMode:Image.PreserveAspectFit
                    Component.onCompleted: {
                        delivery_image.source="qrc:/new/prefix1/delivery.png"
                    }
                }

                Button {
                    anchors.horizontalCenter:parent.horizontalCenter
                    width: parent.width*0.5
                    contentItem: Text {
                        id: button_delivery
                        text: qsTr("投 递")
                        font.pixelSize: text_size
                        horizontalAlignment: Text.AlignHCenter
                    }
                    onClicked: stack.push("qrc:/login.qml")
                }
                Button {
                    anchors.horizontalCenter:parent.horizontalCenter
                    width: parent.width*0.5
                    contentItem: Text {
                        id: button_pickup
                        text: qsTr("取 件")
                        font.pixelSize: text_size
                        horizontalAlignment: Text.AlignHCenter
                    }
                    onClicked: stack.push("qrc:/pickup.qml")
                }
            }
        }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
