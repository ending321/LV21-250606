import QtQuick
import QtQuick.Controls

Item {
    id: pickupView
    Image{
        id:delivery_image
        width:parent.width
        fillMode:Image.PreserveAspectFit
        Component.onCompleted: {
            delivery_image.source="qrc:/new/prefix1/delivery.png"
        }
    }
    Column{
        spacing: spacing_size
        anchors.centerIn:parent
        width:parent.width*0.8
        TextField{
            id:codeNumberField
            placeholderText: "输入取件码" //框内提示
            width:parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            validator: RegularExpressionValidator{regularExpression: /^[0-9]{8}$/} //0-9的输入,最多8位
            inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        Row {
            spacing: spacing_size
            Button {
                text: "取 件"
                font.pixelSize: text_size
                enabled: stack.depth > 1
                onClicked: {
                    //取件码不能为空
                    if(codeNumberField.text === ""){
                        receivedMessage.text = "取件码不能为空"
                    }else if(codeNumberField.text.length !== 8){ //手机号格式不对
                        receivedMessage.text = "取件码位数不对"
                    }else{
                        receivedMessage.text = "发送消息"
                        udpClient.sendMessage('p'+codeNumberField.text+'\0', host, port)
                        //stack.pop()
                    }

                }
            }
            Button {
                text: "取 消"
                font.pixelSize: text_size
                enabled: stack.depth > 1
                onClicked: stack.pop()
            }
            /*
            Text {
                text: "pickupView: "+stack.depth
            }
            */
        }
        // 显示接收到的消息
                Text {
                    id: receivedMessage
                    text: "Received message: " // 初始化文本
                }
                // 连接 udpClient 的 messageReceived 信号，当有新消息时更新显示
                Connections {
                    target: udpClient
                    function onMsgPickup(message) {
                        receivedMessage.text = "Received message: " + message
                        stack.push("qrc:/delivery.qml")
                    }
                }
    }
}
