cmake_minimum_required(VERSION 3.11)

project(PyFinder)

find_package(PythonInterp)
message(STATUS "${PYTHONINTERP_FOUND}: ${PYTHON_VERSION_STRING} ${PYTHON_EXECUTABLE}")
find_package(PythonLibs)
message(STATUS "${PYTHONLIBS_FOUND}: ${PYTHONLIBS_VERSION_STRING} ${PYTHON_LIBRARIES}")

find_package(Python)
message(STATUS "site-packages: ${Python_SITELIB}")
