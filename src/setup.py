from distutils.core import setup, Extension
import os


setup (name = 'service',
       version = '0.1',
       description = 'Python wrapper for Password Service',
       packages=[''],
       package_dir={'':''},
       package_data={'':['service.so']}
       )
