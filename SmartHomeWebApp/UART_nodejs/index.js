const express = require('express');
const superagent = require('superagent');
const app = express();
const cors = require('cors');
const serialController = require('./controllers/serialController');
const fs = require('fs/promises');
let localBuffer = 'Empty';
let dataType = '0';
let portObjTemp;
const statusObj = {
  outdoorTemp: '16°',
  outdoorHum: '67%',
  indoorTemp: '18°',
  homeStatus: true,
  doorStatus: 'Closed',
  fanStatus: false,
  autoFanStatus: false,
  lightStatus: false,
  autoLightStatus: false,
  deviceStatus: false,
  lightIIntensityStatus: '50%',
};
const hexToDecimal = (hex) => {
  return parseInt(hex, 16);
};
// Weather
const getWeather = async () => {
  try
  {
      const response = await superagent.get(
      'http://api.weatherapi.com/v1/current.json?key=1e2e153b52cc4f3ca55212643222812&q=Cairo&aqi=no'
    );
    // console.log(response.body.current);
    let temp = response.body.current.temp_c;
    let hum = response.body.current.humidity;
    statusObj.outdoorTemp = temp + '°';
    statusObj.outdoorHum = hum + '%';
  }
  catch(error){/* Do Nothing */ console.log("No Internet");}
};
getWeather();
setInterval(() => {
  getWeather();
}, 10000);
// status handler
const statusHandler = (data) => {
  let dataArray = data.split(',');
  // dataArray = ['00', '0f', '00', '00', 'F1F0', '01', '01', '01', '01'];
  // homeStatus , temp , fanStatus ,  autoFanStatus , light intensity , light status, autoLightMode , doorStatus , deviceStatus
  statusObj.homeStatus = hexToDecimal(dataArray[0]);
  statusObj.indoorTemp = hexToDecimal(dataArray[1]) + '°';
  console.log(dataArray);
  if (dataArray[2] !== '72') {
    statusObj.fanStatus = false;
  } else {
    statusObj.fanStatus = true;
  }
  if ((dataArray[3]) !== '72') {
    statusObj.autoFanStatus = false;
  } else {
    statusObj.autoFanStatus = true;
  }
  statusObj.lightIIntensityStatus =
    Math.abs((hexToDecimal(dataArray[4]) / 255) * 100 - 100).toFixed(2) + '%';
  console.log(statusObj.lightIIntensityStatus);
  if ((dataArray[5]) !== '72') {
    statusObj.lightStatus = false;
  } else {
    statusObj.lightStatus = true;
  }
  if ((dataArray[6]) !== '72') {
    statusObj.autoLightStatus = false;
  } else {
    statusObj.autoLightStatus = true;
  }
  if ((dataArray[7]) !== '72') {
    statusObj.doorStatus = 'Closed';
  } else {
    statusObj.doorStatus = 'Opened';
  }
  if ((dataArray[8]) !== '72') {
    statusObj.deviceStatus = false;
  } else {
    statusObj.deviceStatus = true;
  }
};
// save data
const saveData = async (data) => {
  console.log(data);
  if (data === 'S') {
    dataType = 'S';
  } else {
    switch (dataType) {
      case 'S':
        statusHandler(data);
        break;

      default:
        localBuffer = data;
        break;
    }
  }
};
const readingPort = () => {
  if (portObjTemp) {
  }
};
/* Turn on reading */
readingPort();
//////////////////////////////////
// Server
app.use(cors());
app.use(express.json({ limit: '50kb' }));
/////////////////////////
// init
app.post('/connect', async (req, res) => {
  /* Writing For Now */
  const port = req.body.port;
  console.log(port);
  const { status, message, PortObj: portObj } = serialController.Open(port);
  /* save object to global variable */
  portObjTemp = portObj;
  /* Turn on reading */
  serialController.readData(portObjTemp, saveData);
  if (status === 'Success') {
    res.status(200).json({
      status,
      message,
    });
  } else {
    res.status(400).json({
      status,
      message,
    });
  }
});
/////////////////////////
// POST Data
app.post('/sendData', async (req, res) => {
  const data = req.body.data;
  const { status, message } = serialController.sendData(data, portObjTemp);

  if (status === 'Success') {
    res.status(200).json({
      status,
      message,
    });
  } else {
    res.status(400).json({
      status,
      message,
    });
  }
});
/////////////////////////
// GET Reading
app.get('/ReadData', async (req, res) => {
  console.log(localBuffer);
  res.status(200).json({
    data: localBuffer,
  });
});

app.get('/statusData', (req, res) => {
  res.status(200).json({
    data: statusObj,
  });
});

const port = 8000;
const server = app.listen(port, () => {
  console.log(`works on ${port} ...`);
});

app.get('/disconnect', (req, res) => {
  const { status, message } = serialController.Close(portObjTemp);
  if (status === 'Success') {
    res.status(200).json({
      status,
      message,
    });
  } else {
    res.status(400).json({
      status,
      message,
    });
  }
});
