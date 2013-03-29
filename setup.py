#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


example_module = Extension('_ladspamm0',
                           sources=['ladspamm_wrap.cc'],
                           )

setup (name = 'ladspamm0',
       version = '0.0.1',
       author      = "Florian Paul Schmidt",
       description = """Simple swig example from docs""",
       ext_modules = [example_module],
       py_modules = ["ladspamm0"],
       )