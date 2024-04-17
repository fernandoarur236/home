const DoorOnBtn = document.querySelector('#door-control-btn');
const DoorOnBtnText = document.querySelector('#door-control-text-btn');
const DoorOnBtnBack = document.querySelector('#door-control-back');

const DeviceOnBtn = document.querySelector('#device-control-btn');
const DeviceOnBtnText = document.querySelector('#device-control-text-btn');
const DeviceOnBtnBack = document.querySelector('#device-control-back');

const MicOnBtn = document.querySelector('#mic-btn-id');
const VoiceValueElem = document.querySelector('.voice-output');

let currentDoorStatus = false;
let currentDeviceStatus = false;

const toggleSideBtn = (btn) => {
  switch (btn) {
    case 'door':
      if (currentDoorStatus !== true) {
        DoorOnBtn.style.order = 1;
        DoorOnBtnText.innerHTML = 'OFF';
        DoorOnBtnText.style.color = '#212c34';
        DoorOnBtnBack.style.background = '#faf4f4a2';
      } else {
        DoorOnBtn.style.order = 3;
        DoorOnBtnText.innerHTML = 'ON';
        DoorOnBtnText.style.color = '#faf4f4';
        DoorOnBtnBack.style.background =
          'linear-gradient(to left, #da4453, #89216b)';
      }
      break;
    case 'device':
      if (currentDeviceStatus !== true) {
        DeviceOnBtn.style.order = 1;
        DeviceOnBtnText.innerHTML = 'OFF';
        DeviceOnBtnText.style.color = '#212c34';
        DeviceOnBtnBack.style.background = '#faf4f4a2';
      } else {
        DeviceOnBtn.style.order = 3;
        DeviceOnBtnText.innerHTML = 'ON';
        DeviceOnBtnText.style.color = '#faf4f4';
        DeviceOnBtnBack.style.background =
          'linear-gradient(to left, #da4453, #89216b)';
      }
      break;
    default:
      break;
  }
};
toggleSideBtn('door');
toggleSideBtn('device');

const updateDoorStatus = (doorStatus) => {
  let frame;
  if (doorStatus) {
    frame = '#rgd;';
  } else {
    frame = '#sgd;';
  }
  sendDataToPort(frame);
  toggleSideBtn('door');
};
const updateDeviceStatus = (deviceStatus) => {
  let frame;
  if (deviceStatus) {
    frame = '#rcd;';
  } else {
    frame = '#scd;';
  }
  sendDataToPort(frame);
  toggleSideBtn('device');
};
DoorOnBtn.addEventListener('click', () => {
  currentDoorStatus = !currentDoorStatus;
  updateDoorStatus(currentDoorStatus);
});
DeviceOnBtn.addEventListener('click', () => {
  currentDeviceStatus = !currentDeviceStatus;
  updateDeviceStatus(currentDeviceStatus);
});
MicOnBtn.addEventListener('click', () => {
  MicOnBtn.classList.remove('mic-btn');
  MicOnBtn.classList.add('mic-btn-active');
  const SpeechRecognition =
    window.SpeechRecognition || window.webkitSpeechRecognition;

  let recognition = new SpeechRecognition();

  recognition.onstart = () => {
    console.log('starting listening, speak in microphone');
  };
  recognition.onspeechend = () => {
    console.log('stopped listening');
    recognition.stop();
    MicOnBtn.classList.remove('mic-btn-active');
    MicOnBtn.classList.add('mic-btn');
  };
  recognition.onresult = (result) => {
    let value = result.results[0][0].transcript;
    VoiceValueElem.innerHTML = value + '..';
    MicOnBtn.classList.remove('mic-btn-active');
    MicOnBtn.classList.add('mic-btn');
    let done = true;
    if (value === 'turn on device') {
      currentDeviceStatus = true;
      updateDeviceStatus(currentDeviceStatus);
      speak('Device is on');
    } else if (value === 'turn off device') {
      currentDeviceStatus = false;
      updateDeviceStatus(currentDeviceStatus);
      speak('Device is off');
    } else if (value === 'open door') {
      currentDoorStatus = true;
      updateDoorStatus(currentDoorStatus);
      speak('door is opened');
    } else if (value === 'close door') {
      currentDoorStatus = false;
      updateDoorStatus(currentDoorStatus);
      speak('door is closed');
    } else if (value === 'turn on lights') {
      lightStatus = true;
      updateLightStatus();
      speak('lights are on');
    } else if (value === 'turn off lights') {
      lightStatus = false;
      updateLightStatus();
      speak('lights are off');
    } else if (value === 'turn on fan') {
      fanStatus = true;
      updateFanStatus();
      speak('fan is on');
    } else if (value === 'turn off fan') {
      fanStatus = false;
      updateFanStatus();
      speak('fan is off');
    } else if (value.includes('hi') || value.includes('hello')) {
      speak(`hello sir`);
    } else if (value.includes('bye')) {
      speak(`bye bye sir have a nice day`);
    } else if (value.includes('night')) {
      speak(`good night sir`);
    } else {
      speak(`i don't understand`);
      done = false;
    }
    // sende frame
    if (done) {
      // speak('Okay');
    }
    setTimeout(() => {
      VoiceValueElem.innerHTML = 'Say Something..';
    }, 1000);
  };
  recognition.start();
});

function setSpeech() {
  return new Promise(function (resolve, reject) {
    let synth = window.speechSynthesis;
    let id;

    id = setInterval(() => {
      if (synth.getVoices().length !== 0) {
        resolve(synth.getVoices());
        clearInterval(id);
      }
    }, 10);
  });
}

function speak(text) {
  var utterance = new SpeechSynthesisUtterance(text);
  let s = setSpeech();
  s.then((voices) => {
    utterance.voice = voices[3];
    speechSynthesis.speak(utterance);
  });
}
