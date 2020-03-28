import QtQuick 2.9
import QtQuick.Window 2.2

Window {
	id: window
	visible: true
	title: qsTr("Hello World")

	Text {
		id: element
		x: 0
		y: 0
		width: 108
		height: 54
		text: qsTr("Hello World form Qt!")
		font.pixelSize: 18
	}

 TextInput {
	 id: textInput
	 x: 93
	 y: 219
	 width: 80
	 height: 20
	 text: qsTr("Text Input")
	 font.pixelSize: 12
 }

 Flow {
	 id: element1
	 anchors.fill: parent
 }
}









/*##^## Designer {
	D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_height:480;anchors_width:640;anchors_x:0;anchors_y:0}
}
 ##^##*/
