#ifndef CONSOLEGAME_H
#define CONSOLEGAME_H

//---------------------------------------
#include <vector>
#include <utility>

#include "player.h"
#include "board.h"
#include "game.h"

//=======================================
class ClassicConsoleGame : public IGame
{
public:
    ClassicConsoleGame() = default;
    ClassicConsoleGame(const std::string& name, IBoard* board /*other parameters*/);
    ~ClassicConsoleGame() = default;

    virtual std::string name() const override {return m_name;}
    virtual bool setup(IBoard* board) override;
    virtual bool waitForPlayers(uint64_t timeout) override;
    virtual int  exec(/*add parameters*/) override;

protected:
    void renderBoard() const;
    int  calculateVictory();

private:
    std::string m_name;
    std::unique_ptr<IBoard> m_board;
    std::vector< std::unique_ptr<IPlayer> > m_players;
    int calculateHorVictory();
    int calculateVertVictory();
    int calculateDiagVictory();
    int calculateNoWin();
};

#endif // CONSOLEGAME_H
