#
# Copyright 2010-2014 Fabric Software Inc. All rights reserved.
#

Import('parentEnv')

SConscript(
  dirs = ['Commands', 'ASTWrapper', 'CodeCompletion'],
  exports = {'parentEnv': parentEnv.CloneSubStage('Services')}
  )
