#include "GameScene.h"
#include "Renderer.h"
#include <QDebug>
#include <random>

GameScene::GameScene(Renderer *renderer) : mRenderer(renderer), mDoorPosition(2.0, 0, 2.0), mDoorOpen(false), mInsideHouse(false) {
    setupScene();
}

void GameScene::setupScene() {
    mPlayerPosition = QVector3D(0, 0, 0);

    // Create ground plane
    mGround = new TriangleSurface();
    mRenderer->addObject(mGround);

    // Randomly place pickups
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-5.0, 5.0);
    for (int i = 0; i < 6; ++i) {
        QVector3D pickupPos(dist(gen), 0, dist(gen));
        mPickups.append(pickupPos);
        VisualObject *pickup = new Triangle(); // Example visual object
        pickup->setPosition(pickupPos);
        mRenderer->addObject(pickup);
    }

    // Setup NPCs
    for (int i = 0; i < 2; ++i) {
        QVector3D p1(dist(gen), 0, dist(gen));
        QVector3D p2(dist(gen), 0, dist(gen));
        mNPCs.append(qMakePair(p1, p2));
        VisualObject *npc = new Triangle();
        npc->setPosition(p1);
        mRenderer->addObject(npc);
    }

    // Setup house and door
    mHouse = new TriangleSurface();
    mHouse->setPosition(QVector3D(2.0, 0, 2.0));
    mRenderer->addObject(mHouse);

    mDoor = new Triangle();
    mDoor->setPosition(mDoorPosition);
    mRenderer->addObject(mDoor);
}

void GameScene::updateScene() {
    // Check for collision with pickups
    for (int i = 0; i < mPickups.size(); ++i) {
        if ((mPlayerPosition - mPickups[i]).length() < 0.5f) {
            qDebug() << "Pickup collected!";
            mPickups.remove(i);
            mRenderer->removeObjectAt(i); // Remove from renderer
        }
    }

    // Check for NPC collision
    for (const auto &npc : mNPCs) {
        if ((mPlayerPosition - npc.first).length() < 0.5f) {
            qDebug() << "You lost!";
            return;
        }
    }

    // Check if player is near the door
    if (!mDoorOpen && (mPlayerPosition - mDoorPosition).length() < 1.0f) {
        mDoorOpen = true;
        qDebug() << "Door opened!";
        mRenderer->removeObject(mDoor); // Hide door
    }

    // Transition to Scene 2
    if (mDoorOpen && (mPlayerPosition - mDoorPosition).length() < 0.2f) {
        mInsideHouse = true;
        qDebug() << "Inside the house! Scene 2 activated.";
        mPickups.clear();

        // Add pickup inside house
        QVector3D insidePickupPos(0, 0, 0);
        mPickups.append(insidePickupPos);
        VisualObject *insidePickup = new Triangle();
        insidePickup->setPosition(insidePickupPos);
        mRenderer->addObject(insidePickup);
    }
}

void GameScene::handlePlayerMovement(int key) {
    switch (key) {
    case Qt::Key_W: mPlayerPosition.setZ(mPlayerPosition.z() - 0.1f); break;
    case Qt::Key_A: mPlayerPosition.setX(mPlayerPosition.x() - 0.1f); break;
    case Qt::Key_S: mPlayerPosition.setZ(mPlayerPosition.z() + 0.1f); break;
    case Qt::Key_D: mPlayerPosition.setX(mPlayerPosition.x() + 0.1f); break;
    }
    updateScene();
}
