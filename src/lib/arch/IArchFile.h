/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2012 - 2016 Symless Ltd.
 * SPDX-FileCopyrightText: (C) 2002 Chris Schoeneman
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include "common/IInterface.h"
#include <string>

//! Interface for architecture dependent file system operations
/*!
This interface defines the file system operations required by
deskflow.  Each architecture must implement this interface.
*/
class IArchFile : public IInterface
{
public:
  //! @name manipulators
  //@{

  //! Extract base name
  /*!
  Find the base name in the given \c pathname.
  */
  virtual const char *getBasename(const char *pathname) = 0;

  //! Get installed directory
  /*!
  Returns the directory in which Deskflow is installed.
  */
  virtual std::string getInstalledDirectory() = 0;

  //! Concatenate path components
  /*!
  Concatenate pathname components with a directory separator
  between them.  This should not check if the resulting path
  is longer than allowed by the system;  we'll rely on the
  system calls to tell us that.
  */
  virtual std::string concatPath(const std::string &prefix, const std::string &suffix) = 0;
};
