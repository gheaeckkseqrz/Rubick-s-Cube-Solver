//
// Threadable.cpp for plazza in /home/jowett_j//pj/plazza/svn
// 
// Made by james jowett
// Login   <jowett_j@epitech.net>
// 
// Started on  Tue Apr 10 05:28:45 2012 james jowett
// Last update Thu Jan  3 22:59:12 2013 WILMOT Pierre
//

#include "Threadable.hpp"

Threadable::Threadable()
  : m_mustQuitMutex(Mutex::Normal), m_mustQuit(false), m_launched(false)
{
}

void			Threadable::threadIt()
{
  pthread_attr_t	attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  errno = 0;
  m_launched = true;
  if (pthread_create(&m_thread, &attr, Threadable::entryPoint, this) != 0)
    {
      m_launched = false;
      throw std::runtime_error(std::string("pthread_create(3): ") + strerror(errno));
    }
  pthread_attr_destroy(&attr);
}

bool			Threadable::mustQuit()
{
  bool			ret;
  bool			gotLock;

  m_mustQuitMutex.trylock(gotLock);
  if (!gotLock)
    return false;
  ret = m_mustQuit;
  m_mustQuitMutex.unlock();
  return ret;
}

void			*Threadable::entryPoint(void *instance)
{
  Threadable		*toLaunch;

  toLaunch = reinterpret_cast<Threadable *>(instance);
  return reinterpret_cast<void *>(toLaunch->threadEntryPoint());
}

void			Threadable::setMustQuit(bool v)
{
  m_mustQuitMutex.lock();
  m_mustQuit = v;
  m_mustQuitMutex.unlock();
}

Threadable::~Threadable()
{
  if (m_launched)
    {
      m_mustQuitMutex.lock();
      m_mustQuit = true;
      m_mustQuitMutex.unlock();
      if (pthread_join(m_thread, NULL) != 0)
	std::cerr << "!! Failed to join with thread !!" << std::endl;
    }
}
