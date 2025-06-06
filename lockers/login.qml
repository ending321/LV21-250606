import QtQuick
import QtQuick.Controls

Item {
    id: loginView
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
            id:phoneNumberField
            placeholderText: "输入手机号码" //框内提示
            validator: RegularExpressionValidator{regularExpression: /^[0-9]{11}$/} //0-9的输入,最多11位
            width:parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        TextField{
            id:passwordField
            width:parent.width
            placeholderText: "输入密码" //框内提示
            echoMode:TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
            //inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        Row {
            spacing: spacing_size
            //width:parent.width*0.8
            //anchors.horizontalCenter: parent.horizontalCenter
            Button {
                text: "登 录"
                font.pixelSize: text_size
                onClicked: {
                    //手机号或密码不能为空
                    if(phoneNumberField.text === "" || passwordField.text === ""){
                        receivedMessage.text = "手机号或密码不能为空"
                    }else if(phoneNumberField.text.length !== 11){ //手机号格式不对
                        receivedMessage.text = "手机号格式不对"
                    }else{
                        receivedMessage.text = "发送消息"
                        udpClient.sendMessage('l'+phoneNumberField.text+'\0'+passwordField.text+'\0', host, port)
                        receivedMessage.text = "登录请求已发送，请等待响应..."
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
            Button {
                text: "注 册"
                font.pixelSize: text_size
                onClicked: stack.push("qrc:/register.qml")
            }
            /*
            Text {
                text: "loginView: "+stack.depth
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
            function onMsgLogin(message) {
                receivedMessage.text = "Received message: " + message
                if(message === "ok")
                    stack.push("qrc:/delivery.qml")
            }
        }
    }

}
