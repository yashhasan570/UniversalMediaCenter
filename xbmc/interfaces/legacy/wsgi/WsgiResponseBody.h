/*
 *  Copyright (C) 2015-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "interfaces/legacy/AddonClass.h"

namespace Addon
{
  namespace wsgi
  {
    /// \defgroup python_wsgi_WsgiResponseBody WsgiResponseBody
    /// \ingroup python_wsgi
    /// @{
    /// @brief **Represents the write callable returned by the start_response callable passed to a WSGI handler.**
    ///
    /// \python_class{ WsgiResponseBody() }
    ///
    ///-------------------------------------------------------------------------
    ///
    class WsgiResponseBody : public AddonClass
    {
    public:
      WsgiResponseBody();
      ~WsgiResponseBody() override;

#ifdef DOXYGEN_SHOULD_USE_THIS
      /// \ingroup python_wsgi_WsgiInputStreamIterator
      /// \python_func{ operator(status, response_headers[, exc_info]) }
      ///
      /// Callable implementation to write data to the response.
      ///
      /// @param data            string data to write
      ///
      operator()(...);
#else
      void operator()(const String& data);
#endif

#if !defined SWIG && !defined DOXYGEN_SHOULD_SKIP_THIS
      String m_data;
#endif
    };
  }
}
