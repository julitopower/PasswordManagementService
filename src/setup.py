from distutils.core import setup, Extension
import os


setup (name = 'adder',
       version = '0.1',
       description = 'Python wrapper for libmtester',
       packages=[''],
       package_dir={'':''},
       package_data={'':['adder.so']}
       )

setup (name = 'basicauthenticator',
       version = '0.1',
       description = 'Python wrapper for libmtester',
       packages=[''],
       package_dir={'':''},
       package_data={'':['basicauthenticator.so']}
       )
