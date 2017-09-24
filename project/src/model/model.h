#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

// Random for selecting which player will go first
#include <random>

#pragma once

// height/width default to 8 (64 cells)
const int WIDTH = 8;
const int HEIGHT = 8;

namespace draughts
{
  namespace model
  {
    class model
    {
      // Game parameters
      private:
        // Game board dimensions
        int width;
        int height;
        // Player stats:
        /* NOTE: since there are only two players, we have just decided to go
         * with pairs of variables for each, in games that have more params/players,
         * it would be better to use another completely separate class for it */
        int player1, player2;
        int p1Score, p2Score;
        int currentPlayer;

      // map of players, datastructure map is used due to get_player_list() type
      std::map<int, std::string> playerList;
      // Number of players registered to the system. Allocates ID based on count
      int playerCount;

      static std::unique_ptr<model> instance;
      model(void);
      bool player_exists(const std::string&);

      public:
        // Game related functions
        void start_game(int, int);
        char get_token(int,int);
        void make_move(int, int, int, int, int);

        // Player related functions
        bool add_player(const std::string &);
        int get_player_score(int);
        int get_current_player(void);
        std::string get_player_name(int);
        std::map<int, std::string> get_player_list(void) const;
        int get_winner();

        // Game related related functions
        int get_player_count();
        int get_width();
        int get_height();
        static model * get_instance(void);
        static void delete_instance(void);
        virtual ~model(void);
    };
  }
}
