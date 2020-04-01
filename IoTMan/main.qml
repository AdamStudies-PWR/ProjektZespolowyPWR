import QtQuick 2.10
import QtQuick.Controls 2.3


ApplicationWindow
{
	id: applicationWindow
	visible: true
	width: 640
	height: 480
	title: qsTr("Tabs")



	SwipeView
	{
		id: swipeView
		anchors.fill: parent
		currentIndex: tabBar.currentIndex

		Page1Form {}

		Page2Form {}

		Page3Form {}
	}

	footer: TabBar
	{
		id: tabBar
		currentIndex: swipeView.currentIndex

		TabButton
		{
			text: qsTr("Urządzenia")
			checked: true
			checkable: true
		}
		TabButton
		{
			text: qsTr("Czujniki")
			checked: false
		}
		TabButton
		{
			text: qsTr("Ustawienia")
		}
	}
}


