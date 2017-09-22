#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

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
      // Inner class - player
      class player {
        std::string name;
        int id;
        int score;

        bool inGame;
        bool currentPlayer;
      };

      // Game parameters
      private:
        int width;
        int height;

      static std::unique_ptr<model> instance;
      model(void);
      bool player_exists(const std::string&);

      public:
        // Game related functions
        void start_game(int, int);
        char get_token(int,int);
        void make_move(int, int, int, int, int);

        // Player related functions
        void add_player(const std::string& );
        int get_player_score(int);
        int get_current_player(void);
        std::string get_player_name(int);
        std::map<int, std::string> get_player_list(void) const;
        int get_winner();

        // Game related related functions
        int get_width();
        int get_height();
        static model * get_instance(void);
        static void delete_instance(void);
        virtual ~model(void);
    };
  }
}
