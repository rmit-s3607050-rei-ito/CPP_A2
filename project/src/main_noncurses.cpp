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

#include "ncview/ui.h"
#include "nc_controller/controller.h"
#include "model/model.h"

int main(void)
{
  draughts::ncview::ui *view = draughts::ncview::ui::get_instance();
  atexit(draughts::ncview::ui::delete_instance);
  atexit(draughts::nc_controller::controller::delete_instance);
  atexit(draughts::model::model::delete_instance);
  view->main_menu();
}
