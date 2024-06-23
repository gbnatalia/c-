#include <string>
#include <iostream>
#include <vector>
#include "simpleboard.h"
#include "consoleplayer.h"
#include "new_consolegame.h"


ClassicConsoleGame::ClassicConsoleGame(const std::string& name, IBoard* board /*other parameters*/)
        :m_name(name)
{
    setup(board);
}

bool ClassicConsoleGame::setup(IBoard* board)
{
    if(m_players.empty())
        m_board.reset(board);
    return true;
}

bool ClassicConsoleGame::waitForPlayers(uint64_t /*timeout*/)
{
    while(m_players.size() < 2)
    {
        std::cout << "Enter name of players "<<std::to_string(m_players.size()+1)<<std::endl;

        std::string name;
        std::cin>>name;
        if(name.empty())
            continue;

        m_players.emplace_back(new ConsolePlayer(name) );
    }

    return true;
}

void ClassicConsoleGame::renderBoard() const
{
    auto dimension = m_board->dimention();
    const auto& xmin = dimension.first.x;
    const auto& ymin = dimension.first.y;
    const auto& xmax = dimension.second.x;
    const auto& ymax = dimension.second.y;

    IBoard::PositionType pos;
    for( auto y = ymin; y < ymax; y++)
    {
        pos.y = y;

        auto x = xmax;
        while (x--){
            std::cout << "--" ;
        }
        std::cout << "-" << std::endl;

        for (auto x = xmin; x < xmax; x++)
        {
            pos.x = x;
            auto mark = m_board->mark(pos);
            std::string outSymbol = " ";
            switch(mark)
            {
                case IBoard::MARK_O: outSymbol = "O"; break;
                case IBoard::MARK_X: outSymbol = "X"; break;
                default: break;
            }

            if (x == (xmax - 1))
                std::cout<<"|" << outSymbol<<"|";
            else
                std::cout<<"|" << outSymbol;

        }
        std::cout << std::endl;
    }
    auto x = xmax;
    while (x--){
        std::cout << "--" ;
    }
    std::cout << "-" << std::endl;
}

int  ClassicConsoleGame::calculateHorVictory(){
    IBoard::PositionType pos;
    std::vector< IBoard::PositionType> res;
    auto dimension = m_board->dimention();

    const auto& xmin = dimension.first.x;
    const auto& ymin = dimension.first.y;
    const auto& xmax = dimension.second.x;
    const auto& ymax = dimension.second.y;
    int x;

    for (auto y = ymin; y < ymax; y++){
        pos.x = xmin;
        pos.y = y;
        auto mark = m_board->mark(pos);
        std::string etSymbol = " ";
        switch(mark)
        {
            case IBoard::MARK_O: etSymbol = "O"; break;
            case IBoard::MARK_X: etSymbol = "X"; break;
            default: continue;
        }
        res.clear();
        for (x = xmin; x < xmax; x++){
            pos.x = x;
            pos.y = y;
            res.push_back(pos);
            auto mark = m_board->mark(pos);
            std::string outSymbol = " ";
            switch(mark)
            {
                case IBoard::MARK_O: outSymbol = "O"; break;
                case IBoard::MARK_X: outSymbol = "X"; break;
                default: break;
            }
            if (outSymbol != etSymbol){
                res.clear();
                break;
            }
        }
        if (x == xmax) {
            for (auto it = res.begin(); it != res.end(); it++){
                if (it != res.begin())
                    std::cout << ", ";
                std::cout << "(" << it->x << ", " << it->y << ")";
            }
            std::cout << std::endl;
            return 1;
        }
    }
    return 0;
}

int  ClassicConsoleGame::calculateVertVictory(){
    IBoard::PositionType pos;
    std::vector< IBoard::PositionType> res;

    auto dimension = m_board->dimention();

    const auto& xmin = dimension.first.x;
    const auto& ymin = dimension.first.y;
    const auto& xmax = dimension.second.x;
    const auto& ymax = dimension.second.y;
    int y;

    for (auto  x = xmin; x < xmax; x++){
        pos.x = x;
        pos.y = ymin;
        auto mark = m_board->mark(pos);
        std::string etSymbol = " ";
        switch(mark)
        {
            case IBoard::MARK_O: etSymbol = "O"; break;
            case IBoard::MARK_X: etSymbol = "X"; break;
            default: continue;
        }

        res.clear();
        for (y = ymin; y < ymax; y++){
            pos.x = x;
            pos.y = y;
            res.push_back(pos);
            auto mark = m_board->mark(pos);
            std::string outSymbol = " ";
            switch(mark)
            {
                case IBoard::MARK_O: outSymbol = "O"; break;
                case IBoard::MARK_X: outSymbol = "X"; break;
                default: break;
            }
            if (outSymbol != etSymbol) {
                res.clear();
                break;
            }
        }

        if (y == ymax){
            for (auto it = res.begin(); it != res.end(); it++){
                if (it != res.begin())
                    std::cout << ", ";
                std::cout << "(" << it->x << ", " << it->y << ")";
            }

            std::cout << std::endl;
            return 1;
        }
    }
    return 0;
}

int  ClassicConsoleGame::calculateDiagVictory(){
    IBoard::PositionType pos;
    auto dimension = m_board->dimention();

    const auto& xmin = dimension.first.x;
    const auto& ymin = dimension.first.y;
    const auto& xmax = dimension.second.x;
    const auto& ymax = dimension.second.y;
    int x;

    pos.x = xmin;
    pos.y = ymin;
    auto mark = m_board->mark(pos);
    std::string etSymbol = " ";
    switch(mark)
    {
        case IBoard::MARK_O: etSymbol = "O"; break;
        case IBoard::MARK_X: etSymbol = "X"; break;
        default: break;
    }
    if (etSymbol != " "){
        for (x = xmin; x < xmax; x++){
            pos.x = x;
            pos.y = x;
            auto mark = m_board->mark(pos);
            std::string outSymbol = " ";
            switch(mark)
            {
                case IBoard::MARK_O: outSymbol = "O"; break;
                case IBoard::MARK_X: outSymbol = "X"; break;
                default: break;
            }
            if (outSymbol != etSymbol)
                break;
        }
        if (x == xmax){
            for (x = xmin; x < xmax; x++){
                if (x != xmin)
                    std::cout << ", ";
                std::cout << "(" << x << ", " << x << ")";
            }
            std::cout << std::endl;
            return 1;
        }
    }

    pos.x = xmin;
    pos.y = ymax - 1;
    mark = m_board->mark(pos);
    etSymbol = " ";
    switch(mark)
    {
        case IBoard::MARK_O: etSymbol = "O"; break;
        case IBoard::MARK_X: etSymbol = "X"; break;
        default: break;
    }
    if (etSymbol != " ") {
        for (x = xmin; x < xmax; x++) {
            pos.x = x;
            pos.y = (xmax - x - 1);
            auto mark = m_board->mark(pos);
            std::string outSymbol = " ";
            switch (mark) {
                case IBoard::MARK_O:
                    outSymbol = "O";
                    break;
                case IBoard::MARK_X:
                    outSymbol = "X";
                    break;
                default:
                    break;
            }
            if (outSymbol != etSymbol)
                break;
        }
        if (x == xmax) {
            for (x = xmin; x < xmax; x++) {
                if (x != xmin)
                    std::cout << ", ";
                std::cout << "(" << x << ", " << (xmax - x - 1) << ")";
            }
            std::cout << std::endl;
            return 1;
        }
    }

    return 0;
}

int ClassicConsoleGame::calculateNoWin(){
    IBoard::PositionType pos;
    auto dimension = m_board->dimention();

    auto& xmin = dimension.first.x;
    auto& ymin = dimension.first.y;
    auto& xmax = dimension.second.x;
    auto& ymax = dimension.second.y;

    for (auto x = xmin; x < xmax; x++) {
        for (auto y = ymin; y < ymax; y++) {
            pos.x = x;
            pos.y = y;
            auto mark = m_board->mark(pos);
            switch (mark) {
                case IBoard::MARK_O: break;
                case IBoard::MARK_X: break;
                default:             return 0;
            }
        }
    }
    return 2;
}


int  ClassicConsoleGame::calculateVictory()
{

    int res = 0;
    res = calculateVertVictory();
    if (res) return res;
    res = calculateHorVictory();
    if (res) return res;
    res = calculateDiagVictory();
    if (res) return res;
    // проверка ничьи
    res = calculateNoWin();
    return res;

}

int ClassicConsoleGame::exec(/*add parameters*/)
{
    int iplayer = 0;
    while(true)
    {
        renderBoard();
        auto& player = m_players[iplayer];
        bool moveAssepted = false;
        while(!moveAssepted)
        {
            auto move = player->getMove();
            if( !move )
                return -1;

            auto currentMark = m_board->mark(move.value());
            if(currentMark == IBoard::MARK_EMPTY)
                moveAssepted = m_board->setMark(move.value(), iplayer == 0 ? IBoard::MARK_X : IBoard::MARK_O);
        }

        if( calculateVictory() == 1){
            std::cout << "player "<< m_players[iplayer]->name()<<" win! Congratulations!"<<std::endl;
            return iplayer;
        }
        else if( calculateVictory() == 2){
            std::cout << "The result is a draw. Game over!" << std::endl;
            return -1;
        }

        iplayer = (iplayer + 1) % 2;
    }
    return -1;
}


