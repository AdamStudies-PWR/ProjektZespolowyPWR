import QtQuick 2.10
import QtQuick.Controls 2.3

Page {
	width: 600
	height: 400
	title: "settings"

	header: Label {
		color: "#85ba3c"
		text: "Ustawienia"
		font.pixelSize: Qt.application.font.pixelSize * 2
		padding: 10
	}

	Label {
		text: qsTr("Jesteś na stronie ustawień.")
		anchors.centerIn: parent
	}
}




/*##^## Designer {
	D{i:0;height:640;width:400}
}
 ##^##*/
