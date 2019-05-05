//
// Created by Кежик Кызыл-оол on 2019-03-19.
//

#ifndef TANCHIKI_GAMESTATES_HPP
#define TANCHIKI_GAMESTATES_HPP

typedef enum gameState {
    GAME_STATE_ENTER_NAME = 0,
    GAME_STATE_MAIN_MENU,
    GAME_STATE_CHOOSE_MAP,
    GAME_STATE_CREATE_MATCH,
    GAME_STATE_MATCH,
    GAME_STATE_MATCH_PAUSE,
    GAME_STATE_ERROR,
    GAME_STATE_ENTER_LOGIN_PASSWORD,
    GAME_STATE_ENTER_NICKNAME,
    GAME_STATE_MATCH_CHOOSE,
    GAME_STATE_WAIT_FOR_OTHER_PLAYERS
}gameState_t;

#endif //TANCHIKI_GAMESTATES_HPP
