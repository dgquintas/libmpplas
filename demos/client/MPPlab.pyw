import __main__
original = __main__.__dict__.keys()

import wx
import Client

class App(wx.App):
    def OnInit(self):
        import os
        import wx
        from wx import py

        img = wx.Bitmap("splash.png", wx.BITMAP_TYPE_PNG)
        splash = wx.SplashScreen(img, wx.SPLASH_CENTRE_ON_SCREEN|wx.SPLASH_TIMEOUT, 10000, None, -1)

        self.SetAppName("MPPlab")
        confDir = wx.StandardPaths.Get().GetUserDataDir()
        if not os.path.exists(confDir):
            os.mkdir(confDir)
        fileName = os.path.join(confDir, 'config')
        self.config = wx.FileConfig(localFilename=fileName)
        self.config.SetRecordDefaults(True)
        
        self.frame = py.crust.CrustFrame(config=self.config, dataDir=confDir)
##        self.frame.startupFileName = os.path.join(confDir,'pycrust_startup')
##        self.frame.historyFileName = os.path.join(confDir,'pycrust_history')
        self.frame.Show()
        self.SetTopWindow(self.frame)
        splash.Destroy()
        if globals().get('updated'):
          dlg = wx.MessageDialog(self.frame, "An update is available. Update?", 
              "Update available", 
              wx.YES_NO | wx.NO_DEFAULT | wx.ICON_QUESTION )
          res = dlg.ShowModal()
          if res == wx.ID_YES:
            import Client 
            backupFileName = Client.performUpdate()
            if backupFileName and len(backupFileName) > 0:
              successDlg = wx.MessageDialog(self.frame, 
                  "Updating successful.\n" + 
                  ("A copy of the old version was made to %s\n" % backupFileName) +
                  "Please, restart the application to use the new version", 
                  "Success!",
                  wx.OK | wx.ICON_INFORMATION )
              successDlg.ShowModal()
              successDlg.Destroy()

          else: # res == wx.ID_NO
            pass

          dlg.Destroy()

        return True
    
    
'''
The main() function needs to handle being imported, such as with the
pycrust script that wxPython installs:

    #!/usr/bin/env python

    from wx.py.PyCrust import main
    main()
'''

def main():
    """The main function for the PyCrust program."""
    # Cleanup the main namespace, leaving the App class.
    import __main__
    md = __main__.__dict__
    keepers = original
    keepers.append('App')
    for key in md.keys():
        if key not in keepers:
            del md[key]
    # Create an application instance.
    app = App(0)
    # Mimic the contents of the standard Python shell's sys.path.
    import sys
    if sys.path[0]:
        sys.path[0] = ''
    # Add the application object to the sys module's namespace.
    # This allows a shell user to do:
    # >>> import sys
    # >>> sys.app.whatever
    sys.app = app
    del sys
    # Cleanup the main namespace some more.
    if md.has_key('App') and md['App'] is App:
        del md['App']
    if md.has_key('__main__') and md['__main__'] is __main__:
        del md['__main__']
    global clientId
    # Start the wxPython event loop.
    try:
      app.MainLoop()
    except:
      pass
    finally:
      #cleanup
      from RPCServer import RPCServer
      rpcServer = RPCServer.getInstance()
      rpcServer.getServer()._discardClientId(clientId)

if __name__ == '__main__':
    import os
    os.environ['PYTHONSTARTUP'] = 'startup.py'
    main()

