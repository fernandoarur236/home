const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

/* ******************************************** */
/* configs */
/* ******************************************** */
const config = {
  path: 'COM2',
  baudRate: 9600,
  dataBits: 8,
  parity: 'none',
  stopBits: 1,
  autoOpen: false,
  flowControl: false,
};

/* ******************************************** */
/* Close Port */
/* ******************************************** */
const closePort = (PortObj) => {
  PortObj.close((err) => {
    if (err) {
      return {
        status: 'Failed',
        message: `Disconnect Port Failed ${err.message}`,
      };
    }
  });
  return { status: 'Success', message: `Port Disconnected Successfully..` };
};
/* ******************************************** */
/* Open Port */
/* ******************************************** */
const openPort = (PortObj) => {
  PortObj.open((err) => {
    if (err) {
      return { status: 'Failed', message: `Error on Open : ${err.message}` };
    }
  });
  return { status: 'Success', message: `Port Opened Successfully..`, PortObj };
};
/* ******************************************** */
/* External Open */
/* ******************************************** */
exports.Open = (port) => {
  config.path = port;
  port = new SerialPort(config);
  const status = openPort(port);
  return status;
};
/* ******************************************** */
/* Send Data */
/* ******************************************** */
exports.sendData = (data, portObj) => {
  portObj.write(data, (err) => {
    if (err) {
      return console.log(`Error on Write: `, err.message);
    }
  });
  return { status: 'Success', message: `Message Written Successfully..` };
};

/* ******************************************** */
/* Read Data */
/* ******************************************** */

exports.readData = (portObj, callBack) => {
  let charArray = [];
  let wordArray = [];
  portObj.on('data', (data) => {
    if (data) {
      const buffArray = data.values();
      for (char of buffArray) {
        if (
          String.fromCharCode(char) !== '+' &&
          String.fromCharCode(char) !== '-'
        ) {
          charArray.push(String.fromCharCode(char));
        } else if (String.fromCharCode(char) === '-') {
          wordArray = [];
          charArray = [];
        } else {
          let receivedWord = charArray.join('');
          charArray = [];
          wordArray.push(receivedWord);
          let receivedSentence = wordArray.join(' ');
          //console.log(receivedSentence.trim());
          callBack(receivedSentence.trim());
        }
      }
      // console.log(data);
    }
  });
};

exports.Close = (PortObj) => {
  const status = closePort(PortObj);
  return status;
};
