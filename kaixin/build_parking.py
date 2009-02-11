from distutils.core import setup

import py2exe

options = {"py2exe":  
             {   "compressed": 1,  
                 "optimize": 2, 
                 "includes": [],          
                 "bundle_files": 1 
             }  
           }  

setup(
     options = {},#options,  
     console=["parking.py"]
     )
#~ setup(console=["parking.py", "common.py", "curl.py", "park_algo.py"])