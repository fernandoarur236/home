const outdoorTempElem = document.querySelector('#status-outdoor-temp');
const outdoorHumElem = document.querySelector('#status-outdoor-hum');
const indoorTempElem = document.querySelector('#status-intdoor-temp');
const doorStatusElem = document.querySelector('#status-door');
const doorIconStatusElem = document.querySelector('#door-icon-status');
const lightIIntensityStatusElem = document.querySelector(
  '.progress-light-status'
);

let outdoorTemp = '16°';
let outdoorHum = '20%';
let indoorTemp = '21°';
let doorStatus = 'Closed';

let homeStatus = true;
const getStatusDataAPi = (data) => {
  outdoorTemp = data.outdoorTemp;
  outdoorHum = data.outdoorHum;
  indoorTemp = data.indoorTemp;
  homeStatus = data.homeStatus;
  doorStatus = data.doorStatus;
  if (doorStatus === 'Closed') {
    currentDoorStatus = false;
  } else {
    currentDoorStatus = true;
  }
  fanStatus = data.fanStatus;
  autoFanStatus = data.autoFanStatus;
  lightStatus = data.lightStatus;
  autoLightStatus = data.autoLightStatus;
  currentDeviceStatus = data.deviceStatus;
  //lightIIntensityStatus = data.lightIIntensityStatus;
  //currentLightIntensity = data.lightIIntensityStatus;
  toggleSideBtn('door');
  toggleSideBtn('device');
  toggleBtn('fan');
  toggleBtn('auto-fan');
  toggleBtnLight('light');
  toggleBtnLight('auto-light');
  updateLigthControl();
};
const updateStatusSection = () => {
  // get the data
  readStatusData(getStatusDataAPi);
  // Display the status data on web page
  outdoorTempElem.innerHTML = outdoorTemp;
  outdoorHumElem.innerHTML = outdoorHum;
  indoorTempElem.innerHTML = indoorTemp;
  doorStatusElem.innerHTML = doorStatus;
  if (doorStatus === 'Closed') {
    doorIconStatusElem.setAttribute('src', './img/door.svg');
  } else {
    doorIconStatusElem.setAttribute('src', './img/door-open.svg');
  }
  lightIIntensityStatusElem.style.width = lightIIntensityStatus;
};

setInterval(() => {
  updateStatusSection();
}, 2000);
// updateStatusSection();
