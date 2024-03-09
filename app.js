const { spawn} = require('node:child_process');
const { stdout, stderr } = require('node:process');
const fs = require('node:fs/promises');

// Spawn a new process to the C application
const numberFormater = spawn('./number_formatter', ['./dest.txt', '$', ',']);

numberFormater.stdout.on('data', (data) => {
  stdout.write(data.toString());
});

numberFormater.stderr.on('data', (data) => {
  stderr.write(data.toString());
});

// when c application emits close event
numberFormater.on('close', (code) => {
  // End because of EOF signal C application exits with code 0 and we catch this signal here
  if(code === 0) {
    return stdout.write('File was read, processed and writen successfully!\n');
  }

  stdout.write('Something went wrong!\n');
});

(async () => {
  const fileHandle = await fs.open('./src.txt', 'r');
  const readStream = fileHandle.createReadStream();

  // in here we are saying C application that we are done to reading and send EOF (End of file) signal
  readStream.pipe(numberFormater.stdin);
  // we can write in C applications stdin manually
  // numberFormater.stdin.write("123 3412 2342");
  // numberFormater.stdin.write("123 3412 8898 2342");
  // numberFormater.stdin.write("123 2 2342");
  // but c application will enver exit until we do not say that we are done
 //  numberFormater.stdin.end("231") // one last write in stdin and EOF signal
 // we are sending same signal for example when we are writing in socket. res.end("")
})();