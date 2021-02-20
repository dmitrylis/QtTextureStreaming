import QtQuick 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15

import QtQuick3D 1.15

import com.dln.streaming 1.0

Window {
    width: 800
    height: 800
    visible: true
    title: qsTr("Texture Streaming: Target Window")
    color: "black"

    QmlFpsCounter {}

    // This is a target object for streaming
    // It's necessary to set streamId property to bind it with the source object
    StreamTarget {
        width: 400
        height: 400
        streamId: "someSourceObjectForStreaming"
    }

    // This is an another target object for streaming with blur effect
    StreamTarget {
        x: 400
        width: 400
        height: 400
        streamId: "someSourceObjectForStreaming"
        layer {
            enabled: true
            effect: FastBlur {
                radius: 48
            }
        }
    }

    // This is an another target object for streaming with texture made from 3D scene
    StreamTarget {
        y: 400
        width: 400
        height: 400
        streamId: "some3dObject"
    }

    // 3D scene with streamed texture on a model
    View3D {
        id: view3D

        x: 400
        y: 400
        width: 400
        height: 400
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
                eulerRotation.x: 30
                materials: cubeMaterial
                eulerRotation.y: 45

                DefaultMaterial {
                    id: cubeMaterial

                    diffuseMap: Texture {
                        sourceItem: StreamTarget {
                            width: 400
                            height: 400
                            streamId: "some3dObject"
                        }
                    }
                }
            }
        }
    }
}
