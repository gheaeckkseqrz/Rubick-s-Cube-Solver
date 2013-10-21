//
// Threadable.hpp for plazza in /home/jowett_j//pj/plazza/svn
// 
// Made by james jowett
// Login   <jowett_j@epitech.net>
// 
// Started on  Tue Apr 10 05:27:59 2012 james jowett
// Last update Sun Oct 20 18:54:36 2013 WILMOT Pierre
//

#ifndef __THREADABLE_HPP_
#define __THREADABLE_HPP_

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <pthread.h>
#include "Mutex.hpp"

class Threadable
{
public:
  Threadable();
  ~Threadable();

  void			setMustQuit(bool v);
  bool			mustQuit();

protected:
  void			threadIt();
  virtual int		threadEntryPoint() = 0;

private:
  static void		*entryPoint(void *);

private:
  Mutex			m_mustQuitMutex;
  volatile bool		m_mustQuit;
  bool			m_launched;
  pthread_t		m_thread;

private:
  Threadable(Threadable const&);
  Threadable	&operator=(Threadable const&);
};

#endif
