import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
	id: page
	antialiasing: true
	title: "devices   "

	header: Label {
		color: "#85ba3c"
		text: qsTr("Urządzenia")
		font.pixelSize: Qt.application.font.pixelSize * 2
		padding: 10

		Row {
			id: row
			height: 50
			anchors.fill: parent
		}
	}

	ItemDelegate {
		id: itemDelegate
		text: qsTr("Item Delegate")
		anchors.bottomMargin: 73
		anchors.fill: parent
	}

	Button {
		id: addButton
		x: 10
		y: 529
		text: qsTr("Dodaj")
		anchors.right: parent.right
		anchors.rightMargin: 310
		anchors.left: parent.left
		anchors.leftMargin: 10
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
		autoRepeat: false
		autoExclusive: false
		checked: false
		checkable: false
	}

	Button {
		id: conButton
		x: 100
		y: 529
		text: qsTr("Połącz")
		anchors.right: parent.right
		anchors.rightMargin: 220
		anchors.left: parent.left
		anchors.leftMargin: 100
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
	}

	Button {
		id: delButton
		x: 220
		y: 529
		text: qsTr("Usuń")
		anchors.left: parent.left
		anchors.leftMargin: 220
		anchors.right: parent.right
		anchors.rightMargin: 100
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
	}

	Button {
		id: helpButton
		x: 310
		y: 529
		text: qsTr("Pomoc")
		anchors.left: parent.left
		anchors.leftMargin: 310
		anchors.right: parent.right
		anchors.rightMargin: 10
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10
		font.bold: true
	}
}




/*##^## Designer {
	D{i:0;autoSize:true;height:640;width:400}D{i:3;anchors_x:95;anchors_y:173}D{i:4;anchors_x:39;anchors_y:362}
D{i:5;anchors_x:165;anchors_y:355}D{i:6;anchors_x:310;anchors_y:355}D{i:7;anchors_x:448;anchors_y:355}
}
 ##^##*/
