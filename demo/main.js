const { app, BrowserWindow } = require('electron');

app.commandLine.appendSwitch("autoplay-policy", "no-user-gesture-required")
const createWindow = () => {
    const webPrefrences = {
        nodeIntegration: true,
        contextIsolation: false,
        webSecurity: false
    }
    const win = new BrowserWindow({
        webPreferences: webPrefrences,
        autoHideMenuBar: true,
        width: 800,
        height: 682,
    });

  win.loadFile('index.html');
};

app.whenReady().then(() => {
  createWindow();

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});