import QtQuick 2.15
import QtQuick.Window 2.15

import QtQuick3D 1.15

import com.dln.streaming 1.0

Window {
    id: rootWindow

    width: 800
    height: 400
    visible: true
    title: qsTr("Texture Streaming: Source Window")
    color: "black"

    property int rotation: 0

    PropertyAnimation on rotation {
        from: 0
        to: 360
        duration: 2000
        loops: Animation.Infinite
        running: true
    }

    QmlFpsCounter {}

    // We want to stream this object.
    // It's necessary:
    // 1. Use QmlStreamSource as a base element for streamed content
    // 2. Set streamId property
    QmlStreamSource {
        width: 400
        height: 400
        streamId: "someSourceObjectForStreaming"
        clip: true

        Repeater {
            model: 200

            Rectangle {
                x: 400 * Math.random()
                y: 400 * Math.random()
                width: 100 * Math.random() + 10
                height: width
                rotation: rootWindow.rotation
                color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
            }
        }
    }

    // This is an example of 3D scene that we want to stream
    QmlStreamSource {
        x: 400
        width: 400
        height: 400
        streamId: "some3dObject"

        View3D {
            id: view3D

            anchors.fill: parent
            environment: sceneEnvironment

            SceneEnvironment {
                id: sceneEnvironment
                antialiasingMode: SceneEnvironment.MSAA
                antialiasingQuality: SceneEnvironment.High
            }

            Node {
                id: scene

                DirectionalLight {
                    id: directionalLight
                }

                PerspectiveCamera {
                    id: camera

                    z: 350
                }

                Model {
                    id: cubeModel

                    source: "#Cube"
                    eulerRotation.x: rootWindow.rotation
                    materials: cubeMaterial
                    eulerRotation.y: rootWindow.rotation

                    DefaultMaterial {
                        id: cubeMaterial

                        diffuseColor: "red"
                    }
                }
            }
        }
    }
}
