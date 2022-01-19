from distutils.core import setup, Extension
 
module = Extension('ex',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['c'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['sample_extension.c'])
 
setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       author = 'Nobody',
       author_email = 'nobody@nodomain.com',
       url = 'https://docs.python.org/extending/building',
       long_description = '''
          This is really just a demo package.
       ''',
       ext_modules = [module])
