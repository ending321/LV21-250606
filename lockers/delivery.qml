import QtQuick
import QtQuick.Controls

Item {
    id: deliveryView
    property string cabinet_size:'0'
    Image{
        id:delivery_image
        width:parent.width
        fillMode:Image.PreserveAspectFit
        Component.onCompleted: {
            delivery_image.source="qrc:/new/prefix1/delivery.png"
        }
    }
    Column {
        spacing: 10
        width: parent.width*0.8
        anchors.centerIn: parent
        TextField{
            id:parcelField
            placeholderText: "输入包裹号" //框内提示
            width:parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            inputMethodHints: Qt.ImhUppercaseOnly
            validator: RegularExpressionValidator{regularExpression: /^[0-9]{12}$/} //0-9的输入,最多12位
            //inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        TextField{
            id:phoneNumberField
            placeholderText: "输入手机号码" //框内提示
            width:parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            validator: RegularExpressionValidator{regularExpression: /^[0-9]{11}$/} //0-9的输入,最多11位
            inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        TextField{
            id:phoneNumberField2
            placeholderText: "确认手机号码" //框内提示
            width:parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            validator: RegularExpressionValidator{regularExpression: /^[0-9]{11}$/} //0-9的输入,最多11位
            inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        Row{
            RadioButton{
                id:cabinet_small
                font.pixelSize: text_size
                text:"小柜"
                checked:true
                onClicked:cabinet_size = '0'
            }
            RadioButton{
                id:cabinet_medium
                font.pixelSize: text_size
                text:"中柜"
                onClicked:cabinet_size = '1'
            }
            RadioButton{
                id:cabinet_large
                font.pixelSize: text_size
                text:"大柜"
                onClicked:cabinet_size = '2'
            }
        }
        Row {
            spacing: 10
            Button {
                font.pixelSize: text_size
                text: "投 递"
                onClicked: {
                    //手机号或包裹号不能为空
                    if(phoneNumberField.text === "" || parcelField.text === ""){
                        receivedMessage.text = "手机号或包裹号不能为空"
                    }else if(phoneNumberField.text.length !== 11){ //手机号格式不对
                        receivedMessage.text = "手机号格式不对"
                    }
                    else if(phoneNumberField.text !== phoneNumberField2.text){ //两次输入的手机号不一致
                                            receivedMessage.text = "两次输入的手机号不一致"
                    }else{
                        receivedMessage.text = "发送消息"
                        udpClient.sendMessage('d'+cabinet_size+parcelField.text+'\0'+phoneNumberField.text+'\0', host, port)
                        //stack.push("qrc:/delivery.qml")
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
            text: "deliveryView: "+stack.depth
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
            function onMsgDelivery(message) {
                receivedMessage.text = "Received message: " + message
            }
        }
    }
}
