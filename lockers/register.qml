import QtQuick
import QtQuick.Controls

Item {
    id: registerView
    property string company:""
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
            width:parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            validator: RegularExpressionValidator{regularExpression: /^[0-9]{11}$/} //0-9的输入,最多11位
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
        TextField{
            id:passwordField2
            width:parent.width
            placeholderText: "确认密码" //框内提示
            echoMode:TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
            //inputMethodHints: Qt.ImhDialableCharactersOnly //数字键盘
            font.pixelSize: text_size
        }
        ComboBox{
            id:courierSelector
            width:200
            //使用列表模型相关的模型数据
            ListModel{
                id:courierList
                ListElement {code:"JD"; name:"京东快递"}
                ListElement { code: "SF"; name: "顺丰速运" }
                ListElement { code: "STO"; name: "百世汇通" }
                ListElement { code: "ST"; name: "申通快递" }
                ListElement { code: "YTO"; name: "圆通速递" }
                ListElement { code: "EMS"; name: "邮政EMS" }
                ListElement { code: "SEE"; name: "速尔快递" }
                ListElement { code: "DBL"; name: "德邦快递" }
                ListElement { code: "UC"; name: "优速快递" }
                ListElement { code: "KT"; name: "快捷快递" }
                ListElement { code: "JT"; name: "极兔快递" }
            }
            // 设置模型和文本角色
            model: courierList
            textRole: "name"
            onCurrentIndexChanged:{
                company = courierList.get(currentIndex).name
            }
        }
        Row {
            spacing: 10
            Button {
                text: "注 册"
                font.pixelSize: text_size
                enabled: stack.depth > 1
                onClicked: {
                    //注册信息不能为空
                    if(phoneNumberField.text === "" || passwordField.text === "" || passwordField2.text === ""){
                        receivedMessage.text = "注册信息不能为空"
                    }else if(phoneNumberField.text.length !== 11){ //手机号格式不对
                        receivedMessage.text = "手机号格式不对"
                    }
                    else if(passwordField.text !== passwordField2.text){ //两次输入的密码不一致
                                            receivedMessage.text = "两次输入的密码不一致"
                    }else{
                        receivedMessage.text = "发送消息"
                        udpClient.sendMessage('r'+phoneNumberField.text+'\0'+passwordField.text+'\0'+company+'\0', host, port)
                        //stack.push("qrc:/delivery.qml")
                    }
                    //stack.pop()
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
            text: "registerView: "+stack.depth
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
            function onMsgRegister(message) {
                receivedMessage.text = "Received message: " + message
                stack.push("qrc:/delivery.qml")
            }
        }
    }
}
