//
// MagicCubeDisplay.hpp for CUBE in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Mon Oct 14 20:17:56 2013 WILMOT Pierre
// Last update Sat Oct 19 20:46:33 2013 WILMOT Pierre
//

#ifndef __MAGICCUBEDISPLAY_HPP__
#define __MAGICCUBEDISPLAY_HPP__

#include	<iostream>

#include	<SDL/SDL.h>

#include	<GL/gl.h>
#include	<GL/glu.h>

#include	"MagicCubeSolver.hpp"

class MagicCubeDisplay
{
public:
  MagicCubeDisplay();
  ~MagicCubeDisplay();

  void			displayResult(MagicCubeSolver &cube);
  void			render(MagicCubeState &cube);
  void			drawFace(MagicCubeState::e_colors f, int x, int y, SDL_Color &c);
private:
  void			pushMatrix(MagicCubeState::e_colors f);
  bool			handleEvent();

private:
  SDL_Surface		*_win;

  float			_xRot;
  float			_yRot;

  SDL_Color		_colors[6];
};

#endif
