// fan control
const fanOnBtn = document.querySelector('#fan-on-btn');
const fanOnBtnText = document.querySelector('#fan-on-text-btn');
const fanOnBtnBack = document.querySelector('#fan-on-btn-back');
const fanControlOption = document.querySelectorAll('.fan-control-option');
const autoFanBtn = document.querySelector('#auto-fan-btn');
const autoFanBtnText = document.querySelector('#auto-fan-text-btn');
const autoFanBtnBack = document.querySelector('#auto-fan-btn-back');
const autofanControlOption = document.querySelector('.temp-control-option');
const fanSpeedBar = document.querySelector('#fan-speed-bar-progress');
const incSpeedBtn = document.querySelector('#plus-fan-speed');
const decSpeedBtn = document.querySelector('#minus-fan-speed');
const minTempBar = document.querySelector('#temp-bar-progress');
const incTempBtn = document.querySelector('#plus-temp');
const decTempBtn = document.querySelector('#minus-temp');

const fanSpeedValueElem = document.querySelector('#control-fan-speed-value');
const minTempValueElem = document.querySelector('#control-temp-value');
let fanStatus = false;
let autoFanStatus = false;
let fanSpeed = '80%';
let minTempDeg = '60%';
let minTempC = '30°';
const updateControl = () => {
  // fan
  fanSpeedBar.style.width = fanSpeed;
  fanSpeedValueElem.innerHTML = fanSpeed;
  minTempBar.style.width = minTempDeg;
  minTempValueElem.innerHTML = minTempC;
};
const toggleBtn = (btn) => {
  switch (btn) {
    case 'fan':
      if (fanStatus !== true) {
        fanOnBtn.style.order = 1;
        fanOnBtnText.innerHTML = 'OFF';
        fanOnBtnText.style.color = '#212c34';
        fanOnBtnBack.style.background = '#faf4f4a2';
        fanControlOption.forEach((el, index) => {
          el.style.opacity = '50%';
        });
      } else {
        fanOnBtn.style.order = 3;
        fanOnBtnText.innerHTML = 'ON';
        fanOnBtnText.style.color = '#faf4f4';
        fanOnBtnBack.style.background =
          'linear-gradient(to left, #da4453, #89216b)';
        fanControlOption.forEach((el, index) => {
          if (index !== 2) {
            el.style.opacity = '100%';
          }
        });
      }
      break;
    case 'auto-fan':
      if (autoFanStatus !== true) {
        autoFanBtn.style.order = 1;
        autoFanBtnText.innerHTML = 'OFF';
        autoFanBtnText.style.color = '#212c34';
        autoFanBtnBack.style.background = '#faf4f4a2';
        autofanControlOption.style.opacity = '50%';
      } else {
        autoFanBtn.style.order = 3;
        autoFanBtnText.innerHTML = 'ON';
        autoFanBtnText.style.color = '#faf4f4';
        autoFanBtnBack.style.background =
          'linear-gradient(to left, #da4453, #89216b)';
        autofanControlOption.style.opacity = '100%';
      }
      break;
    default:
      break;
  }
};
// init
toggleBtn('fan');
toggleBtn('auto-fan');
updateControl();

const updateFanStatus = () => {
  // console.log('frame..');
  let frame;
  if (fanStatus) {
    //frame on
    frame = '#rfd;';
  } else {
    // frame off
    frame = '#sfd;';
  }
  sendDataToPort(frame);
  toggleBtn('fan');
};
fanOnBtn.addEventListener('click', () => {
  fanStatus = !fanStatus;
  updateFanStatus();
});

autoFanBtn.addEventListener('click', () => {
  autoFanStatus = !autoFanStatus;
  toggleBtn('auto-fan');
  let frame;
  if (autoFanStatus) {
    frame = '#rfe;';
  } else {
    frame = '#rfd;';
  }
  sendDataToPort(frame);
});
incSpeedBtn.addEventListener('click', () => {
  let speed = 0;
  speed = +fanSpeed.replace('%', '');
  if (speed < 100) {
    speed++;
  } else {
    speed = 100;
  }
  fanSpeed = speed + '%';
  //   send frame
  updateControl();
});
decSpeedBtn.addEventListener('click', () => {
  let speed = 0;
  speed = +fanSpeed.replace('%', '');
  if (speed > 0) {
    speed--;
  } else {
    speed = 0;
  }
  fanSpeed = speed + '%';
  //   send frame
  updateControl();
});

incTempBtn.addEventListener('click', () => {
  let tempBar = 0;
  let tempValue = 0;
  tempBar = +minTempDeg.replace('%', '');
  tempValue = +minTempC.replace('°', '');
  if (tempBar < 100) {
    tempBar++;
    tempValue += 0.5;
  } else {
    tempBar = 100;
    tempValue = 50;
  }

  minTempDeg = tempBar + '%';
  minTempC = tempValue + '°';
  //   send frame
  updateControl();
});

decTempBtn.addEventListener('click', () => {
  let tempBar = 0;
  let tempValue = 0;
  tempBar = +minTempDeg.replace('%', '');
  tempValue = +minTempC.replace('°', '');
  if (tempBar > 0) {
    tempBar--;
    tempValue -= 0.5;
  } else {
    tempBar = 0;
    tempValue = 0;
  }

  minTempDeg = tempBar + '%';
  minTempC = tempValue + '°';
  //   send frame
  updateControl();
});
