//
// MagicCubeSolver.cpp for CUBE in /home/wilmot_p/PROG/C++/MagicCubeSolver
// 
// Made by WILMOT Pierre
// Login   <pierre.wilmot@gmail.com>
// 
// Started on  Mon Oct 14 19:16:28 2013 WILMOT Pierre
// Last update Sun Oct 20 17:01:02 2013 WILMOT Pierre
//

#include	<cstdio>
#include	<iostream>
#include	<algorithm>

#include        <boost/iterator/indirect_iterator.hpp>

#include	"MagicCubeSolver.hpp"

MagicCubeSolver::MagicCubeSolver()
{
  _actions[0] = &MagicCubeSolver::R;
  _actions[1] = &MagicCubeSolver::B;
  _actions[2] = &MagicCubeSolver::G;
  _actions[3] = &MagicCubeSolver::Y;
  _actions[4] = &MagicCubeSolver::W;
  _actions[5] = &MagicCubeSolver::O;
  _end = false;
}

MagicCubeSolver::~MagicCubeSolver()
{
}

void					MagicCubeSolver::solve()
{
  MagicCubeState	*start = new MagicCubeState();
  start->init(*this);

  _fringe.push_back(start);
  expandNode(_fringe.front());

  while (!_fringe.empty() && !_end)
    {
      if (_fringe.front()->isFinalState())
	_end = true;
      expandNode(_fringe.front());
      _alreadyExploredStates.push_back(_fringe.front());
      _fringe.pop_front();

      std::cout << "Size : " << _fringe.size() << " / " << _alreadyExploredStates.size() << " [Depth : " << _depth << "]" << std::endl;
    }

  std::cout << "Computation Over" << std::endl;
  _fringe.front()->printHistory();
}

void					MagicCubeSolver::expandNode(MagicCubeState *s)
{
  MagicCubeState	*possiblesState;


  for (int i(0) ; i < 12 ; ++i)
    {
      this->init(*s);
      (this->*_actions[i/2]) (((i % 2) ? CW : CCW), true);

      possiblesState = new MagicCubeState(*this);
      possiblesState->setParent(s);

      if (std::find(
		     boost::make_indirect_iterator(_alreadyExploredStates.begin()),
		     boost::make_indirect_iterator(_alreadyExploredStates.end()),
		     *possiblesState) == boost::make_indirect_iterator(_alreadyExploredStates.end()))
	{
	  if (possiblesState->isFinalState())
	    _fringe.push_front(possiblesState);
	  else
	    _fringe.push_back(possiblesState);
	}
      else
	{
	    delete (possiblesState);
	}
    }
}

void					MagicCubeSolver::R(e_way w, bool f)
{
  e_colors	bak[3][3];

  _faceMoved = Red;
  if (f)
    _wayMoved = w;
  if (w == CW)
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  bak[i][j] = _faces[MagicCubeState::Red][i][j];

      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  _faces[MagicCubeState::Red][i][j] = bak[j][2-i];

      for (int i(0) ; i < 3 ; ++i)
	{
	  bak[0][0] = _faces[MagicCubeState::Yellow][0][i];
	  _faces[MagicCubeState::Yellow][0][i] = _faces[MagicCubeState::Blue][i][2];
	  _faces[MagicCubeState::Blue][i][2] = _faces[MagicCubeState::White][2][i];
	  _faces[MagicCubeState::White][2][i] = _faces[MagicCubeState::Green][i][0];
	  _faces[MagicCubeState::Green][i][0] = bak[0][0];
	}
    }
  else if (w == CCW) // TEMP
    {
      for (int i(0) ; i < 3 ; ++i)
	R(CW, false);
    }
}

void					MagicCubeSolver::O(e_way w, bool f)
{
  e_colors	bak[3][3];

  _faceMoved = Orange;
  if (f)
    _wayMoved = w;
  if (w == CCW)
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  bak[i][j] = _faces[MagicCubeState::Orange][i][j];

      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  _faces[MagicCubeState::Orange][i][j] = bak[2-j][i];

      for (int i(0) ; i < 3 ; ++i)
	{
	  bak[0][0] = _faces[MagicCubeState::Blue][i][0];
	  _faces[MagicCubeState::Blue][i][0] = _faces[MagicCubeState::White][0][2-i];
	  _faces[MagicCubeState::White][0][2-i] = _faces[MagicCubeState::Green][2-i][2];
	  _faces[MagicCubeState::Green][2-i][2] = _faces[MagicCubeState::Yellow][2][i];
	  _faces[MagicCubeState::Yellow][2][i] = bak[0][0];
	}
    }
  else if (w == CW) // TEMP
    {
      for (int i(0) ; i < 3 ; ++i)
	O(CCW, false);
    }
}

void					MagicCubeSolver::B(e_way w, bool f)
{
  e_colors	bak[3][3];

  _faceMoved = Blue;
  if (f)
    _wayMoved = w;
  if (w == CW)
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  bak[i][j] = _faces[MagicCubeState::Blue][i][j];

      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  _faces[MagicCubeState::Blue][i][j] = bak[j][2-i];

      for (int i(0) ; i < 3 ; ++i)
      	{
      	  bak[0][0] = _faces[MagicCubeState::Red][2-i][0];
      	  _faces[MagicCubeState::Red][2-i][0] = _faces[MagicCubeState::Yellow][2-i][0];
      	  _faces[MagicCubeState::Yellow][2-i][0] = _faces[MagicCubeState::Orange][i][2];
      	  _faces[MagicCubeState::Orange][i][2] = _faces[MagicCubeState::White][2-i][0];
      	  _faces[MagicCubeState::White][2-i][0] = bak[0][0];
      	}
    }
  else if (w == CCW) // TEMP
    {
      for (int i(0) ; i < 3 ; ++i)
	B(CW, false);
    }
}


void					MagicCubeSolver::G(e_way w, bool f)
{
  e_colors	bak[3][3];

  _faceMoved = Green;
  if (f)
    _wayMoved = w;
  if (w == CW)
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  bak[i][j] = _faces[MagicCubeState::Green][i][j];

      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  _faces[MagicCubeState::Green][i][j] = bak[j][2-i];

      for (int i(0) ; i < 3 ; ++i)
      	{
      	  bak[0][0] = _faces[MagicCubeState::Red][i][2];
      	  _faces[MagicCubeState::Red][i][2] = _faces[MagicCubeState::White][i][2];
      	  _faces[MagicCubeState::White][i][2] = _faces[MagicCubeState::Orange][2-i][0];
      	  _faces[MagicCubeState::Orange][2-i][0] = _faces[MagicCubeState::Yellow][i][2];
      	  _faces[MagicCubeState::Yellow][i][2] = bak[0][0];
      	}
    }
  else if (w == CCW) // TEMP
    {
      for (int i(0) ; i < 3 ; ++i)
	G(CW, false);
    }
}

void					MagicCubeSolver::Y(e_way w, bool f)
{
  e_colors	bak[3][3];

  _faceMoved = Yellow;
  if (f)
    _wayMoved = w;
  if (w == CW)
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  bak[i][j] = _faces[MagicCubeState::Yellow][i][j];

      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  _faces[MagicCubeState::Yellow][i][j] = bak[j][2-i];

      for (int i(0) ; i < 3 ; ++i)
      	{
      	  bak[0][0] = _faces[MagicCubeState::Red][2][2-i];
      	  _faces[MagicCubeState::Red][2][2-i] = _faces[MagicCubeState::Green][2][2-i];
      	  _faces[MagicCubeState::Green][2][2-i] = _faces[MagicCubeState::Orange][2][2-i];
      	  _faces[MagicCubeState::Orange][2][2-i] = _faces[MagicCubeState::Blue][2][2-i];
      	  _faces[MagicCubeState::Blue][2][2-i] = bak[0][0];
      	}
    }
  else if (w == CCW) // TEMP
    {
      for (int i(0) ; i < 3 ; ++i)
	Y(CW, false);
    }
}

void					MagicCubeSolver::W(e_way w, bool f)
{
  e_colors	bak[3][3];

  _faceMoved = White;
  if (f)
    _wayMoved = w;
  if (w == CW)
    {
      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  bak[i][j] = _faces[MagicCubeState::White][i][j];

      for (int i(0) ; i < 3 ; ++i)
	for (int j(0) ; j < 3 ; ++j)
	  _faces[MagicCubeState::White][i][j] = bak[j][2-i];

      for (int i(0) ; i < 3 ; ++i)
      	{
      	  bak[0][0] = _faces[MagicCubeState::Red][0][i];
      	  _faces[MagicCubeState::Red][0][i] = _faces[MagicCubeState::Blue][0][i];
      	  _faces[MagicCubeState::Blue][0][i] = _faces[MagicCubeState::Orange][0][i];
      	  _faces[MagicCubeState::Orange][0][i] = _faces[MagicCubeState::Green][0][i];
      	  _faces[MagicCubeState::Green][0][i] = bak[0][0];
      	}
    }
  else if (w == CCW) // TEMP
    {
      for (int i(0) ; i < 3 ; ++i)
	W(CW, false);
    }
}
