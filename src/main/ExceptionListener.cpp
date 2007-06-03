/*
  Copyright 2007 Albert Strasheim <fullung@gmail.com>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <boost/python/class.hpp>
#include <boost/python/pure_virtual.hpp>

#include <cms/ExceptionListener.h>

namespace py = boost::python;

using cms::ExceptionListener;
using cms::CMSException;

struct ExceptionListenerWrap : ExceptionListener, py::wrapper<ExceptionListener>
{
    virtual void onException(const CMSException& ex)
    {
        PyGILState_STATE gstate = PyGILState_Ensure();
        // TODO clone exception so that exception listener can keep a
        // reference to it
        py::call<void>(this->get_override("onException").ptr(), boost::ref(ex));
        PyGILState_Release(gstate);
    }
};

void export_ExceptionListener()
{
    py::class_<ExceptionListenerWrap, boost::noncopyable>("ExceptionListener")
        .def("onException", py::pure_virtual(&ExceptionListener::onException))
        ;
}