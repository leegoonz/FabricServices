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

servicesLibFiles = SConscript(
  'SConscript.ServicesLib',
  exports = {'parentEnv': env, 'dirs': [
    'Commands',
    'ASTWrapper',
    'DFGWrapper',
    'CodeCompletion',
    # 'SplitSearch',
    ]},
  variant_dir = 'FabricServices'
  )
