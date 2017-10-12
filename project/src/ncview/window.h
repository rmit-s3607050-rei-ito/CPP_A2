/* COSC1254 - Programming using C++ - Assignment 2
 * Assignment done as a pair
 * -----------------------------------------------------------------------------
 * Name             : Rei Ito
 * Student Number   : s3607050
 * -----------------------------------------------------------------------------
 * Name             : Pacific Thai
 * Student Number   : s3429648
 * -----------------------------------------------------------------------------
 * Using skeleton code provided by Paul Miller
 */

#include <vector>
#include <memory>
#include <exception>

#pragma once

namespace draughts
{
  namespace nc_controller
  {
    class command;
    class controller;
  }
  namespace model
  {
    class model;
  }
  namespace ncview
  {
    class ui;
    class input_cancelled : public std::exception
    {
      public:
        virtual const char * what(void) const noexcept override
        {
          return "input was cancelled";
        }

        virtual ~input_cancelled(void){}
    };
    using command_vector = std::vector<std::unique_ptr<nc_controller::command>>;
    class window
    {
      protected:
        ncview::ui * view;
        model::model * the_model;
        nc_controller::controller * the_controller;
      public:
        window(void);
        virtual void activate(void) = 0;
        static std::string get_input(const std::string&);
        virtual ~window(void){}
    };
  }
}
