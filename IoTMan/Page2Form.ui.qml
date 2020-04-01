import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
	width: 600
	height: 400
	property alias button: button
	antialiasing: true
	title: "sensors"

	header: Label {
		color: "#85ba3c"
		text: qsTr("Czujniki")
		font.pixelSize: Qt.application.font.pixelSize * 2
		padding: 10
	}

	Text {
		id: element1
		color: "#ffffff"
		text: qsTr("Text")
		anchors.rightMargin: 0
		anchors.leftMargin: 0
		anchors.topMargin: 7
		anchors.bottomMargin: 60
		anchors.fill: parent
		font.pixelSize: 12
	}

	Button {
		id: button
		x: 165
		y: 531
		text: qsTr("Test")
	}
}




/*##^## Designer {
	D{i:0;height:640;width:400}
}
 ##^##*/
