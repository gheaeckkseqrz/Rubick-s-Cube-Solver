//
// MagicCubeSolver.hpp for CUBE in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Mon Oct 14 19:16:34 2013 WILMOT Pierre
// Last update Sun Oct 20 16:57:49 2013 WILMOT Pierre
//

#ifndef __MAGICCUBESOLVER_HPP__
#define __MAGICCUBESOLVER_HPP__

#include		<iostream>
#include		<list>

#include		"MagicCubeState.hpp"

class MagicCubeSolver : public MagicCubeState
{
public:
  MagicCubeSolver();
  ~MagicCubeSolver();

  void				solve();

  //private:
  void				expandNode(MagicCubeState *s);

  void				R(e_way w, bool f = true);
  void				O(e_way w, bool f = true);
  void				Y(e_way w, bool f = true);
  void				W(e_way w, bool f = true);
  void				B(e_way w, bool f = true);
  void				G(e_way w, bool f = true);

private:
  void				(MagicCubeSolver::*_actions[6])(e_way, bool);

  std::list<MagicCubeState*>	_fringe;
  std::list<MagicCubeState*>	_alreadyExploredStates;

  bool				_end;
};

#endif
