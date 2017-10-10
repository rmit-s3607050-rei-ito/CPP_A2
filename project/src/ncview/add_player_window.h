/* COSC1254 - Programming using C++ - Assignment 2
 * Assignment done as a pair
 * -----------------------------------------------------------------------------
 * Name             : Rei Ito
 * Student Number   : s3607050
 * -----------------------------------------------------------------------------
 * Name             : Pacific Thai
 * Student Number   : s3429648
 * -----------------------------------------------------------------------------
 */

#include "window.h"
#pragma once
namespace draughts
{
  namespace ncview
  {
    class add_player_window : public window
    {
      public:
        virtual void activate(void) override;
        virtual ~add_player_window(void){}
    };
  }
}
