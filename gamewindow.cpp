#include "GameWindow.h"

GameWindow::GameWindow() {
    mRenderer = new Renderer(this, false);
    mScene = new GameScene(mRenderer);
    mScene->setupScene();
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    mScene->handlePlayerMovement(event->key());
}
