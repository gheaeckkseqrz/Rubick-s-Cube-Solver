//
// Mutex.cpp for plazza in /home/jowett_j//pj/plazza/svn
// 
// Made by james jowett
// Login   <jowett_j@epitech.net>
// 
// Started on  Wed Apr 11 02:33:22 2012 james jowett
// Last update Wed Jan 23 23:07:59 2013 WILMOT Pierre
//

#include "Mutex.hpp"

Mutex::Mutex(Mutex::e_type t)
  : m_t(t)
{
  pthread_mutexattr_t	attr;

  if (m_t != Normal)
    {
      errno = 0;
      if (pthread_mutexattr_init(&attr) != 0)
	throw std::runtime_error(std::string("pthread_mutexattr_init(3): ") + strerror(errno));
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    }

  errno = 0;
  if (pthread_mutex_init(&m_mutex, (m_t == Normal) ? NULL : &attr) != 0)
    throw std::runtime_error(std::string("pthread_mutex_init(3): ") + strerror(errno));
}

pthread_mutex_t		*Mutex::getCMutex()
{
  return (&m_mutex);
}

bool	Mutex::lock()
{
  return (pthread_mutex_lock(&m_mutex) == 0);
}

bool	Mutex::trylock(bool& gotLock)
{
  gotLock = true;
  errno = 0;
  if (pthread_mutex_trylock(&m_mutex) == 0)
    return true;
  gotLock = false;
  return (errno == EBUSY);
}

bool	Mutex::unlock()
{
  return (pthread_mutex_unlock(&m_mutex) == 0);
}

Mutex::~Mutex()
{
  if (pthread_mutex_destroy(&m_mutex) != 0)
    std::cerr << "!! Failed to destroy mutex !!" << std::endl;
}
