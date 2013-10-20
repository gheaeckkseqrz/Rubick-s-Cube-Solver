//
// MagicCubeState.hpp for MagicCubeSolver in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Sat Oct 19 20:29:30 2013 WILMOT Pierre
// Last update Sun Oct 20 16:37:33 2013 WILMOT Pierre
//

#ifndef __MAGICCUBESTATE_HPP__
#define __MAGICCUBESTATE_HPP__

#include	<iostream>
#include	<vector>

class MagicCubeState
{
public:
  enum	e_colors
    {
      Red,
      Blue,
      Green,
      Yellow,
      White,
      Orange
    };

  enum	e_way
    {
      CW,
      CCW
    };

 public:
  MagicCubeState();
  MagicCubeState(MagicCubeState const &o);
  ~MagicCubeState();

  void				init(const char *av = NULL);
  void				init(MagicCubeState const &o);

  void				setParent(MagicCubeState *parent);

  bool				isEqualTo(MagicCubeState const &o) const;
  bool				isFinalState() const;

  e_colors			getColor(e_colors f, int x, int y) const;

  void				printState() const;
  void				printHistory() const;

  bool				operator==(MagicCubeState &o);

protected:
  e_colors			_faces[6][3][3];
  const char			*_colorsName[6];

  MagicCubeState		*_parent;
  int				_depth;
  e_colors			_faceMoved;
  e_way				_wayMoved;
};


bool				operator==(MagicCubeState a, MagicCubeState b);

#endif
