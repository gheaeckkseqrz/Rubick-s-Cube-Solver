//
// main.cpp for CUBE in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Mon Oct 14 19:12:45 2013 WILMOT Pierre
// Last update Sun Oct 20 01:29:43 2013 WILMOT Pierre
//

#include	"MagicCubeSolver.hpp"
#include	"MagicCubeDisplay.hpp"

#include	<GL/glut.h>

int		main(int ac, char **av)
{

  MagicCubeSolver	s;
  //  MagicCubeDisplay	d;
  if (ac == 2)
    s.init(av[1]);
  else
    s.init();

  // s.O(MagicCubeSolver::CW);
  // s.B(MagicCubeSolver::CW);
  // s.G(MagicCubeSolver::CW);

  s.solve();
  //  d.displayResult(s);
}
