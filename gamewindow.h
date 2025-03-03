#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "VulkanWindow.h"
#include "GameScene.h"

class GameWindow : public VulkanWindow {
    Q_OBJECT
public:
    GameWindow();
    void keyPressEvent(QKeyEvent *event) override;

private:
    Renderer *mRenderer;
    GameScene *mScene;
};

#endif // GAMEWINDOW_H
