import ConfigParser

class Configuration(object):

  def __init__(self, configFile='config.cfg'):
    self.__config = ConfigParser.SafeConfigParser()
    self.__configFilename = configFile
    self.__config.read(self.__configFilename)

  ######################################

  def _parseConfigURL(self, section):
    transport = self.__config.get(section, 'transport')
    host = self.__config.get(section, 'host')
    port = self.__config.get(section, 'port')
    path = self.__config.get(section, 'path')

    return transport + "://" + host + ":" + port + path


  ######################################

  def _getRPCServerURL(self):
    return self._parseConfigURL('SERVER')

  # url property
  RPCServerURL = property( fget = _getRPCServerURL )

  ######################################

  def _isCheckForUpdates(self):
    return self.__config.get('CLIENT', 'checkForUpdates')

  # checkForUpdates boolean property
  checkForUpdates = property( fget = _isCheckForUpdates )

  ######################################

  def _getUpdatesURL(self):
    return self._parseConfigURL('CLIENT')

  updatesURL = property( fget = _getUpdatesURL )

  ######################################

  def _getRemoteClientSum(self):
    import urllib2,md5
    updateURL = urllib2.urlopen(self.updatesURL)
    self.remoteFileContents = updateURL.read()
    updateURL.close()
    sumStr = md5.new( self.remoteFileContents).hexdigest()


    return sumStr 


  ######################################

  def _getClientLatestUpdateSum(self):
    try:
      lastUpdtSumStr = self.__config.get('CLIENT', 'latestUpdateSum')
    except ConfigParser.NoOptionError:
      # there wasn't any date for the latest update. 
      # This is therefore the initial fetch
      newSum = self._getRemoteClientSum()
 
      lastUpdtSumStr = newSum
  
    return lastUpdtSumStr


  # clientLatestUpdate property
  clientLatestUpdate = property( fget = _getClientLatestUpdateSum )
      

  def _getClientFilename(self):
    return self.__config.get('CLIENT', 'path')[1:]


  clientFilename = property( fget = _getClientFilename )


