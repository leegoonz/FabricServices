#
# Copyright 2010-2015 Fabric Software Inc. All rights reserved.
#

Import('parentEnv')

SConscript(
  dirs = [
    'Commands',
    'ASTWrapper',
    'DFGWrapper',
    'CodeCompletion',
    'SplitSearch',
    ],
  exports = {'parentEnv': parentEnv.CloneSubStage('Services')}
  )
