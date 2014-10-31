import glob
import CppHeaderParser

headerPaths = glob.glob('*.h')

headers = []
for headerPath in headerPaths:
  try:
      header = CppHeaderParser.CppHeader(headerPath)
  except CppHeaderParser.CppParseError as e:
      print(e)
      sys.exit(1)

  headers += [header]

  print header.classes.keys()





