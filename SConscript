#
# Copyright 2010-2015 Fabric Software Inc. All rights reserved.
#

Import('parentEnv')

env = parentEnv.CloneSubStage('Services')

if env['FABRIC_BUILD_OS'] == 'Darwin':
  env.Append(CXXFLAGS = ['-std=c++03'])
  env.Append(CXXFLAGS = ['-stdlib=libstdc++'])
  env.Append(LINKFLAGS = ['-stdlib=libstdc++'])

SConscript(
  dirs = [
    'Commands',
    'ASTWrapper',
    'DFGWrapper',
    'CodeCompletion',
    'SplitSearch',
    ],
  exports = {'parentEnv': env}
  )

allServicesLibFiles = []
msvc_versions = ['12.0']
if 'servicesLib' in COMMAND_LINE_TARGETS and env['FABRIC_BUILD_OS'] == 'Windows':
  msvc_versions = ['10.0', '12.0']

for msvc_version in msvc_versions:

  print msvc_version
  allServicesLibFiles += SConscript(
    'SConscript.ServicesLib',
    exports = {
      'parentEnv': env, 
      'dirs': [
        'Commands',
        'ASTWrapper',
        'DFGWrapper',
        'CodeCompletion',
        # 'SplitSearch',
      ],
      'msvc_version': msvc_version
    },
    variant_dir = 'FabricServices-'+msvc_version
    )

Export('allServicesLibFiles')

env.Alias('servicesLib', allServicesLibFiles)
