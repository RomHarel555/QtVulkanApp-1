#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Renderer.h"
#include <QVector3D>
#include <QKeyEvent>

class GameScene {
public:
    GameScene(Renderer *renderer);
    void setupScene();
    void updateScene();
    void handlePlayerMovement(int key);

private:
    Renderer *mRenderer;
    QVector3D mPlayerPosition;
    QVector<QVector3D> mPickups;
    QVector<QPair<QVector3D, QVector3D>> mNPCs;
    QVector3D mDoorPosition;
    bool mDoorOpen;
    bool mInsideHouse;

    VisualObject *mGround;
    VisualObject *mHouse;
    VisualObject *mDoor;
};

#endif // GAMESCENE_H
