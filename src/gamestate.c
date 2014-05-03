#include "gamestate.h" 

static gamestate_t *_current_state = NULL;

void gamestate_switch(gamestate_t *new_state)
{
  if(_current_state)
    _current_state->leave(_current_state, new_state);

  if(new_state)
    new_state->enter(new_state, _current_state);

  _current_state = new_state;
}

void gamestate_update(double dt)
{
  if(_current_state)
    _current_state->update(_current_state, dt);
}

void gamestate_draw(caca_canvas_t *c)
{
  if(_current_state)
    _current_state->draw(_current_state, c);
}
