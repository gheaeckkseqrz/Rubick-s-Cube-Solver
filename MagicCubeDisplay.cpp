//
// MagicCubeDisplay.cpp for CUBE in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Mon Oct 14 20:17:50 2013 WILMOT Pierre
// Last update Sat Oct 19 22:06:46 2013 WILMOT Pierre
//

#include	<iostream>
#include	<unistd.h>

#include	"MagicCubeDisplay.hpp"

MagicCubeDisplay::MagicCubeDisplay()
{
  SDL_Init(SDL_INIT_VIDEO);
  _win = SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

  _xRot = 0;
  _yRot = 0;

  _colors[MagicCubeState::Red].r = 255;
  _colors[MagicCubeState::Red].g = 0;
  _colors[MagicCubeState::Red].b = 0;
  _colors[MagicCubeState::Green].r = 20;
  _colors[MagicCubeState::Green].g = 98;
  _colors[MagicCubeState::Green].b = 11;
  _colors[MagicCubeState::Blue].r = 0;
  _colors[MagicCubeState::Blue].g = 0;
  _colors[MagicCubeState::Blue].b = 255;
  _colors[MagicCubeState::Orange].r = 255;
  _colors[MagicCubeState::Orange].g = 165;
  _colors[MagicCubeState::Orange].b = 0;
  _colors[MagicCubeState::White].r = 255;
  _colors[MagicCubeState::White].g = 255;
  _colors[MagicCubeState::White].b = 255;
  _colors[MagicCubeState::Yellow].r = 255;
  _colors[MagicCubeState::Yellow].g = 255;
  _colors[MagicCubeState::Yellow].b = 0;

}

MagicCubeDisplay::~MagicCubeDisplay()
{
}

void			MagicCubeDisplay::render(MagicCubeState &cube)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
  glPushMatrix();

  glRotated(_yRot, 0, 1, 0);
  glRotated(_xRot, 1, 0, 0);

  for (MagicCubeState::e_colors c(MagicCubeState::Red) ; c <= MagicCubeState::Orange ; c = MagicCubeState::e_colors(c + 1))
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  drawFace(c, i, j, _colors[cube.getColor(c, i, j)]);
    }

  SDL_GL_SwapBuffers();
  glPopMatrix();
}

void			MagicCubeDisplay::drawFace(MagicCubeState::e_colors f, int x, int y, SDL_Color &c)
{
  pushMatrix(f);

  glBegin(GL_QUADS);
  glColor3ub(c.r, c.g, c.b); //face rouge
  glVertex3d(-1.5 + x, 1.5 - y, 1.5);
  glVertex3d(-1.5 + x, 0.5 - y, 1.5);
  glVertex3d(-0.5 + x, 0.5 - y, 1.5);
  glVertex3d(-0.5 + x, 1.5 - y, 1.5);

  if (!x && !y)
    {
      glColor3ub(0, 0, 0); //face rouge
      glVertex3d(-1.3 + x, 1.3 - y, 1.51);
      glVertex3d(-1.3 + x, 0.7 - y, 1.51);
      glVertex3d(-0.7 + x, 0.7 - y, 1.51);
      glVertex3d(-0.7 + x, 1.3 - y, 1.51);
    }

  if (x == 2 && y == 0)
    {
      glColor3ub(127, 127, 127); //face rouge
      glVertex3d(-1.3 + x, 1.3 - y, 1.51);
      glVertex3d(-1.3 + x, 0.7 - y, 1.51);
      glVertex3d(-0.7 + x, 0.7 - y, 1.51);
      glVertex3d(-0.7 + x, 1.3 - y, 1.51);
    }

  glEnd();
  glFlush();

  glPopMatrix();
}

void			MagicCubeDisplay::pushMatrix(MagicCubeState::e_colors f)
{
  glPushMatrix();
  switch (f)
    {
    case MagicCubeState::Red:
      break;
    case MagicCubeState::Orange:
      glRotated(180, 1, 0, 0);
      break;

    case MagicCubeState::White:
      glRotated(-90, 0, 1, 0);
      break;

    case MagicCubeState::Yellow:
      glRotated(90, 0, 1, 0);
      break;

    case MagicCubeState::Green:
      glRotated(90, 1, 0, 0);
      break;

    case MagicCubeState::Blue:
      glRotated(-90, 1, 0, 0);
      break;

    default:
      break;
    }
}

void			MagicCubeDisplay::displayResult(MagicCubeSolver &cube)
{
  while (handleEvent())
    render(cube);
}

bool			MagicCubeDisplay::handleEvent()
{
  SDL_Event	event;

  SDL_EnableKeyRepeat(10,10);
  SDL_WaitEvent(&event);
    switch(event.type)
      {
      case SDL_QUIT:
	return false;
	break;
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym)
	  {
	  case SDLK_UP:
	    _xRot += 10;
	    break;
	  case SDLK_DOWN:
	    _xRot -= 10;
	    break;
	  case SDLK_LEFT:
	    _yRot -= 10;
	    break;
	  case SDLK_RIGHT:
	    _yRot += 10;
	    break;
	  default:
	    break;
	  }
	break;
      default:
	break;
      }
  return true;
}

