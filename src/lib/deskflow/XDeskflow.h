/*
 * Deskflow -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2002 Chris Schoeneman
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "base/XBase.h"

//! Generic deskflow exception
XBASE_SUBCLASS(XDeskflow, XBase);

//! Subscription error
/*!
Thrown when there is a problem with the subscription.
*/
XBASE_SUBCLASS(XSubscription, XDeskflow);

//! Client error exception
/*!
Thrown when the client fails to follow the protocol.
*/
XBASE_SUBCLASS_WHAT(XBadClient, XDeskflow);

//! Server protocol error
/*!
Thrown when the server protocol is unrecognized.
*/
XBASE_SUBCLASS_WHAT(XInvalidProtocol, XDeskflow);

//! Incompatible client exception
/*!
Thrown when a client attempting to connect has an incompatible version.
*/
class XIncompatibleClient : public XDeskflow
{
public:
  XIncompatibleClient(int major, int minor);

  //! @name accessors
  //@{

  //! Get client's major version number
  int getMajor() const throw();
  //! Get client's minor version number
  int getMinor() const throw();

  //@}

protected:
  virtual std::string getWhat() const throw();

private:
  int m_major;
  int m_minor;
};

//! Client already connected exception
/*!
Thrown when a client attempting to connect is using the same name as
a client that is already connected.
*/
class XDuplicateClient : public XDeskflow
{
public:
  XDuplicateClient(const std::string &name);
  virtual ~XDuplicateClient() _NOEXCEPT
  {
  }

  //! @name accessors
  //@{

  //! Get client's name
  virtual const std::string &getName() const throw();

  //@}

protected:
  virtual std::string getWhat() const throw();

private:
  std::string m_name;
};

//! Client not in map exception
/*!
Thrown when a client attempting to connect is using a name that is
unknown to the server.
*/
class XUnknownClient : public XDeskflow
{
public:
  XUnknownClient(const std::string &name);
  virtual ~XUnknownClient() _NOEXCEPT
  {
  }

  //! @name accessors
  //@{

  //! Get the client's name
  virtual const std::string &getName() const throw();

  //@}

protected:
  virtual std::string getWhat() const throw();

private:
  std::string m_name;
};

//! Generic exit eception
/*!
Thrown when we want to abort, with the opportunity to clean up. This is a
little bit of a hack, but it's a better way of exiting, than just calling
exit(int).
*/
class XExitApp : public XDeskflow
{
public:
  XExitApp(int code);
  virtual ~XExitApp() _NOEXCEPT
  {
  }

  //! Get the exit code
  int getCode() const throw();

protected:
  virtual std::string getWhat() const throw();

private:
  int m_code;
};
