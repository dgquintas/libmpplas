from ConfigParser import SafeConfigParser

class Configuration(object):

  def __init__(self, configFile='config.cfg'):
    self.__config = SafeConfigParser()
    self.__config.read(configFile)


  def _getRPCServerURL(self):
    transport = self.__config.get('SERVER', 'transport')
    host = self.__config.get('SERVER', 'host')
    port = self.__config.get('SERVER', 'port')
    path = self.__config.get('SERVER', 'path')

    return transport + "://" + host + ":" + port + path


  url = property( fget = _getRPCServerURL )
      


