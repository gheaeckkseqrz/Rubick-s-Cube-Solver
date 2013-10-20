//
// MagicCubeState.cpp for MagicCubeSolver in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Sat Oct 19 20:34:46 2013 WILMOT Pierre
// Last update Sun Oct 20 16:45:07 2013 WILMOT Pierre
//

#include	<iostream>
#include	"MagicCubeState.hpp"

MagicCubeState::MagicCubeState()
{
  _colorsName[Red] = "Red";
  _colorsName[Blue] = "Blue";
  _colorsName[Green] = "Green";
  _colorsName[Yellow] = "Yellow";
  _colorsName[White] = "White";
  _colorsName[Orange] = "Orange";
  _parent = NULL;
  _depth = 0;
}

MagicCubeState::MagicCubeState(MagicCubeState const &o)
{
  _colorsName[Red] = "Red";
  _colorsName[Blue] = "Blue";
  _colorsName[Green] = "Green";
  _colorsName[Yellow] = "Yellow";
  _colorsName[White] = "White";
  _colorsName[Orange] = "Orange";
  _parent = NULL;
  _depth = 0;
  init(o);
}

MagicCubeState::~MagicCubeState()
{
}

void					MagicCubeState::init(const char *av)
{
  bool	f = false;
  int	v = 'N';
  int	p(0);

  for (int i(0) ; i < 6 ; ++i)
    {
      if (!av)
      std::cout << "Face " << _colorsName[i] << std::endl;
      for (int k(0) ; k < 3 ; k++)
      {
  	for (int j(0) ; j < 3 ; j++)
  	{
  	  f = false;
  	  while (!f)
  	    {
  	      if (v != '\n' && !av)
  		std::cout << "Square " << j << " / " << k << std::endl;
  	      if (!av)
  		v = getchar();
  	      else
  		{
  		  v = av[p];
  		  p++;
  		}
  	      switch (v)
  		{
  		case 'R':
  		  _faces[i][j][k] = Red;
  		  f = true;
  		  break;
  		case 'B':
  		  _faces[i][j][k] = Blue;
  		  f = true;
  		  break;
  		case 'G':
  		  _faces[i][j][k] = Green;
  		  f = true;
  		  break;
  		case 'Y':
  		  _faces[i][j][k] = Yellow;
  		  f = true;
  		  break;
  		case 'W':
  		  _faces[i][j][k] = White;
  		  f = true;
  		  break;
  		case 'O':
  		  _faces[i][j][k] = Orange;
  		  f = true;
  		  break;
  		case 'Q':
		  return;
  		  break;

  		default:
		  if (!av)
  		  std::cout << v << " is NOT a valid choice" << std::endl;
  		}
  	    }
  	}
      }
    }
}

void					MagicCubeState::init(MagicCubeState const &o)
{
  for (int i(0) ; i < 6 ; ++i)
    for (int j(0) ; j < 3 ; ++j)
      for (int k(0) ; k < 3 ; ++k)
	_faces[i][j][k] = o._faces[i][j][k];
  _parent = o._parent;
  _faceMoved = o._faceMoved;
  _wayMoved = o._wayMoved;
  _depth = o._depth;
}

void					MagicCubeState::setParent(MagicCubeState *parent)
{
  _parent = parent;
  _depth = parent->_depth + 1;
}

bool					MagicCubeState::isEqualTo(MagicCubeState const &o) const
{
  for (int i(0) ; i < 6 ; ++i)
    for (int j(0) ; j < 3 ; ++j)
      for (int k(0) ; k < 3 ; ++k)
	if (_faces[i][j][k] != o._faces[i][j][k])
	  return false;
  return true;
}

bool					MagicCubeState::isFinalState() const
{
  for (int i(0) ; i < 6 ; ++i)
    for (int j(0) ; j < 3 ; ++j)
      for (int k(0) ; k < 3 ; ++k)
	if (_faces[i][j][k] != _faces[i][1][1])
	  return false;
  std::cout << "Found final State" << std::endl;
  return true;
}

MagicCubeState::e_colors		MagicCubeState::getColor(e_colors f, int x, int y) const
{
  return _faces[f][x][y];
}

void					MagicCubeState::printState() const
{
  for (int f(0) ; f < 6 ; ++f)
    {
      std::cout << "Face " << _colorsName[f] << std::endl;
      for (int i(0) ; i < 3 ; ++i)
	{
	  for (int j(0) ; j < 3 ; ++j)
	    {
	      std::cout << "|" << _colorsName[_faces[f][j][i]][0];
	    }
	  std::cout << "|" << std::endl;
	}

    }
}

void					MagicCubeState::printHistory() const
{
  std::cout << _colorsName[_faceMoved] << " CW" << std::endl;
  if (_parent)
    _parent->printHistory();
}

bool					MagicCubeState::operator==(MagicCubeState &o)
{
  return isEqualTo(o);
}

bool					operator==(MagicCubeState a, MagicCubeState b)
{
  return a.isEqualTo(b);
}
