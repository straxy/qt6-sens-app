import QtQuick
import QtQuick.Controls
import QtCharts
import QtQuick.Layouts

Item {
    width: 800
    height: 600
    visible: true
    id: item

    signal enableI2CSens(enable: bool)
    signal enableMMSens(enable: bool, speed: string)
    signal setSamplingSpeed(speed: string)

    function newMMSensValue(data: string) {
        console.log("New MM sensor value " + data)
        mmsensVal.text = data
    }

    function newI2CSensValue(val: int) {
        console.log("New I2C sensor value " + val)
        temperatureChart.append(val)
    }

    Column {
        id: column
        anchors.fill: parent

        Text {
            topPadding: 10
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Memory mapped sensor")
            font.underline: true
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Switch {
                id: mmsensEn
                text: qsTr("Enable\ncomponent")
                anchors.verticalCenter: parent.verticalCenter
                onCheckedChanged: item.enableMMSens(mmsensEn.checked, cbItems.get(sspeed.currentIndex).text)
            }

            ToolSeparator {}

            Text {
                id: samplingText
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Sampling \nspeed")
            }

            ComboBox {
                id: sspeed
                leftPadding: 10
                currentIndex: 0
                model: ListModel {
                    id: cbItems
                    ListElement { text: "normal" }
                    ListElement { text: "fast" }
                }
                width: 90
                anchors.verticalCenter: parent.verticalCenter
                onActivated: item.setSamplingSpeed(cbItems.get(currentIndex).text)
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Count value")
        }

        Text {
            id: mmsensVal
            font.pointSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            text: "0000"
        }

        ToolSeparator {
            height: 0.05*parent.height
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("I2C temperature sensor")
            font.underline: true
        }

        Switch {
            id: i2csensEn
            text: qsTr("Enable")
            anchors.horizontalCenter: parent.horizontalCenter
            onCheckedChanged: item.enableI2CSens(i2csensEn.checked)
        }

        ChartView {
            anchors.horizontalCenter: parent.horizontalCenter
            id: temperatureChart
            width: parent.width
            height: 0.6*parent.height
            property var series: null
            property int cnt: 0
            axes: [
                DateTimeAxis {
                    format: "mm:ss"
                    id: xAxis
                    tickCount: 10
                },
                ValueAxis {
                    id: yAxis
                    min: 10.0
                    max: 40.0
                }
            ]
            function init() {
                temperatureChart.removeAllSeries()
                xAxis.min = new Date(1970, 0, 1, 0, 0, 0)
                xAxis.max = new Date(1970, 0, 1, 0, 0, 10)
                temperatureChart.series = temperatureChart.createSeries(ChartView.SeriesTypeLine, "temperature", xAxis, yAxis)
            }

            function append(y: int) {
                var x = new Date(1970, 0, 1, 0, 0, temperatureChart.cnt)
                temperatureChart.cnt += 1
                series.append(x, y);
                if (temperatureChart.series.count > 10) {
                    temperatureChart.series.remove(0)
                    xAxis.min = new Date(1970, 0, 1, 0, 0, cnt - 10)
                    xAxis.max = new Date(1970, 0, 1, 0, 0, cnt - 1)
                }
            }
            Component.onCompleted: init()
        }
    }
}
