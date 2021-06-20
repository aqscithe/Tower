#include <iostream>
#include <chrono>
#include <string>

#include <gp/gp.h>

#include "Screen.h"
#include "Game.h"


int main(int argc, char* argv[])
{
    GPLib* gp = gpInit(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower++", GP_VSYNC_ON);
    std::cout << std::endl; // Force flush stdout

    /**
    *   REVIEW:
    *   Pourquoi utiliser un pointeur ici? Une variable suffit.
    *   Ex: Game game{gp};
    * 
    *   La class Game pourrait directement contenir un GPLib* et
    *   g�rer le gpInit() et gpShutdown.
    *   Ex:
    *   Game game{SCREEN_WIDTH, SCREEN_HEIGHT, "Tower++", GP_VSYNC_ON}
    *   Game(...){ gpInit(...); }
    *   ~Game(){ gpShutdown(...); }
    */
    // Draw map
    Game* game = new Game(gp);

    /**
    *   REVIEW:
    *   Habituellement les resources (*.txt) sont dans un dossier "Bin" ou "Resources"
    *   et non dans le dossier "src". "src" ou "Source" ne doit contenir que les .cpp.
    */
    game->readGrid("src/Grid.txt");
    game->readWaves("src/Waves.txt");

    /**
    *   REVIEW:
    *   Devrait etre appel� automatiquement dans readGrid().
    */
    game->setPositions();

    /**
    *   REVIEW:
    *   La boucle de jeu devrait etre contenue dans Game.
    *   Game est la class qui manage le jeu.
    */
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (gpWindowShouldClose(gp) == false)
    {
        // Poll events (mouse, keyboards, etc...)
        gpEventsPoll(gp);

        // TODO: Update game

        gpDrawBegin(gp);
        gpDrawClearBackground(gp, GP_CBLACK);

        // TODO: Draw stuff

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        game->update
        (
            std::chrono::duration<float>(elapsedTime).count(), gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_1 ), 
            gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_2 ), gpMousePosition(gp), 
            gpKeyIsPressed(gp, GP_KEY_SPACE), gpMouseButtonIsReleased(gp, GP_MOUSE_BUTTON_1 )
        );

        game->draw(gp);
        game->drawStore(gp);

        gpDrawEnd(gp);
    }

    gpShutdown(gp);
    return 0;
}